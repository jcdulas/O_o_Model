#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <vector>

namespace oor::model
{

// One SinglePointConstrUnion card: a constraint set that is the union of other constraint sets.
//
// Card layout: SinglePointConstrUnion  SID  S1  S2  S3  S4  S5  S6  S7
//                                     S8  S9  -etc.-
// The Si are set IDs of cards of the Constraint category (SinglePointConstr, SinglePointConstrList, ...), kept in the
// order they are written in.
struct SinglePointConstrUnionCard
{
    base::EntityId id = 0;
    std::vector<base::EntityId> sets;
};

} // namespace oor::model
