#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstdint>

namespace oor::model
{

// One AcousticInfiniteProp card: the property of the acoustic conjugate infinite elements (AcousticInfiniteTria3 and
// AcousticInfiniteQuad4). The pole and the grid points of the base give the geometry of each element (format reference
// figure: the element goes from the base away from the pole).
//
// Card layout: AcousticInfiniteProp  PID  MID  RIO  XP  YP  ZP
// PID is a property ID (positive); MID names a FluidMat, the fluid of the element; RIO is the radial interpolation
// order, a positive integer with no default. XP, YP and ZP are the coordinates of the pole in the basic system. The
// format reference gives them no default and no "required" mark; a blank one is read as 0.0, as every blank coordinate
// of the Bulk Data is, and is written back as a blank.
struct AcousticInfinitePropCard
{
    base::EntityId id = 0;        // unique among the properties
    base::EntityId matId = 0;     // a FluidMat
    std::int32_t radialOrder = 0; // radial interpolation order, greater than zero
    double poleX = 0.0;           // the pole, in the basic coordinate system
    double poleY = 0.0;
    double poleZ = 0.0;
};

} // namespace oor::model
