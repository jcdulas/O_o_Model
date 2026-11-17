#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One CouplingInteraction card (SOL 700): an interaction between two coupling surfaces that becomes active when the
// structure that carries them fails. Like CouplingFailedSegmentFlow it belongs to the fast coupling algorithm in its
// failure form (ExplicitParam,FASTCOUP,,FAIL) with the HYDRO, MMHYDRO or MMSTREN Euler solver.
//
// Card layout: CouplingInteraction  CID  CID1  CID2  fields 1 to 3
// CID numbers the card; CID1 and CID2 are the numbers of the two EulerLagrangeCoupling cards. a common deck gives CID1
// only (CouplingInteraction 33 and 2) and the format does not say that CID2 is required, so a blank CID2 is read as 0,
// no second surface, and CID1 is the one that must be there.
struct CouplingInteractionCard
{
    base::EntityId id = 0;          // unique among the CouplingInteraction cards
    base::EntityId couplingId1 = 0; // an EulerLagrangeCoupling
    base::EntityId couplingId2 = 0; // an EulerLagrangeCoupling, 0 when blank
};

} // namespace oor::model
