// A record says which field each of its values is for; the slots of a card do not. In a group with a nested list (the
// terms of a RigidInterpolation: a weight, components, then nodes) the card reader has only the kind of a slot text to
// tell a weight from one more node, so CardLayout::toSlots writes the values of such a group with the kind of their
// field. Everywhere else a value goes to its slot as the record writes it and the card reader checks it.

#include "oor/base/errors/Errors.hpp"
#include "oor/base/text/NumberParser.hpp"
#include "oor/model/cards/elements/shellQuad4/ShellQuad4Table.hpp"
#include "oor/model/cards/nodes/node/NodeTable.hpp"
#include "oor/model/cards/rigid_elements/rigidInterpolation/RigidInterpolationTable.hpp"
#include "oor/model/format/CardLayouts.hpp"
#include "oor/model/format/SignificantDigits.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

using namespace oor;
using namespace oor::model;
using Catch::Matchers::ContainsSubstring;
using oor::testing::readModelText;
using oor::testing::writeModelText;

namespace
{

// The slot texts of a card given by the filled slots (slot 1 is the first field after the name).
std::vector<std::string> slotsOf(std::initializer_list<std::pair<int, const char*>> filled)
{
    std::vector<std::string> slots;
    for (const auto& [slot, text] : filled)
    {
        if (slots.size() < static_cast<std::size_t>(slot))
            slots.resize(static_cast<std::size_t>(slot));
        slots[static_cast<std::size_t>(slot - 1)] = text;
    }
    return slots;
}

const CardLayout& layoutOf(const char* card)
{
    const CardLayout* layout = CardLayouts::standard()->find(card);
    REQUIRE(layout != nullptr);
    return *layout;
}

// The problem toSlots reports for a record it refuses.
std::string refusalOf(const CardLayout& layout, const std::vector<std::string>& values)
{
    std::vector<std::string> slots;
    std::string problem;
    REQUIRE_FALSE(layout.toSlots(values, slots, problem));
    return problem;
}

// Two terms, each with the weight 1, the components 123 and two nodes; the second weight is written as an integer.
const std::vector<std::string> TWO_TERMS{"50", "50", "123", "2", "1.", "123", "2", "2", "3", "1", "123", "2", "4", "5"};

} // namespace

TEST_CASE("an integer given for the weight of a term goes to its slot as a real", "[model][layouts][review]")
{
    const CardLayout& layout = layoutOf("RigidInterpolation");
    std::vector<std::string> slots;
    std::string problem;
    REQUIRE(layout.toSlots(TWO_TERMS, slots, problem));
    CHECK(slots == slotsOf({{1, "50"},
                            {3, "50"},
                            {4, "123"},
                            {5, "1."},
                            {6, "123"},
                            {7, "2"},
                            {8, "3"},
                            {9, "1."},
                            {10, "123"},
                            {11, "4"},
                            {12, "5"}}));
    // The slots give the two terms back: the nested lists end where the second weight starts.
    std::vector<std::string> back;
    REQUIRE(layout.toValues(slots, {}, back, problem));
    std::vector<std::string> expected = TWO_TERMS;
    expected[9] = "1.";
    CHECK(back == expected);
}

TEST_CASE("the real written for an integer weight keeps its sign and its significant digits",
          "[model][layouts][review]")
{
    const CardLayout& layout = layoutOf("RigidInterpolation");
    std::vector<std::string> slots;
    std::string problem;
    // Three terms of one node each, with the weights -3, +2 and 100.
    const std::vector<std::string> values{"50", "50",  "123", "3", "-3",  "123", "1", "2",
                                          "+2", "123", "1",   "4", "100", "123", "1", "6"};
    REQUIRE(layout.toSlots(values, slots, problem));
    REQUIRE(slots.size() == 13);
    CHECK(slots[4] == "-3.");
    CHECK(slots[7] == "+2.");
    CHECK(slots[10] == "100.");
    for (const std::size_t weight : {std::size_t{4}, std::size_t{7}, std::size_t{10}})
    {
        INFO(slots[weight]);
        CHECK_FALSE(base::NumberParser::parseInteger(slots[weight]).has_value());
        CHECK(base::NumberParser::parseReal(slots[weight]).has_value());
    }
    CHECK(base::NumberParser::parseReal(slots[4]).value_or(0.0) == -3.0);
    CHECK(base::NumberParser::parseReal(slots[7]).value_or(0.0) == 2.0);
    // The precision noted for the field is the one of the value as the record wrote it.
    CHECK(significantDigitsOf("-3.") == significantDigitsOf("-3"));
    CHECK(significantDigitsOf("100.") == significantDigitsOf("100"));
}

TEST_CASE("a real given for a node or for the components of a term is refused with the field named",
          "[model][layouts][review]")
{
    const CardLayout& layout = layoutOf("RigidInterpolation");
    // The second node is written as a real: in the slots it would start a term of its own.
    const std::string node = refusalOf(layout, {"50", "50", "123", "1", "1.", "123", "2", "2", "3."});
    CHECK_THAT(node, ContainsSubstring("node") && ContainsSubstring("\"3.\"") && ContainsSubstring("integer") &&
                         ContainsSubstring("RigidInterpolation"));
    const std::string exponent = refusalOf(layout, {"50", "50", "123", "1", "1.", "123", "2", "2", "3e0"});
    CHECK_THAT(exponent, ContainsSubstring("node") && ContainsSubstring("\"3e0\""));
    const std::string components = refusalOf(layout, {"50", "50", "123", "1", "1.", "123.", "1", "2"});
    CHECK_THAT(components, ContainsSubstring("components") && ContainsSubstring("\"123.\""));
}

TEST_CASE("blank values, words and the sections of a card with terms stay as the record writes them",
          "[model][layouts][review]")
{
    const CardLayout& layout = layoutOf("RigidInterpolation");
    std::vector<std::string> slots;
    std::string problem;
    // A blank node between two nodes, then the dependent degrees of freedom on the next line.
    REQUIRE(layout.toSlots(std::vector<std::string>{"50", "50", "123", "1", "0.5", "123", "3", "2", "", "3",
                                                    "DependentDofs", "1", "7", "12"},
                           slots, problem));
    CHECK(slots == slotsOf({{1, "50"},
                            {3, "50"},
                            {4, "123"},
                            {5, "0.5"},
                            {6, "123"},
                            {7, "2"},
                            {9, "3"},
                            {17, "DependentDofs"},
                            {18, "7"},
                            {19, "12"}}));
    // A word where a number goes is left to the card reader, which reports it with the name of the field.
    REQUIRE(layout.toSlots(std::vector<std::string>{"50", "50", "123", "1", "heavy", "123", "1", "Through"}, slots,
                           problem));
    REQUIRE(slots.size() == 7);
    CHECK(slots[4] == "heavy");
    CHECK(slots[6] == "Through");
}

TEST_CASE("an integer given for the real one of two alternatives stays an integer", "[model][layouts][review]")
{
    // docs/model-format.md: where an integer and a real are alternatives, the decimal point decides.
    const CardLayout& layout = layoutOf("ShellQuad4");
    std::vector<std::string> slots;
    std::string problem;
    REQUIRE(layout.toSlots(std::vector<std::string>{"12", "101", "1", "2", "3", "4", "30"}, slots, problem));
    REQUIRE(slots.size() == 7);
    CHECK(slots[6] == "30");
    REQUIRE(layout.toSlots(std::vector<std::string>{"12", "101", "1", "2", "3", "4", "30."}, slots, problem));
    CHECK(slots[6] == "30.");

    const Model model = readModelText("ShellQuad4;12;101;1;2;3;4;30\nShellQuad4;13;101;1;2;3;4;30.\n", true);
    const ShellQuad4Table& table = *model.findTable<ShellQuad4Table>();
    const ShellQuad4Card byFrame = table.card(model.locate(base::IdSpace::Element, 12)->row);
    CHECK(byFrame.usesMaterialSystem());
    CHECK(byFrame.matFrameId == 30);
    const ShellQuad4Card byAngle = table.card(model.locate(base::IdSpace::Element, 13)->row);
    CHECK_FALSE(byAngle.usesMaterialSystem());
    CHECK(byAngle.thetaInDegrees == 30.0);
}

TEST_CASE("the values of the other groups and lists go to their slots as written", "[model][layouts][review]")
{
    std::vector<std::string> slots;
    std::string problem;
    // A list of nodes of kind `any`: numbers, a blank and the word of a range.
    REQUIRE(layoutOf("AccelNodeLoad")
                .toSlots(std::vector<std::string>{"1", "", "9.81", "0.", "0.", "1.", "5", "Through", "9", "", "12"},
                         slots, problem));
    CHECK(slots == slotsOf({{1, "1"},
                            {3, "9.81"},
                            {4, "0."},
                            {5, "0."},
                            {6, "1."},
                            {9, "5"},
                            {10, "Through"},
                            {11, "9"},
                            {13, "12"}}));
    // The fifth field of a region of a ComplexEigenMethod is a real width or, for the block method, an integer number
    // of steps that its card reader reads as an integer: the value must reach the slot as the record writes it.
    REQUIRE(layoutOf("ComplexEigenMethod")
                .toSlots(std::vector<std::string>{"2", "ComplexLanczos", "", "", "", "", "", "0.", "6.", "12.", "4.",
                                                  "7", "", "5"},
                         slots, problem));
    REQUIRE(slots.size() == 15);
    CHECK(slots[12] == "7");
    CHECK(slots[14] == "5");
}

TEST_CASE("a term whose weight is written as an integer is read as a term of its own", "[model][model-file][review]")
{
    const Model model = readModelText("RigidInterpolation;50;50;123;2;1.;123;2;2;3;1;123;2;4;5\n", true);
    const RigidInterpolationTable* table = model.findTable<RigidInterpolationTable>();
    REQUIRE(table != nullptr);
    REQUIRE(table->rows().rowCount() == 1);
    const RigidInterpolationCard card = table->card(0);
    REQUIRE(card.groups.size() == 2);
    CHECK(card.groups[0].weight == 1.0);
    CHECK(card.groups[0].components == 123);
    CHECK(card.groups[0].nodes == std::vector<base::EntityId>{2, 3});
    CHECK(card.groups[1].weight == 1.0);
    CHECK(card.groups[1].components == 123);
    CHECK(card.groups[1].nodes == std::vector<base::EntityId>{4, 5});
    CHECK_THAT(writeModelText(model), ContainsSubstring("RigidInterpolation;50;50;123;2;1.;123;2;2;3;1.;123;2;4;5\n"));
}

TEST_CASE("a node of a term written as a real is an error of the record in both modes", "[model][model-file][review]")
{
    const std::string record = "RigidInterpolation;50;50;123;2;1.;123;2;2;3.;1.;123;2;4;5\n";
    REQUIRE_THROWS_AS(readModelText(record, true), base::DeckError);
    const Model tolerant = readModelText(record, false);
    REQUIRE(tolerant.diagnostics().hasErrors());
    const auto error = tolerant.diagnostics().firstError();
    REQUIRE(error.has_value());
    CHECK(error->code == "model-file.bad-record");
    CHECK(error->location.cardName == "RigidInterpolation");
    CHECK_THAT(error->message, ContainsSubstring("node") && ContainsSubstring("\"3.\""));
    // No term was read with a weight of 3.
    const RigidInterpolationTable* table = tolerant.findTable<RigidInterpolationTable>();
    CHECK((table == nullptr || table->rows().rowCount() == 0));
}

TEST_CASE("outside a group with a nested list the card reader takes an integer for a real and names a bad field",
          "[model][model-file][review]")
{
    // An integer in a field that is only a real is that real.
    const Model model = readModelText("Node;7;;3;1;2\n", true);
    const NodeCard node = model.findTable<NodeTable>()->card(model.locate(base::IdSpace::Node, 7)->row);
    CHECK(node.xyz.x == 3.0);
    CHECK(node.xyz.y == 1.0);
    CHECK(node.xyz.z == 2.0);
    // A real in a field that is only an integer is the error of the card, with the field named.
    const Model tolerant = readModelText("Node;7.5;;3.;1.;2.\n", false);
    const auto error = tolerant.diagnostics().firstError();
    REQUIRE(error.has_value());
    CHECK(error->code == "card.bad-integer");
    CHECK(error->location.fieldName == "id");
}
