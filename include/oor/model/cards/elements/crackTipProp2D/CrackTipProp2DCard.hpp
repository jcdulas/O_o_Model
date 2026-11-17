#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstdint>

namespace oor::model
{

// One CrackTipProp2D card: the property of a CrackTip2D crack tip element.
//
// Card layout:
//   CrackTipProp2D  PID  MID  T  IPLANE  NSM  GAMMA  PHI
//
// MID is an IsoMat, an AnisoMat2D or an OrthoMat2D (plane strain, IPLANE 0, takes IsoMat data only: advice of the
// format reference, not checked here). T is the thickness (positive). IPLANE is 0 for plane strain and 1 for plane
// stress, and 0 when blank. NSM is the non-structural mass per unit area (not negative, 0.0 by default). GAMMA is the
// exponent of the displacement field (0.5 by default) and PHI the angle in degrees, from the element x axis, along
// which the stress intensity factors are found (180.0 by default); the format reference says other values than the
// defaults of these two have not been tested. The format reference gives IPLANE a default, so a blank IPLANE reads as
// 0.
struct CrackTipProp2DCard
{
    static constexpr std::int32_t DEFAULT_PLANE_CONDITION = 0;
    static constexpr double DEFAULT_GAMMA = 0.5;
    static constexpr double DEFAULT_PHI = 180.0;

    base::EntityId id = 0;
    base::EntityId matId = 0;
    double thickness = 0.0;
    std::int32_t planeCondition = DEFAULT_PLANE_CONDITION;
    double nonStructMass = 0.0;
    double gammaCoefficient = DEFAULT_GAMMA;
    double phiAngle = DEFAULT_PHI;
};

} // namespace oor::model
