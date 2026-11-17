#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <array>
#include <cstddef>
#include <optional>

namespace oor::model
{

// One AxisymFluid4 card: a fluid element of an axisymmetric fluid model, a body of revolution whose outer corners are
// the rings IDF1 to IDF4.
//
// Card layout: AxisymFluid4  EID  IDF1  IDF2  IDF3  IDF4  RHO  B
// IDF1 to IDF4 are AxisymFluidRing IDs below 500000 (the AxisymFluidRing card is not typed, so they are not
// references). RHO, the mass density, and B, the bulk modulus (0.0 is an incompressible fluid), are blank when the
// AxisymFluidControl card gives the values: `std::nullopt`.
struct AxisymFluid4Card
{
    static constexpr std::size_t RING_COUNT = 4;

    base::EntityId id = 0;
    std::array<base::EntityId, RING_COUNT> rings = {};
    std::optional<double> density;
    std::optional<double> bulkModulus;
};

} // namespace oor::model
