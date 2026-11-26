// The workbook at the limits of a sheet and of its texts: a named result longer or wider than a sheet, sheet names
// cut between two characters, texts that are not UTF-8, and numbers written the same way in every locale.
#include "oor/io/zip/Zip.hpp"
#include "oor/results/core/MemoryResults.hpp"
#include "oor/results/xlsx/XlsxWriter.hpp"

#include <catch2/catch_test_macros.hpp>

#include <clocale>
#include <cstdint>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace oor;
using namespace oor::results;

namespace
{

constexpr std::size_t SHEET_COLUMNS = 16'384; // what a sheet of the format holds
constexpr std::size_t SHEET_ROWS = 1'048'576;

// The files of a workbook, by name.
std::map<std::string, std::string> partsOf(const std::string& bytes)
{
    std::map<std::string, std::string> parts;
    for (io::ZipFile& file : io::readZip(bytes))
        parts[file.name] = std::move(file.content);
    return parts;
}

bool has(const std::string& text, const std::string& part)
{
    return text.find(part) != std::string::npos;
}

std::size_t countOf(const std::string& text, const std::string& part)
{
    std::size_t count = 0;
    for (std::size_t at = text.find(part); at != std::string::npos; at = text.find(part, at + part.size()))
        ++count;
    return count;
}

// Whether the text is well-formed UTF-8 (Unicode Standard, table 3-7).
bool isUtf8(const std::string& text)
{
    for (std::size_t at = 0; at < text.size();)
    {
        const auto lead = static_cast<unsigned char>(text[at]);
        const std::size_t length = lead < 0x80 ? 1 : lead >= 0xC2 && lead <= 0xDF ? 2 : lead >= 0xE0 && lead <= 0xEF ? 3
                                 : lead >= 0xF0 && lead <= 0xF4 ? 4 : 0;
        if (length == 0 || at + length > text.size())
            return false;
        std::uint32_t code = length == 1 ? lead : lead & (0xFFU >> (length + 1));
        for (std::size_t index = 1; index < length; ++index)
        {
            const auto next = static_cast<unsigned char>(text[at + index]);
            if ((next & 0xC0U) != 0x80U)
                return false;
            code = (code << 6U) | (next & 0x3FU);
        }
        const bool overlong = (length == 3 && code < 0x800U) || (length == 4 && code < 0x10000U);
        if (overlong || (code >= 0xD800U && code <= 0xDFFFU) || code > 0x10FFFFU)
            return false;
        at += length;
    }
    return true;
}

// A set with one named result of one array of `shape`, its values 1, 2, 3, ...
ResultTables namedArray(const std::string& name, std::vector<std::size_t> shape)
{
    auto data = std::make_shared<NamedResultData>();
    ResultArray array;
    array.name = "terms";
    array.type = ArrayType::Float64;
    array.shape = std::move(shape);
    array.allocate();
    const auto values = array.mutableValues<double>();
    for (std::size_t index = 0; index < values.size(); ++index)
        values[index] = static_cast<double>(index + 1);
    data->arrays.push_back(std::move(array));
    NamedResultMeta meta;
    meta.kind = "matrix";
    meta.name = name;
    ResultTables tables;
    tables.addNamed(std::make_shared<NamedResult>(std::move(meta), std::shared_ptr<const NamedResultData>(data)));
    return tables;
}

// The largest row number of a sheet.
std::size_t lastRowOf(const std::string& sheet)
{
    const std::size_t at = sheet.rfind("<row r=\"");
    return at == std::string::npos ? 0 : static_cast<std::size_t>(std::stoul(sheet.substr(at + 8)));
}

// A locale that writes a decimal comma, set while the object lives when the machine has one (isSet()); the locale of
// the program is put back at the end, also when a check stops the test.
class DecimalCommaLocale
{
public:
    DecimalCommaLocale() : m_before(std::setlocale(LC_NUMERIC, nullptr))
    {
        for (const char* name :
             {"fr_FR.UTF-8", "fr_FR", "French_France.1252", "fr-FR", "de_DE.UTF-8", "German_Germany.1252"})
            if (std::setlocale(LC_NUMERIC, name) != nullptr && *std::localeconv()->decimal_point == ',')
            {
                m_isSet = true;
                return;
            }
    }
    DecimalCommaLocale(const DecimalCommaLocale&) = delete;
    DecimalCommaLocale& operator=(const DecimalCommaLocale&) = delete;
    ~DecimalCommaLocale() { std::setlocale(LC_NUMERIC, m_before.c_str()); }

    [[nodiscard]] bool isSet() const noexcept { return m_isSet; }

private:
    std::string m_before;
    bool m_isSet = false;
};

} // namespace

TEST_CASE("a named result longer than a sheet goes on in the next sheets", "[results][xlsx][review]")
{
    const ResultTables tables = namedArray("KAA", {60});
    XlsxWriteOptions options;
    options.maxRowsPerSheet = 20; // 2 rows of heading and 18 lines a sheet: 62 lines take 4 sheets
    ResultWriteReport report;
    const auto parts = partsOf(formatXlsx(tables, options, &report));

    const std::string& workbook = parts.at("xl/workbook.xml");
    CHECK(has(workbook, "name=\"matrix KAA 1\""));
    CHECK(has(workbook, "name=\"matrix KAA 4\""));
    CHECK_FALSE(has(workbook, "name=\"matrix KAA 5\""));
    CHECK(parts.count("xl/worksheets/sheet5.xml") == 1); // the index and four sheets
    CHECK(parts.count("xl/worksheets/sheet6.xml") == 0);

    std::size_t values = 0;
    for (int number = 2; number <= 5; ++number)
    {
        const std::string& sheet = parts.at("xl/worksheets/sheet" + std::to_string(number) + ".xml");
        INFO("sheet " << number);
        CHECK(lastRowOf(sheet) <= options.maxRowsPerSheet);
        CHECK(has(sheet, "(part " + std::to_string(number - 1) + " of 4)"));
        CHECK(has(sheet, "Back to the index"));
        values += countOf(sheet, "<v>");
    }
    CHECK(values == 60); // every value once
    CHECK(has(parts.at("xl/worksheets/sheet5.xml"), "<v>60</v>"));

    // one line of the index a sheet, one entry of the report for the result
    CHECK(countOf(parts.at("xl/worksheets/sheet1.xml"), "location=\"&apos;matrix KAA ") == 4);
    REQUIRE(report.written.size() == 1);
    CHECK(report.written.front().fileTable == "matrix KAA 1");
    CHECK(report.skipped.empty());
}

TEST_CASE("a named result that fits keeps one sheet under its own name", "[results][xlsx][review]")
{
    const auto parts = partsOf(formatXlsx(namedArray("KAA", {2, 3})));
    CHECK(has(parts.at("xl/workbook.xml"), "name=\"matrix KAA\""));
    const std::string& sheet = parts.at("xl/worksheets/sheet2.xml");
    CHECK_FALSE(has(sheet, "(part "));
    // a grid: the second row of the array is one line of three cells
    CHECK(has(sheet, "<c r=\"A6\"><v>4</v></c><c r=\"B6\"><v>5</v></c><c r=\"C6\"><v>6</v></c>"));
}

TEST_CASE("an array wider than a sheet is written one value a line", "[results][xlsx][review]")
{
    const std::size_t columns = SHEET_COLUMNS + 1;
    ResultWriteReport report;
    const auto parts = partsOf(formatXlsx(namedArray("WIDE", {2, columns}), {}, &report));
    const std::string& sheet = parts.at("xl/worksheets/sheet2.xml");
    CHECK(has(sheet, "one value a line"));
    CHECK(has(sheet, "2 x " + std::to_string(columns)));
    CHECK(countOf(sheet, "<v>") == 2 * columns);
    CHECK_FALSE(has(sheet, "<c r=\"B5\">")); // the values are in the first column only
    CHECK(lastRowOf(sheet) == 4 + 2 * columns);
    CHECK(lastRowOf(sheet) <= SHEET_ROWS);
    CHECK(report.written.size() == 1);
}

TEST_CASE("a table with more columns than a sheet is reported as skipped", "[results][xlsx][review]")
{
    auto data = std::make_shared<ResultData>();
    data->type = ValueType::Float64;
    data->stepCount = 1;
    data->rowCount = 1;
    data->components.assign(SHEET_COLUMNS, "c");
    data->componentCount = data->components.size();
    data->allocate();
    data->steps = {std::numeric_limits<double>::quiet_NaN()};
    data->ids = {1};
    ResultTableMeta meta;
    meta.kind = ResultKind::Displacements;
    meta.subcase = 3;
    ResultTables tables;
    addTableToResults(tables,
                      std::make_shared<ResultTable>(std::move(meta), std::shared_ptr<const ResultData>(data)));

    ResultWriteReport report;
    const auto parts = partsOf(formatXlsx(tables, {}, &report));
    CHECK(report.written.empty());
    REQUIRE(report.skipped.size() == 1);
    CHECK(report.skipped.front().subcase == 3);
    CHECK(has(report.skipped.front().message, "columns"));
    CHECK(parts.count("xl/worksheets/sheet2.xml") == 0); // the index alone
}

TEST_CASE("a sheet name is cut between two characters", "[results][xlsx][review]")
{
    const std::string eAcute = "\xC3\xA9";      // U+00E9, two bytes
    const std::string face = "\xF0\x9F\x98\x80"; // U+1F600, four bytes and two UTF-16 code units
    std::string accents;
    for (int index = 0; index < 30; ++index)
        accents += eAcute;

    SECTION("a two-byte character at the limit")
    {
        const auto parts = partsOf(formatXlsx(namedArray(accents, {1})));
        const std::string& workbook = parts.at("xl/workbook.xml");
        CHECK(isUtf8(workbook));
        // "matrix " and 24 of the characters: 31 characters, where 31 bytes would end inside one
        CHECK(has(workbook, "name=\"matrix " + accents.substr(0, 24 * eAcute.size()) + "\""));
        for (const auto& [name, content] : parts)
        {
            INFO(name);
            CHECK(isUtf8(content));
        }
    }
    SECTION("a character of two code units is kept whole or left out")
    {
        // "matrix " is 7 units and 23 letters make 30: the character would be the units 31 and 32
        const auto parts = partsOf(formatXlsx(namedArray(std::string(23, 'a') + face + "z", {1})));
        const std::string& workbook = parts.at("xl/workbook.xml");
        CHECK(isUtf8(workbook));
        CHECK(has(workbook, "name=\"matrix " + std::string(23, 'a') + "\""));
    }
    SECTION("apostrophes at the ends and forbidden characters")
    {
        const auto parts = partsOf(formatXlsx(namedArray("a/b'", {1})));
        CHECK(has(parts.at("xl/workbook.xml"), "name=\"matrix a_b_\""));
    }
}

TEST_CASE("bytes that are not UTF-8 are replaced in every text of the workbook", "[results][xlsx][review]")
{
    const std::string replacement = "\xEF\xBF\xBD"; // U+FFFD
    XlsxWriteOptions options;
    options.title = "r\xE9sultats & co"; // a title in a one-byte encoding
    options.subtitle = "cut \xC3";        // a sequence cut short
    const auto parts = partsOf(formatXlsx(namedArray("aile \xE9", {1}), options));
    for (const auto& [name, content] : parts)
    {
        INFO(name);
        CHECK(isUtf8(content));
    }
    const std::string& index = parts.at("xl/worksheets/sheet1.xml");
    CHECK(has(index, "r" + replacement + "sultats &amp; co"));
    CHECK(has(index, "cut " + replacement));
    CHECK(has(parts.at("xl/workbook.xml"), "name=\"matrix aile " + replacement + "\""));
    CHECK(has(parts.at("docProps/core.xml"), "r" + replacement + "sultats"));
}

TEST_CASE("the numbers of a workbook do not follow the locale of the program", "[results][xlsx][review]")
{
    const DecimalCommaLocale locale;
    const auto parts = partsOf(formatXlsx(namedArray("KAA", {2})));
    INFO("a decimal-comma locale was " << (locale.isSet() ? "set" : "not available: the check is of the format only"));
    const std::string& sheet = parts.at("xl/worksheets/sheet2.xml");
    REQUIRE(has(sheet, "<cols>"));
    const std::string columns = sheet.substr(sheet.find("<cols>"), sheet.find("</cols>") - sheet.find("<cols>"));
    CHECK_FALSE(has(columns, ","));
    CHECK(has(columns, "width=\""));
}

TEST_CASE("a sheet cannot be asked more rows than the format holds", "[results][xlsx][review]")
{
    XlsxWriteOptions options;
    options.maxRowsPerSheet = SHEET_ROWS;
    CHECK_NOTHROW(formatXlsx(namedArray("KAA", {2}), options));
    options.maxRowsPerSheet = SHEET_ROWS + 1;
    CHECK_THROWS(formatXlsx(namedArray("KAA", {2}), options));
}
