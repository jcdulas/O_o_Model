#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <array>
#include <cstdint>
#include <string_view>

namespace oor::model
{

// How the grid points of a marker element move inside the Euler domain (the TYPE field of a MarkerProp). The
// enumerators are numbered in the order of MARKER_PROP_TYPE_WORDS.
enum class MarkerPropType : std::uint8_t
{
    Fixed, // FIXED (the default): the marker stays where it is, whatever the Euler velocity
    Moving // MOVING: the marker is carried by the velocity of the Eulerian material
};

inline constexpr std::array<std::string_view, 2> MARKER_PROP_TYPE_WORDS{"Fixed", "Moving"};

// One MarkerProp card (SOL 700): the property of the marker elements (MarkerBody and MarkerNode), which record the
// variables of the Euler domain at a point or along a line. The format reference says the property is ignored for
// markers that sit on structural grid points: those follow the structure.
//
// Card layout: MarkerProp  ID  TYPE         fields 1 and 2
// The ID is a property number, so it is in the space of all the properties (a MarkerBody or MarkerNode names it in its
// PID).
struct MarkerPropCard
{
    base::EntityId id = 0; // unique among the properties
    MarkerPropType type = MarkerPropType::Fixed;
};

} // namespace oor::model
