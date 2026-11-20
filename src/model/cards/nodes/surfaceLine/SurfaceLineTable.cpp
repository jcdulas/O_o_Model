#include "oor/model/cards/nodes/surfaceLine/SurfaceLineTable.hpp"

#include "oor/model/cards/explicit/ExplicitSupport.hpp"

namespace oor::model
{

namespace
{

constexpr int LAST_FIELD = 4; // node2Id

} // namespace

std::optional<SurfaceLineCard> SurfaceLineFormat::read(FieldReader& reader)
{
    SurfaceLineCard card;
    card.id = reader.requiredInteger(1, "id");
    card.node1Id = reader.requiredInteger(2, "node1Id");
    card.throughNodeId = reader.requiredInteger(3, "throughNodeId");
    card.node2Id = reader.integer(4, "node2Id", 0);
    if (reader.lastUsedField() > LAST_FIELD)
        reader.error("card.bad-value", "a " + std::string(reader.cardName()) + " has 4 fields", "");
    if (!reader.failed())
        reader.report(check(card));
    return card;
}

std::optional<CardProblem> SurfaceLineFormat::check(const SurfaceLineCard& card)
{
    if (const auto problem = checkRequiredId(card.id, "id"))
        return problem;
    if (const auto problem = checkRequiredId(card.node1Id, "node1Id"))
        return problem;
    if (const auto problem = checkRequiredId(card.throughNodeId, "throughNodeId"))
        return problem;
    if (card.node1Id == card.throughNodeId)
        return CardProblem{"card.duplicate-node", "{field} and {field:throughNodeId} must be different", "node1Id"};
    if (const auto problem = checkOptionalId(card.node2Id, "node2Id"))
        return problem;
    // A blank node2Id (0) is the end of the mesh line; a given one is a third grid point.
    if (card.node2Id != 0 && (card.node2Id == card.node1Id || card.node2Id == card.throughNodeId))
        return CardProblem{"card.duplicate-node",
                           "{field} must be different from {field:node1Id} and {field:throughNodeId}", "node2Id"};
    return std::nullopt;
}

void SurfaceLineFormat::write(const SurfaceLineCard& card, FieldWriter& writer)
{
    writer.integer(1, card.id);
    writer.integer(2, card.node1Id);
    writer.integer(3, card.throughNodeId);
    writer.integerUnlessDefault(4, card.node2Id, 0);
}

std::uint32_t SurfaceLineTable::append(const SurfaceLineCard& card, base::CardKey key)
{
    const std::uint32_t row = m_rows.append(key);
    m_id.push(card.id);
    m_node1Id.push(card.node1Id);
    m_throughNodeId.push(card.throughNodeId);
    m_node2Id.push(card.node2Id);
    return row;
}

SurfaceLineCard SurfaceLineTable::card(std::uint32_t row) const
{
    return SurfaceLineCard{m_id.get(row), m_node1Id.get(row), m_throughNodeId.get(row), m_node2Id.get(row)};
}

void SurfaceLineTable::store(std::uint32_t row, const SurfaceLineCard& card)
{
    m_id.set(row, card.id);
    m_node1Id.set(row, card.node1Id);
    m_throughNodeId.set(row, card.throughNodeId);
    m_node2Id.set(row, card.node2Id);
}

void SurfaceLineTable::keepRows(const std::vector<std::uint32_t>& rows)
{
    m_id.keepRows(rows);
    m_node1Id.keepRows(rows);
    m_throughNodeId.keepRows(rows);
    m_node2Id.keepRows(rows);
}

void SurfaceLineTable::visitReferences(std::uint32_t row, ReferenceVisitor& visitor)
{
    m_node1Id.set(row, visitor.visit("node1Id", ReferenceTarget::Node, m_node1Id.get(row)));
    m_throughNodeId.set(row, visitor.visit("throughNodeId", ReferenceTarget::Node, m_throughNodeId.get(row)));
    // A blank last grid point (0) is the end of the mesh line: it is not looked up.
    if (const base::EntityId node = m_node2Id.get(row); node > 0)
        m_node2Id.set(row, visitor.visit("node2Id", ReferenceTarget::Node, node));
}

} // namespace oor::model
