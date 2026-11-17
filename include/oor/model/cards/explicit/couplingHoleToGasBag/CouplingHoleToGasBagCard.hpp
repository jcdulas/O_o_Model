#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/explicit/ExplicitKeywords.hpp"

namespace oor::model
{

// One CouplingHoleToGasBag card (SOL 700): a hole in an EulerLagrangeCoupling or GasBag (sub)surface that is connected
// to another GasBag, to model the flow between two air bags (two GasBags, a GasBag and an Eulerian air bag, or two
// Eulerian air bags). A GasBagLeakage of PORTYPE CouplingHoleToGasBag names it.
//
// Card layout: CouplingHoleToGasBag  FID  SIZE  (blank)  FLOW  GBID  MID  fields 1, 2, 4, 5 and 6; field 3 is an empty
// cell SIZE is the flow method (SMALL when blank: one dimensional flow through an orifice; LARGE: the velocity method
// of an Eulerian air bag), FLOW the allowed direction into the GasBag or coupling surface that names the card (BOTH
// when blank). GBID is the GasBag on the other side of the hole, required. MID is the EulerMat of the gas of that
// GasBag, used only when it meets an Eulerian air bag of the multi-material solver with SIZE LARGE: blank otherwise.
struct CouplingHoleToGasBagCard
{
    base::EntityId id = 0; // unique among the CouplingHoleToGasBag cards
    HoleSize size = HoleSize::Small;
    FlowDirection flow = FlowDirection::Both;
    base::EntityId gasBagId = 0; // the GasBag on the other side
    base::EntityId matId = 0;    // an EulerMat, 0 when blank
};

} // namespace oor::model
