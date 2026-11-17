#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/sets/DofLists.hpp"

#include <vector>

namespace oor::model
{

// One AeroBoxList card: a list of aerodynamic boxes (or aerodynamic grid points) that an AeroControlSurface, an
// AeroComponent or an AeroSurfaceSpline4 or AeroBeamSpline5 names by its SID.
//
// Card layout: AeroBoxList  SID  E1  E2  E3  E4  E5  E6  E7
//                          E8  -etc.-
// or, with ranges: AeroBoxList  SID  E1  "THRU"  E2  E3  "THRU"  E4 ...
// The list is kept as written: single IDs and THRU ranges, in order. The items are the IDs of the boxes of a CAERO
// (ReferenceTarget::AeroBox), the numbers of the (x, y) pairs of a Mach box lifting surface or the aerodynamic grid
// points of an AeroNode mesh, which the card cannot tell apart.
struct AeroBoxListCard
{
    base::EntityId id = 0;
    std::vector<IdRun> ids;
};

} // namespace oor::model
