#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One scalar point defined by a ScalarPoint card.
//
// Card layout (up to eight IDs per line, continued on further lines; a range is written with THRU):
//   ScalarPoint  ID1  ID2  ID3  ID4  ID5  ID6  ID7  ID8
//   ScalarPoint  ID1  THRU ID2
//
// A ScalarPoint card defines many points, so the card is read as one row per point (ScalarPointFormat::readAll): the
// library keeps no list of IDs, every scalar point is a member of the node ID space with its own row, found by
// `ReferenceTarget::Node` like a Node. A written model has one ScalarPoint card per point; a THRU range is not rebuilt.
struct ScalarPointCard
{
    base::EntityId id = 0;
};

} // namespace oor::model
