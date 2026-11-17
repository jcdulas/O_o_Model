#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <array>

namespace oor::model
{

// One spherical coordinate system defined by three grid points: what a SphericalFrame1 card holds for one system.
//
// Card layout:
//   SphericalFrame1  CIDA  G1A  G2A  G3A  CIDB  G1B  G2B  G3B
//
// A SphericalFrame1 card defines one or two systems (A and B). Each system is a card value of its own: reading a card
// with two systems gives two values, and each is written as a SphericalFrame1 card of its own. G1 is the origin, G2 a
// point on the z-axis and G3 a point in the plane of the azimuthal origin.
struct SphericalFrame1Card
{
    base::EntityId id = 0;
    std::array<base::EntityId, 3> nodes = {};
};

} // namespace oor::model
