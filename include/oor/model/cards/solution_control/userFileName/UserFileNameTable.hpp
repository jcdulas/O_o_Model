#pragma once

#include "oor/model/cards/solution_control/userFileName/UserFileNameCard.hpp"
#include "oor/model/core/TypedTable.hpp"
#include "oor/model/storage/CardRows.hpp"
#include "oor/model/storage/Column.hpp"

#include <optional>
#include <vector>

namespace oor::model
{

struct UserFileNameFormat
{
    // The first thing wrong with the values of a card, if anything (used by read and by editing).
    [[nodiscard]] static std::optional<CardProblem> check(const UserFileNameCard& card);
    [[nodiscard]] static std::optional<UserFileNameCard> read(FieldReader& reader);
    static void write(const UserFileNameCard& card, FieldWriter& writer);
};

// All the UserFileName cards. The UDID is unique among them (IdSpace::PerCardType) and is what a FatigueLoad, a
// TableTimeHistoryFile, a MicromechanicsCompositeMat and a ResultFileModules name: the category UserDefinedName. An
// UserFileName names no other card. The cards are kept whole (CardRows) next to their ID: the name is a text of any
// length, and the query engine reads the ID.
class UserFileNameTable final : public TypedTable<UserFileNameTable, UserFileNameCard>
{
public:
    static constexpr std::string_view NAME = "UserFileName";
    static inline const CardTypeInfo INFO{NAME, CardCategory::UserDefinedName, base::IdSpace::PerCardType};
    using Format = UserFileNameFormat;

    [[nodiscard]] static base::EntityId cardId(const UserFileNameCard& card) noexcept { return card.id; }
    std::uint32_t append(const UserFileNameCard& card, base::CardKey key);
    [[nodiscard]] UserFileNameCard card(std::uint32_t row) const { return m_cards.get(row); }
    void store(std::uint32_t row, const UserFileNameCard& card);
    void keepRows(const std::vector<std::uint32_t>& rows);

    [[nodiscard]] base::EntityId idAtRow(std::uint32_t row) const { return m_id.get(row); }
    void setIdAtRow(std::uint32_t row, base::EntityId id);
    void visitReferences(std::uint32_t, ReferenceVisitor&) override {} // a UserFileName refers to no other card

    [[nodiscard]] Column<base::EntityId>& idColumn() noexcept { return m_id; }

private:
    Column<base::EntityId> m_id;
    CardRows<UserFileNameCard> m_cards;
};

} // namespace oor::model
