#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One CompPropFreqDamping card (SOL 400): the frequency dependent structural damping of the CompProp or CompPropGlobal
// with the same PID.
//
// Card layout:
//   CompPropFreqDamping  PID  (blank x5)  GE        GE is field 7 (column 8, the one the GE of a CompProp has)
//
// The ID is the one of the CompProp or CompPropGlobal it extends (the card has an ID space of its own: one
// CompPropFreqDamping for each laminate). GE is the TABLEDi that gives the non-dimensional structural damping
// coefficient against frequency; it replaces the GE of the CompProp or CompPropGlobal, 0 when blank (the format
// reference says the table must be blank or 0 when that GE is zero, which is a rule between the two cards).
struct CompPropFreqDampingCard
{
    base::EntityId id = 0;
    base::EntityId structuralDamping = 0; // a TABLEDi, 0 when blank
};

} // namespace oor::model
