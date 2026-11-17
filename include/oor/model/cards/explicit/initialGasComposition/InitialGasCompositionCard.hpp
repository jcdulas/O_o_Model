#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <vector>

namespace oor::model
{

// One GASNAMi and FRACi pair of an InitialGasComposition: a gas and its share of the initial composition.
struct InitialGasFraction
{
    base::EntityId gasId = 0; // the InflatorGas of the gas
    double fraction = 0.0;    // its mass fraction, not negative

    [[nodiscard]] bool operator==(const InitialGasFraction&) const noexcept = default;
};

// One InitialGasComposition card (SOL 700): the composition of the gas that is in a gas bag (GasBag) or inside an Euler
// coupling surface (EulerLagrangeCoupling) at the start; the GasBag or EulerLagrangeCoupling names the card in its
// INTID field.
//
// Card layout: field 2 is a blank cell and the pairs follow, three on the first line and four on each continuation
// line:
//   InitialGasComposition  INTID  (blank)  GASNAM1  FRAC1  GASNAM2  FRAC2  etc.    fields 1, then from field 3
// INTID numbers the card (unique among the InitialGasComposition cards). Each GASNAMi is the number of an InflatorGas
// card; the format asks for at least one. The fractions are mass fractions, not negative, and the solver scales them to
// add up to 1.0, so the card does not check the sum. The pairs are kept in the order read.
struct InitialGasCompositionCard
{
    base::EntityId id = 0;                 // unique number of the initial gas composition
    std::vector<InitialGasFraction> gases; // at least one
};

} // namespace oor::model
