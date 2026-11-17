#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <string>

namespace oor::model
{

// One WettedSurfaceLoad card (SOL 400): the load set that stands for an external fluid-structure service, with the
// wetted surface the service loads.
//
// Card layout: WettedSurfaceLoad  WLID  WSID  SERV_ID                        fields 1 to 3
// WLID is the EXCITEID of a TransientTableLoad1 (the TransientTableLoad1 has to exist and be selected for the generator
// of the solver to build the load, though its values do not matter to the external program). WSID names a
// WettedSurface, and SERV_ID the service, at most eight characters and kept as written: it is the name of the CONNECT
// SERVICE statement and of the FluidStructureControl of the service. Several WettedSurfaceLoad cards may have one
// SERV_ID: the surfaces are merged and the WLID of the first replaces the others, so several cards may also share one
// WLID.
//
// The card is filed under the WLID as a set (IdSpace::Group, category Other: it is not a load that a LoadCombination or
// a DynamicLoadCombination selects) and defines excitation IDs (CardTable::definesExcitationIds), as the
// EulerFlowBoundary, UserEnforcedVelocity and OccupantAccelField cards do, so the EXCITEID of a TransientTableLoad1
// that names it resolves.
struct WettedSurfaceLoadCard
{
    base::EntityId id = 0;
    base::EntityId wettedSurfaceId = 0;
    std::string serviceName;
};

} // namespace oor::model
