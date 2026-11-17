#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/dynamics/DynamicLoadFields.hpp"

namespace oor::model
{

// One TransientTableLoad1 card: a transient excitation P(t) = A * F(t - tau), where F is a table.
//
// Card layout: TransientTableLoad1  SID  EXCITEID  DELAYI/DELAYR  TYPE  TID/F  US0  VS0
// Three fields hold an ID or a real, and each is two members here:
//  - DELAYI/DELAYR: the ID of a DELAY card (delayId) or a fixed delay (delay); both blank is no delay;
//  - TID/F: the ID of the TABLEDi that gives F(t) (tableId) or a constant F (value).
// EXCITEID is the set ID of a DynamicLoadScale or of a static load set for an applied load (the set of an
// EnforcedMotionConstr for an enforced motion, TYPE other than LOAD), or the number of a flow boundary or user-defined
// load of SOL 700 (EulerFlowBoundary, EulerTimeFlowBoundary, EulerUserFlowBoundary, UserEnforcedVelocity), in which
// case TID and F are both blank. A TransientTableLoad1 with neither is read as it is; the validation check
// `load.transient-table-load1-no-function` reports it when EXCITEID names none of those.
struct TransientTableLoad1Card
{
    base::EntityId id = 0;
    base::EntityId excitationId = 0;
    base::EntityId delayId = 0; // DELAYI; 0 is blank
    double delay = 0.0;         // DELAYR
    ExcitationType kind = ExcitationType::Load;
    base::EntityId tableId = 0;             // TID; 0 is blank
    double value = 0.0;                     // F
    double initialDisplacementFactor = 0.0; // factor for the initial displacements of the enforced degrees of freedom
    double initialVelocityFactor = 0.0;     // factor for their initial velocities
};

} // namespace oor::model
