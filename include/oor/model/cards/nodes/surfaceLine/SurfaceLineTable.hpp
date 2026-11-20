#pragma once

#include "oor/model/cards/nodes/surfaceLine/SurfaceLineCard.hpp"
#include "oor/model/core/TypedTable.hpp"
#include "oor/model/storage/Column.hpp"

#include <optional>
#include <vector>

namespace oor::model
{

struct SurfaceLineFormat
{
    // The first thing wrong with the values of a card, if anything (used by read and by editing).
    [[nodiscard]] static std::optional<CardProblem> check(const SurfaceLineCard& card);
    [[nodiscard]] static std::optional<SurfaceLineCard> read(FieldReader& reader);
    static void write(const SurfaceLineCard& card, FieldWriter& writer);
};

// All the SurfaceLine cards of a model. The ID is the card's own, unique per card type (IdSpace::PerCardType). The grid
// points are references to nodes; a blank last grid point (0, the mesh line ends) is not one.
class SurfaceLineTable final : public TypedTable<SurfaceLineTable, SurfaceLineCard>
{
public:
    static constexpr std::string_view NAME = "SurfaceLine";
    static inline const CardTypeInfo INFO{NAME, CardCategory::Other, base::IdSpace::PerCardType};
    using Format = SurfaceLineFormat;

    [[nodiscard]] static base::EntityId cardId(const SurfaceLineCard& card) noexcept { return card.id; }
    std::uint32_t append(const SurfaceLineCard& card, base::CardKey key);
    [[nodiscard]] SurfaceLineCard card(std::uint32_t row) const;
    void store(std::uint32_t row, const SurfaceLineCard& card);
    void keepRows(const std::vector<std::uint32_t>& rows);

    [[nodiscard]] base::EntityId idAtRow(std::uint32_t row) const { return m_id.get(row); }
    void setIdAtRow(std::uint32_t row, base::EntityId id) { m_id.set(row, id); }
    void visitReferences(std::uint32_t row, ReferenceVisitor& visitor) override;

    [[nodiscard]] Column<base::EntityId>& idColumn() noexcept { return m_id; }
    [[nodiscard]] Column<base::EntityId>& node1IdColumn() noexcept { return m_node1Id; }
    [[nodiscard]] Column<base::EntityId>& throughNodeIdColumn() noexcept { return m_throughNodeId; }
    [[nodiscard]] Column<base::EntityId>& node2IdColumn() noexcept { return m_node2Id; }

private:
    Column<base::EntityId> m_id;
    Column<base::EntityId> m_node1Id;
    Column<base::EntityId> m_throughNodeId;
    Column<base::EntityId> m_node2Id;
};

} // namespace oor::model
