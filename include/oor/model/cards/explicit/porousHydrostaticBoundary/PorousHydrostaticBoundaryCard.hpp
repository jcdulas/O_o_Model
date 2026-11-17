#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One PorousHydrostaticBoundary card (SOL 700): a porous flow boundary that prescribes a hydrostatic pressure profile
// on a part of a coupling surface. A GasBagLeakage of PORTYPE PorousHydrostaticBoundary names it.
//
// Card layout: PorousHydrostaticBoundary  PID  field 1
// The card holds nothing but its number. The profile comes from the EulerHydrostaticPreset card that the
// EulerLagrangeCoupling of the surface names in its HYDSTAT field (the coupling surface must refer to one, and the
// water level, the atmospheric pressure and the inflow density are taken from it). That is a rule between three cards,
// not of this one.
struct PorousHydrostaticBoundaryCard
{
    base::EntityId id = 0; // unique among the PorousHydrostaticBoundary cards
};

} // namespace oor::model
