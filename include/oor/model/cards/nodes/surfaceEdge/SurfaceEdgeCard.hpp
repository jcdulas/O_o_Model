#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <string>
#include <string_view>

namespace oor::model
{

// One SurfaceEdge card: a geometry declaration on the mesh edge between two grid points. It tells a solver that reads
// a surface from the mesh what that surface does across the edge, in place of the angle between the elements, which
// decides it where no card does.
//
// Record:
//   SurfaceEdge;id;node1Id;node2Id;state;elementId
//
// `id` is the ID of the card (unique among the SurfaceEdge cards). `node1Id` and `node2Id` are the two grid points of
// the edge; they are different. `state` is one of three words:
//   Smooth  the surface is smooth across the edge;
//   Sharp   the surface folds along the edge, which keeps its own line and may be curved;
//   Raw     the surface folds along the edge, which is straight.
// `elementId` narrows the declaration to the side of one shell element of an edge that three elements or more share;
// blank (0) is the whole edge. A Raw edge is always declared whole: it takes no element.
struct SurfaceEdgeCard
{
    static constexpr std::string_view SMOOTH = "Smooth";
    static constexpr std::string_view SHARP = "Sharp";
    static constexpr std::string_view RAW = "Raw";

    base::EntityId id = 0;
    base::EntityId node1Id = 0;
    base::EntityId node2Id = 0;
    std::string state;            // Smooth, Sharp or Raw
    base::EntityId elementId = 0; // 0 = the whole edge
};

} // namespace oor::model
