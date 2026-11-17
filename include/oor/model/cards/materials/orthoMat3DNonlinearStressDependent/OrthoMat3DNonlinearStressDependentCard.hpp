#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One OrthoMat3DNonlinearStressDependent card: the nonlinear elastic (NLELAST) properties of an OrthoMat3DNonlinear,
// the 3D orthotropic material, in SOL 400. Each field holds the ID of a TABL3Di (0 when blank: the property is not a
// table): a table whose entry may be a function of up to four variables (strain, temperature, strain rate, ...). The
// TableMultiVariable0, TableMultiVariable1 and TableMultiVariable2 cards are typed, so the IDs are references to them.
//
// Card layout:
//   OrthoMat3DNonlinearStressDependent  MID  TE1  TE2  TE3  TNU12  TNU23  TNU31  TRHO
//                                       TG12  TG23  TG31  TA1  TA2  TA3
struct OrthoMat3DNonlinearStressDependentCard
{
    base::EntityId id = 0; // the OrthoMat3DNonlinear that the card extends
    base::EntityId youngsModulus1TableId = 0;
    base::EntityId youngsModulus2TableId = 0;
    base::EntityId youngsModulus3TableId = 0;
    base::EntityId poissonRatio12TableId = 0;
    base::EntityId poissonRatio23TableId = 0;
    base::EntityId poissonRatio31TableId = 0;
    base::EntityId densityTableId = 0;
    base::EntityId shearModulus12TableId = 0;
    base::EntityId shearModulus23TableId = 0;
    base::EntityId shearModulus31TableId = 0;
    base::EntityId thermalExpansion1TableId = 0;
    base::EntityId thermalExpansion2TableId = 0;
    base::EntityId thermalExpansion3TableId = 0;
};

} // namespace oor::model
