#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One scalar damper property of a DamperProp card.
//
// Card layout (a card defines one to four properties, each of two fields):
//   DamperProp  PID1  B1  PID2  B2  PID3  B3  PID4  B4
//
// A card with several properties gives one DamperPropCard value each, written as a card of its own, so that every
// property can be renumbered or deleted alone (as a SpringProp with two springs is).
struct DamperPropCard
{
    base::EntityId id = 0;
    double damping = 0.0; // force per unit velocity
};

} // namespace oor::model
