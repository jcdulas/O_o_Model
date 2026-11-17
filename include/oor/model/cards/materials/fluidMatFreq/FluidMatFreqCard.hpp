#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One FluidMatFreq card: the frequency dependence of the properties of a FluidMat (a fluid material). Each field holds
// the ID of a TABLEDi (0 when blank: the property does not depend on the frequency) that replaces the property of the
// FluidMat with the same MID.
//
// Card layout:
//   FluidMatFreq  MID  BULK  RHO  C  GE  ALPHA                                    fields 1 to 6
// RHO and C are used in SOL 108 only. The GE of the FluidMat must not be 0 for the GE table to be of use, and an ALPHA
// table takes precedence over the ALPHA of the FluidMat (which is multiplied by the frequency otherwise).
struct FluidMatFreqCard
{
    base::EntityId id = 0; // the FluidMat that the card extends
    base::EntityId bulkModulusTableId = 0;
    base::EntityId densityTableId = 0;
    base::EntityId soundSpeedTableId = 0;
    base::EntityId structuralDampingTableId = 0;
    base::EntityId normalizedAdmittanceTableId = 0;
};

} // namespace oor::model
