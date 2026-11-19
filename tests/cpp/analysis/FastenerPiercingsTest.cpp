// The piercing points of Fastener and Weld on the shells (FastenerPiercings), on small decks whose answers are worked
// out by hand.

#include "oor/analysis/connections/FastenerPiercings.hpp"
#include "support/ModelRecord.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <string>
#include <tuple>
#include <vector>

using namespace oor;
using oor::testing::readModelText;

namespace
{

// Two plates of 2 by 2 unit squares, at z = 0 (nodes 1 to 9, elements 1 to 4, ShellProp 1) and z = 0.5 (nodes 101 to
// 109, elements 101 to 104, ShellProp 2), and the cards `fasteners`.
std::string twoPlates(const std::string& fasteners)
{
    std::string text =
        "IsoMat;1;2.E+5;7.5E+4;0.3\nShellProp;1;1;0.1\nShellProp;2;1;0.1\n"
        "FastenerProp;10;0.2;;;1.;1.;1.\nWeldProp;20;1;0.2\n";
    for (const auto& [first, pid, z] : {std::tuple{1, 1, 0.0}, std::tuple{101, 2, 0.5}})
    {
        for (int j = 0; j <= 2; ++j)
        {
            for (int i = 0; i <= 2; ++i)
                text += oor::testing::modelRecord("Node", first + i + 3 * j, "", static_cast<double>(i),
                                                  static_cast<double>(j), z);
        }
        for (int j = 0; j < 2; ++j)
        {
            for (int i = 0; i < 2; ++i)
            {
                const int n = first + i + 3 * j;
                text += oor::testing::modelRecord("ShellQuad4", first + i + 2 * j, pid, n, n + 1, n + 4, n + 3);
            }
        }
    }
    return text + fasteners;
}

const analysis::FastenerPiercing& sideOf(const analysis::FastenerPiercings& piercings, base::EntityId eid, char side)
{
    for (const analysis::FastenerPiercing& row : piercings.sides())
    {
        if (row.eid == eid && row.side == side)
            return row;
    }
    FAIL("no row for the fastener side");
    return piercings.sides().front();
}

// One ShellQuad4 `eid` of property `pid` on the square [x0, x1] x [y0, y1] at height z, its grid points numbered
// from `firstNode`.
std::string squareSheet(int eid, int pid, int firstNode, double x0, double x1, double y0, double y1, double z)
{
    std::string text;
    const double corners[4][2] = {{x0, y0}, {x1, y0}, {x1, y1}, {x0, y1}};
    for (int k = 0; k < 4; ++k)
        text += oor::testing::modelRecord("Node", firstNode + k, "", corners[k][0], corners[k][1], z);
    return text +
           oor::testing::modelRecord("ShellQuad4", eid, pid, firstNode, firstNode + 1, firstNode + 2, firstNode + 3);
}

const std::string SHEET_PROPERTIES = "IsoMat;1;2.E+5;7.5E+4;0.3\nShellProp;1;1;0.1\nShellProp;2;1;0.1\n"
                                     "FastenerProp;10;0.2;;;1.;1.;1.\n";

} // namespace

TEST_CASE("a weld between flat plates pierces them under its location", "[analysis][connections]")
{
    const model::Model model =
        readModelText(twoPlates("Node;600;;0.5;0.4;0.3\nWeld;500;20;600;ElemPatch;;;;1;101\n"));
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(model);
    REQUIRE(piercings.sides().size() == 2);
    for (const auto& [side, element, z] : {std::tuple{'A', 1, 0.0}, std::tuple{'B', 101, 0.5}})
    {
        const analysis::FastenerPiercing& row = sideOf(piercings, 500, side);
        REQUIRE(row.isFound);
        CHECK(row.elementId == element);
        CHECK(row.position.x == Catch::Approx(0.5));
        CHECK(row.position.y == Catch::Approx(0.4));
        CHECK(row.position.z == Catch::Approx(z).margin(1e-12));
        // element 1 spans x 0..1, y 0..1: xi = 2x - 1 = 0, eta = 2y - 1 = -0.2
        CHECK(row.xi == Catch::Approx(0.0).margin(1e-12));
        CHECK(row.eta == Catch::Approx(-0.2));
        REQUIRE(row.nids.size() == 4);
        CHECK(row.shapeValues[0] == Catch::Approx(0.25 * 1.0 * 1.2));
        CHECK(row.shapeValues[2] == Catch::Approx(0.25 * 1.0 * 0.8));
    }
}

TEST_CASE("a fastener on a grid point shared by four shells pierces the lowest element ID", "[analysis][connections]")
{
    const model::Model model = readModelText(twoPlates("Node;600;;1.;1.;0.3\nFastener;500;10;Property;1;2;600\n"));
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(model);
    const analysis::FastenerPiercing& row = sideOf(piercings, 500, 'A');
    REQUIRE(row.isFound);
    CHECK(row.elementId == 1);
    // node 5 is corner 3 of element 1: its shape function is 1 there, the others 0
    REQUIRE(row.nids == std::vector<base::EntityId>{1, 2, 5, 4});
    CHECK(row.shapeValues[2] == Catch::Approx(1.0));
    CHECK(sideOf(piercings, 500, 'B').elementId == 101);
}

TEST_CASE("the fastener axis finds the shell of a property it crosses, not the lowest ID", "[analysis][connections]")
{
    const model::Model model =
        readModelText(twoPlates("Node;600;;1.5;1.7;0.2\nFastener;500;10;Property;1;2;600\n"));
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(model);
    CHECK(sideOf(piercings, 500, 'A').elementId == 4);
    const analysis::FastenerPiercing& b = sideOf(piercings, 500, 'B');
    REQUIRE(b.isFound);
    CHECK(b.elementId == 104);
    CHECK(b.position.x == Catch::Approx(1.5));
    CHECK(b.position.y == Catch::Approx(1.7));
    CHECK(b.position.z == Catch::Approx(0.5));
}

TEST_CASE("the fastener axis crosses a curved quadratic shell where its surface is", "[analysis][connections]")
{
    // A ShellQuad8 on [-1, 1] x [-1, 1] whose mid-side points 5 and 7 are raised by h = 0.3: its surface is
    // z = h (1 - xi^2) with x = xi, y = eta. A flat ShellQuad4 below at z = -1; the location (0.4, 0.2, -0.5).
    const std::string deck =
        "IsoMat;1;2.E+5;7.5E+4;0.3\n"
        "ShellProp;1;1;0.1\n"
        "ShellProp;2;1;0.1\n"
        "FastenerProp;10;0.2;;;1.;1.;1.\n"
        "Node;1;;-1.;-1.;-1.\n"
        "Node;2;;1.;-1.;-1.\n"
        "Node;3;;1.;1.;-1.\n"
        "Node;4;;-1.;1.;-1.\n"
        "ShellQuad4;1;1;1;2;3;4\n"
        "Node;11;;-1.;-1.;0.\n"
        "Node;12;;1.;-1.;0.\n"
        "Node;13;;1.;1.;0.\n"
        "Node;14;;-1.;1.;0.\n"
        "Node;15;;0.;-1.;0.3\n"
        "Node;16;;1.;0.;0.\n"
        "Node;17;;0.;1.;0.3\n"
        "Node;18;;-1.;0.;0.\n"
        "ShellQuad8;2;2;11;12;13;14;15;16;17;18\n"
        "Fastener;500;10;Property;1;2;;;;0.4;0.2;-0.5\n";
    const model::Model model = readModelText(deck);
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(model);
    const analysis::FastenerPiercing& b = sideOf(piercings, 500, 'B');
    REQUIRE(b.isFound);
    CHECK(b.elementId == 2);
    CHECK(b.position.x == Catch::Approx(0.4));
    CHECK(b.position.y == Catch::Approx(0.2));
    CHECK(b.position.z == Catch::Approx(0.3 * (1.0 - 0.4 * 0.4)));
    CHECK(b.xi == Catch::Approx(0.4));
    CHECK(b.eta == Catch::Approx(0.2));
    double sum = 0.0;
    for (const double value : b.shapeValues)
        sum += value;
    CHECK(sum == Catch::Approx(1.0));
}

TEST_CASE("a location off the shells gives no piercing point and says why", "[analysis][connections]")
{
    const model::Model model = readModelText(twoPlates("Node;600;;5.;0.5;0.3\nFastener;500;10;Property;1;2;600\n"));
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(model);
    const analysis::FastenerPiercing& a = sideOf(piercings, 500, 'A');
    CHECK_FALSE(a.isFound);
    CHECK(a.field == "patchIdA");
    CHECK(a.problem.find("ProjectionTolerance") != std::string::npos);
    CHECK_FALSE(sideOf(piercings, 500, 'B').isFound);
}

TEST_CASE("the fastener axis is found on shells far from the origin", "[analysis][connections]")
{
    // Two 0.5 x 0.5 plates 0.8 apart at x = 132.5 .. 133, y = 13.5 .. 14 (coordinates 260 element sizes from the
    // origin, where Newton's steps stagnate at round-off instead of reaching 0).
    const std::string deck =
        "IsoMat;1;2.E+5;7.5E+4;0.3\n"
        "ShellProp;1;1;0.1\n"
        "ShellProp;2;1;0.1\n"
        "FastenerProp;10;0.2;;;1.;1.;1.\n"
        "Node;1;;132.5;13.5;0.\n"
        "Node;2;;133.;13.5;0.\n"
        "Node;3;;133.;14.;0.\n"
        "Node;4;;132.5;14.;0.\n"
        "Node;11;;132.5;13.5;0.8\n"
        "Node;12;;133.;13.5;0.8\n"
        "Node;13;;133.;14.;0.8\n"
        "Node;14;;132.5;14.;0.8\n"
        "ShellQuad4;1;1;1;2;3;4\n"
        "ShellQuad4;2;2;11;12;13;14\n"
        "Fastener;500;10;Property;1;2;;;;132.967;13.5667;0.4\n";
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(readModelText(deck));
    const analysis::FastenerPiercing& b = sideOf(piercings, 500, 'B');
    REQUIRE(b.isFound);
    CHECK(b.elementId == 2);
    CHECK(b.position.x == Catch::Approx(132.967));
    CHECK(b.position.z == Catch::Approx(0.8));
}

// Several sheets may have the property a fastener names (the caps of the two faces of a box, two skins). The sheet a
// point belongs to is the nearest one it projects on, also when it reaches that sheet on its edge, within the
// tolerance, and projects well inside a sheet farther away.

TEST_CASE("a location beside the edge of a sheet is placed on it, not on a farther sheet of the property",
          "[analysis][connections]")
{
    // Property 1: the unit sheet 1 at z = 0, and the sheet 2 at z = 3, wide enough to hold the projection of the
    // location. Property 2: the sheet 3 at z = -0.2. The location is 0.005 beyond the edge x = 0 of the sheet 1
    // (0.01 in its natural coordinates, within the tolerance of 0.02), 0.1 below it.
    const std::string deck = SHEET_PROPERTIES + squareSheet(1, 1, 1, 0.0, 1.0, 0.0, 1.0, 0.0) +
                             squareSheet(2, 1, 11, -2.0, 3.0, -2.0, 3.0, 3.0) +
                             squareSheet(3, 2, 21, -1.0, 2.0, -1.0, 2.0, -0.2) +
                             "Fastener;500;10;Property;1;2;;;;-0.005;0.5;-0.1\n";
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(readModelText(deck));
    const analysis::FastenerPiercing& a = sideOf(piercings, 500, 'A');
    REQUIRE(a.isFound);
    CHECK(a.elementId == 1);
    // brought onto the edge of the sheet
    CHECK(a.position.x == Catch::Approx(0.0).margin(1e-12));
    CHECK(a.position.y == Catch::Approx(0.5));
    CHECK(a.position.z == Catch::Approx(0.0).margin(1e-12));
    const analysis::FastenerPiercing& b = sideOf(piercings, 500, 'B');
    REQUIRE(b.isFound);
    CHECK(b.elementId == 3);
    CHECK(b.position.z == Catch::Approx(-0.2));
}

TEST_CASE("a grid point given on the edge of a sheet is placed on it when a sheet of the property lies far away",
          "[analysis][connections]")
{
    // The grid points of the two ends are on the edge x = 0 of the sheets 1 and 3, to the rounding of a model file
    // (1e-9 beyond it). The other sheet of property 1 is 60 away, more than a fastener reaches (10 element sizes of
    // a sheet of 5): held for the sheet of the point, it left the side without a piercing point.
    const std::string deck = SHEET_PROPERTIES + squareSheet(1, 1, 1, 0.0, 1.0, 0.0, 1.0, 0.0) +
                             squareSheet(2, 1, 11, -2.0, 3.0, -2.0, 3.0, 60.0) +
                             squareSheet(3, 2, 21, 0.0, 1.0, 0.0, 1.0, -0.2) +
                             squareSheet(4, 2, 31, -2.0, 3.0, -2.0, 3.0, -60.0) +
                             "Node;600;;-1.E-9;0.5;0.\nNode;601;;-1.E-9;0.5;-0.2\n"
                             "Fastener;500;10;Property;1;2;;600;601\n";
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(readModelText(deck));
    for (const auto& [side, element] : {std::tuple{'A', 1}, std::tuple{'B', 3}})
    {
        const analysis::FastenerPiercing& row = sideOf(piercings, 500, side);
        INFO(row.problem);
        REQUIRE(row.isFound);
        CHECK(row.elementId == element);
        CHECK(row.xi == Catch::Approx(-1.0));
        CHECK(row.eta == Catch::Approx(0.0).margin(1e-9));
    }
}

TEST_CASE("the fastener axis crosses the sheet beside it, not a farther sheet of the property",
          "[analysis][connections]")
{
    // Side A: the sheet 1 at z = 0, pierced on its edge x = 0. Property 2: the sheet 3 at z = -0.2, whose edge is
    // at x = 0.005 (the axis passes 0.005 beside it: 0.005 in its natural coordinates), and the sheet 4 at z = -3,
    // which the axis crosses well inside.
    const std::string deck = SHEET_PROPERTIES + squareSheet(1, 1, 1, 0.0, 1.0, 0.0, 1.0, 0.0) +
                             squareSheet(3, 2, 21, 0.005, 2.005, -1.0, 2.0, -0.2) +
                             squareSheet(4, 2, 31, -2.0, 3.0, -2.0, 3.0, -3.0) +
                             "Fastener;500;10;Property;1;2;;;;0.;0.5;-0.1\n";
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(readModelText(deck));
    const analysis::FastenerPiercing& b = sideOf(piercings, 500, 'B');
    INFO(b.problem);
    REQUIRE(b.isFound);
    CHECK(b.elementId == 3);
    CHECK(b.position.x == Catch::Approx(0.005));
    CHECK(b.position.z == Catch::Approx(-0.2));
}

TEST_CASE("a point inside an element stays on it beside a neighbour whose extended surface is nearer",
          "[analysis][connections]")
{
    // Two elements of one sheet folded along x = 1: the element 1 flat on [0, 1], the element 2 going up at 45
    // degrees from the fold. A location 0.01 under the element 1 and 0.001 before the fold is strictly inside the
    // element 1 (0.01 away); the extended plane of the element 2 is nearer (0.0064) and the location projects 0.011
    // beyond its edge, within the tolerance: the point is on the element it is inside of.
    const std::string deck =
        SHEET_PROPERTIES +
        "Node;1;;0.;0.;0.\nNode;2;;1.;0.;0.\nNode;3;;1.;1.;0.\nNode;4;;0.;1.;0.\n"
        "Node;5;;2.;0.;1.\nNode;6;;2.;1.;1.\n"
        "ShellQuad4;1;1;1;2;3;4\nShellQuad4;2;1;2;5;6;3\n" +
        squareSheet(3, 2, 21, -1.0, 3.0, -1.0, 2.0, -0.2) + "Fastener;500;10;Property;1;2;;;;0.999;0.5;-0.01\n";
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(readModelText(deck));
    const analysis::FastenerPiercing& a = sideOf(piercings, 500, 'A');
    REQUIRE(a.isFound);
    CHECK(a.elementId == 1);
    CHECK(a.position.x == Catch::Approx(0.999));
    CHECK(a.position.z == Catch::Approx(0.0).margin(1e-12));
}
