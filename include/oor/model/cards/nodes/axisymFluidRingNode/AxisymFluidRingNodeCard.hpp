#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstdint>

namespace oor::model
{

// One AxisymFluidRingNode card: a grid point on a fluid ring (AxisymFluidRing) of an axisymmetric model.
//
// Card layout (fields 2, 3 and 5 are ignored on reading, so that a Node can be turned into an AxisymFluidRingNode; they
// are not kept):
//   AxisymFluidRingNode  ID  PHI       CD  PS  IDF
//
// The ID shares the node ID space with the GRIDs and the scalar points.
struct AxisymFluidRingNodeCard
{
    base::EntityId id = 0;
    double phiAngle = 0.0;                  // azimuthal position of the fluid, in degrees
    base::EntityId displacementFrameId = 0; // coordinate system of the displacements (0 = basic)
    std::int32_t permanentConstraints = 0;  // permanent single-point constraints, as digits 1..6 (0 = none)
    base::EntityId fluidPointId = 0;        // the AxisymFluidRing entry this point is on
};

} // namespace oor::model
