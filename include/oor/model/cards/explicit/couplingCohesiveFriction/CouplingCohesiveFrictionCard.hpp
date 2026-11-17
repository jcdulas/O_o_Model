#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One CouplingCohesiveFriction card (SOL 700): a cohesive friction model on one part of the coupling surface of an
// EulerLagrangeCoupling. An EulerLagrangeCoupling names the set of CouplingCohesiveFriction cards in its COHFRID field,
// so that the friction may vary along the surface.
//
// Card layout: CouplingCohesiveFriction  CID  COHFRID  SUBID  COHFRICID  fields 1 to 4
// CID numbers the card. COHFRID is the number of the set (the cards of a set share it, so it is the ID the model files
// the card under: IdSpace::Group). SUBID names the ContactElemSurface, ContactSegment or ContactPropertyRegion, a part
// of the surface of the EulerLagrangeCoupling, that the friction applies to; blank means the whole surface. COHFRICID
// is the CohesiveFriction card that holds the friction parameters. The format reference gives CID, COHFRID and
// COHFRICID as required and zero or more: a zero would name nothing, so the three must be positive here.
struct CouplingCohesiveFrictionCard
{
    base::EntityId id = 0;                      // the number of the card
    base::EntityId setId = 0;                   // the number of the set, which an EulerLagrangeCoupling names
    base::EntityId subsurfaceId = 0;            // a part of the coupling surface, 0 for the whole of it
    base::EntityId cohesiveFrictionModelId = 0; // a CohesiveFriction
};

} // namespace oor::model
