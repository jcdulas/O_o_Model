#include "oor/model/core/CardRecord.hpp"

#include "oor/base/errors/Errors.hpp"
#include "oor/deck/records/RecordText.hpp"
#include "oor/model/core/UnknownCardTable.hpp"

namespace oor::model
{
// The record of one card: its neutral name, then the fields of its layout.
std::vector<std::string> cardValues(const Model& model, const CardTable& table, std::uint16_t type, std::uint32_t row,
                                    const CardLayouts& layouts, bool omitDefaults)
{
    if (type == CardRegistry::UNKNOWN_TYPE)
    {
        // A card the library does not know, or could not read, keeps its name and its fields as they were.
        const auto& unknown = static_cast<const UnknownCardTable&>(table);
        std::vector<std::string> values{std::string(unknown.nameAt(row).view())};
        for (std::string& field : unknown.fieldsAt(row))
            values.push_back(std::move(field));
        return values;
    }
    const std::string_view name = CardRegistry::instance().entry(type).info.name;
    const CardLayout* layout = layouts.find(name);
    if (layout == nullptr)
        throw base::UsageError("the card " + std::string(name) + " has no layout in the card catalogue");
    // Exact reals, the defaults left blank, the sign of a zero kept: what reads back to the same card.
    FieldWriter writer(omitDefaults, 0, false, table.fieldsGovernedByDefaults(model));
    writer.keepSignOfZero(true);
    table.writeCard(row, writer);
    std::vector<std::string> slots = writer.fields();
    std::vector<SlotKind> kinds(slots.size(), SlotKind::Blank);
    for (std::size_t index = 0; index < slots.size(); ++index)
    {
        const int field = static_cast<int>(index) + 1;
        if (slots[index].empty())
            continue;
        kinds[index] = writer.holdsReal(field)     ? SlotKind::Real
                       : writer.holdsNumber(field) ? SlotKind::Integer
                                                   : SlotKind::Text;
        if (kinds[index] == SlotKind::Real)
            slots[index] = deck::RecordText::realText(std::move(slots[index]));
    }
    std::vector<std::string> values;
    std::string problem;
    if (!layout->toValues(slots, kinds, values, problem))
        throw base::UsageError("a " + std::string(name) + " " + std::to_string(table.idAt(row)) +
                               " cannot be written as a record: " + problem);
    values.insert(values.begin(), std::string(name));
    return values;
}

std::string cardRecord(const Model& model, CardLocation location, const CardLayouts& layouts)
{
    const CardTable* table = model.findTable(location.table);
    if (table == nullptr)
        return {};
    return deck::RecordText::format(cardValues(model, *table, location.table, location.row, layouts, true));
}

} // namespace oor::model
