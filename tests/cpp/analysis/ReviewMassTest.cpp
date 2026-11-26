#include "oor/analysis/mass/MassCalculator.hpp"
#include "support/ModelRecord.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <string>

using namespace oor;
using namespace oor::analysis;
using Catch::Approx;
using oor::testing::readModelText;

// The structural mass of a beam is on its neutral axis, which a BeamProp gives as (y, z) from the line of the shear
// centres (the element x axis) at the two ends; the non-structural mass is at its own centre of gravity.

namespace
{

constexpr double RHO = 0.001;
const char* const MATERIAL = "IsoMat;1;2.1E+5;;0.3;0.001\n";

// The record of a node: id, x, y, z in the basic system.
std::string grid(int id, double x, double y, double z)
{
    return oor::testing::modelRecord("Node", id, "", x, y, z);
}

// A Beam2 along the basic x axis from the origin, oriented by the vector (0, 0, 1): its y axis is the basic z and its
// z axis the opposite of the basic y.
std::string beamAlongX(double length)
{
    return grid(1, 0, 0, 0) + grid(2, length, 0, 0) + "Beam2;10;1;1;2;0.;;0.;1.\n";
}

// A BeamProp of two stations (the areas and the non-structural masses of ends A and B) with the centre of the
// non-structural mass (M1, M2) and the neutral axis (N1, N2) of the two ends, each written "y(A);z(A);y(B);z(B)".
std::string beamProp(const std::string& areaA, const std::string& nsmA, const std::string& areaB,
                     const std::string& nsmB, const std::string& nsmCentre, const std::string& neutralAxis)
{
    return "BeamProp;1;1;" + areaA + ";1.;1.;0.;1.;" + nsmA + ";No;1.;" + areaB + ";1.;1.;0.;1.;" + nsmB +
           ";;1.;1.;;;;;;;" + nsmCentre + ";" + neutralAxis + "\n";
}

ElementMasses massOfBeam(const model::Model& model)
{
    const auto location = model.locate(base::IdSpace::Element, 10);
    REQUIRE(location.has_value());
    return MassCalculator::of(model, *location, MassOptions{});
}

void requireVec(const base::Vec3& actual, double x, double y, double z, double margin = 1e-12)
{
    REQUIRE(actual.x == Approx(x).margin(margin));
    REQUIRE(actual.y == Approx(y).margin(margin));
    REQUIRE(actual.z == Approx(z).margin(margin));
}

} // namespace

TEST_CASE("the structural mass of a beam is on the neutral axis its property gives", "[analysis][mass][review]")
{
    // A uniform beam 4 long whose neutral axis is at (0.5, 0.25) in the element system: 0.5 along the basic z and
    // 0.25 against the basic y.
    const model::Model model = readModelText(
        std::string(MATERIAL) + beamProp("1.", "0.", "1.", "0.", "0.;0.;0.;0.", "0.5;0.25;0.5;0.25") + beamAlongX(4.0));
    const ElementMasses masses = massOfBeam(model);
    REQUIRE(masses.structural.front() == Approx(RHO * 4.0));
    REQUIRE(masses.nonStructural.front() == 0.0);
    requireVec(masses.center.front(), 2.0, -0.25, 0.5);
    // one mass at one place: no inertia of its own
    REQUIRE(masses.inertia.empty());
}

TEST_CASE("a neutral axis that moves along a tapered beam is taken at the centre of its structural mass",
          "[analysis][mass][review]")
{
    // The area goes from 2 to 4 over a beam 6 long: A(x) = 2 + 2x over [0, 1] has its centre at 5/9. The neutral axis
    // goes from 0 to 0.9 along the element y axis: the mean of that offset weighted by the area is 0.9 * 5/9 = 0.5.
    const model::Model model = readModelText(
        std::string(MATERIAL) + beamProp("2.", "0.", "4.", "0.", "0.;0.;0.;0.", "0.;0.;0.9;0.") + beamAlongX(6.0));
    const ElementMasses masses = massOfBeam(model);
    REQUIRE(masses.structural.front() == Approx(RHO * 3.0 * 6.0));
    requireVec(masses.center.front(), 6.0 * 5.0 / 9.0, 0.0, 0.5);
}

TEST_CASE("the structural and the non-structural mass of a beam each have their own place off its axis",
          "[analysis][mass][review]")
{
    // A uniform beam 4 long, area 1, non-structural mass 0.5 per unit length.
    const double structural = RHO * 4.0;
    const double nonStructural = 0.5 * 4.0;
    const double total = structural + nonStructural;

    // Both at 1 along the element y axis: one body at one place.
    const model::Model together = readModelText(
        std::string(MATERIAL) + beamProp("1.", "0.5", "1.", "0.5", "1.;0.;1.;0.", "1.;0.;1.;0.") + beamAlongX(4.0));
    const ElementMasses one = massOfBeam(together);
    REQUIRE(one.structural.front() == Approx(structural));
    REQUIRE(one.nonStructural.front() == Approx(nonStructural));
    requireVec(one.center.front(), 2.0, 0.0, 1.0);
    REQUIRE(one.inertia.empty());

    // The neutral axis at 0.5 and the non-structural mass at 1: their common centre, and the inertia of two masses
    // 0.5 apart along the basic z about it, m1 m2 / (m1 + m2) d^2 about the basic x and y axes.
    const model::Model apart = readModelText(
        std::string(MATERIAL) + beamProp("1.", "0.5", "1.", "0.5", "1.;0.;1.;0.", "0.5;0.;0.5;0.") + beamAlongX(4.0));
    const ElementMasses two = massOfBeam(apart);
    requireVec(two.center.front(), 2.0, 0.0, (structural * 0.5 + nonStructural * 1.0) / total);
    REQUIRE(two.inertia.size() == 1);
    const double own = structural * nonStructural / total * 0.25;
    REQUIRE(two.inertia.front().tensor(0, 0) == Approx(own));
    REQUIRE(two.inertia.front().tensor(1, 1) == Approx(own));
    REQUIRE(two.inertia.front().tensor(2, 2) == Approx(0.0).margin(1e-15));
}
