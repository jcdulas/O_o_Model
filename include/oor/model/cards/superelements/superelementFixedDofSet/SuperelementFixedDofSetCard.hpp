#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/sets/DofLists.hpp"

#include <vector>

namespace oor::model
{

// One SuperelementFixedDofSet card: degrees of freedom of the exterior points of a superelement that are fixed (b-set)
// in the component mode synthesis.
//
// Card layout: SuperelementFixedDofSet  SEID  ID1  C1  ID2  C2  ID3  C3
// and, for more than three points, the pairs ID C on the continuation lines, four to a line (field 9 on). IDi is a grid
// or scalar point, Ci the digits of its components as one number (0 for a scalar point). SEID is the superelement, and
// the points are those of that superelement (its part, when the deck has one). Without any SuperelementFixedDofSet or
// SuperelementFreeDofSet every boundary point is fixed; with SuperelementFixedDofSet alone the boundary degrees of
// freedom not listed are free. The degrees of freedom must be exterior ones and are not in a SuperelementFreeDofSet.
// The card has no ID of its own.
struct SuperelementFixedDofSetCard
{
    base::EntityId superelementId = 0;
    std::vector<DofPair> dofs;

    [[nodiscard]] bool operator==(const SuperelementFixedDofSetCard&) const noexcept = default;
};

} // namespace oor::model
