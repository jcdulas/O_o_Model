#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One SpringPropTable card: the property of a spring of SOL 700 whose force-deflection curve is a TableDynamic1.
//
// Card layout:
//   SpringPropTable  PID  TID                fields 1 and 2
// Both fields are required: the card has no default for either. The PID is a property number, unique among the
// SpringProp and the SpringPropTable, which is the property space of every property type; the format says that only a
// SpringDofPropertyExplicit may name the property, a rule of the model and not of the card. Unlike a SpringPropFreq, a
// SpringPropTable has no SpringProp that it extends.
struct SpringPropTableCard
{
    base::EntityId id = 0;      // unique among the properties
    base::EntityId tableId = 0; // the TableDynamic1 with the force against the deflection
};

} // namespace oor::model
