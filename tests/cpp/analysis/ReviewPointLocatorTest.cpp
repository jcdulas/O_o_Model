// Points located in solids: a solid collapsed to no volume holds no point, a point inside a proper solid or within the
// tolerance of it is found as before, and a curved solid is still found where it reaches beyond the box of its nodes.

#include "oor/analysis/geometry/PointLocator.hpp"
#include "support/ModelRecord.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <numeric>
#include <string>
#include <vector>

using namespace oor;
using namespace oor::analysis;
using namespace oor::model;
using Catch::Approx;
using oor::testing::readModelText;

namespace
{

// The largest distance of the tests: 5 % of the unit size of their elements, given so that it does not depend on the
// median size of the elements of each model.
constexpr double TOLERANCE = 0.05;

const char* const PROPERTIES = "IsoMat;1;2.1E+5;;0.3\nSolidProp;1;1\n";

std::string grid(int id, double x, double y, double z)
{
    return oor::testing::modelRecord("Node", id, "", x, y, z);
}

// The eight nodes `first` to `first + 7` of a box in the order of a hexahedron card: the face at `z0` counter-clockwise
// seen from above, then the face at `z1` above it. With `z1 == z0` the box has no thickness.
std::string boxNodes(int first, double x0, double x1, double z0, double z1)
{
    return grid(first, x0, 0, z0) + grid(first + 1, x1, 0, z0) + grid(first + 2, x1, 1, z0) +
           grid(first + 3, x0, 1, z0) + grid(first + 4, x0, 0, z1) + grid(first + 5, x1, 0, z1) +
           grid(first + 6, x1, 1, z1) + grid(first + 7, x0, 1, z1);
}

// A hexahedron card on the nodes `first` to `first + 7`.
std::string hexa(int eid, int first)
{
    std::string record = "SolidHexa;" + std::to_string(eid) + ";1";
    for (int node = first; node < first + 8; ++node)
        record += ";" + std::to_string(node);
    return record + "\n";
}

std::vector<LocatedPoint> locate(const Model& model, const std::vector<base::Vec3>& points)
{
    return PointLocator::locate(model, points, std::nullopt, TOLERANCE);
}

void requireNotLocated(const LocatedPoint& point)
{
    REQUIRE_FALSE(point.element.has_value());
    REQUIRE(point.eid == 0);
    REQUIRE(point.nodes.empty());
    REQUIRE(std::isnan(point.natural.x));
}

void requireWeightsSumToOne(const LocatedPoint& point, std::size_t nodeCount)
{
    REQUIRE(point.nodes.size() == nodeCount);
    REQUIRE(point.weights.size() == nodeCount);
    REQUIRE(std::accumulate(point.weights.begin(), point.weights.end(), 0.0) == Approx(1.0));
}

} // namespace

TEST_CASE("a hexahedron with no thickness does not take the points of the hexahedron above it", "[analysis][geometry]")
{
    // element 1: the unit square at z = 0, its top face on its bottom face (eight nodes, four positions);
    // element 2: the unit cube on that square, with nodes of its own
    const Model model =
        readModelText(std::string(PROPERTIES) + boxNodes(1, 0, 1, 0, 0) + boxNodes(11, 0, 1, 0, 1) + hexa(1, 1) +
                      hexa(2, 11));
    const std::vector<base::Vec3> points = {
        {0.3, 0.6, 0.02},  // in the cube, near the flat element
        {0.3, 0.6, -0.03}, // under both, near them
        {0.5, 0.5, 1.5},   // well above both
    };
    const std::vector<LocatedPoint> located = locate(model, points);
    REQUIRE(located.size() == points.size());
    // inside the cube: the cube, although the flat element has the lower ID. Its natural coordinates are 2 x - 1.
    REQUIRE(located[0].eid == 2);
    REQUIRE(located[0].distance == 0.0);
    REQUIRE(located[0].natural.x == Approx(-0.4));
    REQUIRE(located[0].natural.y == Approx(0.2));
    REQUIRE(located[0].natural.z == Approx(-0.96));
    requireWeightsSumToOne(located[0], 8);
    REQUIRE(located[0].nodes.front() == 11);
    // the weight of the first corner (-1, -1, -1): (1 + 0.4) (1 - 0.2) (1 + 0.96) / 8
    REQUIRE(located[0].weights.front() == Approx(1.4 * 0.8 * 1.96 / 8.0));
    // 0.03 under the bottom face of the cube, within the tolerance: the cube, at that distance
    REQUIRE(located[1].eid == 2);
    REQUIRE(located[1].distance == Approx(0.03));
    REQUIRE(located[1].natural.z == Approx(-1.06));
    // out of reach of the cube: no element, the flat one does not hold what is above it
    requireNotLocated(located[2]);
}

TEST_CASE("a hexahedron with no thickness holds no point of the cells it is in", "[analysis][geometry]")
{
    // element 1: the flat hexahedron on the unit square at z = 0; element 2: the unit cube next to it, from x = 1 to 2
    const Model model =
        readModelText(std::string(PROPERTIES) + boxNodes(1, 0, 1, 0, 0) + boxNodes(11, 1, 2, 0, 1) + hexa(1, 1) +
                      hexa(2, 11));
    const std::vector<base::Vec3> points = {
        {1.5, 0.5, 0.5},  // the middle of the cube
        {0.3, 0.6, 0.3},  // well above the flat element
        {0.3, 0.6, 0.02}, // just above the flat element
        {5.0, 5.0, 5.0},  // far from everything
    };
    const std::vector<LocatedPoint> located = locate(model, points);
    REQUIRE(located.size() == points.size());
    REQUIRE(located[0].eid == 2);
    REQUIRE(located[0].distance == 0.0);
    REQUIRE(located[0].natural.x == Approx(0.0).margin(1e-12));
    requireWeightsSumToOne(located[0], 8);
    // above the flat element and beside the cube: nothing holds these points. The flat element has no volume for
    // Newton's method to move in, so its natural coordinates say nothing of where the point is.
    requireNotLocated(located[1]);
    requireNotLocated(located[2]);
    requireNotLocated(located[3]);
}

TEST_CASE("points in, on and near two proper hexahedra are located as before", "[analysis][geometry]")
{
    // element 2: the unit cube; element 3: the cube next to it, from x = 1 to 2, on nodes of its own
    const Model model =
        readModelText(std::string(PROPERTIES) + boxNodes(11, 0, 1, 0, 1) + boxNodes(21, 1, 2, 0, 1) + hexa(2, 11) +
                      hexa(3, 21));
    const std::vector<base::Vec3> points = {
        {1.0, 0.5, 0.5},   // on the face they share
        {1.0, 1.0, 1.0},   // on a corner of both
        {1.5, 0.5, 1.02},  // just above the second
        {1.5, 0.5, 1.2},   // too far above it
        {1.75, 0.25, 0.5}, // inside the second
    };
    const std::vector<LocatedPoint> located = locate(model, points);
    REQUIRE(located.size() == points.size());
    // on the shared face both hold the point at the distance 0: the lower ID
    REQUIRE(located[0].eid == 2);
    REQUIRE(located[0].distance == 0.0);
    REQUIRE(located[0].natural.x == Approx(1.0));
    // on the corner (1, 1, 1): the seventh node of the first cube has all the weight
    REQUIRE(located[1].eid == 2);
    requireWeightsSumToOne(located[1], 8);
    REQUIRE(located[1].nodes[6] == 17);
    REQUIRE(located[1].weights[6] == Approx(1.0));
    // 0.02 above the top face: within the tolerance, at that distance, zeta = 2 * 1.02 - 1
    REQUIRE(located[2].eid == 3);
    REQUIRE(located[2].distance == Approx(0.02));
    REQUIRE(located[2].natural.z == Approx(1.04));
    // 0.2 above it: beyond the tolerance
    requireNotLocated(located[3]);
    REQUIRE(located[4].eid == 3);
    REQUIRE(located[4].distance == 0.0);
    REQUIRE(located[4].natural.x == Approx(0.5));
    REQUIRE(located[4].natural.y == Approx(-0.5));
    REQUIRE(located[4].natural.z == Approx(0.0).margin(1e-12));
}

TEST_CASE("a point in the dome of a curved hexahedron is found beyond the box of its nodes", "[analysis][geometry]")
{
    // A 20-node hexahedron on the unit cube whose four top mid-side nodes are raised to z = 1.2. On the line through
    // the middle of its faces (xi = eta = 0) the shape functions give
    //   z = (1 + zeta) (zeta - 2) / 2 * 1    the four top corners, at z = 1
    //     + (1 + zeta) * 1.2                 the four top mid-side nodes
    //     + (1 - zeta^2) * 0.5               the four mid-side nodes of the vertical edges
    //     = 0.7 (1 + zeta)
    // so the top face reaches z = 1.4 at its middle, 0.2 above the highest node. The point at z = 1.35 is inside the
    // element, at zeta = 1.35 / 0.7 - 1, and 0.15 above the box of the nodes: three times the tolerance.
    const double corners[8][3] = {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
                                  {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}};
    const double midSides[12][3] = {{0.5, 0, 0},   {1, 0.5, 0},   {0.5, 1, 0},   {0, 0.5, 0},
                                    {0, 0, 0.5},   {1, 0, 0.5},   {1, 1, 0.5},   {0, 1, 0.5},
                                    {0.5, 0, 1.2}, {1, 0.5, 1.2}, {0.5, 1, 1.2}, {0, 0.5, 1.2}};
    std::string deck = PROPERTIES;
    std::string card = "SolidHexa;10;1";
    for (int node = 0; node < 8; ++node)
        deck += grid(node + 1, corners[node][0], corners[node][1], corners[node][2]);
    for (int node = 0; node < 12; ++node)
        deck += grid(node + 9, midSides[node][0], midSides[node][1], midSides[node][2]);
    for (int node = 1; node <= 20; ++node)
        card += ";" + std::to_string(node);
    const Model model = readModelText(deck + card + "\n");
    const std::vector<base::Vec3> points = {
        {0.5, 0.5, 1.35}, // in the dome
        {0.5, 0.5, 0.35}, // in the lower half
        {0.5, 0.5, 1.6},  // above the dome
    };
    const std::vector<LocatedPoint> located = locate(model, points);
    REQUIRE(located.size() == points.size());
    REQUIRE(located[0].eid == 10);
    REQUIRE(located[0].distance == 0.0);
    REQUIRE(located[0].natural.x == Approx(0.0).margin(1e-9));
    REQUIRE(located[0].natural.y == Approx(0.0).margin(1e-9));
    REQUIRE(located[0].natural.z == Approx(1.35 / 0.7 - 1.0));
    requireWeightsSumToOne(located[0], 20);
    REQUIRE(located[1].eid == 10);
    REQUIRE(located[1].natural.z == Approx(0.35 / 0.7 - 1.0));
    // 0.2 above the top of the dome: beyond the tolerance
    requireNotLocated(located[2]);
}
