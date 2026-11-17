#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <vector>

namespace oor::model
{

// One ContactRigidSurfaceList card: a list of rigid contact surfaces (ContactPatchSurface, ContactBezierSurface,
// ContactNurbsCurve or ContactNurbsSurface) that a ContactBody1 names as a whole in its BSID (SOLs 101 and 400).
// Without it, a ContactBody1 may name one of those surfaces directly.
//
// Card layout: ContactRigidSurfaceList  BSID  RBID1  RBID2  RBID3  ...  over as many continuation lines as needed.
struct ContactRigidSurfaceListCard
{
    base::EntityId id = 0;                // BSID: unique among the contact surfaces
    std::vector<base::EntityId> surfaces; // the RBID of each rigid surface
};

} // namespace oor::model
