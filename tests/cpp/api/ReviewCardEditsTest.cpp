// Typed card input and the kind of a field: a card of fixed fields gets each value at the place of its field, a card
// with groups goes through the record mapping of its layout (CardLayout::toSlots), which gives the values of a group
// with a nested list the kind of their field.

#include "oor/api/CardEdits.hpp"
#include "oor/api/Deck.hpp"
#include "oor/base/errors/Errors.hpp"
#include "oor/model/cards/rigid_elements/rigidInterpolation/RigidInterpolationTable.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <string>
#include <vector>

using namespace oor;
using Catch::Matchers::ContainsSubstring;

namespace
{

model::FieldValue integer(std::int64_t value)
{
    return {model::FieldValue::Kind::Integer, value, 0, {}};
}

model::FieldValue real(double value)
{
    return {model::FieldValue::Kind::Real, 0, value, {}};
}

// A RigidInterpolation of two terms, each with the components 123 and two nodes: 2 and 3, then 4 and `lastNode`.
api::CardInput twoTerms(const model::FieldValue& firstWeight, const model::FieldValue& secondWeight,
                        const model::FieldValue& lastNode)
{
    return {"RigidInterpolation",
            {integer(50), integer(1), integer(123), integer(2), firstWeight, integer(123), integer(2), integer(2),
             integer(3), secondWeight, integer(123), integer(2), integer(4), lastNode},
            {}};
}

} // namespace

TEST_CASE("a typed integer given for the weight of a term is the weight of a term of its own", "[api][cards][review]")
{
    const auto deck = api::Deck::createModel();
    const api::AddedCard added = api::insertCard(*deck, twoTerms(real(1), integer(1), integer(5)));
    CHECK(added.id == 50);
    const auto* table = deck->model()->findTable<model::RigidInterpolationTable>();
    REQUIRE(table != nullptr);
    const model::RigidInterpolationCard card = table->card(0);
    REQUIRE(card.groups.size() == 2);
    CHECK(card.groups[0].weight == 1.0);
    CHECK(card.groups[0].nodes == std::vector<base::EntityId>{2, 3});
    CHECK(card.groups[1].weight == 1.0);
    CHECK(card.groups[1].components == 123);
    CHECK(card.groups[1].nodes == std::vector<base::EntityId>{4, 5});
    CHECK(api::cardFields(*deck, "RigidInterpolation", 50) ==
          std::vector<std::string>{"50", "1", "123", "2", "1.", "123", "2", "2", "3", "1.", "123", "2", "4", "5"});
}

TEST_CASE("a typed real given for a node of a term is refused with the field named", "[api][cards][review]")
{
    const auto deck = api::Deck::createModel();
    const api::CardInput card = twoTerms(real(1), real(1), real(5));
    CHECK_THROWS_AS(api::insertCard(*deck, card), base::UsageError);
    CHECK_THROWS_WITH(api::insertCard(*deck, card), ContainsSubstring("RigidInterpolation") &&
                                                        ContainsSubstring("node") &&
                                                        ContainsSubstring("takes an integer"));
    CHECK(deck->cardCount() == 0);
}

TEST_CASE("a typed integer given for a real field of a simple group is read as that real", "[api][cards][review]")
{
    const auto deck = api::Deck::createModel();
    // The scale factor of the combination and the one of its term, both given as integers.
    api::insertCard(*deck, {"LoadCombination", {integer(40), integer(2), integer(1), integer(3)}, {}});
    CHECK(api::cardFields(*deck, "LoadCombination", 40) == std::vector<std::string>{"40", "2.", "1.", "3"});
    // A real given for the load set of the term: the card reader refuses it and names the field.
    const api::CardInput bad{"LoadCombination", {integer(41), real(2), real(1), real(3)}, {}};
    CHECK_THROWS_AS(api::insertCard(*deck, bad), base::UsageError);
    CHECK_THROWS_WITH(api::insertCard(*deck, bad), ContainsSubstring("loadSetId") && ContainsSubstring("integer"));
    CHECK(deck->cardCount() == 1);
}

TEST_CASE("a card of fixed fields gives a typed value the kind of its field", "[api][cards][review]")
{
    const auto deck = api::Deck::createModel();
    // Integers given for the coordinates of a node are reals.
    api::insertCard(*deck, {"Node", {integer(7), {}, integer(3), integer(1), integer(2)}, {}});
    CHECK(api::cardFields(*deck, "Node", 7) == std::vector<std::string>{"7", "", "3.", "1.", "2."});
    // A real given for an identifier is refused with the field named.
    const api::CardInput bad{"Node", {real(7.5), {}, real(3), real(1), real(2)}, {}};
    CHECK_THROWS_AS(api::insertCard(*deck, bad), base::UsageError);
    CHECK_THROWS_WITH(api::insertCard(*deck, bad), ContainsSubstring("Node.id") && ContainsSubstring("integer"));
    // Two alternatives have a field each: a typed value is the alternative of the field it is given for, so an
    // integer given for the material angle is the angle and an integer given for the material frame is the frame.
    const api::CardInput byAngle{
        "ShellQuad4", {integer(12), integer(101), integer(1), integer(2), integer(3), integer(4), integer(30)}, {}};
    api::insertCard(*deck, byAngle);
    CHECK(api::cardFields(*deck, "ShellQuad4", 12) ==
          std::vector<std::string>{"12", "101", "1", "2", "3", "4", "30."});
    const api::CardInput byFrame{
        "ShellQuad4", {integer(13), integer(101), integer(1), integer(2), integer(3), integer(4), {}, integer(30)}, {}};
    api::insertCard(*deck, byFrame);
    CHECK(api::cardFields(*deck, "ShellQuad4", 13) ==
          std::vector<std::string>{"13", "101", "1", "2", "3", "4", "", "30"});
}
