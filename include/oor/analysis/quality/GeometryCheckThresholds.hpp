#pragma once

#include "oor/analysis/adjacency/ElementTopology.hpp"
#include "oor/analysis/quality/QualityMetrics.hpp"
#include "oor/model/core/Model.hpp"

#include <cstdint>
#include <string_view>
#include <vector>

namespace oor::analysis
{

// The tests an element can fail. A bit each; an element's failed checks are the bits that are set.
enum class QualityCheck : std::uint16_t
{
    AspectRatio = 1,
    Skew = 2,
    Warp = 4,
    Taper = 8,
    MinAngle = 16,
    MaxAngle = 32,
    Jacobian = 64,
    EdgePointLength = 128,
    EdgePointAngle = 256,
    FaceWarp = 512
};

inline constexpr std::size_t QUALITY_CHECK_COUNT = 10;

[[nodiscard]] constexpr std::uint16_t bit(QualityCheck check) noexcept
{
    return static_cast<std::uint16_t>(check);
}
// The name of a check, as the Python arrays and the quality query call it: "aspectRatio", "skew", "warp", "taper",
// "minAngle", "maxAngle", "jacobian", "edgePointLengthRatio", "edgePointAngle", "faceWarp".
[[nodiscard]] std::string_view qualityCheckName(QualityCheck check) noexcept;
// Every check, in the order of the bits.
[[nodiscard]] const std::vector<QualityCheck>& allQualityChecks();

// clang-format off
// The tolerances of the element geometry tests of the GeometryCheck statement (format reference GEOMCHECK). The
// defaults are the format's; fromModel() gives the ones the deck's own GeometryCheck statements change. A tolerance is
// named by its keyword in the model file (QuadSkewLimit, TetrahedronAspectRatioLimit, ...), whatever the case of its
// letters.
//
// How each keyword is used (the format reference says which elements it applies to; here a Quad keyword applies to
// every quadrilateral shell and a Triangle keyword to every triangle shell, the ones of a solid shape to the solids of
// that shape: Shape below is Tetrahedron, Pentahedron, Hexahedron or Pyramid). An element fails a test when:
//
//   QuadSkewLimit      skew > 90 - tolerance: the tolerance is the smallest angle allowed between the lines that join
//                      the middles of opposite sides, and the skew of this library is 90 degrees less that angle
//   QuadTaperLimit     taper > tolerance
//   QuadWarpLimit      warp > tolerance
//   QuadMinAngle       minAngle < tolerance
//   QuadMaxAngle       maxAngle > tolerance
//   TriangleMinAngle   minAngle < tolerance (the format reference tests the skew of a triangle, which it defines as
//                      its smallest vertex angle)
//   TriangleMaxAngle   maxAngle > tolerance
//   ShapeAspectRatioLimit            aspectRatio > tolerance
//   ShapeEdgePointLengthRatioLimit   edgePointLengthRatio > tolerance
//   ShapeEdgePointAngleLimit         edgePointAngle < tolerance
//   ShapeJacobianLimit               jacobianMin <= tolerance (TetrahedronGlobalJacobianLimit too: the same value,
//                                    taken at the corners and the centre)
//   ShapeWarpLimit                   faceWarp < tolerance (Hexahedron, Pentahedron, Pyramid)
//
// A metric that is NaN fails nothing. The other parameters of the statement (the offsets of bars and beams, and what
// the solver prints: MessageLimit, MessageKind, NoMessages, ...) do not concern the quality of a mesh and are ignored.
// clang-format on
struct GeometryCheckThresholds
{
    double q4Skew = 30.0;
    double q4Taper = 0.50;
    double q4Warp = 0.05;
    double q4Iamin = 30.0;
    double q4Iamax = 150.0;
    double t3Skew = 10.0;
    double t3Iamax = 160.0;
    double tetAr = 100.0;
    double tetEplr = 0.50;
    double tetEpia = 150.0;
    double tetDetj = 0.0;
    double tetDetg = 0.0;
    double hexAr = 100.0;
    double hexEplr = 0.50;
    double hexEpia = 150.0;
    double hexDetj = 0.0;
    double hexWarp = 0.707;
    double penAr = 100.0;
    double penEplr = 0.50;
    double penEpia = 150.0;
    double penDetj = 0.0;
    double penWarp = 0.707;
    double pyrAr = 100.0;
    double pyrEplr = 0.50;
    double pyrEpia = 150.0;
    double pyrDetj = 0.0;
    double pyrWarp = 0.707;

    // Sets the tolerance a keyword names (QuadSkewLimit, ...; case does not matter); false when the keyword is not one
    // of the tolerances above.
    bool set(std::string_view keyword, double value) noexcept;

    // The defaults changed by the GeometryCheck statements of the Executive Control of the model, in order (the last
    // one that names a keyword counts). A tolerance that is not a number is ignored.
    [[nodiscard]] static GeometryCheckThresholds fromModel(const model::Model& model);

    // The checks the element fails, as the bits of QualityCheck, for an element of this shape with these metrics.
    [[nodiscard]] std::uint16_t failedChecks(ElementShape shape, const QualityValues& values) const noexcept;
};

} // namespace oor::analysis
