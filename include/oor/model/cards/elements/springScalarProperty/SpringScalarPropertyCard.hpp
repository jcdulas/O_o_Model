#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One SpringScalarProperty card: a scalar spring between two scalar points, with a SpringProp property.
//
// Card layout:
//   SpringScalarProperty  EID  PID  S1  S2
//
// S1 and S2 are scalar points; 0 (or blank) is a grounded end.
struct SpringScalarPropertyCard
{
    base::EntityId id = 0;
    base::EntityId propId = 0; // stored resolved: a blank PID is EID
    base::EntityId scalarPoint1 = 0;
    base::EntityId scalarPoint2 = 0;
};

} // namespace oor::model
