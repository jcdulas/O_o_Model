#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <vector>

namespace oor::model
{

// The perturbation values of a RigidInterpolationOverride when a field is blank (0.01 for each of the three).
inline constexpr double RIGID_OVERRIDE_DEFAULT_PERTURBATION = 0.01;

// One RigidInterpolation of a RigidInterpolationOverride: the element and the values that override the
// ModelParams,GMOVR3 perturbation of the coincident grid points of its Lagrange formulation.
struct RigidInterpolationOverrideGroup
{
    base::EntityId elemId = 0;                                  // ELEMi: the RigidInterpolation element
    double perturbationX = RIGID_OVERRIDE_DEFAULT_PERTURBATION; // the perturbation of the X coordinate
    double perturbationY = RIGID_OVERRIDE_DEFAULT_PERTURBATION; // ... of the Y coordinate
    double perturbationZ = RIGID_OVERRIDE_DEFAULT_PERTURBATION; // ... of the Z coordinate
    // the adjustment to the ModelParams,GMOVR3T value (GMOVR3Ti)
    double toleranceAdjustment = 0.0;

    [[nodiscard]] bool operator==(const RigidInterpolationOverrideGroup&) const noexcept = default;
};

// One RigidInterpolationOverride card (SOL 400): overrides, for the RigidInterpolation elements it lists, of the
// perturbation that ModelParams,GMOVR3 gives to the grid points that coincide in a Lagrange (rigid = Lagrange)
// formulation.
//
// Card layout: RigidInterpolationOverride  ELEM1  dX1  dY1  dZ1  dGMOVR3T1              fields 1 to 5 of each line
//                                         ELEM2  dX2  dY2  dZ2  dGMOVR3T2              fields 9 to 13 of the next line
//                                         -etc.-                                       one RigidInterpolation to a line
// Each line has a RigidInterpolation element and four reals: the perturbations of the three coordinates (0.01 when
// blank) and the adjustment to the ModelParams,GMOVR3T value (0.0 when blank; the zero tolerance, GMOVR3T + dGMOVR3Ti,
// must not be negative, which depends on the ModelParams and is not checked). The first line of the format's grid has
// the first RigidInterpolation beside the card name and the second line starts at its first field, so a group is at
// fields 1, 9, 17, ... and its three last fields are blank. The entry acts only when ModelParams,GMOVR3 is 3 or 4; it
// affects a RigidInterpolation only when every connected grid point coincides with the reference grid point within the
// tolerance (an entry that does not meet that is ignored). The card names the RigidInterpolation elements (`Element`:
// an ID that is not a RigidInterpolation is a rule between two cards). The card has no ID of its own and any number of
// cards may be in a deck.
struct RigidInterpolationOverrideCard
{
    std::vector<RigidInterpolationOverrideGroup> groups; // one RigidInterpolation each, in the order of the card

    [[nodiscard]] bool operator==(const RigidInterpolationOverrideCard&) const noexcept = default;
};

} // namespace oor::model
