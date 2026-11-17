#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/explicit/ExplicitSupport.hpp"

#include <array>
#include <cstdint>
#include <string_view>

namespace oor::model
{

enum class InflatorInletInflator : std::uint8_t
{
    Standard, // StandardInflator
    Hybrid,   // HybridInflator
    ColdGas,  // ColdGasInflator
    TankTest  // TankTestInflator
};
inline constexpr std::array<std::string_view, 4> INFLATOR_INLET_INFLATOR_WORDS{"StandardInflator", "HybridInflator",
                                                                               "ColdGasInflator", "TankTestInflator"};

// COEFF and COEFFV (fields 6 and 7): the area coefficient is a constant or varies with time (COEFFV is then the number
// of a TableDynamic1). A blank COEFF is CONSTANT. The format reference gives COEFFV no default; a blank value is read
// as 1.0, the whole area of the subsurface open, which is also the value a coefficient has when it is not mentioned.
inline constexpr SourcedValueLayout INFLATOR_INLET_COEFF_LAYOUT{
    6,
    7,
    "areaCoefficientSource",
    "areaCoefficient",
    static_cast<std::uint8_t>(sourceBit(ValueSource::Constant) | sourceBit(ValueSource::Table)),
    ValueSource::Constant,
    1.0};

// One InflatorInlet card (SOL 700): one inflator that blows into a gas bag (GasBag) or an Euler coupling surface
// (EulerLagrangeCoupling), on a part of their surface.
//
// Card layout: InflatorInlet  CID  INFID  SUBID  INFTYPE  INFTYPID  COEFF  COEFFV     fields 1 to 7
// CID numbers the card (unique among the InflatorInlet cards). INFID is the number of the set of InflatorInlet cards
// that a GasBag or a EulerLagrangeCoupling names in its INFID field, so it is the ID the model files the card under (a
// set ID: IdSpace::Group) and the cards of a set share it. SUBID names the ContactElemSurface, ContactBoxRegion,
// ContactPropertyRegion, ContactMaterialRegion or ContactSegment, a part of the surface of the GasBag or
// EulerLagrangeCoupling, where the gas comes in. INFTYPE says which kind of inflator card INFTYPID is the number of: a
// StandardInflator, HybridInflator, ColdGasInflator or TankTestInflator. The four share one category and one reference
// kind (Inflator), so the card does not check the number against the kind a word names.
//
// The gas enters through the area of the subsurface times the coefficient. The format says 0 < COEFFV < 1 and also
// that 1.0 opens the whole area and 0.0 closes it, so the card accepts the closed interval [0, 1].
struct InflatorInletCard
{
    base::EntityId id = 0;           // the number of the card
    base::EntityId inflatorId = 0;   // the number of the set, which a GasBag or an EulerLagrangeCoupling names
    base::EntityId subsurfaceId = 0; // the part of the surface where the gas comes in
    InflatorInletInflator inflatorKind = InflatorInletInflator::Standard;
    base::EntityId inflatorKindId = 0; // the number of the inflator card that INFTYPE names
    SourcedValue coeff{ValueSource::Constant, 1.0, 0};
};

} // namespace oor::model
