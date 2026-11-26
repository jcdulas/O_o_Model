#include "oor/analysis/quality/GeometryCheckThresholds.hpp"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <string>

namespace oor::analysis
{

std::string_view qualityCheckName(QualityCheck check) noexcept
{
    switch (check)
    {
    case QualityCheck::AspectRatio:
        return "aspectRatio";
    case QualityCheck::Skew:
        return "skew";
    case QualityCheck::Warp:
        return "warp";
    case QualityCheck::Taper:
        return "taper";
    case QualityCheck::MinAngle:
        return "minAngle";
    case QualityCheck::MaxAngle:
        return "maxAngle";
    case QualityCheck::Jacobian:
        return "jacobian";
    case QualityCheck::EdgePointLength:
        return "edgePointLengthRatio";
    case QualityCheck::EdgePointAngle:
        return "edgePointAngle";
    case QualityCheck::FaceWarp:
        return "faceWarp";
    }
    return {};
}

const std::vector<QualityCheck>& allQualityChecks()
{
    static const std::vector<QualityCheck> CHECKS = {
        QualityCheck::AspectRatio,    QualityCheck::Skew,     QualityCheck::Warp,     QualityCheck::Taper,
        QualityCheck::MinAngle,       QualityCheck::MaxAngle, QualityCheck::Jacobian, QualityCheck::EdgePointLength,
        QualityCheck::EdgePointAngle, QualityCheck::FaceWarp};
    return CHECKS;
}

namespace
{

// True when the two texts are the same but for the case of their letters.
bool sameIgnoringCase(std::string_view left, std::string_view right) noexcept
{
    const auto sameLetter = [](unsigned char first, unsigned char second)
    { return std::tolower(first) == std::tolower(second); };
    return std::equal(left.begin(), left.end(), right.begin(), right.end(), sameLetter);
}

} // namespace

bool GeometryCheckThresholds::set(std::string_view keyword, double value) noexcept
{
    // The neutral keywords, whatever the case of their letters.
    const auto is = [keyword](std::string_view name) { return sameIgnoringCase(keyword, name); };
    if (is("QuadSkewLimit"))
        q4Skew = value;
    else if (is("QuadTaperLimit"))
        q4Taper = value;
    else if (is("QuadWarpLimit"))
        q4Warp = value;
    else if (is("QuadMinAngle"))
        q4Iamin = value;
    else if (is("QuadMaxAngle"))
        q4Iamax = value;
    else if (is("TriangleMinAngle"))
        t3Skew = value;
    else if (is("TriangleMaxAngle"))
        t3Iamax = value;
    else if (is("TetrahedronAspectRatioLimit"))
        tetAr = value;
    else if (is("TetrahedronEdgePointLengthRatioLimit"))
        tetEplr = value;
    else if (is("TetrahedronEdgePointAngleLimit"))
        tetEpia = value;
    else if (is("TetrahedronJacobianLimit"))
        tetDetj = value;
    else if (is("TetrahedronGlobalJacobianLimit"))
        tetDetg = value;
    else if (is("HexahedronAspectRatioLimit"))
        hexAr = value;
    else if (is("HexahedronEdgePointLengthRatioLimit"))
        hexEplr = value;
    else if (is("HexahedronEdgePointAngleLimit"))
        hexEpia = value;
    else if (is("HexahedronJacobianLimit"))
        hexDetj = value;
    else if (is("HexahedronWarpLimit"))
        hexWarp = value;
    else if (is("PentahedronAspectRatioLimit"))
        penAr = value;
    else if (is("PentahedronEdgePointLengthRatioLimit"))
        penEplr = value;
    else if (is("PentahedronEdgePointAngleLimit"))
        penEpia = value;
    else if (is("PentahedronJacobianLimit"))
        penDetj = value;
    else if (is("PentahedronWarpLimit"))
        penWarp = value;
    else if (is("PyramidAspectRatioLimit"))
        pyrAr = value;
    else if (is("PyramidEdgePointLengthRatioLimit"))
        pyrEplr = value;
    else if (is("PyramidEdgePointAngleLimit"))
        pyrEpia = value;
    else if (is("PyramidJacobianLimit"))
        pyrDetj = value;
    else if (is("PyramidWarpLimit"))
        pyrWarp = value;
    else
        return false;
    return true;
}

GeometryCheckThresholds GeometryCheckThresholds::fromModel(const model::Model& model)
{
    GeometryCheckThresholds thresholds;
    for (const model::ControlStatement* statement : model.control().executive.findAll("GeometryCheck"))
    {
        for (const model::StatementParameter& parameter : statement->parameters)
        {
            if (!parameter.hasValue)
                continue;
            double value = 0.0;
            const char* begin = parameter.value.data();
            const char* end = begin + parameter.value.size();
            const auto [stop, error] = std::from_chars(begin, end, value);
            if (error != std::errc() || stop != end)
                continue; // not a number: the statement is not one of the tolerances
            thresholds.set(parameter.name, value);
        }
    }
    return thresholds;
}

namespace
{

constexpr double RIGHT_ANGLE = 90.0; // degrees

// The checks of a solid: the aspect ratio, the position and angle of the mid-side nodes, the Jacobian, the warp of the
// quadrilateral faces.
std::uint16_t solidChecks(const QualityValues& values, double aspect, double eplr, double epia, double detj,
                          double warp) noexcept
{
    std::uint16_t failed = 0;
    if (values.aspectRatio > aspect)
        failed |= bit(QualityCheck::AspectRatio);
    if (values.edgePointLengthRatio > eplr)
        failed |= bit(QualityCheck::EdgePointLength);
    if (values.edgePointAngle < epia)
        failed |= bit(QualityCheck::EdgePointAngle);
    if (values.jacobianMin <= detj)
        failed |= bit(QualityCheck::Jacobian);
    if (values.faceWarp < warp)
        failed |= bit(QualityCheck::FaceWarp);
    return failed;
}

} // namespace

std::uint16_t GeometryCheckThresholds::failedChecks(ElementShape shape, const QualityValues& values) const noexcept
{
    std::uint16_t failed = 0;
    switch (shape)
    {
    case ElementShape::Triangle:
        if (values.minAngle < t3Skew)
            failed |= bit(QualityCheck::MinAngle);
        if (values.maxAngle > t3Iamax)
            failed |= bit(QualityCheck::MaxAngle);
        break;
    case ElementShape::Quadrilateral:
        // The limit is the smallest angle allowed between the lines that join the middles of opposite sides;
        // the skew is 90 degrees less that angle.
        if (values.skew > RIGHT_ANGLE - q4Skew)
            failed |= bit(QualityCheck::Skew);
        if (values.taper > q4Taper)
            failed |= bit(QualityCheck::Taper);
        if (values.warp > q4Warp)
            failed |= bit(QualityCheck::Warp);
        if (values.minAngle < q4Iamin)
            failed |= bit(QualityCheck::MinAngle);
        if (values.maxAngle > q4Iamax)
            failed |= bit(QualityCheck::MaxAngle);
        break;
    case ElementShape::Tetrahedron:
        failed = solidChecks(values, tetAr, tetEplr, tetEpia, std::max(tetDetj, tetDetg), -2.0);
        break;
    case ElementShape::Hexahedron:
        failed = solidChecks(values, hexAr, hexEplr, hexEpia, hexDetj, hexWarp);
        break;
    case ElementShape::Pentahedron:
        failed = solidChecks(values, penAr, penEplr, penEpia, penDetj, penWarp);
        break;
    case ElementShape::Pyramid:
        failed = solidChecks(values, pyrAr, pyrEplr, pyrEpia, pyrDetj, pyrWarp);
        break;
    default:
        break;
    }
    return failed;
}

} // namespace oor::analysis
