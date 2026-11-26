// Corner cases of the connections, on small decks whose answers are worked out by hand: a fastener located far from
// the shells of its property, the points of a RigidSpline whose components are blank, and a contact face two corners
// of which coincide.

#include "oor/analysis/connections/ContactSearch.hpp"
#include "oor/analysis/connections/FastenerPiercings.hpp"
#include "oor/analysis/connections/RigidElementTerms.hpp"
#include "oor/model/cards/rigid_elements/rigidSpline/RigidSplineTable.hpp"
#include "oor/model/core/CardRegistry.hpp"
#include "support/ModelRecord.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <optional>
#include <string>
#include <vector>

using namespace oor;
using oor::testing::modelRecord;
using oor::testing::readModelText;

namespace
{

// A plate of 10 by 10 unit squares at z = 0 (nodes 1 to 121 numbered along x, elements 1 to 100 likewise, ShellProp
// 1): enough elements for the shells of the property to be searched through their grid of cells. One square of
// ShellProp 2 over the whole plate at z = 0.5 (nodes 201 to 204, element 200). Then the cards `fasteners`.
std::string largePlate(const std::string& fasteners)
{
    constexpr int SIDE = 10;
    std::string text = "IsoMat;1;2.E+5;7.5E+4;0.3\nShellProp;1;1;0.1\nShellProp;2;1;0.1\n"
                       "FastenerProp;10;0.2;;;1.;1.;1.\n";
    for (int j = 0; j <= SIDE; ++j)
    {
        for (int i = 0; i <= SIDE; ++i)
            text += modelRecord("Node", 1 + i + (SIDE + 1) * j, "", static_cast<double>(i), static_cast<double>(j),
                                0.0);
    }
    for (int j = 0; j < SIDE; ++j)
    {
        for (int i = 0; i < SIDE; ++i)
        {
            const int n = 1 + i + (SIDE + 1) * j;
            text += modelRecord("ShellQuad4", 1 + i + SIDE * j, 1, n, n + 1, n + SIDE + 2, n + SIDE + 1);
        }
    }
    text += "Node;201;;0.;0.;0.5\nNode;202;;10.;0.;0.5\nNode;203;;10.;10.;0.5\nNode;204;;0.;10.;0.5\n"
            "ShellQuad4;200;2;201;202;203;204\n";
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

} // namespace

TEST_CASE("a fastener located very far from the shells of its property is refused at once", "[analysis][connections]")
{
    // Fastener 501 is a million element sizes away in the plane of the plate: it projects on no element. Fastener 502
    // is as far above the middle of element 45 (x and y from 4 to 5): it projects on that element, out of reach (10
    // element sizes). Neither search may walk the cells between the point and the plate.
    const model::Model model = readModelText(largePlate("Fastener;501;10;Property;1;2;;;;1.E+6;4.5;0.\n"
                                                        "Fastener;502;10;Property;1;2;;;;4.5;4.5;1.E+6\n"));
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(model);
    REQUIRE(piercings.sides().size() == 4);

    const analysis::FastenerPiercing& inPlane = sideOf(piercings, 501, 'A');
    CHECK_FALSE(inPlane.isFound);
    CHECK(inPlane.field == "patchIdA");
    CHECK(inPlane.problem.find("falls on none of") != std::string::npos);
    CHECK_FALSE(sideOf(piercings, 501, 'B').isFound);

    const analysis::FastenerPiercing& above = sideOf(piercings, 502, 'A');
    CHECK_FALSE(above.isFound);
    CHECK(above.field == "patchIdA");
    // the nearest element is still found, to say how far it is
    CHECK(above.problem.find("it falls on element 45 ") != std::string::npos);
    CHECK_FALSE(sideOf(piercings, 502, 'B').isFound);
}

TEST_CASE("a fastener near a large plate pierces the element under its location", "[analysis][connections]")
{
    // Both locations are over the middle of element 45, within reach: 3 above the plate (inside the grid of cells,
    // three rings from the cell of the element) and 5 below it (five cells outside the grid). Side B is where the
    // normal at the piercing point of side A crosses the square at z = 0.5.
    const model::Model model = readModelText(largePlate("Fastener;500;10;Property;1;2;;;;4.5;4.5;3.\n"
                                                        "Fastener;503;10;Property;1;2;;;;4.5;4.5;-5.\n"));
    const analysis::FastenerPiercings piercings = analysis::FastenerPiercings::compute(model);
    for (const base::EntityId eid : {500, 503})
    {
        INFO("fastener " << eid);
        const analysis::FastenerPiercing& a = sideOf(piercings, eid, 'A');
        INFO(a.problem);
        REQUIRE(a.isFound);
        CHECK(a.elementId == 45);
        CHECK(a.position.x == Catch::Approx(4.5));
        CHECK(a.position.y == Catch::Approx(4.5));
        CHECK(a.position.z == Catch::Approx(0.0).margin(1e-12));
        // element 45 spans x 4..5, y 4..5: its middle is xi = eta = 0
        CHECK(a.xi == Catch::Approx(0.0).margin(1e-9));
        CHECK(a.eta == Catch::Approx(0.0).margin(1e-9));
        const analysis::FastenerPiercing& b = sideOf(piercings, eid, 'B');
        INFO(b.problem);
        REQUIRE(b.isFound);
        CHECK(b.elementId == 200);
        CHECK(b.position.x == Catch::Approx(4.5));
        CHECK(b.position.y == Catch::Approx(4.5));
        CHECK(b.position.z == Catch::Approx(0.5));
    }
}

TEST_CASE("a point of a RigidSpline with blank components is independent", "[analysis][connections]")
{
    // G1 = 1, G2 = 2 with blank components, G3 = 3 with the components 123456, G4 = 4: the two ends and the point 2
    // are independent with their six components, the point 3 has its six components dependent.
    const model::Model model =
        readModelText("Node;1;;0.;0.;0.\nNode;2;;1.;0.;0.\nNode;3;;2.;0.;0.\nNode;4;;3.;0.;0.\n"
                      "RigidSpline;74;;1;2;;3;123456;4\n");
    const model::CardLocation spline{model::typeIndexOf<model::RigidSplineTable>(), 0};
    const std::vector<analysis::RigidTerm> terms = analysis::RigidElementTerms::of(model, spline);
    REQUIRE(terms.size() == 4);
    const bool independent[4] = {true, true, false, true};
    for (std::size_t index = 0; index < terms.size(); ++index)
    {
        INFO("point " << index + 1);
        CHECK(terms[index].node == static_cast<base::EntityId>(index + 1));
        CHECK(terms[index].isIndependent == independent[index]);
        CHECK(terms[index].components == analysis::RigidElementTerms::ALL_COMPONENTS);
    }
}

TEST_CASE("a contact face whose first two corners coincide meets the grid points on its third corner's side",
          "[analysis][contact]")
{
    // Body 1 is one ShellTria3 whose grid points 21 and 22 are both at (0, 0, 1) and 23 at (1, 0, 1): a face without
    // area, the segment from 21 to 23. Body 2 is a unit cube on it (nodes 11 to 14 at z = 1, 15 to 18 at z = 2). The
    // distance of the pair is 5 % of the edge of the cube, 0.05. Node 11 is on the first corner and node 12 on the
    // third: both are on the face (within its half thickness, 0.01). Nodes 13 and 14 are 1 away, the top of the cube
    // farther: they do not meet it.
    const std::string deck =
        "IsoMat;1;2.E+5;7.5E+4;0.3\nSolidProp;1;1\nShellProp;3;1;0.02\n"
        "Node;11;;0.;0.;1.\nNode;12;;1.;0.;1.\nNode;13;;1.;1.;1.\nNode;14;;0.;1.;1.\n"
        "Node;15;;0.;0.;2.\nNode;16;;1.;0.;2.\nNode;17;;1.;1.;2.\nNode;18;;0.;1.;2.\n"
        "SolidHexa;2;1;11;12;13;14;15;16;17;18\n"
        "Node;21;;0.;0.;1.\nNode;22;;0.;0.;1.\nNode;23;;1.;0.;1.\n"
        "ShellTria3;3;3;21;22;23\n"
        "ContactElemSurface;1;3\nContactElemSurface;2;2\n"
        "ContactBody1;1;;ThreeDimensional;Deformable;1\nContactBody1;2;;ThreeDimensional;Deformable;2\n"
        "ContactPair;5;;;2;1\n";
    const model::Model model = readModelText(deck);
    const auto search = analysis::ContactSearch::compute(model, std::nullopt);
    REQUIRE(search->results().size() == 1);
    const analysis::ContactPairResult& result = search->results().front();
    CHECK(result.tolerance == Catch::Approx(0.05));
    REQUIRE(result.meets);
    std::vector<base::EntityId> nids;
    for (const analysis::ContactMeeting& meeting : result.meetings)
    {
        INFO("grid point " << meeting.nid);
        nids.push_back(meeting.nid);
        CHECK(meeting.searchedFrom == analysis::SearchSide::Secondary);
        CHECK(meeting.face->eid == 3);
        CHECK(std::isfinite(meeting.gap));
        CHECK(meeting.distance == Catch::Approx(0.0).margin(1e-12));
        // the closest point of the face is the grid point itself: the corner 21 for node 11, the corner 23 for 12
        CHECK(meeting.point.x == Catch::Approx(meeting.nid == 11 ? 0.0 : 1.0).margin(1e-12));
        CHECK(meeting.point.y == Catch::Approx(0.0).margin(1e-12));
        CHECK(meeting.point.z == Catch::Approx(1.0));
    }
    CHECK(nids == std::vector<base::EntityId>{11, 12});
}
