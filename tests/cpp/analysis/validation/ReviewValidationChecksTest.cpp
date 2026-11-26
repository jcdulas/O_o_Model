#include "oor/analysis/validation/engine/ValidationEngine.hpp"
#include "oor/model/cards/nodes/node/NodeTable.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <chrono>
#include <limits>
#include <map>
#include <string>
#include <vector>

using namespace oor;
using namespace oor::analysis;
using oor::testing::readModelText;

namespace
{

// The findings of one check on a model.
std::vector<ValidationFinding> findingsOf(const model::Model& model, const std::string& code,
                                          ValidationOptions options = {})
{
    options.select = {code};
    return ValidationEngine::run(model, options).findings;
}

std::vector<ValidationFinding> findingsOf(const std::string& text, const std::string& code)
{
    return findingsOf(readModelText(text), code);
}

void addNode(model::Model& model, base::EntityId id, double x, double y, double z)
{
    model::NodeCard card;
    card.id = id;
    card.xyz = base::Vec3{x, y, z};
    model.add<model::NodeTable>(card);
}

// A model 60 000 long (in millimetres, 60 m) with small elements at its two ends.
const char* const LONG_MODEL =
    "IsoMat;1;2.1E+5;;0.3\nShellProp;1;1;0.1\nSolidProp;2;1\nRodProp;3;1;1.\n"
    "Node;1;;0.;0.;0.\nNode;2;;1.;0.;0.\nNode;3;;0.;1.;0.\nNode;4;;0.;0.;1.\n"
    "Node;5;;60000.;0.;0.\nNode;6;;59999.;0.;0.\nNode;7;;60000.;1.;0.\n"
    "Node;8;;59999.;1.;0.\nNode;9;;59998.;0.;0.\nNode;10;;60000.;0.;0.\n";

} // namespace

TEST_CASE("a small tetrahedron of a large model has a volume, a flat one has none",
          "[validation][compatibility][review]")
{
    // Element 10 has edges of 1 and a volume of 1/6; the four corners of element 11 are in the plane z = 0.
    const std::vector<ValidationFinding> found = findingsOf(
        std::string(LONG_MODEL) + "SolidTetra;10;2;1;2;3;4\nSolidTetra;11;2;5;6;7;8\n", "compat.zero-volume-element");
    REQUIRE(found.size() == 1);
    REQUIRE(found.front().severity == base::Severity::Error);
    REQUIRE(found.front().cardName == "SolidTetra");
    REQUIRE(found.front().cardId == 11);
}

TEST_CASE("the lengths and the areas of a large model are judged by the same linear tolerance",
          "[validation][compatibility][review]")
{
    // Triangle 20 has legs of 1; the corners of triangle 21 are on a line. Rod 30 has a length of 1; the two ends of
    // rod 31 are at the same place.
    const std::string elements = std::string(LONG_MODEL) +
                                 "ShellTria3;20;1;1;2;3\nShellTria3;21;1;5;6;9\n"
                                 "Rod2;30;3;1;2\nRod2;31;3;5;10\n";
    const std::vector<ValidationFinding> flat = findingsOf(elements, "compat.zero-area-element");
    REQUIRE(flat.size() == 1);
    REQUIRE(flat.front().cardId == 21);
    const std::vector<ValidationFinding> shortRods = findingsOf(elements, "compat.zero-length-element");
    REQUIRE(shortRods.size() == 1);
    REQUIRE(shortRods.front().cardId == 31);
}

TEST_CASE("a coincidence tolerance of zero finds the grid points at the same position",
          "[validation][geometry][review]")
{
    model::Model model;
    addNode(model, 1, 0.0, 0.0, 0.0);
    addNode(model, 2, 1000.0, 0.0, 0.0);
    addNode(model, 3, 1000.0, 250.5, -30.0);
    addNode(model, 4, 1000.0, 250.5, -30.0);
    addNode(model, 5, -7.25, 3.0, 12.0);
    addNode(model, 6, 1000.0, 250.5, -30.001);
    // Zero, a negative value and a value that is not a number all mean "the same position".
    for (const double tolerance : {0.0, -1.0, std::numeric_limits<double>::quiet_NaN()})
    {
        ValidationOptions options;
        options.coincidentTolerance = tolerance;
        const std::vector<ValidationFinding> found = findingsOf(model, "geometry.coincident", options);
        REQUIRE(found.size() == 1);
        REQUIRE(found.front().cardId == 4);
        REQUIRE(found.front().message == "coincides with grid point 3");
    }
    // A tolerance that reaches grid point 6 as well: each point with the lowest ID near it.
    ValidationOptions wide;
    wide.coincidentTolerance = 0.01;
    std::map<base::EntityId, std::string> near;
    for (const ValidationFinding& finding : findingsOf(model, "geometry.coincident", wide))
        near[finding.cardId] = finding.message;
    REQUIRE(near == std::map<base::EntityId, std::string>{{4, "coincides with grid point 3"},
                                                          {6, "coincides with grid point 3"}});
}

TEST_CASE("a coincidence tolerance of zero keeps the points of a mesh in cubes of their own",
          "[validation][geometry][review]")
{
    // A lattice of 20 000 points and an exact copy of every thousandth one. Were the points all in one cube, each
    // would be compared with every other one.
    model::Model model;
    base::EntityId next = 1;
    for (int ix = 0; ix < 200; ++ix)
    {
        for (int iy = 0; iy < 100; ++iy)
            addNode(model, next++, ix * 0.5, iy * 0.25, 0.0);
    }
    int copies = 0;
    for (base::EntityId id = 1; id < next; id += 1000)
    {
        const int ix = (id - 1) / 100;
        const int iy = (id - 1) % 100;
        addNode(model, 100000 + id, ix * 0.5, iy * 0.25, 0.0);
        ++copies;
    }
    ValidationOptions options;
    options.coincidentTolerance = 0.0;
    const auto start = std::chrono::steady_clock::now();
    const std::vector<ValidationFinding> found = findingsOf(model, "geometry.coincident", options);
    const std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
    REQUIRE(static_cast<int>(found.size()) == copies);
    for (const ValidationFinding& finding : found)
    {
        REQUIRE(finding.cardId > 100000);
        REQUIRE(finding.message == "coincides with grid point " + std::to_string(finding.cardId - 100000));
    }
    REQUIRE(elapsed.count() < 0.5);
}

TEST_CASE("a set member that a part defines is not missing", "[validation][case_control][review]")
{
    const std::string control = "[executive]\nSolutionSequence;101\n[case]\n";
    const std::string request = "SubcaseStart;1\nDisplacementOutput;3\n";
    const std::string models =
        "[model]\nNode;1;;0.;0.;0.\nNode;5;;1.;0.;0.\n"
        "[model;SuperelementPart;3]\nNode;99;;2.;0.;0.\n";
    // Grid point 99 is a point of the part.
    REQUIRE(findingsOf(control + "SetDefinition;3;1;5;99\n" + request + models, "case.set-member-missing").empty());
    // Grid point 77 is nowhere.
    const std::vector<ValidationFinding> missing =
        findingsOf(control + "SetDefinition;3;1;5;77\n" + request + models, "case.set-member-missing");
    REQUIRE(missing.size() == 1);
    REQUIRE_THAT(missing.front().message, Catch::Matchers::ContainsSubstring("the first is 77"));
}

TEST_CASE("a point listed twice for one superelement is interior to one superelement",
          "[validation][superelement][review]")
{
    const std::string nodes =
        "Node;1;;0.;0.;0.\nNode;2;;1.;0.;0.\nNode;3;;2.;0.;0.\nNode;4;;3.;0.;0.\n"
        "Node;5;;4.;0.;0.\n";
    // Two lists of superelement 1 share grid point 3.
    const std::string sameSuperelement = nodes + "SuperelementInteriorNodes;1;2;3\nSuperelementInteriorNodes;1;3;4\n";
    REQUIRE(findingsOf(sameSuperelement, "superelement.node-in-two").empty());
    // A list of superelement 2 shares grid point 4 with superelement 1.
    const std::vector<ValidationFinding> twoSuperelements =
        findingsOf(sameSuperelement + "SuperelementInteriorNodes;2;4;5\n", "superelement.node-in-two");
    REQUIRE(twoSuperelements.size() == 1);
    REQUIRE_THAT(twoSuperelements.front().message,
                 Catch::Matchers::ContainsSubstring("point 4 is in the list of superelement 2 and in the list of "
                                                    "superelement 1"));
}

TEST_CASE("a point card kept as text silences the check of the interior points that no card defines",
          "[validation][superelement][review]")
{
    const char* const MISSING_NODE = "superelement.superelement-interior-nodes-missing-node";
    const std::string deck = "Node;1;;0.;0.;0.\nSuperelementInteriorNodes;5;1;77\n";
    REQUIRE(findingsOf(deck, MISSING_NODE).size() == 1);
    // A card of an unknown type says nothing of the points.
    REQUIRE(findingsOf(deck + "FutureCard;77\n", MISSING_NODE).size() == 1);
    // A Node the library cannot read (its ID is not a number) is kept as text under its card name: it may be the
    // point the list names.
    REQUIRE(findingsOf(deck + "Node;abc;;0.;0.;0.\n", MISSING_NODE).empty());
}
