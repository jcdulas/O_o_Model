// Checks of the fields that hold a set of digits as one integer (the components of a degree-of-freedom list, pin
// flags, permanent constraints): the value as written is judged before its digits are sorted, so a digit given twice
// or a zero among other digits is an error and not a smaller set, and a valid set still comes out sorted.

#include "oor/model/cards/constraints/singlePointConstr/SinglePointConstrTable.hpp"
#include "oor/model/cards/constraints/singlePointConstrList/SinglePointConstrListTable.hpp"
#include "oor/model/cards/elements/bar2/Bar2Table.hpp"
#include "oor/model/cards/nodes/node/NodeTable.hpp"
#include "oor/model/cards/rigid_elements/rigidBodyStar/RigidBodyStarTable.hpp"
#include "oor/model/cards/sets/analysisDofSet/AnalysisDofSetTable.hpp"
#include "oor/model/format/DigitSetField.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <cstdint>
#include <string>

using namespace oor;
using namespace oor::model;
using oor::testing::readModelText;

namespace
{

template <typename TableT>
typename TableT::CardType cardAt(const Model& model, std::uint32_t row = 0)
{
    return model.findTable<TableT>()->card(row);
}

template <typename TableT>
std::size_t rowCount(const Model& model)
{
    const TableT* table = model.findTable<TableT>();
    return table == nullptr ? 0 : table->rows().rowCount();
}

// The record is refused in strict mode; in tolerant mode its first error is a bad value of `field` and the card is not
// kept in its table.
template <typename TableT>
void requireRefused(const std::string& record, const std::string& field)
{
    INFO(record);
    REQUIRE_THROWS_AS(readModelText(record, true), base::DeckError);
    const Model tolerant = readModelText(record, false);
    REQUIRE(tolerant.diagnostics().hasErrors());
    const auto error = tolerant.diagnostics().firstError();
    REQUIRE(error.has_value());
    INFO(error->message);
    REQUIRE(error->code == "card.bad-value");
    REQUIRE(error->location.fieldName == field);
    REQUIRE(rowCount<TableT>(tolerant) == 0);
}

// What the sort would hide, judged on the value as written.
static_assert(hasRepeatedOrZeroDigit(10));
static_assert(hasRepeatedOrZeroDigit(1203));
static_assert(hasRepeatedOrZeroDigit(1123));
static_assert(hasRepeatedOrZeroDigit(66));
static_assert(!hasRepeatedOrZeroDigit(1));
static_assert(!hasRepeatedOrZeroDigit(321));
static_assert(!hasRepeatedOrZeroDigit(123456));
static_assert(!hasRepeatedOrZeroDigit(17)); // a digit out of the range of a field is the card's own check

} // namespace

TEST_CASE("the components of a SinglePointConstrList are refused with a zero among them or a digit twice",
          "[model][cards]")
{
    // `10` is not component 1 and `1123` is not the components 1, 2 and 3.
    requireRefused<SinglePointConstrListTable>("SinglePointConstrList;7;10;5", "components");
    requireRefused<SinglePointConstrListTable>("SinglePointConstrList;7;1123;5", "components");
    requireRefused<SinglePointConstrListTable>("SinglePointConstrList;7;1203;5", "components");

    // The message gives the value as it was written.
    const Model tolerant = readModelText("SinglePointConstrList;7;1123;5", false);
    const auto error = tolerant.diagnostics().firstError();
    REQUIRE(error.has_value());
    REQUIRE(error->message.find("1123") != std::string::npos);

    // A digit out of range is still the card's own error, on the same field.
    requireRefused<SinglePointConstrListTable>("SinglePointConstrList;7;17;5", "components");
}

TEST_CASE("valid components of a SinglePointConstrList are kept, sorted", "[model][cards]")
{
    const Model model = readModelText(
        "SinglePointConstrList;7;321;5\n"
        "SinglePointConstrList;8;123456;5\n"
        "SinglePointConstrList;9;0;5\n"
        "SinglePointConstrList;10;4;5\n",
        true);
    REQUIRE_FALSE(model.diagnostics().hasErrors());
    REQUIRE(rowCount<SinglePointConstrListTable>(model) == 4);
    REQUIRE(cardAt<SinglePointConstrListTable>(model, 0).components == 123);
    REQUIRE(cardAt<SinglePointConstrListTable>(model, 1).components == 123456);
    REQUIRE(cardAt<SinglePointConstrListTable>(model, 2).components == 0); // scalar points
    REQUIRE(cardAt<SinglePointConstrListTable>(model, 3).components == 4);
}

TEST_CASE("the components of a SinglePointConstr may be 0 or blank, and are refused with a digit twice",
          "[model][cards]")
{
    const Model model = readModelText(
        "SinglePointConstr;2;27;0;-1.4\n"
        "SinglePointConstr;3;27;;-1.4;5;654;0.5\n",
        true);
    REQUIRE_FALSE(model.diagnostics().hasErrors());
    REQUIRE(cardAt<SinglePointConstrTable>(model, 0).components[0] == 0);
    REQUIRE(cardAt<SinglePointConstrTable>(model, 1).components[0] == 0);
    REQUIRE(cardAt<SinglePointConstrTable>(model, 1).components[1] == 456);

    requireRefused<SinglePointConstrTable>("SinglePointConstr;2;27;33;-1.4", "components1");
    requireRefused<SinglePointConstrTable>("SinglePointConstr;3;27;3;-1.4;5;4506;0.5", "components2");
}

TEST_CASE("the permanent constraints of a Node are refused with a zero among them and kept sorted when valid",
          "[model][cards]")
{
    requireRefused<NodeTable>("Node;7;;0.;0.;0.;;1203", "permanentConstraints");
    requireRefused<NodeTable>("Node;7;;0.;0.;0.;;1223", "permanentConstraints");

    const Model model = readModelText(
        "Node;7;;0.;0.;0.;;321\n"
        "Node;8;;1.;0.;0.\n"
        "Node;9;;2.;0.;0.;;0\n",
        true);
    REQUIRE_FALSE(model.diagnostics().hasErrors());
    REQUIRE(rowCount<NodeTable>(model) == 3);
    REQUIRE(cardAt<NodeTable>(model, 0).permanentConstraints == 123);
    REQUIRE(cardAt<NodeTable>(model, 1).permanentConstraints == 0);
    REQUIRE(cardAt<NodeTable>(model, 2).permanentConstraints == 0);
}

TEST_CASE("the dependent components of a RigidBodyStar are refused with a zero among them or a digit twice",
          "[model][cards]")
{
    requireRefused<RigidBodyStarTable>("RigidBodyStar;7;1;1203;2", "dependentComponents");
    requireRefused<RigidBodyStarTable>("RigidBodyStar;7;1;1223;2", "dependentComponents");

    const Model model = readModelText("RigidBodyStar;7;1;321;2", true);
    REQUIRE_FALSE(model.diagnostics().hasErrors());
    REQUIRE(cardAt<RigidBodyStarTable>(model).components == 123);
}

TEST_CASE("the pin flags of a Bar2 are refused with a zero among them or a digit twice", "[model][cards]")
{
    requireRefused<Bar2Table>("Bar2;1;1;1;2;0.;;0.;1.;;4456", "pinFlagsA");
    requireRefused<Bar2Table>("Bar2;1;1;1;2;0.;;0.;1.;;;60", "pinFlagsB");

    const Model model = readModelText("Bar2;1;1;1;2;0.;;0.;1.;;654;21", true);
    REQUIRE_FALSE(model.diagnostics().hasErrors());
    REQUIRE(cardAt<Bar2Table>(model).pinFlagsA == 456);
    REQUIRE(cardAt<Bar2Table>(model).pinFlagsB == 12);
}

TEST_CASE("the components of a pair of a degree-of-freedom set are judged as written too", "[model][cards]")
{
    // The pairs are read by a helper that several sets share; the field name carries the number of the pair.
    requireRefused<AnalysisDofSetTable>("AnalysisDofSet;1;1203", "components1");
    requireRefused<AnalysisDofSetTable>("AnalysisDofSet;1;123;2;455", "components2");

    const Model model = readModelText("AnalysisDofSet;1;321;2;0;3;6", true);
    REQUIRE_FALSE(model.diagnostics().hasErrors());
    const AnalysisDofSetCard card = cardAt<AnalysisDofSetTable>(model);
    REQUIRE(card.dofs.size() == 3);
    REQUIRE(card.dofs[0].components == 123);
    REQUIRE(card.dofs[1].components == 0);
    REQUIRE(card.dofs[2].components == 6);
}
