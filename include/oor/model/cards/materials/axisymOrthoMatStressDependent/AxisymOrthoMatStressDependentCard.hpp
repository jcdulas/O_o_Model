#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One AxisymOrthoMatStressDependent card: the nonlinear elastic (NLELAST) properties of an AxisymOrthoMat, the
// orthotropic material of the axisymmetric elements, in SOL 400. Each field holds the ID of a TABL3Di (0 when blank:
// the property is not a table): a table whose entry may be a function of up to four variables (strain, temperature,
// strain rate, ...). The TableMultiVariable0, TableMultiVariable1 and TableMultiVariable2 cards are typed, so the IDs
// are references to them.
//
// Card layout:
//   AxisymOrthoMatStressDependent  MID      TEX  TETH     TEZ    TNUXTH   TNUTHZ   TNUZX   TRHO
//                                  (blank)  (blank)  TGZX     TAX    TATH  TAZ
// The fields follow the AxisymOrthoMat card: TGZX is field 11 (as the format reference draws it: fields 9 and 10 are
// blank).
struct AxisymOrthoMatStressDependentCard
{
    base::EntityId id = 0; // the AxisymOrthoMat that the card extends
    base::EntityId youngsModulusXTableId = 0;
    base::EntityId youngsModulusThetaTableId = 0;
    base::EntityId youngsModulusZTableId = 0;
    base::EntityId poissonRatioXthTableId = 0;
    base::EntityId poissonRatioThzTableId = 0;
    base::EntityId poissonRatioZxTableId = 0;
    base::EntityId densityTableId = 0;
    base::EntityId shearModulusZxTableId = 0;
    base::EntityId thermalExpansionXTableId = 0;
    base::EntityId thermalExpansionThetaTableId = 0;
    base::EntityId thermalExpansionZTableId = 0;
};

} // namespace oor::model
