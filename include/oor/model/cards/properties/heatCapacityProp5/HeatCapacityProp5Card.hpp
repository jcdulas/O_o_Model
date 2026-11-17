#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One HeatCapacityProp5 card: the property of a HeatCapacity2 (a heat transfer damper: the mass that multiplies the
// heat capacity of a HeatIsoMat or HeatAnisoMat material).
//
// Card layout:
//   HeatCapacityProp5  PID  MID  B
struct HeatCapacityProp5Card
{
    base::EntityId id = 0;
    base::EntityId matId = 0;
    double heatCapacity = 0.0; // damping multiplier
};

} // namespace oor::model
