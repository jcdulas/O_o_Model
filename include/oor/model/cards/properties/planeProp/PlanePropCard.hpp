#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstdint>
#include <optional>

namespace oor::model
{

// One PlaneProp card: the property of a plane strain or plane stress element (the CPLSTN and CPLSTS elements of another
// implementation of the format), with a thickness and a mass that is not structural.
//
// Layout: PlaneProp  PID  MID  T  NSM  FORMULATION_OPTION
//
// The layout is that of another implementation of the format (for example PlaneProp 3 1 1.); the card is not in the
// format reference list and the format reference says no more. MID is a material of the solid kinds (IsoMat,
// AxisymOrthoMat, HeatIsoMat, HeatAnisoMat, OrthoMat2D, HyperelasticMat and HyperelasticPolynomialMat). A blank T has
// no default that a source here confirms (decks give 1.0): it stays blank, as `std::nullopt`. A blank NSM is 0.0. The
// meaning of the FORMULATION_OPTION is not given by any source here; the card keeps the number as the deck wrote it (0
// when blank) and refuses a negative one.
struct PlanePropCard
{
    base::EntityId id = 0;
    base::EntityId matId = 0;
    std::optional<double> thickness;
    double nonStructMass = 0.0;
    std::int32_t formulationOption = 0;
};

} // namespace oor::model
