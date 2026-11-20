#pragma once

#include "oor/model/cards/nodes/surfaceEdge/SurfaceEdgeCard.hpp"
#include "oor/model/core/TypedTable.hpp"
#include "oor/model/storage/Column.hpp"

#include <optional>
#include <string>
#include <vector>

namespace oor::model
{

struct SurfaceEdgeFormat
{
    // The first thing wrong with the values of a card, if anything (used by read and by editing).
    [[nodiscard]] static std::optional<CardProblem> check(const SurfaceEdgeCard& card);
    [[nodiscard]] static std::optional<SurfaceEdgeCard> read(FieldReader& reader);
    static void write(const SurfaceEdgeCard& card, FieldWriter& writer);
};

// All the SurfaceEdge cards of a model. The ID is the card's own, unique per card type (IdSpace::PerCardType). The two
// grid points of the edge are references to nodes and the element, when the card names one, a reference to an element
// of any type.
class SurfaceEdgeTable final : public TypedTable<SurfaceEdgeTable, SurfaceEdgeCard>
{
public:
    static constexpr std::string_view NAME = "SurfaceEdge";
    static inline const CardTypeInfo INFO{NAME, CardCategory::Other, base::IdSpace::PerCardType};
    using Format = SurfaceEdgeFormat;

    [[nodiscard]] static base::EntityId cardId(const SurfaceEdgeCard& card) noexcept { return card.id; }
    std::uint32_t append(const SurfaceEdgeCard& card, base::CardKey key);
    [[nodiscard]] SurfaceEdgeCard card(std::uint32_t row) const;
    void store(std::uint32_t row, const SurfaceEdgeCard& card);
    void keepRows(const std::vector<std::uint32_t>& rows);

    [[nodiscard]] base::EntityId idAtRow(std::uint32_t row) const { return m_id.get(row); }
    void setIdAtRow(std::uint32_t row, base::EntityId id) { m_id.set(row, id); }
    void visitReferences(std::uint32_t row, ReferenceVisitor& visitor) override;

    [[nodiscard]] Column<base::EntityId>& idColumn() noexcept { return m_id; }
    [[nodiscard]] Column<base::EntityId>& node1IdColumn() noexcept { return m_node1Id; }
    [[nodiscard]] Column<base::EntityId>& node2IdColumn() noexcept { return m_node2Id; }
    [[nodiscard]] Column<std::string>& stateColumn() noexcept { return m_state; }
    [[nodiscard]] Column<base::EntityId>& elementIdColumn() noexcept { return m_elementId; }

private:
    Column<base::EntityId> m_id;
    Column<base::EntityId> m_node1Id;
    Column<base::EntityId> m_node2Id;
    Column<std::string> m_state;
    Column<base::EntityId> m_elementId;
};

} // namespace oor::model
