#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/explicit/ExplicitKeywords.hpp"

namespace oor::model
{

// One InitialSurfaceVolume card (SOL 700): an initialization surface, a closed volume (made of the segments of a
// ContactElemSurface) that a EulerInitialRegions region or an EulerForceRegion region uses to give initial conditions
// to the Eulerian elements inside or outside it. It is not a coupling, contact or rigid surface and cannot be used as
// one.
//
// Card layout: InitialSurfaceVolume  VID  BSID  COVER  REVERSE  CHECK  fields 1 to 5
// VID numbers the shape: the VID of an InitialConditionRegion or EulerForceRegion of type SURF names it, and so do the
// other shapes of the same family (SphereShape, CylinderShape), which share the category EulerRegionShape. BSID is the
// ContactElemSurface that holds the segments. COVER says which side of the closed volume gets the initial conditions:
// the format reference lists INSIDE (the default) and OUTSIDE only, although the keyword of EulerLagrangeCoupling has a
// third word, NONE, which the shared CoverSide enumeration also holds: the check refuses it here. REVERSE ON (the
// default) turns the segment normals around where needed so that they all point the same way and enclose a positive
// volume; CHECK ON (the default) only verifies that. The format reference adds that REVERSE = ON sets CHECK to ON by
// itself: the card keeps the CHECK it was given (OFF with REVERSE ON is not an error) and the solver applies the rule.
struct InitialSurfaceVolumeCard
{
    base::EntityId id = 0;        // unique among the shapes of an Euler region
    base::EntityId surfaceId = 0; // a ContactElemSurface
    CoverSide cover = CoverSide::Inside;
    Switch reverse = Switch::On;
    Switch check = Switch::On;
};

} // namespace oor::model
