#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One AxisymConePoint card: a point on a ring of a conical shell model, where FORCE or MOMENT loads may be applied and
// displacements requested. The point is not subject to constraints of a MultiPointConstrAxisym, SinglePointConstrAxisym
// or AxisymOmittedDofSet. The card needs an AxisymConeControl card in the deck, which is a rule between cards.
//
// Card layout:
//   AxisymConePoint  ID  RID  PHI
//
// The ID is in the node ID space (the format reference asks it to be unique among the AxisymConePoint, AxisymConeRing
// and AxisymConeSector numbers: an AxisymConeRing shares the space, the AxisymConeSector, which is typed apart, is a
// rule between cards). RID is the number of the AxisymConeRing the point is on (a node reference) and PHI the azimuthal
// angle in degrees, a real the format gives no default for, so it is required.
struct AxisymConePointCard
{
    base::EntityId id = 0;
    base::EntityId ringId = 0; // the AxisymConeRing the point is on
    double phiAngle = 0.0;     // azimuthal angle, in degrees
};

} // namespace oor::model
