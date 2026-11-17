#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/explicit/ExplicitSupport.hpp"

#include <array>
#include <cstdint>
#include <string_view>

namespace oor::model
{

enum class PorosityType : std::uint8_t
{
    PorousFlow,                 // PorousFlowBoundary: a constant flow boundary
    PorousFlowTimed,            // PorousTimeFlowBoundary: a flow boundary that varies with time
    Hole,                       // GasBagVentHole: small holes in an air bag
    Permeability,               // SurfacePermeability: permeable air bag material
    HoleBetweenGasBags,         // CouplingHoleToGasBag: flow through a hole to another GasBag
    PermeabilityBetweenGasBags, // GasBagPermeableLink: flow through a permeable area to another GasBag
    HoleBetweenCouplings,       // CouplingHoleToCoupling: flow through a hole to another coupling surface
    HydrostaticProfile,         // PorousHydrostaticBoundary: a hydrostatic pressure profile
    UserDefined                 // PorousUserBoundary: a user-written porosity model
};
inline constexpr std::array<std::string_view, 9> POROSITY_TYPE_WORDS{
    "PorousFlowBoundary",     "PorousTimeFlowBoundary",    "GasBagVentHole",
    "SurfacePermeability",    "CouplingHoleToGasBag",      "GasBagPermeableLink",
    "CouplingHoleToCoupling", "PorousHydrostaticBoundary", "PorousUserBoundary"};

// COEFF and COEFFV of a GasBagLeakage (fields 6 and 7): the porosity coefficient is a constant or a table of time (a
// TableDynamic1); a blank COEFFV is 1.0, the whole area open. The constant is given an open range from 0.0 to
// 1.0, but the description of PORTYPE says that 1.0 opens the whole area and 0.0 closes it, so both ends are
// allowed.
inline constexpr SourcedValueLayout GAS_BAG_LEAKAGE_COEFF_LAYOUT{
    6,
    7,
    "coefficientSource",
    "coefficient",
    static_cast<std::uint8_t>(sourceBit(ValueSource::Constant) | sourceBit(ValueSource::Table)),
    ValueSource::Constant,
    1.0};

// One GasBagLeakage card (SOL 700): a porosity definition of a part of the surface of a GasBag or an
// EulerLagrangeCoupling, which names the card that describes the flow (a hole, a permeable material, a flow boundary).
// A GasBag or an EulerLagrangeCoupling names the set of GasBagLeakage cards in its PORID field.
//
// Card layout: GasBagLeakage  LID  PORID  SUBID  PORTYPE  PORTYPID  COEFF  COEFFV      fields 1 to 7
// LID numbers the card, PORID is the number of the set (the cards of a set share it, so it is the ID the model files
// the card under: IdSpace::Group). SUBID names the ContactElemSurface, ContactBoxRegion, ContactPropertyRegion,
// ContactMaterialRegion or ContactSegment, a part of the surface of the GasBag or EulerLagrangeCoupling; 0 or blank
// means the whole surface. PORTYPE says what kind of card PORTYPID is the number of. The model keeps the number as a
// reference to the category of the porosity cards (ReferenceTarget::Porosity) and does not match the PORTYPE word
// against the card that has the number, so a PorousFlowBoundary 5 satisfies a PORTYPID 5 of type SurfacePermeability.
struct GasBagLeakageCard
{
    base::EntityId id = 0;           // the number of the card
    base::EntityId setId = 0;        // the number of the set, which a GasBag or an EulerLagrangeCoupling names
    base::EntityId subsurfaceId = 0; // a part of the surface, 0 for the whole of it
    PorosityType porosityKind = PorosityType::PorousFlow;
    base::EntityId porosityModelId = 0; // the porosity card
    SourcedValue coefficient{ValueSource::Constant, 1.0, 0};
};

} // namespace oor::model
