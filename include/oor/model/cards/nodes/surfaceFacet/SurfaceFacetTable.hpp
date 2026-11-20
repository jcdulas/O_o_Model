#pragma once

#include "oor/model/cards/nodes/surfaceFacet/SurfaceFacetCard.hpp"
#include "oor/model/core/TypedTable.hpp"
#include "oor/model/storage/Column.hpp"

#include <optional>
#include <vector>

namespace oor::model
{

struct SurfaceFacetFormat
{
    // The first thing wrong with the values of a card, if anything (used by read and by editing).
    [[nodiscard]] static std::optional<CardProblem> check(const SurfaceFacetCard& card);
    [[nodiscard]] static std::optional<SurfaceFacetCard> read(FieldReader& reader);
    static void write(const SurfaceFacetCard& card, FieldWriter& writer);
};

// All the SurfaceFacet cards of a model. The ID is the one of the element the card declares flat: it is not an element
// ID of its own, so the card has its own ID space (IdSpace::PerCardType: one SurfaceFacet per element) and refers to an
// element.
class SurfaceFacetTable final : public TypedTable<SurfaceFacetTable, SurfaceFacetCard>
{
public:
    static constexpr std::string_view NAME = "SurfaceFacet";
    static inline const CardTypeInfo INFO{NAME, CardCategory::Other, base::IdSpace::PerCardType};
    using Format = SurfaceFacetFormat;

    [[nodiscard]] static base::EntityId cardId(const SurfaceFacetCard& card) noexcept { return card.elementId; }
    std::uint32_t append(const SurfaceFacetCard& card, base::CardKey key);
    [[nodiscard]] SurfaceFacetCard card(std::uint32_t row) const;
    void store(std::uint32_t row, const SurfaceFacetCard& card);
    void keepRows(const std::vector<std::uint32_t>& rows);

    [[nodiscard]] base::EntityId idAtRow(std::uint32_t row) const { return m_elementId.get(row); }
    void setIdAtRow(std::uint32_t row, base::EntityId id) { m_elementId.set(row, id); }
    void visitReferences(std::uint32_t row, ReferenceVisitor& visitor) override;

    [[nodiscard]] Column<base::EntityId>& elementIdColumn() noexcept { return m_elementId; }

private:
    Column<base::EntityId> m_elementId;
};

} // namespace oor::model
