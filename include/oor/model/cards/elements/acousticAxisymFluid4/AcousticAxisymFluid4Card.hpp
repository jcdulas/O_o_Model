#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <array>
#include <optional>

namespace oor::model
{

// One AcousticAxisymFluid4 card: an axisymmetric fluid element that connects four fluid points (the fluid of an
// axisymmetric slot or cavity analysis, together with an AcousticSlotControl card).
//
// Card layout: AcousticAxisymFluid4  EID  IDF1  IDF2  IDF3  IDF4  RHO  B
// The points are AcousticSlotFluidPoint fluid points, which no card of the library defines yet: IDF1 to IDF4 are plain
// IDs, neither looked up nor renumbered. They are given around the element, since the plot elements the solver
// generates join the pairs 1-2, 2-3, 3-4 and 4-1. The element has no geometry here and no mass.
//
// EID is a positive integer below 100,000,000 and shares the element ID space with every structural and fluid element,
// so the duplicate rule of the element space applies. RHO is the fluid density (positive) and B the
// bulk modulus (not negative; 0.0 is an incompressible fluid); a blank one is given by the RHOD or BD field
// of the AcousticSlotControl card that governs the element, so it is kept blank (nothing) and not replaced by a
// default.
struct AcousticAxisymFluid4Card
{
    base::EntityId id = 0;
    std::array<base::EntityId, 4> fluidPoints = {}; // IDF1 to IDF4: AcousticSlotFluidPoint fluid points, plain IDs
    std::optional<double> density;                  // blank: the RHOD of the AcousticSlotControl card
    std::optional<double> bulkModulus;              // blank: the BD of the AcousticSlotControl card
};

} // namespace oor::model
