#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <vector>

namespace oor::model
{

// One NonStructMassUnion card: a set of non-structural mass that is the sum of other sets.
//
// Card layout: NonStructMassUnion  SID  S1  S2  S3  S4  S5  S6  S7
//                                 S8  S9  -etc.-
// Each Si is the set ID of NonStructMass, NonStructMass1, NonStructMassLumped or NonStructMassLumped1 cards; none may
// be the ID of another NonStructMassUnion. An NonStructMassUnion takes precedence over the cards of the same set ID.
struct NonStructMassUnionCard
{
    base::EntityId id = 0;
    std::vector<base::EntityId> sets;
};

} // namespace oor::model
