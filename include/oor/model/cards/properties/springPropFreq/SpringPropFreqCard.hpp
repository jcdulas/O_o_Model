#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One SpringPropFreq card: the frequency dependent or nonlinear properties of the SpringProp with the same ID.
//
// Card layout:
//   SpringPropFreq  PID  TKID  TGEID  TKNID
//
// The ID is the one of the SpringProp it extends (the card has an ID space of its own: one SpringPropFreq per
// SpringProp). The three others are TABLEDi entries, 0 when blank: the force per unit displacement against frequency,
// the structural damping against frequency, and the nonlinear force against displacement.
struct SpringPropFreqCard
{
    base::EntityId id = 0;
    base::EntityId stiffnessTableId = 0;
    base::EntityId structuralDampingTableId = 0;
    base::EntityId nonlinearForceTableId = 0;
};

} // namespace oor::model
