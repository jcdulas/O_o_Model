#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/explicit/ExplicitKeywords.hpp"

#include <array>
#include <cstdint>
#include <string_view>

namespace oor::model
{

// The CTYPE of an EulerLagrangeCoupling (field 8): the standard Euler-Lagrange interaction, or the variant tuned for
// air bags (inflow through a porous surface only into an element that already holds gas, and almost empty elements are
// removed).
enum class EulerLagrangeCouplingType : std::uint8_t
{
    Standard,
    Airbag
};
inline constexpr std::array<std::string_view, 2> EULER_LAGRANGE_COUPLING_TYPE_WORDS{"Standard", "AirbagCoupling"};

// An EulerLagrangeCoupling that is never deactivated has this TDEAC.
inline constexpr double EULER_LAGRANGE_COUPLING_DEFAULT_DEACTIVATION_TIME = 1.0E20;

// One EulerLagrangeCoupling card (SOL 700): a general coupling surface, the interface between an Eulerian domain
// (finite volume) and a Lagrangian one (finite elements). It is the largest card of the Euler-Lagrange coupling and it
// names most of the others: the surface itself, the porosity, the options, the inflators, the initial gas, the Euler
// mesh.
//
// Card layout, 23 fields over three lines (fields 15 and 16 are blank cells of the grid):
//   EulerLagrangeCoupling  CID  BSID  COVER  REVERSE  CHECK  PORID  OPTID  CTYPE    fields 1 to 8
//                          INFID  HTRID  FS  FK  EXP  INTID                                        fields 9 to 14
//                          SET1ID  MESHID  TDEAC  COUP1FL  HYDSTAT  SKFRIC  COHFRID                fields 17 to 23
// The grid cuts the name of the last field in two cells; it is COHFRID (the description calls it that). No other entry
// of the format reference is called EulerLagrangeCoupling, so there is nothing to tell it apart from.
//
// BSID is a ContactElemSurface, ContactBoxRegion, ContactPropertyRegion, ContactMaterialRegion or ContactSegment (or a
// ContactNodeRegion of SOL 700): the ContactSurface kind. PORID, OPTID, INFID, HTRID and COHFRID name a set of cards
// (GasBagLeakage, CouplingOptions, InflatorInlet, GasBagHeatTransfer and CouplingCohesiveFriction cards that share the
// number; for GasBagHeatTransfer the target is ReferenceTarget::HeatLossSet). INTID is an InitialGasComposition, SET1ID
// an IdListSet1 (the Euler elements of this surface), MESHID an EulerMeshGenerator (the Euler mesh of this surface; the
// format reference says only one of the two may be given), COUP1FL a CouplingFailedSegmentFlow and
// EulerHydrostaticPreset a HYDSTAT. Blank and 0 are the same for each of them: 0 here, None in Python.
//
// FS, FK and EXP are the static and kinetic friction coefficients and the exponential decay of a Coulomb law, the
// SKFRIC a skin friction. TDEAC is the time at which the surface and its Euler mesh are deactivated.
struct EulerLagrangeCouplingCard
{
    base::EntityId id = 0;        // the number of the card
    base::EntityId surfaceId = 0; // the coupling surface
    CoverSide cover = CoverSide::Inside;
    Switch reverseNormals = Switch::On; // REVERSE: flip the segment normals when the volume would be negative
    Switch checkNormals = Switch::On;   // CHECK: verify the direction of the segment normals
    base::EntityId porosityId = 0;      // a set of GasBagLeakage cards
    base::EntityId optionId = 0;        // a set of CouplingOptions cards
    EulerLagrangeCouplingType couplingType = EulerLagrangeCouplingType::Standard;
    base::EntityId inflatorId = 0;     // a set of InflatorInlet cards
    base::EntityId heatTransferId = 0; // a set of GasBagHeatTransfer cards
    double staticFriction = 0.0;       // static friction coefficient
    double kineticFriction = 0.0;      // kinetic friction coefficient
    double frictionDecay = 0.0;        // exponential decay coefficient
    base::EntityId initialGasId = 0;   // an InitialGasComposition
    base::EntityId elemSetId = 0;      // an IdListSet1 of Euler elements
    base::EntityId meshId = 0;         // an EulerMeshGenerator
    double deactivationTime = EULER_LAGRANGE_COUPLING_DEFAULT_DEACTIVATION_TIME;
    base::EntityId failedSegmentFlowId = 0;   // a COUP1FL
    base::EntityId hydrostaticId = 0;         // a HYDSTAT
    double skinFriction = 0.0;                // skin friction value
    base::EntityId cohesiveFrictionSetId = 0; // a set of CouplingCohesiveFriction cards
};

} // namespace oor::model
