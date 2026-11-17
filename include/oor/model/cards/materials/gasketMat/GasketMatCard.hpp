#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <array>
#include <cstdint>

namespace oor::model
{

// One GasketMat card: a gasket material of SOL 400, nonlinear in the thickness direction and for compression only (the
// membrane behaviour is the one of the IsoMat named in IDMEM).
//
// Card layout:
//   GasketMat  MID  IDMEM   BEHAV   TABLD   TABLU1  TABLU2  TABLU3  TABLU4
//              TABLU5  TABLU6  TABLU7  TABLU8  TABLU9  TABLU10 YPRS  EPL
//              GPL     GAP  TABYPRS TABEPL  TABGPL  TABGAP
// TABLD is the loading path and TABLU1 to TABLU10 the unloading paths, TableStress1 tables of pressure against closure
// (the unloading paths may be left out when the gasket does not unload). YPRS, EPL and GPL are required.
struct GasketMatCard
{
    static constexpr std::size_t UNLOADING_TABLES = 10;

    base::EntityId id = 0;             // the gasket material ID (the material ID space)
    base::EntityId membraneMatId = 0;  // the IsoMat of the membrane behaviour
    std::int32_t behaviorKind = 0;     // 0: the only type there is
    base::EntityId loadingTableId = 0; // the TableStress1 of the loading path
    std::array<base::EntityId, UNLOADING_TABLES>
        unloadingTableIds{};                          // the TableStress1 of each unloading path (0 when blank)
    double yieldPressure = 0.0;                       // the yield pressure
    double tensileModulus = 0.0;                      // the tensile modulus (pressure per unit length)
    double transverseShearModulus = 0.0;              // the transverse shear modulus
    double initialGap = 0.0;                          // the initial gap
    // TableStress1 of the yield pressure (not used yet by the program)
    base::EntityId yieldPressureTableId = 0;
    base::EntityId tensileModulusTableId = 0;         // TableStress1 of the tensile modulus (not used yet)
    base::EntityId transverseShearModulusTableId = 0; // TableStress1 of the transverse shear modulus (not used yet)
    base::EntityId initialGapTableId = 0;             // TableStress1 of the initial gap (not used yet)
};

} // namespace oor::model
