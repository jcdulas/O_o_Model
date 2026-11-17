#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <array>

namespace oor::model
{

// One moving rectangular coordinate system defined by three grid points (SOL 700 only): what a RectFrame3 card holds
// for one system.
//
// Card layout:
//   RectFrame3  CID  N1  N2  N3  CID  N1  N2  N3      fields 1 to 4 and 5 to 8
//
// A RectFrame3 card defines one or two systems. Each system is a card value of its own, as for a RectFrame1: reading a
// card with two systems gives two values, and each is written as a RectFrame3 card of its own. N1 is the origin, N2 a
// point on the z-axis and N3 a point in the x-z plane. The points must be different from one another (and not on a
// line: a rule of their positions, not of the card) and must be defined in an independent coordinate system (a rule of
// the model). Unlike the RectFrame1, the system moves: its position and orientation follow the grid points during the
// analysis, so the positions of a coordinate system code that reads it describe the start only.
//
// The members have the names of `RectFrame1Card` (`cid`, `nodes`), so that the code of the analysis module that turns a
// system defined by three points into a frame reads both with the same template.
struct RectFrame3Card
{
    base::EntityId id = 0;
    std::array<base::EntityId, 3> nodes = {};
};

} // namespace oor::model
