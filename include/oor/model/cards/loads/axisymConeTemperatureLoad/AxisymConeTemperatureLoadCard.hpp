#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One temperature of an AxisymConeTemperatureLoad card: the temperature of a ring of a conical shell model at an
// azimuth angle.
//
// Card layout: AxisymConeTemperatureLoad  SID1  RID1  PHI1  T1  SID2  RID2  PHI2  T2
// A card holds one or two such groups, each for a set of its own: the groups are separate objects here, one row each,
// and are written as cards of their own. AxisymConeTemperatureLoad needs an AxisymConeControl card in the deck.
struct AxisymConeTemperatureLoadCard
{
    base::EntityId id = 0;
    base::EntityId ringId = 0; // RID: an AxisymConeRing
    double phi = 0.0;          // the azimuth angle, in degrees
    double temperature = 0.0;
};

} // namespace oor::model
