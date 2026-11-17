#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <optional>
#include <vector>

namespace oor::model
{

// One HybridInflator card (SOL 700): a hybrid airbag inflator, which blows a mixture of gases into a GasBag or an Euler
// coupling surface (EulerLagrangeCoupling) through the InflatorInlet that names the card. The mass flow rate and the
// static temperature of the gas are tables of time, or the temperature a constant; the share of each gas in the mixture
// is a table of time too, the HybridInflatorFractions that FRAC names. With an Euler domain it works only with the
// single material hydrodynamic solver and an GammaLawStateEquation equation of state.
//
// Card layout, two lines or more (fields 6 to 8 are blank cells):
//   HybridInflator  INFLID  MASFLRT  TEMPT  TEMPC  FRAC                            fields 1 to 5
//   GASNAM1  GASNAM2  GASNAM3  etc.                                                 fields 9 and on, eight to a line
// (the grid of the format reference prints the first field as INFLHID and TEMPT as TBMPT; the field list says INFLID
// and TEMPT.) INFLID numbers the card (unique among the inflators of every kind, which the InflatorInlet INFTYPID
// names). MASFLRT and FRAC are required: the number of a TableDynamic1 and the number of a HybridInflatorFractions. The
// static temperature is TEMPT, the number of a TableDynamic1, or TEMPC, a constant: the format reference says that
// either one must be given, and the card reads them as the two forms of one field (exactly one of them). The gases are
// the numbers of InflatorGas cards, at least one and as many as needed; the order is the order of the fractions on the
// HybridInflatorFractions.
struct HybridInflatorCard
{
    base::EntityId id = 0;                 // unique number of the inflator
    base::EntityId massFlowTableId = 0;    // a TableDynamic1: the mass flow rate against time
    // a TableDynamic1: the static temperature against time, 0 when TEMPC is given
    base::EntityId temperatureTableId = 0;
    std::optional<double> temperature;     // the constant static temperature, greater than zero
    base::EntityId fractionId = 0;         // a HybridInflatorFractions: the fractions of the gases against time
    std::vector<base::EntityId> gasId;     // the InflatorGas of each gas, in order
};

} // namespace oor::model
