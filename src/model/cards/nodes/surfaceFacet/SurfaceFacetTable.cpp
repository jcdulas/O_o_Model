#include "oor/model/cards/nodes/surfaceFacet/SurfaceFacetTable.hpp"

#include "oor/model/cards/explicit/ExplicitSupport.hpp"

namespace oor::model
{

namespace
{

constexpr int LAST_FIELD = 1; // elementId

} // namespace

std::optional<SurfaceFacetCard> SurfaceFacetFormat::read(FieldReader& reader)
{
    SurfaceFacetCard card;
    card.elementId = reader.requiredInteger(1, "elementId");
    if (reader.lastUsedField() > LAST_FIELD)
        reader.error("card.bad-value", "a " + std::string(reader.cardName()) + " has 1 field", "");
    if (!reader.failed())
        reader.report(check(card));
    return card;
}

std::optional<CardProblem> SurfaceFacetFormat::check(const SurfaceFacetCard& card)
{
    return checkRequiredId(card.elementId, "elementId");
}

void SurfaceFacetFormat::write(const SurfaceFacetCard& card, FieldWriter& writer)
{
    writer.integer(1, card.elementId);
}

std::uint32_t SurfaceFacetTable::append(const SurfaceFacetCard& card, base::CardKey key)
{
    const std::uint32_t row = m_rows.append(key);
    m_elementId.push(card.elementId);
    return row;
}

SurfaceFacetCard SurfaceFacetTable::card(std::uint32_t row) const
{
    return SurfaceFacetCard{m_elementId.get(row)};
}

void SurfaceFacetTable::store(std::uint32_t row, const SurfaceFacetCard& card)
{
    m_elementId.set(row, card.elementId);
}

void SurfaceFacetTable::keepRows(const std::vector<std::uint32_t>& rows)
{
    m_elementId.keepRows(rows);
}

void SurfaceFacetTable::visitReferences(std::uint32_t row, ReferenceVisitor& visitor)
{
    // The ID is the one of the element the card declares flat.
    m_elementId.set(row, visitor.visit("elementId", ReferenceTarget::Element, m_elementId.get(row)));
}

} // namespace oor::model
