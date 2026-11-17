#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One AxisymOrthoMatTemperature card: the temperature dependent properties of an AxisymOrthoMat. Each field holds the
// ID of a TABLEMi (0 when blank: the property does not depend on the temperature) that modifies the property of the
// same name on the AxisymOrthoMat with the same MID.
//
// Card layout:
//   AxisymOrthoMatTemperature  MID  T(EX)   T(ETH)   T(EZ)   T(NUXTH)   T(NUTHZ)   T(NUZX)   T(RHO)
//                              (blank)  (blank) T(GZX)   T(AX)   T(ATH)     T(AZ)  (blank)   T(GE)
// The fields follow the AxisymOrthoMat card (EZ is field 4, GZX field 11); the cells of fields 9, 10 and 15 are blank,
// and T(EZ) is field 4.
struct AxisymOrthoMatTemperatureCard
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
    base::EntityId structuralDampingTableId = 0;
};

} // namespace oor::model
