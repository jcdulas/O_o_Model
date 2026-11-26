#include "oor/results/xlsx/XlsxWriter.hpp"

#include "oor/base/Version.hpp"
#include "oor/base/errors/Errors.hpp"
#include "oor/base/text/Json.hpp"
#include "oor/base/text/TextUtilities.hpp"
#include "oor/io/zip/Zip.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <set>
#include <system_error>

// An .xlsx file is a ZIP of XML files (Office Open XML, SpreadsheetML). The parts written here, the smallest set Excel,
// LibreOffice and the common libraries open:
//
//   [Content_Types].xml          the type of every part
//   _rels/.rels                  where the workbook and the document properties are
//   docProps/core.xml, app.xml   title, author program, date
//   xl/workbook.xml              the sheets, in order, and the ranges of their filters
//   xl/_rels/workbook.xml.rels   where each sheet and the styles are
//   xl/styles.xml                four cell styles: plain, header (bold), title (bold, larger), link (blue, underlined)
//   xl/worksheets/sheetN.xml     the cells of sheet N; texts are written in the cells ("inline strings")

namespace oor::results
{

namespace
{

constexpr int STYLE_PLAIN = 0;
constexpr int STYLE_HEADER = 1;
constexpr int STYLE_TITLE = 2;
constexpr int STYLE_LINK = 3;
// What a sheet of the workbook format holds: its rows, its columns, and the length of its name, which the format
// counts in UTF-16 code units (a character outside the basic plane counts for two).
constexpr std::size_t SHEET_ROW_LIMIT = 1'048'576;
constexpr std::size_t SHEET_COLUMN_LIMIT = 16'384;
constexpr std::size_t SHEET_NAME_LIMIT = 31;
// U+FFFD, written in place of bytes that are not a character.
constexpr std::string_view REPLACEMENT_CHARACTER = "\xEF\xBF\xBD";

constexpr const char* XML_DECLARATION = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n";
constexpr const char* MAIN_NAMESPACE = "http://schemas.openxmlformats.org/spreadsheetml/2006/main";
constexpr const char* RELATIONSHIP_NAMESPACE = "http://schemas.openxmlformats.org/officeDocument/2006/relationships";

// The number of bytes of the UTF-8 character that starts at text[at], or 0 when the bytes there are not a character
// XML allows: a stray continuation byte, a sequence cut short or longer than its code point needs, a surrogate, a code
// point above U+10FFFF, U+FFFE or U+FFFF (Unicode Standard, table 3-7, "Well-Formed UTF-8 Byte Sequences").
std::size_t utf8CharacterLength(std::string_view text, std::size_t at)
{
    const auto byteAt = [&](std::size_t index) { return static_cast<unsigned char>(text[index]); };
    const unsigned char lead = byteAt(at);
    if (lead < 0x80)
        return 1;
    std::size_t length = 0;
    std::uint32_t code = 0;
    if (lead >= 0xC2 && lead <= 0xDF)
    {
        length = 2;
        code = lead & 0x1FU;
    }
    else if (lead >= 0xE0 && lead <= 0xEF)
    {
        length = 3;
        code = lead & 0x0FU;
    }
    else if (lead >= 0xF0 && lead <= 0xF4)
    {
        length = 4;
        code = lead & 0x07U;
    }
    else
    {
        return 0;
    }
    if (at + length > text.size())
        return 0;
    for (std::size_t index = 1; index < length; ++index)
    {
        const unsigned char next = byteAt(at + index);
        if ((next & 0xC0U) != 0x80U)
            return 0;
        code = (code << 6U) | (next & 0x3FU);
    }
    const bool overlong = (length == 3 && code < 0x800U) || (length == 4 && code < 0x10000U);
    const bool surrogate = code >= 0xD800U && code <= 0xDFFFU;
    const bool notACharacter = code == 0xFFFEU || code == 0xFFFFU;
    if (overlong || surrogate || notACharacter || code > 0x10FFFFU)
        return 0;
    return length;
}

// A text for XML content or attributes: the five characters XML gives a meaning to are escaped, the control
// characters XML 1.0 does not allow are dropped, and bytes that are not UTF-8 (a title read from a file in another
// encoding) become U+FFFD, so that the part is always well-formed.
std::string xmlEscaped(std::string_view text)
{
    std::string escaped;
    escaped.reserve(text.size());
    for (std::size_t at = 0; at < text.size();)
    {
        const std::size_t length = utf8CharacterLength(text, at);
        if (length == 0)
        {
            escaped += REPLACEMENT_CHARACTER;
            ++at;
            continue;
        }
        if (length > 1)
        {
            escaped += text.substr(at, length);
            at += length;
            continue;
        }
        const char character = text[at++];
        switch (character)
        {
        case '&':
            escaped += "&amp;";
            break;
        case '<':
            escaped += "&lt;";
            break;
        case '>':
            escaped += "&gt;";
            break;
        case '"':
            escaped += "&quot;";
            break;
        case '\'':
            escaped += "&apos;";
            break;
        default:
            if (static_cast<unsigned char>(character) >= 0x20 || character == '\t' || character == '\n')
                escaped += character;
        }
    }
    return escaped;
}

// The letters of a column, from 0: A, B, ..., Z, AA, AB, ...
std::string columnLetters(std::size_t column)
{
    std::string letters;
    ++column;
    while (column > 0)
    {
        const std::size_t remainder = (column - 1) % 26;
        letters.insert(letters.begin(), static_cast<char>('A' + remainder));
        column = (column - 1) / 26;
    }
    return letters;
}

std::string cellReference(std::size_t column, std::size_t row)
{
    return columnLetters(column) + std::to_string(row);
}

std::string currentTimeUtc()
{
    const std::time_t now = std::time(nullptr);
    std::tm parts{};
#if defined(_WIN32)
    gmtime_s(&parts, &now);
#else
    gmtime_r(&now, &parts);
#endif
    char text[32];
    std::strftime(text, sizeof(text), "%Y-%m-%dT%H:%M:%SZ", &parts);
    return text;
}

// The cells of one sheet, line by line. Rows are numbered from 1, columns from 0, as Excel shows them.
class SheetBuilder
{
public:
    explicit SheetBuilder(std::string name) : m_name(std::move(name)) {}

    [[nodiscard]] const std::string& name() const noexcept { return m_name; }
    [[nodiscard]] std::size_t rowCount() const noexcept { return m_row; }

    // Starts the next row; the cells added go to it.
    void newRow()
    {
        closeRow();
        ++m_row;
        m_column = 0;
        m_rows += "<row r=\"" + std::to_string(m_row) + "\">";
        m_rowOpen = true;
    }

    void text(std::string_view value, int style = STYLE_PLAIN)
    {
        if (!value.empty())
        {
            m_rows += "<c r=\"" + cellReference(m_column, m_row) + "\" t=\"inlineStr\"" + styleAttribute(style) +
                      "><is><t xml:space=\"preserve\">" + xmlEscaped(value) + "</t></is></c>";
            noteWidth(value.size());
        }
        ++m_column;
    }

    // A number; NaN leaves the cell empty. `singlePrecision`: the value was a float, written in its shortest form.
    void number(double value, bool singlePrecision = false)
    {
        if (std::isfinite(value))
        {
            std::string written;
            base::appendJsonNumber(written, value, singlePrecision);
            m_rows += "<c r=\"" + cellReference(m_column, m_row) + "\"><v>" + written + "</v></c>";
            noteWidth(written.size());
        }
        ++m_column;
    }

    // A text that is a link to cell A1 of another sheet of the workbook.
    void link(std::string_view value, const std::string& targetSheet)
    {
        m_links.push_back("<hyperlink ref=\"" + cellReference(m_column, m_row) + "\" location=\"" +
                          xmlEscaped(quotedSheet(targetSheet) + "!A1") + "\" display=\"" + xmlEscaped(value) + "\"/>");
        text(value, STYLE_LINK);
    }

    void skipCell() { ++m_column; }

    // The current row is the header of a table: frozen above the data, with filters over `columns` columns down to the
    // last row written.
    void markHeader(std::size_t columns)
    {
        m_headerRow = m_row;
        m_headerColumns = columns;
    }

    // The range of the filters ("'Name'!$A$5:$H$100"), empty when the sheet has none.
    [[nodiscard]] std::string filterRange() const
    {
        if (m_headerRow == 0 || m_headerColumns == 0)
            return {};
        return quotedSheet(m_name) + "!$A$" + std::to_string(m_headerRow) + ":$" + columnLetters(m_headerColumns - 1) +
               "$" + std::to_string(std::max(m_row, m_headerRow));
    }

    [[nodiscard]] std::string xml()
    {
        closeRow();
        std::string out = XML_DECLARATION;
        out += std::string("<worksheet xmlns=\"") + MAIN_NAMESPACE + "\" xmlns:r=\"" + RELATIONSHIP_NAMESPACE + "\">";
        if (m_headerRow > 0)
            out += "<sheetViews><sheetView workbookViewId=\"0\"><pane ySplit=\"" + std::to_string(m_headerRow) +
                   "\" topLeftCell=\"A" + std::to_string(m_headerRow + 1) +
                   "\" activePane=\"bottomLeft\" state=\"frozen\"/></sheetView></sheetViews>";
        if (!m_widths.empty())
        {
            out += "<cols>";
            for (std::size_t column = 0; column < m_widths.size(); ++column)
            {
                const double width = std::min(60.0, std::max(9.0, static_cast<double>(m_widths[column]) + 2.0));
                // std::to_string of a double follows the locale of the program (a decimal comma is not a number of
                // the format): the width is written as the cells are.
                std::string widthText;
                base::appendJsonNumber(widthText, width);
                out += "<col min=\"" + std::to_string(column + 1) + "\" max=\"" + std::to_string(column + 1) +
                       "\" width=\"" + widthText + "\" customWidth=\"1\"/>";
            }
            out += "</cols>";
        }
        out += "<sheetData>" + m_rows + "</sheetData>";
        if (m_headerRow > 0 && m_headerColumns > 0)
            out += "<autoFilter ref=\"A" + std::to_string(m_headerRow) + ":" + columnLetters(m_headerColumns - 1) +
                   std::to_string(std::max(m_row, m_headerRow)) + "\"/>";
        if (!m_links.empty())
        {
            out += "<hyperlinks>";
            for (const std::string& link : m_links)
                out += link;
            out += "</hyperlinks>";
        }
        out += "</worksheet>";
        return out;
    }

    // A sheet name as a formula writes it: between quotes, a quote doubled.
    static std::string quotedSheet(const std::string& name)
    {
        std::string quoted = "'";
        for (const char character : name)
            quoted += character == '\'' ? std::string("''") : std::string(1, character);
        return quoted + "'";
    }

private:
    void closeRow()
    {
        if (m_rowOpen)
            m_rows += "</row>";
        m_rowOpen = false;
    }

    static std::string styleAttribute(int style)
    {
        return style == STYLE_PLAIN ? std::string() : " s=\"" + std::to_string(style) + "\"";
    }

    // The widest content of each column (in characters), for the column widths; the first rows are enough.
    void noteWidth(std::size_t characters)
    {
        if (m_row > 200)
            return;
        if (m_widths.size() <= m_column)
            m_widths.resize(m_column + 1, 0);
        m_widths[m_column] = std::max(m_widths[m_column], characters);
    }

    std::string m_name;
    std::string m_rows;
    std::vector<std::string> m_links;
    std::vector<std::size_t> m_widths;
    std::size_t m_row = 0;
    std::size_t m_column = 0;
    std::size_t m_headerRow = 0;
    std::size_t m_headerColumns = 0;
    bool m_rowOpen = false;
};

// The names of the sheets: Excel wants them unique (ignoring case), at most 31 characters, without : \ / ? * [ ],
// and neither starting nor ending with an apostrophe.
class SheetNames
{
public:
    std::string make(const std::string& wanted)
    {
        std::string base = cleaned(wanted);
        if (base.empty())
            base = "Sheet";
        for (int number = 1;; ++number)
        {
            const std::string suffix = number == 1 ? std::string() : " (" + std::to_string(number) + ")";
            std::string name = cutToLength(base, SHEET_NAME_LIMIT - suffix.size()) + suffix;
            if (name.front() == '\'')
                name.front() = '_';
            if (name.back() == '\'')
                name.back() = '_';
            // ASCII letters only, whatever the locale of the program: the names of the tables are ASCII.
            if (m_taken.insert(base::toUpperAscii(name)).second)
                return name;
        }
    }

private:
    // The text as UTF-8 without what a sheet name cannot have: a forbidden or control character becomes '_', bytes
    // that are not a character become U+FFFD.
    static std::string cleaned(std::string_view wanted)
    {
        std::string text;
        for (std::size_t at = 0; at < wanted.size();)
        {
            const std::size_t length = utf8CharacterLength(wanted, at);
            if (length == 0)
            {
                text += REPLACEMENT_CHARACTER;
                ++at;
            }
            else if (length == 1)
            {
                const char character = wanted[at++];
                const bool refused = std::string_view(":\\/?*[]").find(character) != std::string_view::npos ||
                                     static_cast<unsigned char>(character) < 0x20;
                text += refused ? '_' : character;
            }
            else
            {
                text += wanted.substr(at, length);
                at += length;
            }
        }
        return text;
    }

    // The longest start of `text` (valid UTF-8) of at most `limit` UTF-16 code units, cut between two characters:
    // a cut by bytes could fall inside a character and leave a name that is not a text.
    static std::string cutToLength(const std::string& text, std::size_t limit)
    {
        std::size_t units = 0;
        std::size_t at = 0;
        while (at < text.size())
        {
            const std::size_t length = utf8CharacterLength(text, at);
            const std::size_t characterUnits = length == 4 ? 2 : 1; // beyond the basic plane: a surrogate pair
            if (units + characterUnits > limit)
                break;
            units += characterUnits;
            at += length;
        }
        return text.substr(0, at);
    }

    std::set<std::string> m_taken;
};

// What the index lists about a sheet.
struct IndexLine
{
    std::string sheet;
    std::string kind;
    std::string elementType;
    std::string variant;
    std::int32_t subcase = 0;
    std::string analysis;
    std::string stepKind;
    std::size_t steps = 0;
    std::size_t rows = 0;
    std::size_t components = 0;
    std::string valueType;
    std::string tableName;
};

// ---------------------------------------------------------------------------------------------------------------
// The sheets of a result table.

// The columns that label a row of a table, in the order they are written.
struct RowLabels
{
    bool step = false;
    bool eigenvalue = false;
    bool cycles = false;
    std::string idTitle;
    bool pointType = false;
    bool nodeId = false;
    bool elementId = false;
    bool layer = false;
    bool position = false;
    std::vector<const ResultText*> texts;

    [[nodiscard]] std::size_t count() const
    {
        return (step ? 1 : 0) + (eigenvalue ? 1 : 0) + (cycles ? 1 : 0) + 1 + (pointType ? 1 : 0) + (nodeId ? 1 : 0) +
               (elementId ? 1 : 0) + (layer ? 1 : 0) + (position ? 1 : 0) + texts.size();
    }
};

RowLabels rowLabelsOf(const ResultTableMeta& meta, const ResultData& data)
{
    RowLabels labels;
    const bool valuedSteps = meta.stepKind != StepKind::None && meta.stepKind != StepKind::LoadCombinationSet;
    labels.step = valuedSteps || data.stepCount > 1;
    labels.eigenvalue = !data.eigenvalues.empty();
    labels.cycles = !data.cycles.empty();
    switch (resultKindInfo(meta.kind).rows)
    {
    case RowKind::GridPoint:
        labels.idTitle = "Grid";
        break;
    case RowKind::Element:
        labels.idTitle = "Element";
        break;
    case RowKind::GridPointElement:
        labels.idTitle = "Grid";
        break;
    case RowKind::Mode:
        labels.idTitle = "Mode";
        break;
    }
    labels.pointType = !data.pointTypes.empty();
    labels.nodeId = !data.nodeIds.empty();
    labels.elementId = !data.elementIds.empty();
    labels.layer = data.isElementData() &&
                   std::any_of(data.layers.begin(), data.layers.end(), [](std::int32_t layer) { return layer != 1; });
    labels.position = !data.positions.empty();
    for (const ResultText& text : data.texts)
        labels.texts.push_back(&text);
    return labels;
}

std::string stepTitle(StepKind kind)
{
    switch (kind)
    {
    case StepKind::Mode:
        return "Mode";
    case StepKind::Frequency:
        return "Frequency";
    case StepKind::Time:
        return "Time";
    case StepKind::LoadFactor:
        return "Load factor";
    default:
        return "Step";
    }
}

std::string pointTypeText(std::int32_t type)
{
    switch (type)
    {
    case 1:
        return "G";
    case 2:
        return "S";
    case 3:
        return "E";
    default:
        return std::to_string(type);
    }
}

std::string sheetTitleOf(const ResultTableMeta& meta)
{
    std::string title = "SC" + std::to_string(meta.subcase) + " ";
    if (meta.variant != ResultVariant::Plain)
        title += std::string(resultVariantName(meta.variant)) + " ";
    title += std::string(resultKindName(meta.kind));
    const std::string container = meta.elementName.empty() ? meta.subName : meta.elementName;
    if (!container.empty())
        title += " " + container;
    return title;
}

// The lines at the top of a table sheet: what the table is, a link back to the index, then the header line.
void writeTableHeader(SheetBuilder& sheet, const ResultTableMeta& meta, const ResultData& data, const RowLabels& labels,
                      std::size_t part, std::size_t parts)
{
    sheet.newRow();
    std::string title = std::string(resultKindName(meta.kind));
    const std::string container = meta.elementName.empty() ? meta.subName : meta.elementName;
    if (!container.empty())
        title += " of " + container;
    title += ", subcase " + std::to_string(meta.subcase);
    if (parts > 1)
        title += " (part " + std::to_string(part) + " of " + std::to_string(parts) + ")";
    sheet.text(title, STYLE_TITLE);

    sheet.newRow();
    std::string facts = "Analysis: " + std::string(analysisTypeName(meta.analysisCode)) +
                        "   Steps: " + std::to_string(data.stepCount) + "   Rows: " + std::to_string(data.rowCount) +
                        "   Values: " + std::string(valueTypeName(data.type));
    if (meta.variant != ResultVariant::Plain)
        facts += "   Variant: " + std::string(resultVariantName(meta.variant));
    if (!meta.layout.empty())
        facts += "   Layout: " + meta.layout;
    if (meta.units != "unknown" && !meta.units.empty())
        facts += "   Units: " + meta.units;
    sheet.text(facts);

    if (!meta.title.empty() || !meta.subtitle.empty() || !meta.label.empty())
    {
        sheet.newRow();
        sheet.text(meta.title);
        sheet.text(meta.subtitle);
        sheet.text(meta.label);
    }
    sheet.newRow();
    sheet.link("Back to the index", "Index");

    sheet.newRow(); // the header line
    if (labels.step)
        sheet.text(stepTitle(meta.stepKind), STYLE_HEADER);
    if (labels.eigenvalue)
        sheet.text("Eigenvalue", STYLE_HEADER);
    if (labels.cycles)
        sheet.text("Cycles", STYLE_HEADER);
    sheet.text(labels.idTitle, STYLE_HEADER);
    if (labels.pointType)
        sheet.text("Type", STYLE_HEADER);
    if (labels.nodeId)
        sheet.text("Grid", STYLE_HEADER);
    if (labels.elementId)
        sheet.text("Element", STYLE_HEADER);
    if (labels.layer)
        sheet.text("Layer", STYLE_HEADER);
    if (labels.position)
        sheet.text("Position", STYLE_HEADER);
    for (const ResultText* text : labels.texts)
        sheet.text(text->name, STYLE_HEADER);
    const bool complex = isComplexType(data.type);
    for (const std::string& component : data.components)
    {
        if (complex)
        {
            sheet.text(component + " (real)", STYLE_HEADER);
            sheet.text(component + " (imag)", STYLE_HEADER);
        }
        else
        {
            sheet.text(component, STYLE_HEADER);
        }
    }
    sheet.markHeader(labels.count() + data.componentCount * (complex ? 2 : 1));
}

// One data line: the labels of the row, then its values.
void writeTableRow(SheetBuilder& sheet, const ResultData& data, const RowLabels& labels, std::size_t step,
                   std::size_t row)
{
    sheet.newRow();
    if (labels.step)
        sheet.number(data.steps[step]);
    if (labels.eigenvalue)
        sheet.number(data.eigenvalues[step]);
    if (labels.cycles)
        sheet.number(data.cycles[step]);
    sheet.number(data.ids[row]);
    if (labels.pointType)
        sheet.text(pointTypeText(data.pointTypes[row]));
    if (labels.nodeId)
        sheet.number(data.nodeIds[row]);
    if (labels.elementId)
        sheet.number(data.elementIds[row]);
    if (labels.layer)
        sheet.number(data.layers[row]);
    if (labels.position)
        sheet.number(data.positions[row]);
    for (const ResultText* text : labels.texts)
        sheet.text(text->at(row));

    const bool complex = isComplexType(data.type);
    const bool single = data.type == ValueType::Float32 || data.type == ValueType::Complex64;
    const std::size_t width = data.componentCount * (complex ? 2 : 1);
    const std::size_t first = (step * data.rowCount + row) * width;
    if (single)
    {
        const auto values = data.values<float>();
        for (std::size_t index = 0; index < width; ++index)
            sheet.number(values[first + index], true);
    }
    else
    {
        const auto values = data.values<double>();
        for (std::size_t index = 0; index < width; ++index)
            sheet.number(values[first + index]);
    }
}

// ---------------------------------------------------------------------------------------------------------------
// The workbook.

class WorkbookBuilder
{
public:
    explicit WorkbookBuilder(const XlsxWriteOptions& options, ResultWriteReport& report)
        : m_options(options), m_report(report)
    {
        if (options.maxRowsPerSheet < 20)
            throw base::UsageError("xlsx: maxRowsPerSheet is " + std::to_string(options.maxRowsPerSheet) +
                                   "; a sheet needs room for its header and some rows (at least 20)");
        if (options.maxRowsPerSheet > SHEET_ROW_LIMIT)
            throw base::UsageError("xlsx: maxRowsPerSheet is " + std::to_string(options.maxRowsPerSheet) +
                                   "; a sheet of the format holds at most " + std::to_string(SHEET_ROW_LIMIT) +
                                   " rows");
        m_names.make("Index"); // reserved for the index sheet
    }

    void addTable(const ResultTable& table)
    {
        const ResultTableMeta& meta = table.meta();
        const std::shared_ptr<const ResultData> data = table.data();
        const std::string container = meta.elementName.empty() ? meta.subName : meta.elementName;
        if (data->stepCount == 0 || data->rowCount == 0 || data->componentCount == 0)
        {
            m_report.skipped.push_back(SkippedTable{std::string(resultKindName(meta.kind)), container, meta.subcase,
                                                    std::string(write_reasons::NO_FILE_LAYOUT),
                                                    "an empty table (no step, row or component) has nothing to write"});
            return;
        }
        const RowLabels labels = rowLabelsOf(meta, *data);
        const std::size_t columns = labels.count() + data->componentCount * (isComplexType(data->type) ? 2 : 1);
        if (columns > SHEET_COLUMN_LIMIT)
        {
            m_report.skipped.push_back(
                SkippedTable{std::string(resultKindName(meta.kind)), container, meta.subcase,
                             std::string(write_reasons::NO_FILE_LAYOUT),
                             "a line of the table has " + std::to_string(columns) + " columns, a sheet holds " +
                                 std::to_string(SHEET_COLUMN_LIMIT)});
            return;
        }
        const std::size_t headerRows = 8; // the most rows the header block takes (writeTableHeader)
        const std::size_t perSheet = m_options.maxRowsPerSheet - headerRows;
        const std::size_t total = data->stepCount * data->rowCount;
        const std::size_t parts = (total + perSheet - 1) / perSheet;
        const std::string title = sheetTitleOf(meta);
        std::string firstSheet;
        for (std::size_t part = 0; part < parts; ++part)
        {
            SheetBuilder sheet(m_names.make(parts == 1 ? title : title + " " + std::to_string(part + 1)));
            if (part == 0)
                firstSheet = sheet.name();
            writeTableHeader(sheet, meta, *data, labels, part + 1, parts);
            const std::size_t end = std::min(total, (part + 1) * perSheet);
            for (std::size_t line = part * perSheet; line < end; ++line)
                writeTableRow(sheet, *data, labels, line / data->rowCount, line % data->rowCount);
            IndexLine index;
            index.sheet = sheet.name();
            index.kind = std::string(resultKindName(meta.kind));
            index.elementType = container;
            index.variant = std::string(resultVariantName(meta.variant));
            index.subcase = meta.subcase;
            index.analysis = std::string(analysisTypeName(meta.analysisCode));
            index.stepKind = std::string(stepKindName(meta.stepKind));
            index.steps = data->stepCount;
            index.rows = data->rowCount;
            index.components = data->componentCount;
            index.valueType = std::string(valueTypeName(data->type));
            index.tableName = meta.tableName;
            m_index.push_back(std::move(index));
            m_sheets.push_back(std::move(sheet));
        }
        WrittenTable written;
        written.kind = std::string(resultKindName(meta.kind));
        written.container = container;
        written.subcase = meta.subcase;
        written.fileTable = firstSheet;
        written.steps = data->stepCount;
        written.rows = data->rowCount;
        m_report.written.push_back(std::move(written));
    }

    void addNamed(const NamedResult& named)
    {
        const NamedResultMeta& meta = named.meta();
        const std::shared_ptr<const NamedResultData> data = named.data();
        // The lines of the result are counted first: the names of its sheets say whether it has several.
        std::size_t lines = meta.attributes.size();
        for (const ResultArray& array : data->arrays)
            lines += BLOCK_HEADER_LINES + arrayLayoutOf(array).rows;
        for (const ResultText& text : data->texts)
            lines += BLOCK_HEADER_LINES + text.size();
        NamedSheets sheets(m_names, meta, lines, m_options.maxRowsPerSheet);

        for (const auto& [key, value] : meta.attributes)
        {
            SheetBuilder& sheet = sheets.line();
            sheet.text(key, STYLE_HEADER);
            sheet.text(value);
        }
        for (const ResultArray& array : data->arrays)
            writeArray(sheets, array);
        for (const ResultText& text : data->texts)
        {
            sheets.line();
            sheets.line().text(text.name, STYLE_HEADER);
            for (std::size_t row = 0; row < text.size(); ++row)
                sheets.line().text(text.at(row));
        }

        std::string firstSheet;
        for (SheetBuilder& sheet : sheets.take())
        {
            if (firstSheet.empty())
                firstSheet = sheet.name();
            IndexLine index;
            index.sheet = sheet.name();
            index.kind = meta.kind;
            index.elementType = meta.name;
            index.subcase = meta.subcase;
            index.analysis = std::string(analysisTypeName(meta.analysisCode));
            index.tableName = meta.tableName;
            m_index.push_back(std::move(index));
            m_sheets.push_back(std::move(sheet));
        }
        WrittenTable written;
        written.kind = meta.kind;
        written.container = meta.name;
        written.subcase = meta.subcase;
        written.fileTable = firstSheet;
        m_report.written.push_back(std::move(written));
    }

    // The bytes of the .xlsx file.
    [[nodiscard]] std::string finish()
    {
        SheetBuilder index = indexSheet();
        std::vector<SheetBuilder*> ordered;
        ordered.push_back(&index);
        for (SheetBuilder& sheet : m_sheets)
            ordered.push_back(&sheet);

        io::ZipWriter zip(m_options.compressionLevel);
        zip.addFile("[Content_Types].xml", contentTypes(ordered.size()));
        zip.addFile("_rels/.rels", packageRelationships());
        zip.addFile("docProps/core.xml", coreProperties());
        zip.addFile("docProps/app.xml", appProperties());
        zip.addFile("xl/workbook.xml", workbook(ordered));
        zip.addFile("xl/_rels/workbook.xml.rels", workbookRelationships(ordered.size()));
        zip.addFile("xl/styles.xml", styles());
        for (std::size_t number = 0; number < ordered.size(); ++number)
            zip.addFile("xl/worksheets/sheet" + std::to_string(number + 1) + ".xml", ordered[number]->xml());
        return zip.finish();
    }

private:
    // The lines before the values of an array or of a list of texts of a named result: a blank line, then its name.
    static constexpr std::size_t BLOCK_HEADER_LINES = 2;
    // The rows at the top of every sheet of a named result: what it is, and the link back to the index.
    static constexpr std::size_t NAMED_HEADER_ROWS = 2;

    // The sheets of one named result, filled line by line: a line that does not fit the current sheet opens the next
    // one, so that no sheet has more rows than XlsxWriteOptions::maxRowsPerSheet (as the sheets of a table).
    class NamedSheets
    {
    public:
        NamedSheets(SheetNames& names, const NamedResultMeta& meta, std::size_t lines, std::size_t maxRowsPerSheet)
            : m_names(names), m_meta(meta), m_perSheet(maxRowsPerSheet - NAMED_HEADER_ROWS),
              m_parts(std::max<std::size_t>(1, (lines + m_perSheet - 1) / m_perSheet))
        {
            open(); // a result without a line still has its sheet
        }

        // Starts the next line of the result and gives the sheet it is in. The reference is good until the next call.
        SheetBuilder& line()
        {
            if (m_linesInSheet == m_perSheet)
                open();
            ++m_linesInSheet;
            m_sheets.back().newRow();
            return m_sheets.back();
        }

        [[nodiscard]] std::vector<SheetBuilder> take() { return std::move(m_sheets); }

    private:
        void open()
        {
            const std::string title = m_meta.kind + " " + m_meta.name;
            const std::size_t part = m_sheets.size() + 1;
            m_sheets.emplace_back(m_names.make(m_parts == 1 ? title : title + " " + std::to_string(part)));
            SheetBuilder& sheet = m_sheets.back();
            sheet.newRow();
            std::string heading = title + ", subcase " + std::to_string(m_meta.subcase);
            if (m_parts > 1)
                heading += " (part " + std::to_string(part) + " of " + std::to_string(m_parts) + ")";
            sheet.text(heading, STYLE_TITLE);
            sheet.newRow();
            sheet.link("Back to the index", "Index");
            m_linesInSheet = 0;
        }

        SheetNames& m_names;
        const NamedResultMeta& m_meta;
        std::size_t m_perSheet;
        std::size_t m_parts;
        std::size_t m_linesInSheet = 0;
        std::vector<SheetBuilder> m_sheets;
    };

    // How an array of a named result is laid out: a grid for a two-dimensional one whose lines fit the columns of a
    // sheet, one value a line (in the order of the array) for the others.
    struct ArrayLayout
    {
        std::size_t rows = 0;
        std::size_t columns = 1;
        bool isUnfolded = false; // two-dimensional, but wider than a sheet
    };

    static ArrayLayout arrayLayoutOf(const ResultArray& array)
    {
        const bool complex = array.type == ArrayType::Complex64 || array.type == ArrayType::Complex128;
        const std::size_t cellsPerValue = complex ? 2 : 1;
        ArrayLayout layout;
        layout.columns = array.shape.size() == 2 ? array.shape[1] : 1;
        if (layout.columns > SHEET_COLUMN_LIMIT / cellsPerValue)
        {
            layout.columns = 1;
            layout.isUnfolded = true;
        }
        layout.rows = layout.columns == 0 ? 0 : array.valueCount() / layout.columns;
        return layout;
    }

    // An array of a named result: a grid for a two-dimensional one, a column for the others.
    static void writeArray(NamedSheets& sheets, const ResultArray& array)
    {
        const ArrayLayout layout = arrayLayoutOf(array);
        sheets.line();
        {
            std::string shape;
            for (const std::size_t extent : array.shape)
                shape += (shape.empty() ? "" : " x ") + std::to_string(extent);
            SheetBuilder& sheet = sheets.line();
            sheet.text(array.name, STYLE_HEADER);
            sheet.text(shape.empty() ? std::string("a number") : shape);
            sheet.text(array.description);
            if (layout.isUnfolded)
                sheet.text("one value a line, row after row: a row of the array is wider than a sheet");
        }

        const bool complex = array.type == ArrayType::Complex64 || array.type == ArrayType::Complex128;
        const std::size_t parts = complex ? 2 : 1;
        const auto valueAt = [&](std::size_t index) -> double
        {
            switch (array.type)
            {
            case ArrayType::Int32:
                return array.values<std::int32_t>()[index];
            case ArrayType::Int64:
                return static_cast<double>(array.values<std::int64_t>()[index]);
            case ArrayType::Float32:
            case ArrayType::Complex64:
                return array.values<float>()[index];
            case ArrayType::Float64:
            case ArrayType::Complex128:
                return array.values<double>()[index];
            }
            return 0.0;
        };
        for (std::size_t row = 0; row < layout.rows; ++row)
        {
            SheetBuilder& sheet = sheets.line();
            for (std::size_t column = 0; column < layout.columns; ++column)
                for (std::size_t part = 0; part < parts; ++part)
                    sheet.number(valueAt((row * layout.columns + column) * parts + part));
        }
    }

    SheetBuilder indexSheet()
    {
        SheetBuilder sheet("Index");
        sheet.newRow();
        sheet.text(m_options.title.empty() ? std::string("Results") : m_options.title, STYLE_TITLE);
        if (!m_options.subtitle.empty())
        {
            sheet.newRow();
            sheet.text(m_options.subtitle);
        }
        if (!m_options.label.empty())
        {
            sheet.newRow();
            sheet.text(m_options.label);
        }
        sheet.newRow();
        sheet.text("Written by " + std::string(base::LIBRARY_NAME) + " " + std::string(base::LIBRARY_VERSION) + " on " +
                   currentTimeUtc());
        sheet.newRow();
        sheet.newRow();
        for (const char* title : {"Sheet", "Kind", "Element type", "Variant", "Subcase", "Analysis", "Step kind",
                                  "Steps", "Rows", "Components", "Values", "Table name"})
            sheet.text(title, STYLE_HEADER);
        sheet.markHeader(12);
        for (const IndexLine& line : m_index)
        {
            sheet.newRow();
            sheet.link(line.sheet, line.sheet);
            sheet.text(line.kind);
            sheet.text(line.elementType);
            sheet.text(line.variant);
            sheet.number(line.subcase);
            sheet.text(line.analysis);
            sheet.text(line.stepKind);
            if (line.steps > 0)
            {
                sheet.number(static_cast<double>(line.steps));
                sheet.number(static_cast<double>(line.rows));
                sheet.number(static_cast<double>(line.components));
            }
            else
            {
                sheet.skipCell();
                sheet.skipCell();
                sheet.skipCell();
            }
            sheet.text(line.valueType);
            sheet.text(line.tableName);
        }
        return sheet;
    }

    static std::string contentTypes(std::size_t sheets)
    {
        std::string xml = XML_DECLARATION;
        xml +=
            "<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">"
            "<Default Extension=\"rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>"
            "<Default Extension=\"xml\" ContentType=\"application/xml\"/>"
            "<Override PartName=\"/xl/workbook.xml\" "
            "ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml\"/>"
            "<Override PartName=\"/xl/styles.xml\" "
            "ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.styles+xml\"/>"
            "<Override PartName=\"/docProps/core.xml\" "
            "ContentType=\"application/vnd.openxmlformats-package.core-properties+xml\"/>"
            "<Override PartName=\"/docProps/app.xml\" "
            "ContentType=\"application/vnd.openxmlformats-officedocument.extended-properties+xml\"/>";
        for (std::size_t number = 1; number <= sheets; ++number)
            xml += "<Override PartName=\"/xl/worksheets/sheet" + std::to_string(number) +
                   ".xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml\"/>";
        return xml + "</Types>";
    }

    static std::string packageRelationships()
    {
        return std::string(XML_DECLARATION) +
               "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">"
               "<Relationship Id=\"rId1\" Type=\"" +
               RELATIONSHIP_NAMESPACE +
               "/officeDocument\" Target=\"xl/workbook.xml\"/>"
               "<Relationship Id=\"rId2\" "
               "Type=\"http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties\" "
               "Target=\"docProps/core.xml\"/>"
               "<Relationship Id=\"rId3\" Type=\"" +
               RELATIONSHIP_NAMESPACE +
               "/extended-properties\" Target=\"docProps/app.xml\"/>"
               "</Relationships>";
    }

    std::string coreProperties() const
    {
        const std::string producer = std::string(base::LIBRARY_NAME) + " " + std::string(base::LIBRARY_VERSION);
        return std::string(XML_DECLARATION) +
               "<cp:coreProperties "
               "xmlns:cp=\"http://schemas.openxmlformats.org/package/2006/metadata/core-properties\" "
               "xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" "
               "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"
               "<dc:title>" +
               xmlEscaped(m_options.title.empty() ? std::string("Results") : m_options.title) +
               "</dc:title><dc:creator>" + xmlEscaped(producer) +
               "</dc:creator>"
               "<dcterms:created xsi:type=\"dcterms:W3CDTF\">" +
               currentTimeUtc() +
               "</dcterms:created>"
               "</cp:coreProperties>";
    }

    static std::string appProperties()
    {
        return std::string(XML_DECLARATION) +
               "<Properties xmlns=\"http://schemas.openxmlformats.org/officeDocument/2006/extended-properties\">"
               "<Application>" +
               std::string(base::LIBRARY_NAME) + "</Application></Properties>";
    }

    static std::string workbook(const std::vector<SheetBuilder*>& sheets)
    {
        std::string xml = XML_DECLARATION;
        xml += std::string("<workbook xmlns=\"") + MAIN_NAMESPACE + "\" xmlns:r=\"" + RELATIONSHIP_NAMESPACE +
               "\"><sheets>";
        for (std::size_t number = 0; number < sheets.size(); ++number)
            xml += "<sheet name=\"" + xmlEscaped(sheets[number]->name()) + "\" sheetId=\"" +
                   std::to_string(number + 1) + "\" r:id=\"rId" + std::to_string(number + 1) + "\"/>";
        xml += "</sheets>";
        // the range of the filters of each sheet, as Excel records it
        std::string names;
        for (std::size_t number = 0; number < sheets.size(); ++number)
        {
            const std::string range = sheets[number]->filterRange();
            if (!range.empty())
                names += "<definedName name=\"_xlnm._FilterDatabase\" localSheetId=\"" + std::to_string(number) +
                         "\" hidden=\"1\">" + xmlEscaped(range) + "</definedName>";
        }
        if (!names.empty())
            xml += "<definedNames>" + names + "</definedNames>";
        return xml + "</workbook>";
    }

    static std::string workbookRelationships(std::size_t sheets)
    {
        std::string xml = XML_DECLARATION;
        xml += "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">";
        for (std::size_t number = 1; number <= sheets; ++number)
            xml += "<Relationship Id=\"rId" + std::to_string(number) + "\" Type=\"" + RELATIONSHIP_NAMESPACE +
                   "/worksheet\" Target=\"worksheets/sheet" + std::to_string(number) + ".xml\"/>";
        xml += "<Relationship Id=\"rId" + std::to_string(sheets + 1) + "\" Type=\"" + RELATIONSHIP_NAMESPACE +
               "/styles\" Target=\"styles.xml\"/>";
        return xml + "</Relationships>";
    }

    // Four styles, in the order of the STYLE_ constants: plain, header, title, link.
    static std::string styles()
    {
        return std::string(XML_DECLARATION) + "<styleSheet xmlns=\"" + MAIN_NAMESPACE + "\">" +
               "<fonts count=\"4\">"
               "<font><sz val=\"11\"/><name val=\"Calibri\"/></font>"
               "<font><b/><sz val=\"11\"/><name val=\"Calibri\"/></font>"
               "<font><b/><sz val=\"14\"/><name val=\"Calibri\"/></font>"
               "<font><u/><sz val=\"11\"/><color rgb=\"FF0563C1\"/><name val=\"Calibri\"/></font>"
               "</fonts>"
               "<fills count=\"3\"><fill><patternFill patternType=\"none\"/></fill>"
               "<fill><patternFill patternType=\"gray125\"/></fill>"
               "<fill><patternFill patternType=\"solid\"><fgColor rgb=\"FFDDEBF7\"/><bgColor indexed=\"64\"/>"
               "</patternFill></fill></fills>"
               "<borders count=\"1\"><border><left/><right/><top/><bottom/><diagonal/></border></borders>"
               "<cellStyleXfs count=\"1\"><xf numFmtId=\"0\" fontId=\"0\" fillId=\"0\" borderId=\"0\"/></cellStyleXfs>"
               "<cellXfs count=\"4\">"
               "<xf numFmtId=\"0\" fontId=\"0\" fillId=\"0\" borderId=\"0\" xfId=\"0\"/>"
               "<xf numFmtId=\"0\" fontId=\"1\" fillId=\"2\" borderId=\"0\" xfId=\"0\" applyFont=\"1\" "
               "applyFill=\"1\"/>"
               "<xf numFmtId=\"0\" fontId=\"2\" fillId=\"0\" borderId=\"0\" xfId=\"0\" applyFont=\"1\"/>"
               "<xf numFmtId=\"0\" fontId=\"3\" fillId=\"0\" borderId=\"0\" xfId=\"0\" applyFont=\"1\"/>"
               "</cellXfs>"
               "<cellStyles count=\"1\"><cellStyle name=\"Normal\" xfId=\"0\" builtinId=\"0\"/></cellStyles>"
               "</styleSheet>";
    }

    const XlsxWriteOptions& m_options;
    ResultWriteReport& m_report;
    SheetNames m_names;
    std::vector<SheetBuilder> m_sheets;
    std::vector<IndexLine> m_index;
};

} // namespace

std::string formatXlsx(const ResultTables& tables, const XlsxWriteOptions& options, ResultWriteReport* report)
{
    ResultWriteReport local;
    ResultWriteReport& target = report != nullptr ? *report : local;
    target.format = "xlsx";
    WorkbookBuilder workbook(options, target);
    for (const std::shared_ptr<ResultTable>& table : tables.all())
        workbook.addTable(*table);
    for (const std::shared_ptr<NamedResult>& named : tables.namedResults())
        workbook.addNamed(*named);
    std::string bytes = workbook.finish();
    target.finished = true;
    target.bytes = bytes.size();
    return bytes;
}

ResultWriteReport writeXlsx(const std::filesystem::path& path, const ResultTables& tables,
                            const XlsxWriteOptions& options)
{
    ResultWriteReport report;
    const std::string bytes = formatXlsx(tables, options, &report);
    if (path.has_parent_path())
        std::filesystem::create_directories(path.parent_path()); // the folder of the file, when it is missing
    std::filesystem::path temporary = path;
    temporary += ".oor_tmp";
    {
        std::ofstream stream(temporary, std::ios::binary);
        if (!stream)
            throw base::IoError("cannot write " + base::pathToUtf8(temporary));
        stream.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
        if (!stream)
            throw base::IoError("cannot write " + base::pathToUtf8(temporary));
    }
    std::error_code ignored;
    std::filesystem::remove(path, ignored);
    std::filesystem::rename(temporary, path);
    report.path = base::pathToUtf8(path); // text that leaves the library is UTF-8 (TextUtilities.hpp)
    return report;
}

} // namespace oor::results
