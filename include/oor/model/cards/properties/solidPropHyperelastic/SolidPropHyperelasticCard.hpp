#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One SolidPropHyperelastic card: the property of a fully nonlinear hyperelastic solid element.
//
// Card layout:
//   SolidPropHyperelastic  PID  MID  STR
//
// STR is the location of the stress and strain output, GRID (the default) or GAUS.
struct SolidPropHyperelasticCard
{
    base::EntityId id = 0;
    base::EntityId matId = 0;
    bool gaussOutput = false; // STR = GAUS (true) or GRID (false)
};

} // namespace oor::model
