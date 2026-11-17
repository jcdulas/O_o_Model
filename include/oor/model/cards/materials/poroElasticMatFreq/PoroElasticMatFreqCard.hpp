#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One PoroElasticMatFreq card: the frequency dependent properties of an isotropic poroelastic material (it extends the
// IsoMat with the same ID, and a PoroElasticMat refers to it). Each field holds the ID of a TABLEMi (0 when blank: the
// property does not depend on the frequency). The card belongs to the trim component part of the deck (BEGIN BULK
// TRMC).
//
// Card layout:
//   PoroElasticMatFreq  MID  T(E)  T(G)  T(NU)  T(RHO)  T(A)  (blank)  T(GE)     fields 1 to 8
//                       T(ST) T(SC) T(SS)                                                      9 to 11
struct PoroElasticMatFreqCard
{
    base::EntityId id = 0; // the IsoMat that the card extends
    base::EntityId youngsModulusTableId = 0;
    base::EntityId shearModulusTableId = 0;
    base::EntityId poissonRatioTableId = 0;
    base::EntityId densityTableId = 0;
    base::EntityId thermalExpansionTableId = 0;
    base::EntityId structuralDampingTableId = 0;
    base::EntityId tensionAllowableTableId = 0;
    base::EntityId compressionAllowableTableId = 0;
    base::EntityId shearAllowableTableId = 0;
};

} // namespace oor::model
