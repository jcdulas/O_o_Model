#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/sets/DofLists.hpp"

#include <vector>

namespace oor::model
{

// One IdListSet1 card: a list of structural grid points or elements that other cards (SPLINEi, FluidStructureInterface,
// AeroComponent, ...) refer to.
//
// Card layout: IdListSet1  SID  ID1  ID2  ID3  ID4  ID5  ID6  ID7
//                         ID8  ID9  -etc.-
// or, with ranges: IdListSet1  SID  ID1  "THRU"  ID2  ID3  "THRU"  ID4 ...
// or:             IdListSet1  SID  "SKIN"
// The list is kept as written: single IDs and THRU ranges, in order. With SKIN the card has no list (the set is the
// skin of the fluid-structure boundary). The format reference says the IDs are positive; decks of the public data that
// use the supersonic lifting-surface theory list negative ones, which are kept (zero is refused). Several cards may
// have the same SID: they are one set.
struct IdListSet1Card
{
    base::EntityId id = 0;
    bool skin = false;
    std::vector<IdRun> ids;
};

} // namespace oor::model
