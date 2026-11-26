// The skew test of a quadrilateral and the keywords of the tolerances of the element geometry tests.

#include "oor/analysis/quality/GeometryCheckThresholds.hpp"
#include "oor/analysis/quality/MeshQuality.hpp"
#include "support/ModelRecord.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <numbers>
#include <string>

using namespace oor;
using namespace oor::analysis;
using Catch::Approx;
using oor::testing::modelRecord;
using oor::testing::readModelText;

namespace
{

// The quality of a parallelogram of unit sides that make the angle `degrees`: the lines that join the middles of its
// opposite sides are parallel to its sides, so they cross at that angle, and its interior angles are that angle and
// 180 degrees less it.
QualityValues parallelogramQuality(double degrees)
{
    const double angle = degrees * std::numbers::pi / 180.0;
    const double dx = std::cos(angle);
    const double dy = std::sin(angle);
    const std::string deck = std::string("IsoMat;1;2.1E+5;;0.3\nShellProp;1;1;0.1\n") +
                             modelRecord("Node", 1, "", 0.0, 0.0, 0.0) + modelRecord("Node", 2, "", 1.0, 0.0, 0.0) +
                             modelRecord("Node", 3, "", 1.0 + dx, dy, 0.0) + modelRecord("Node", 4, "", dx, dy, 0.0) +
                             "ShellQuad4;10;1;1;2;3;4\n";
    const model::Model model = readModelText(deck);
    const auto location = model.locate(base::IdSpace::Element, 10);
    REQUIRE(location.has_value());
    return MeshQuality::of(model, *location);
}

} // namespace

TEST_CASE("the skew limit of a quadrilateral is the smallest angle allowed between its mid-lines",
          "[analysis][quality]")
{
    const GeometryCheckThresholds defaults;
    REQUIRE(defaults.q4Skew == 30.0);

    // Mid-lines at 55 degrees, more than the 30 of the limit: the skew, 90 - 55 = 35, fails nothing (the interior
    // angles 55 and 125 are within 30 and 150).
    const QualityValues open = parallelogramQuality(55.0);
    REQUIRE(open.skew == Approx(35.0));
    CHECK(defaults.failedChecks(ElementShape::Quadrilateral, open) == 0);

    // Mid-lines at 25 degrees, less than the limit: the skew, 65, fails.
    const QualityValues closed = parallelogramQuality(25.0);
    REQUIRE(closed.skew == Approx(65.0));
    CHECK((defaults.failedChecks(ElementShape::Quadrilateral, closed) & bit(QualityCheck::Skew)) != 0);

    // The skew alone, on each side of 90 - 30 = 60.
    QualityValues skewed;
    skewed.skew = 59.0;
    CHECK(defaults.failedChecks(ElementShape::Quadrilateral, skewed) == 0);
    skewed.skew = 61.0;
    CHECK(defaults.failedChecks(ElementShape::Quadrilateral, skewed) == bit(QualityCheck::Skew));

    // A limit of 20 degrees accepts the mid-lines at 25.
    GeometryCheckThresholds loose;
    REQUIRE(loose.set("QuadSkewLimit", 20.0));
    CHECK((loose.failedChecks(ElementShape::Quadrilateral, closed) & bit(QualityCheck::Skew)) == 0);
}

TEST_CASE("a tolerance is named by its keyword whatever the case of its letters", "[analysis][quality]")
{
    GeometryCheckThresholds thresholds;
    REQUIRE(thresholds.set("quadskewlimit", 20.0));
    CHECK(thresholds.q4Skew == 20.0);
    REQUIRE(thresholds.set("QuadSkewLimit", 25.0));
    CHECK(thresholds.q4Skew == 25.0);
    REQUIRE(thresholds.set("TETRAHEDRONASPECTRATIOLIMIT", 50.0));
    CHECK(thresholds.tetAr == 50.0);
    REQUIRE(thresholds.set("hexahedronWarpLimit", 0.5));
    CHECK(thresholds.hexWarp == 0.5);

    // Any other name is refused and changes nothing: an abbreviation, a keyword cut short or made longer, nothing.
    CHECK_FALSE(thresholds.set("Q4_SKEW", 20.0));
    CHECK_FALSE(thresholds.set("QuadSkew", 1.0));
    CHECK_FALSE(thresholds.set("QuadSkewLimits", 1.0));
    CHECK_FALSE(thresholds.set("", 1.0));
    CHECK(thresholds.q4Skew == 25.0);
}
