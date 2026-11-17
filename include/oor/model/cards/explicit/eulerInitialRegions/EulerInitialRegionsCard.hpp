#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One EulerInitialRegions card (SOL 700): the initial conditions of the Eulerian regions. An EulerRegionProp names it
// in its SID, and it names the group of InitialConditionRegion cards that define the regions and the values each one
// starts with. An InitialElemValues initializes a set of elements and an EulerInitialRegions initializes regions
// (spheres, cylinders, ...); an Euler element that both name takes the InitialElemValues. No other entry of the format
// reference has this name.
//
// Card layout: EulerInitialRegions  SID  TSID                                      fields 1 and 2
// SID is the number of the card, the one an EulerRegionProp names: the ID of the table, unique among the
// EulerInitialRegions cards. TSID is the number of a group of InitialConditionRegion cards, which share it in their
// first TSID field: a reference to the group, so Python sees the list of the cards of the group.
struct EulerInitialRegionsCard
{
    base::EntityId id = 0;            // the number of the card
    base::EntityId regionGroupId = 0; // the group of InitialConditionRegion cards
};

} // namespace oor::model
