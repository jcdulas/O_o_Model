#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/explicit/ExplicitKeywords.hpp"

namespace oor::model
{

// One CouplingHoleToCoupling card (SOL 700): a hole in a coupling surface through which gas flows to another coupling
// surface. A GasBagLeakage of PORTYPE CouplingHoleToCoupling names it (and only a GasBagLeakage does).
//
// Card layout: CouplingHoleToCoupling  PID  SIZE  (blank)  FLOW  CSID  MID  fields 1, 2, 4, 5 and 6; field 3 is an
//                                      empty
// cell SIZE says how the gas that crosses the hole is computed: SMALL (the hole is no larger than the Euler mesh: one
// dimensional flow through an orifice) or LARGE (a hole larger than the mesh: the velocity method of an Eulerian air
// bag); SMALL when blank. FLOW is the allowed direction into the EulerLagrangeCoupling that names the card (BOTH when
// blank). CSID is the EulerLagrangeCoupling on the other side of the hole, required. MID is the EulerMat of the gas
// that is transported, used only when the hole joins a GasBag with the multi-material Euler solver and SIZE is LARGE:
// blank otherwise.
struct CouplingHoleToCouplingCard
{
    base::EntityId id = 0; // unique among the CouplingHoleToCoupling cards
    HoleSize size = HoleSize::Small;
    FlowDirection flow = FlowDirection::Both;
    base::EntityId couplingId = 0; // the EulerLagrangeCoupling on the other side
    base::EntityId matId = 0;      // an EulerMat, 0 when blank
};

} // namespace oor::model
