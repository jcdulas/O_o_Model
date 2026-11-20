#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One SurfaceFacet card: a geometry declaration on a shell element. The edges of the element are all straight folds of
// the surface: the element is a flat facet.
//
// Record:
//   SurfaceFacet;elementId
//
// `elementId` is the ID of the element, not a new element. It is also the ID of the card: one SurfaceFacet per
// element.
struct SurfaceFacetCard
{
    base::EntityId elementId = 0;
};

} // namespace oor::model
