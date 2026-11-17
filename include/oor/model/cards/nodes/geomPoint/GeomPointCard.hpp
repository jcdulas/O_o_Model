#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/base/math/Vec3.hpp"

namespace oor::model
{

// One GeomPoint card: a geometric point that is not a grid point (an edge point for SuperelementLocation, a profile
// point of a BeamArbitrarySectionProp).
//
// Card layout:
//   GeomPoint  ID  CP  X1  X2  X3
//
// The ID shares the node ID space with the GRIDs (the format reference: unique with respect to the GRID IDs).
struct GeomPointCard
{
    base::EntityId id = 0;
    base::EntityId positionFrameId = 0; // coordinate system of the location (0 = basic)
    base::Vec3 xyz;                     // X1 X2 X3 in the system CP
};

} // namespace oor::model
