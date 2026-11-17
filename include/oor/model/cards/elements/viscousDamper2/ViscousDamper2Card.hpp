#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One ViscousDamper2 card: a viscous damper between two grid points, with a ViscousDamperProp property.
//
// Card layout:
//   ViscousDamper2  EID  PID  G1  G2
//
// G1 and G2 are two different grid points.
struct ViscousDamper2Card
{
    base::EntityId id = 0;
    base::EntityId propId = 0; // stored resolved: a blank PID is EID
    base::EntityId node1 = 0;
    base::EntityId node2 = 0;
};

} // namespace oor::model
