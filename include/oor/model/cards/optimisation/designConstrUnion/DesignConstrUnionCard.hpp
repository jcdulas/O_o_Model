#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <vector>

namespace oor::model
{

// One DesignConstrUnion card: the design constraints of a subcase as the union of several DesignConstr sets.
//
// Card layout: DesignConstrUnion  DCID  DC1  DC2  DC3  DC4  DC5  DC6  DC7  fields 1 to 8
//                                DC8   -etc.-                             fields 9 to 16, and so on
// The set DCID is selected by DESSUB or DESGLB; each DCi is the DCID of a DesignConstr set (a DCi is named by one
// DesignConstrUnion only).
struct DesignConstrUnionCard
{
    base::EntityId constraintSetId = 0;
    std::vector<base::EntityId> sets; // the DCi; at least one
};

} // namespace oor::model
