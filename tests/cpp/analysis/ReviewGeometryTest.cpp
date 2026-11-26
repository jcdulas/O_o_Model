// The volume of an axisymmetric quadrilateral that is not a parallelogram, a panel whose box count is absurd, and the
// segment a bush with an orientation node is drawn with.

#include "oor/analysis/geometry/AeroPanels.hpp"
#include "oor/analysis/geometry/DisplayMesh.hpp"
#include "oor/analysis/geometry/ElementGeometry.hpp"
#include "oor/base/errors/Errors.hpp"
#include "support/ModelRecord.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <numbers>
#include <string>
#include <vector>

using namespace oor;
using namespace oor::analysis;
using namespace oor::model;
using Catch::Approx;
using oor::testing::readModelText;

namespace
{

ElementValues geometryOf(const Model& model, base::EntityId eid)
{
    const auto location = model.locate(base::IdSpace::Element, eid);
    REQUIRE(location.has_value());
    return ElementGeometry::of(model, *location);
}

// The record of a node: id, x, y, z (in the basic system).
std::string grid(int id, double x, double y, double z)
{
    return oor::testing::modelRecord("Node", id, "", x, y, z);
}

const char* const PROPERTIES = "IsoMat;1;2.1E+5;;0.3\nShellProp;1;1;0.1\n";

} // namespace

TEST_CASE("the ring of an axisymmetric trapezoid has the volume of the integral of the radius over its section",
          "[analysis][geometry]")
{
    // The axis is the basic z axis and the radius the basic x coordinate (the grid points are in the x-z plane). The
    // section (r, z): (0, 0), (2, 0), (1, 1), (0, 1). At the height z it runs from r = 0 to r = 2 - z, so
    //   area               = integral of (2 - z) dz         = 3/2
    //   integral of r dA   = integral of (2 - z)^2 / 2 dz   = 7/6   (the centroid is at r = 7/9)
    // The mean radius of the four corners is 3/4, which would give 9/8 instead of 7/6.
    const Model model =
        readModelText(std::string(PROPERTIES) + grid(1, 0, 0, 0) + grid(2, 2, 0, 0) + grid(3, 1, 0, 1) +
                      grid(4, 0, 0, 1) + grid(5, -2, 0, 0) + grid(6, -1, 0, 1) +
                      "AxisymQuad;10;1;1;2;3;4\n"   // counter-clockwise seen from -y
                      "AxisymQuad;11;1;1;4;3;2\n"   // the same section, its corners the other way round
                      "AxisymQuad;12;1;1;5;6;4\n"); // its mirror image on the negative side of x
    const double expected = 2.0 * std::numbers::pi * 7.0 / 6.0;
    const ElementValues values = geometryOf(model, 10);
    REQUIRE(values.area == Approx(1.5));
    REQUIRE(values.volume == Approx(expected).epsilon(1e-12));
    // the centre stays the mean of the corners
    REQUIRE(values.center.x == Approx(0.75));
    REQUIRE(values.center.z == Approx(0.5));
    // the order of the corners and the side of the axis do not change the volume
    REQUIRE(geometryOf(model, 11).volume == Approx(expected).epsilon(1e-12));
    REQUIRE(geometryOf(model, 12).volume == Approx(expected).epsilon(1e-12));
}

TEST_CASE("the rings of an axisymmetric rectangle, of a slice of a cone and of a triangle", "[analysis][geometry]")
{
    const Model model =
        readModelText(std::string(PROPERTIES) + grid(1, 1, 0, 0) + grid(2, 2, 0, 0) + grid(3, 2, 0, 1) +
                      grid(4, 1, 0, 1) + grid(5, 10, 0, 0) + grid(6, 11, 0, 0) + grid(7, 11, 0, 2) + grid(8, 10, 0, 1) +
                      "AxisymQuad;10;1;1;2;3;4\n"
                      "AxisymQuad;11;1;5;6;7;8\n"
                      "AxisymTria;12;1;1;2;4\n");
    // a rectangle from r = 1 to 2, one unit high: its centroid is the mean of its corners, r = 3/2
    REQUIRE(geometryOf(model, 10).area == Approx(1.0));
    REQUIRE(geometryOf(model, 10).volume == Approx(2.0 * std::numbers::pi * 1.5).epsilon(1e-12));
    // a slice from r = 10 to 11 whose height grows from 1 to 2: the height at r is r - 9, so
    //   area = integral of (r - 9) dr = 3/2,   integral of r dA = integral of r (r - 9) dr = 331/3 - 189/2 = 95/6
    const ElementValues slice = geometryOf(model, 11);
    REQUIRE(slice.area == Approx(1.5));
    REQUIRE(slice.volume == Approx(2.0 * std::numbers::pi * 95.0 / 6.0).epsilon(1e-12));
    // a triangle (1, 0), (2, 0), (1, 1): area 1/2, centroid at r = 4/3 (the mean of its corners, exact)
    REQUIRE(geometryOf(model, 12).volume == Approx(2.0 * std::numbers::pi * (4.0 / 3.0) * 0.5).epsilon(1e-12));
}

TEST_CASE("a panel with an absurd number of boxes is left out of the list and the others are still given",
          "[analysis][aero]")
{
    // 1000: 2 x 4 boxes. 2000: a span count no panel has. 3000: each count is plausible alone, their product is not.
    // 2147483000: a small lattice of 30 x 30 boxes whose last ID, 2147483899, is above the largest ID (2147483647).
    const Model model = readModelText("AeroLiftingPanel1;1000;1;;2;4;;;1;0.;0.;0.;2.;1.;4.;0.;2.\n"
                                      "AeroLiftingPanel1;2000;1;;2000000000;4;;;1;0.;0.;0.;2.;1.;4.;0.;2.\n"
                                      "AeroLiftingPanel1;3000;1;;50000;50000;;;1;0.;0.;0.;2.;1.;4.;0.;2.\n"
                                      "AeroLiftingPanel1;2147483000;1;;30;30;;;1;0.;0.;0.;2.;1.;4.;0.;2.\n");
    std::vector<base::EntityId> skipped;
    const std::vector<AeroPanelBoxes> panels = allAeroPanelBoxes(model, &skipped);
    REQUIRE(panels.size() == 1);
    REQUIRE(panels[0].eid == 1000);
    REQUIRE(panels[0].boxCount() == 8);
    REQUIRE(skipped == std::vector<base::EntityId>{2000, 3000, 2147483000});

    // asked for alone, such a panel is an error of the library that names the panel
    for (const base::EntityId eid : {2000, 3000, 2147483000})
    {
        try
        {
            (void)aeroPanelBoxes(model, eid);
            FAIL("the panel " << eid << " has no boxes to give");
        }
        catch (const base::OorError& error)
        {
            REQUIRE(std::string(error.what()).find(std::to_string(eid)) != std::string::npos);
        }
    }
}

TEST_CASE("a bush with an orientation node is drawn from GA to GB only", "[analysis][geometry]")
{
    // grid points 1 and 2 are the ends of the bush, grid point 3 its orientation node G0
    const Model model = readModelText("BushProp;1;Stiffness;100.\n" + grid(1, 0, 0, 0) + grid(2, 4, 0, 0) +
                                      grid(3, 0, 1, 0) + "Bushing;11;1;1;2;3\n");
    const DisplayMesh mesh = buildDisplayMesh(model, DisplayMeshOptions{});
    REQUIRE(mesh.connectionEid == std::vector<std::int32_t>{11});
    REQUIRE(mesh.connectionEnds == std::vector<double>{0.0, 0.0, 0.0, 4.0, 0.0, 0.0});
    // the rows of the grid points are those of the node cards by increasing ID: 1 and 2 are the rows 0 and 1
    REQUIRE(mesh.connectionGridRows == std::vector<std::int64_t>{0, 1});
    const std::vector<std::string>& kinds = connectionKinds();
    REQUIRE(mesh.connectionKind.size() == 1);
    REQUIRE(kinds[mesh.connectionKind[0]] == "bush");
}
