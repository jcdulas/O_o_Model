#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <array>

namespace oor::model
{

// One ContactSegment card: a segment of a contact surface of SOL 700 given by the grid points of an element face. The
// segments with the same IBODY make the surface that the BSID of a ContactBody names.
//
// Card layout: ContactSegment  ID  IBODY  G1  G2  G3  G4  (G4 blank for a triangle)
struct ContactSegmentCard
{
    base::EntityId id = 0;                 // the segment number: unique among the ContactSegment cards of the model
    base::EntityId surfaceId = 0;          // the surface the segment belongs to
    std::array<base::EntityId, 4> nodes{}; // G1 to G4; G4 is 0 for a triangle
};

} // namespace oor::model
