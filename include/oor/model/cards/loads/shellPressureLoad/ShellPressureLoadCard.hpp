#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/loads/ElementRuns.hpp"

#include <vector>

namespace oor::model
{

// One ShellPressureLoad card: a uniform pressure normal to a list of shell elements (ShellQuad4, ShearPanel4,
// ShellTria3).
//
// Card layout: ShellPressureLoad  SID  P  EID1  EID2  EID3  EID4  EID5  EID6
//                                     EID7  EID8  -etc.-
// or:         ShellPressureLoad  SID  P  EID1  "THRU"  EID2
// The list is kept as written: single elements, or one THRU range (the alternate format, which has no other element).
// The elements continue over as many lines as needed (the format accepts long lists).
struct ShellPressureLoadCard
{
    base::EntityId id = 0;
    double pressure = 0.0;
    std::vector<ElementRun> elements;
};

} // namespace oor::model
