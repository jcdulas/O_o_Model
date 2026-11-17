#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstdint>
#include <optional>

namespace oor::model
{

// A pole of the complex plane for the determinant method: its coordinates in radians per unit time and the
// multiplicity of the complex root there.
struct ComplexEigenPolesPole
{
    double realPart = 0.0;
    double imaginaryPart = 0.0;
    std::int32_t multiplicity = 1;
};

// One ComplexEigenPoles card: one or two poles of the determinant method (ComplexEigenMethod with METHOD = DET).
//
// Card layout: ComplexEigenPoles  SID  ALPHA1  OMEGA1  M1  ALPHA2  OMEGA2  M2
// The SID is the ID of the ComplexEigenMethod card the poles go with (the ComplexEigenMethod of the same set number),
// not a method of its own: several ComplexEigenPoles cards may share it, and it is renumbered with the
// ComplexEigenMethod (the ComplexMethod space).
struct ComplexEigenPolesCard
{
    base::EntityId id = 0;
    ComplexEigenPolesPole first;
    std::optional<ComplexEigenPolesPole> second;
};

} // namespace oor::model
