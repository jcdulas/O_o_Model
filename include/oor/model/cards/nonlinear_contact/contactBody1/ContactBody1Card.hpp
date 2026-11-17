#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstdint>
#include <string>

namespace oor::model
{

// One ContactBody1 card: a flexible or rigid contact body (SOLs 101, 400 and 700), the new form of ContactBody. A
// ContactPair or a ContactBodyChange names it by its BID.
//
// Card layout: ContactBody1  BID  BPID  DIM  BEHAV  BSID  BCRGID  BCGOUT
// (SOL 700 reads the BID and the BSID only; the other fields are ignored there.)
struct ContactBody1Card
{
    // BID: unique among ContactBody1, ContactFaceRegion and ContactNodeRegion
    base::EntityId id = 0;
    base::EntityId bodyParamsId = 0;            // the ContactBodyParams of the body parameters; 0 when blank (defaults)
    std::string dimension = "ThreeDimensional"; // 2D or 3D
    std::string behavior = "Deformable"; // DEFORM, RIGID, SYMM (a symmetry rigid body) or HEAT (a heat-rigid body)
    // ContactElemSurface or ContactPropertyRegion (deformable), ContactRigidSurfaceList, ContactPatchSurface,
    // ContactBezierSurface, ContactNurbsCurve or ContactNurbsSurface (rigid)
    base::EntityId surfaceId = 0;
    base::EntityId rigidMotionId = 0; // the ContactRigidMotion of a rigid body; 0 when blank
    std::int32_t forceReferencePoint =
        0; // the reference point of the resultant contact force: -1 origin, 0 centroid of the body
};

} // namespace oor::model
