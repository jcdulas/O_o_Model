#include "oor/model/cards/nodes/surfaceEdge/SurfaceEdgeTable.hpp"

#include "oor/model/cards/explicit/ExplicitSupport.hpp"

namespace oor::model
{

namespace
{

constexpr int LAST_FIELD = 5; // elementId

bool isState(std::string_view word) noexcept
{
    return word == SurfaceEdgeCard::SMOOTH || word == SurfaceEdgeCard::SHARP || word == SurfaceEdgeCard::RAW;
}

} // namespace

std::optional<SurfaceEdgeCard> SurfaceEdgeFormat::read(FieldReader& reader)
{
    SurfaceEdgeCard card;
    card.id = reader.requiredInteger(1, "id");
    card.node1Id = reader.requiredInteger(2, "node1Id");
    card.node2Id = reader.requiredInteger(3, "node2Id");
    card.state = std::string(reader.word(4));
    card.elementId = reader.integer(5, "elementId", 0);
    if (reader.lastUsedField() > LAST_FIELD)
        reader.error("card.bad-value", "a " + std::string(reader.cardName()) + " has 5 fields", "");
    if (!reader.failed())
        reader.report(check(card));
    return card;
}

std::optional<CardProblem> SurfaceEdgeFormat::check(const SurfaceEdgeCard& card)
{
    if (const auto problem = checkRequiredId(card.id, "id"))
        return problem;
    if (const auto problem = checkRequiredId(card.node1Id, "node1Id"))
        return problem;
    if (const auto problem = checkRequiredId(card.node2Id, "node2Id"))
        return problem;
    if (card.node1Id == card.node2Id)
        return CardProblem{"card.duplicate-node", "the two grid points of the edge must be different", "node1Id"};
    if (card.state.empty())
        return CardProblem{"card.missing-field", "{field} is required: Smooth, Sharp or Raw", "state"};
    if (!isState(card.state))
        return CardProblem{"card.bad-value", "{field} must be Smooth, Sharp or Raw", "state"};
    if (const auto problem = checkOptionalId(card.elementId, "elementId"))
        return problem;
    // A Raw edge is declared whole: there is no side of it to single out.
    if (card.state == SurfaceEdgeCard::RAW && card.elementId != 0)
        return CardProblem{"card.exclusive-fields", "{field} must be blank when {field:state} is Raw", "elementId"};
    return std::nullopt;
}

void SurfaceEdgeFormat::write(const SurfaceEdgeCard& card, FieldWriter& writer)
{
    writer.integer(1, card.id);
    writer.integer(2, card.node1Id);
    writer.integer(3, card.node2Id);
    writer.text(4, card.state);
    writer.integerUnlessDefault(5, card.elementId, 0);
}

std::uint32_t SurfaceEdgeTable::append(const SurfaceEdgeCard& card, base::CardKey key)
{
    const std::uint32_t row = m_rows.append(key);
    m_id.push(card.id);
    m_node1Id.push(card.node1Id);
    m_node2Id.push(card.node2Id);
    m_state.push(card.state);
    m_elementId.push(card.elementId);
    return row;
}

SurfaceEdgeCard SurfaceEdgeTable::card(std::uint32_t row) const
{
    SurfaceEdgeCard card;
    card.id = m_id.get(row);
    card.node1Id = m_node1Id.get(row);
    card.node2Id = m_node2Id.get(row);
    card.state = m_state.get(row);
    card.elementId = m_elementId.get(row);
    return card;
}

void SurfaceEdgeTable::store(std::uint32_t row, const SurfaceEdgeCard& card)
{
    m_id.set(row, card.id);
    m_node1Id.set(row, card.node1Id);
    m_node2Id.set(row, card.node2Id);
    m_state.set(row, card.state);
    m_elementId.set(row, card.elementId);
}

void SurfaceEdgeTable::keepRows(const std::vector<std::uint32_t>& rows)
{
    m_id.keepRows(rows);
    m_node1Id.keepRows(rows);
    m_node2Id.keepRows(rows);
    m_state.keepRows(rows);
    m_elementId.keepRows(rows);
}

void SurfaceEdgeTable::visitReferences(std::uint32_t row, ReferenceVisitor& visitor)
{
    m_node1Id.set(row, visitor.visit("node1Id", ReferenceTarget::Node, m_node1Id.get(row)));
    m_node2Id.set(row, visitor.visit("node2Id", ReferenceTarget::Node, m_node2Id.get(row)));
    // A blank element (0) is the whole edge: it is not looked up.
    if (const base::EntityId element = m_elementId.get(row); element > 0)
        m_elementId.set(row, visitor.visit("elementId", ReferenceTarget::Element, element));
}

} // namespace oor::model
