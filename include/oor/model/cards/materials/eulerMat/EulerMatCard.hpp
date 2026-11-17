#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstdint>

namespace oor::model
{

// The bulk viscosity type of an EulerMat card.
enum class EulerMatBulkType : std::uint8_t
{
    Standard, // the default: the standard model
    Enhanced  // the enhanced model
};

// One EulerMat card: a general constitutive model for an Eulerian material (SOL 700): an equation of state, a shear
// model, a yield model, a failure model and a spall model.
//
// Card layout:
//   EulerMat  MID    RHO    EID    SID    YID    FID    PID                       fields 1 to 7
//             BULKL  BULKQ  (blank) (blank) BULKTYP                                9 to 13
// RHO is the density (greater than zero) and EID the ID of an equation of state card (DeflagrationStateEquation,
// GammaLawStateEquation, IgnitionGrowthStateEquation, JonesWilkinsLeeStateEquation, MieGruneisenStateEquation,
// NobleAbelStateEquation, PolynomialStateEquation or UserStateEquation: the category EquationOfState). SID, YID, FID
// and PID (0 when blank) name a shear model (ElasticShearModel, PolynomialShearModel, UserShearModel: ShearModel), a
// yield model (HydrodynamicYield, JohnsonCookYield, SnowMultiSurfaceYield, PolynomialYield, RatePowerLawYield,
// SteinbergGuinanYield, TanimuraMimuraYield, UserYield, VonMisesYield, ZerilliArmstrongYield: YieldModel; blank is the
// hydrodynamic one), a failure model (JohnsonCookFailure, MaxPlasticStrainFailure, UserFailureModel: FailureModel) and
// a spall model (ConstantSpallation: SpallModel). Those cards are typed, so the five IDs are references (the
// MohrCoulombYield of the format reference, a Mohr-Coulomb model, is not typed yet: a YID that names it is reported as
// unresolved until it is). BULKL (0.0) and BULKQ (1.0) are the linear and quadratic bulk viscosity coefficients. The
// material ID is in the space every material type shares.
struct EulerMatCard
{
    base::EntityId id = 0;
    double density = 0.0;
    base::EntityId equationOfStateId = 0;
    base::EntityId shearModelId = 0;
    base::EntityId yieldModelId = 0;
    base::EntityId failureModelId = 0;
    base::EntityId spallModelId = 0;
    double linearBulkViscosity = 0.0;
    double quadraticBulkViscosity = 1.0;
    EulerMatBulkType bulkViscosityKind = EulerMatBulkType::Standard;
};

} // namespace oor::model
