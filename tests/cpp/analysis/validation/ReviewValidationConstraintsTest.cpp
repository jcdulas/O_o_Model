#include "oor/analysis/validation/engine/ValidationEngine.hpp"
#include "support/ModelRecord.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

using namespace oor;
using namespace oor::analysis;
using oor::testing::modelRecord;
using oor::testing::readModelText;

namespace
{

const char* const SPC_ON_MPC = "constraint.spc-on-mpc-dependent";
const char* const MPC_TWICE = "constraint.mpc-dependent-twice";
const char* const RIGID_LOOP = "constraint.rigid-loop";

// Grid points 1 to `count` on the x axis, one unit apart.
std::string nodesOnLine(int count)
{
    std::string text;
    for (int id = 1; id <= count; ++id)
        text += modelRecord("Node", id, "", static_cast<double>(id), "0.", "0.");
    return text;
}

// The findings of one check on a model file given as text.
std::vector<ValidationFinding> findingsOf(const std::string& text, const std::string& code)
{
    const model::Model model = readModelText(text);
    ValidationOptions options;
    options.select = {code};
    return ValidationEngine::run(model, options).findings;
}

// A static deck of two subcases: the first selects SPC 10 and MPC 100, the second SPC 20 and no MPC.
const char* const TWO_SUBCASES =
    "[executive]\n"
    "SolutionSequence;101\n"
    "[case]\n"
    "SubcaseStart;1\n"
    "SinglePointConstrSelection;10\n"
    "MultiPointConstrSelection;100\n"
    "SubcaseStart;2\n"
    "SinglePointConstrSelection;20\n";

// MPC 100: the translation 1 of grid point 2 (the dependent term) follows the one of grid point 3.
const char* const MPC_100 = "MultiPointConstr;100;2;1;1.;3;1;-1.\n";

} // namespace

TEST_CASE("a single point constraint meets the multipoint constraints of its own subcase only",
          "[validation][constraints][review]")
{
    const std::string deck = std::string(TWO_SUBCASES) + "[model]\n" + nodesOnLine(4) + MPC_100;
    // SPC 20 fixes the dependent term of MPC 100, but the subcase that selects SPC 20 selects no MPC: a valid deck.
    REQUIRE(findingsOf(deck + "SinglePointConstrList;10;123456;1\nSinglePointConstrList;20;123456;2\n", SPC_ON_MPC)
                .empty());
    // SPC 10 and MPC 100 are of the same subcase: a clash, reported on the constraint card.
    const std::vector<ValidationFinding> clash =
        findingsOf(deck + "SinglePointConstrList;10;123456;2\nSinglePointConstrList;20;123456;1\n", SPC_ON_MPC);
    REQUIRE(clash.size() == 1);
    REQUIRE(clash.front().severity == base::Severity::Error);
    REQUIRE(clash.front().cardName == "SinglePointConstrList");
    REQUIRE(clash.front().cardId == 10);
}

TEST_CASE("the constraint sets of two subcases are not crossed", "[validation][constraints][review]")
{
    // Subcase 1 has SPC 10 with MPC 100, subcase 2 has SPC 20 with MPC 200. Each SPC set fixes the dependent term of
    // the MPC set of the other subcase, never of its own.
    const std::string deck =
        "[executive]\n"
        "SolutionSequence;101\n"
        "[case]\n"
        "SubcaseStart;1\n"
        "SinglePointConstrSelection;10\n"
        "MultiPointConstrSelection;100\n"
        "SubcaseStart;2\n"
        "SinglePointConstrSelection;20\n"
        "MultiPointConstrSelection;200\n"
        "[model]\n" +
        nodesOnLine(6) + MPC_100 +
        "MultiPointConstr;200;5;1;1.;6;1;-1.\n"
        "SinglePointConstrList;10;123456;5\n"
        "SinglePointConstrList;20;123456;2\n";
    REQUIRE(findingsOf(deck, SPC_ON_MPC).empty());
}

TEST_CASE("a permanent constraint meets the multipoint constraints of every subcase that selects some",
          "[validation][constraints][review]")
{
    // Grid point 2 has its translation 1 fixed by its own card, and MPC 100 makes it dependent.
    const std::string bulk =
        std::string("[model]\nNode;1;;1.;0.;0.\nNode;2;;2.;0.;0.;;1\nNode;3;;3.;0.;0.\n") + MPC_100;
    const std::string selected =
        "[executive]\nSolutionSequence;101\n[case]\nSubcaseStart;1\n"
        "MultiPointConstrSelection;100\n";
    const std::vector<ValidationFinding> clash = findingsOf(selected + bulk, SPC_ON_MPC);
    REQUIRE(clash.size() == 1);
    REQUIRE(clash.front().cardName == "Node");
    REQUIRE(clash.front().cardId == 2);
    // The Case Control names single point constraints and no multipoint constraint: MPC 100 is not used.
    const std::string unused =
        "[executive]\nSolutionSequence;101\n[case]\nSubcaseStart;1\n"
        "SinglePointConstrSelection;10\n";
    REQUIRE(findingsOf(unused + bulk + "SinglePointConstrList;10;123456;3\n", SPC_ON_MPC).empty());
}

TEST_CASE("a model with no constraint command is judged on each pair of constraint sets",
          "[validation][constraints][review]")
{
    // No Case Control: a single point constraint set on the dependent term of a multipoint set is a clash of that pair.
    const std::string bulk = nodesOnLine(4) + MPC_100;
    const std::vector<ValidationFinding> clash = findingsOf(bulk + "SinglePointConstrList;10;123456;2\n", SPC_ON_MPC);
    REQUIRE(clash.size() == 1);
    REQUIRE(clash.front().cardId == 10);
    REQUIRE(findingsOf(bulk + "SinglePointConstrList;10;123456;4\n", SPC_ON_MPC).empty());
}

TEST_CASE("two multipoint constraint sets that nothing puts together are alternatives",
          "[validation][constraints][review]")
{
    // Sets 1 and 2 make the same degree of freedom dependent.
    const std::string bulk = nodesOnLine(4) +
                             "MultiPointConstr;1;2;1;1.;3;1;-1.\n"
                             "MultiPointConstr;2;2;1;1.;4;1;-1.\n";
    // No MPC command at all, with no Case Control and with one that names single point constraints only.
    REQUIRE(findingsOf(bulk, MPC_TWICE).empty());
    const std::string spcOnly =
        "[executive]\nSolutionSequence;101\n[case]\nSubcaseStart;1\n"
        "SinglePointConstrSelection;10\n[model]\n";
    REQUIRE(findingsOf(spcOnly + bulk + "SinglePointConstrList;10;123456;1\n", MPC_TWICE).empty());
    // One subcase for each set.
    const std::string oneEach =
        "[executive]\nSolutionSequence;101\n[case]\nSubcaseStart;1\n"
        "MultiPointConstrSelection;1\nSubcaseStart;2\nMultiPointConstrSelection;2\n[model]\n";
    REQUIRE(findingsOf(oneEach + bulk, MPC_TWICE).empty());
}

TEST_CASE("two multipoint constraints of one set with the same dependent term are reported",
          "[validation][constraints][review]")
{
    const std::string twice = nodesOnLine(4) +
                              "MultiPointConstr;1;2;1;1.;3;1;-1.\n"
                              "MultiPointConstr;1;2;1;1.;4;1;-1.\n";
    // With no MPC command, and with the command that selects the set.
    for (const std::string& control :
         {std::string(), std::string("[executive]\nSolutionSequence;101\n[case]\nSubcaseStart;1\n"
                                     "MultiPointConstrSelection;1\n[model]\n")})
    {
        const std::vector<ValidationFinding> found = findingsOf(control + twice, MPC_TWICE);
        REQUIRE(found.size() == 1);
        REQUIRE(found.front().severity == base::Severity::Error);
        REQUIRE(found.front().cardName == "MultiPointConstr");
        REQUIRE(found.front().cardId == 1);
    }
    // A union puts two sets together: its sets are one set, selected or not.
    const std::string united = nodesOnLine(4) +
                               "MultiPointConstr;1;2;1;1.;3;1;-1.\n"
                               "MultiPointConstr;2;2;1;1.;4;1;-1.\n"
                               "MultiPointConstrUnion;5;1;2\n";
    REQUIRE(findingsOf(united, MPC_TWICE).size() == 1);
    const std::string selectsUnion =
        "[executive]\nSolutionSequence;101\n[case]\nSubcaseStart;1\n"
        "MultiPointConstrSelection;5\n[model]\n";
    REQUIRE(findingsOf(selectsUnion + united, MPC_TWICE).size() == 1);
}

TEST_CASE("the constraints of a part are judged on the Case Control of the deck", "[validation][constraints][review]")
{
    // The part holds MPC 100 and the two SPC sets; the Case Control, which the residual structure holds, selects SPC 20
    // without MPC 100.
    const std::string deck = std::string(TWO_SUBCASES) + "[model]\nNode;1;;0.;0.;0.\n[model;SuperelementPart;3]\n" +
                             nodesOnLine(4) + MPC_100;
    REQUIRE(findingsOf(deck + "SinglePointConstrList;10;123456;1\nSinglePointConstrList;20;123456;2\n", SPC_ON_MPC)
                .empty());
    const std::vector<ValidationFinding> clash =
        findingsOf(deck + "SinglePointConstrList;10;123456;2\nSinglePointConstrList;20;123456;1\n", SPC_ON_MPC);
    REQUIRE(clash.size() == 1);
    REQUIRE(clash.front().part == "SuperelementPart 3");
    REQUIRE(clash.front().cardId == 10);
}

TEST_CASE("a single point constraint set that no command names is judged alone against the rigid elements",
          "[validation][constraints][review]")
{
    // No Case Control: the RigidBodyStar makes grid point 2 dependent, SPC 20 fixes it and SPC 10 does not.
    const std::vector<ValidationFinding> found =
        findingsOf(nodesOnLine(4) +
                       "RigidBodyStar;60;1;123456;2\n"
                       "SinglePointConstrList;10;123456;3\nSinglePointConstrList;20;123456;2\n",
                   "constraint.spc-on-rigid-dependent");
    REQUIRE(found.size() == 1);
    REQUIRE(found.front().cardId == 20);
}

TEST_CASE("rigid rods that meet at a grid point or close a triangle are not a rigid loop",
          "[validation][constraints][review]")
{
    const std::string triangle = "Node;1;;0.;0.;0.\nNode;2;;1.;0.;0.\nNode;3;;0.;1.;0.\n";
    // Two rods from grid point 1, dependent there on components 1 and 2: two equations for its two translations.
    REQUIRE(findingsOf(triangle + "RigidRod;50;1;2;1\nRigidRod;51;1;3;2\n", RIGID_LOOP).empty());
    // The three sides of the triangle, each dependent at its first end.
    REQUIRE(findingsOf(triangle + "RigidRod;60;1;2;1\nRigidRod;61;2;3;2\nRigidRod;62;3;1;2\n", RIGID_LOOP).empty());
    // A rod between two grid points that a rigid body already ties, dependent at the independent point of the body:
    // a loop through the body, reported on both elements.
    const std::vector<ValidationFinding> loop =
        findingsOf(triangle + "RigidBodyStar;70;1;123456;2\nRigidRod;71;1;2;1\n", RIGID_LOOP);
    REQUIRE(loop.size() == 2);
    // Two rigid bodies that depend on one another are still a loop.
    REQUIRE(findingsOf(triangle + "RigidBodyStar;80;1;123456;2\nRigidBodyStar;81;2;123456;1\n", RIGID_LOOP).size() ==
            2);
}

TEST_CASE("a constraint card kept as text silences the check of a static model without constraint",
          "[validation][constraints][review]")
{
    const std::string deck = "[executive]\nSolutionSequence;101\n[model]\nNode;1;;0.;0.;0.\nNode;2;;1.;0.;0.\n";
    const char* const NO_CONSTRAINT = "constraint.none-in-static-model";
    REQUIRE(findingsOf(deck, NO_CONSTRAINT).size() == 1);
    // A SinglePointConstr the library cannot read (its set ID is not a number) is kept as text under its card name:
    // the model has a constraint the check cannot see.
    REQUIRE(findingsOf(deck + "SinglePointConstr;abc;1;123456\n", NO_CONSTRAINT).empty());
}
