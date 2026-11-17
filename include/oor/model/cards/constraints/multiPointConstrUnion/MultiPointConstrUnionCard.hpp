#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <vector>

namespace oor::model
{

// One MultiPointConstrUnion card: a multipoint constraint set that is the union of other multipoint constraint sets.
//
// Card layout: MultiPointConstrUnion  SID  S1  S2  S3  S4  S5  S6  S7
//                                    S8  S9  -etc.-
// The Si are set IDs of cards of the Constraint category (MPC, ...), kept in the order they are written in. The MPC
// Case Control command selects SID; a MultiPointConstrUnion wins over a MultiPointConstr that has the same SID.
struct MultiPointConstrUnionCard
{
    base::EntityId id = 0;
    std::vector<base::EntityId> sets;
};

} // namespace oor::model
