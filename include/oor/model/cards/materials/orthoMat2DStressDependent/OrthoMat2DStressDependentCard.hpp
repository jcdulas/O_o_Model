#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One OrthoMat2DStressDependent card: the nonlinear elastic (NLELAST) properties of an OrthoMat2D, the orthotropic
// material of the plane stress and shell elements, in SOL 400. Each field holds the ID of a TABL3Di (0 when blank: the
// property is not a table): a table whose entry may be a function of up to four variables (strain, temperature, strain
// rate, ...). The TableMultiVariable0, TableMultiVariable1 and TableMultiVariable2 cards are typed, so the IDs are
// references to them.
//
// Card layout:
//   OrthoMat2DStressDependent  MID  TE1  TE2  TNU12  TG12  TG1Z  TG2Z  TRHO
//                              TA1  TA2
struct OrthoMat2DStressDependentCard
{
    base::EntityId id = 0; // the OrthoMat2D that the card extends
    base::EntityId youngsModulus1TableId = 0;
    base::EntityId youngsModulus2TableId = 0;
    base::EntityId poissonRatio12TableId = 0;
    base::EntityId shearModulus12TableId = 0;
    base::EntityId shearModulus1ZTableId = 0;
    base::EntityId shearModulus2ZTableId = 0;
    base::EntityId densityTableId = 0;
    base::EntityId thermalExpansion1TableId = 0;
    base::EntityId thermalExpansion2TableId = 0;
};

} // namespace oor::model
