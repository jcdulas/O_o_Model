#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One SurfaceLine card: a geometry declaration on a mesh line at a grid point. It tells a solver how the line of mesh
// edges that arrives at a grid point goes on, or that it ends there.
//
// Record:
//   SurfaceLine;id;node1Id;throughNodeId;node2Id
//
// `id` is the ID of the card (unique among the SurfaceLine cards). With `node2Id`, the mesh line of the edge
// node1Id-throughNodeId goes on, at throughNodeId, into the edge throughNodeId-node2Id. Without it (blank, 0), that
// mesh line ends at throughNodeId. The grid points of a card are all different.
struct SurfaceLineCard
{
    base::EntityId id = 0;
    base::EntityId node1Id = 0;
    base::EntityId throughNodeId = 0;
    base::EntityId node2Id = 0; // 0 = the mesh line ends at throughNodeId
};

} // namespace oor::model
