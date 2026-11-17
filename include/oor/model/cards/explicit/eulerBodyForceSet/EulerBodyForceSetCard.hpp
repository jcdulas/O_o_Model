#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One EulerBodyForceSet card (SOL 700): the body force of the Eulerian regions of a set. It is the alternative to an
// EulerBodyForce for the multi-material Euler solver: the acceleration is applied where the region and the material of
// an EulerForceRegion say, so the card only names the set of regions.
//
// Card layout: EulerBodyForceSet  SID  ESID  fields 1 and 2
// SID is the number an EulerProp or EulerRegionProp names in its SID2 (the category EulerBodyForce, shared with
// EulerBodyForce). ESID is the number of the set of EulerForceRegion cards that give the regions and the acceleration
// tables: several EulerForceRegion share it.
struct EulerBodyForceSetCard
{
    base::EntityId id = 0;          // unique among the body forces
    base::EntityId regionSetId = 0; // a set of EulerForceRegion cards
};

} // namespace oor::model
