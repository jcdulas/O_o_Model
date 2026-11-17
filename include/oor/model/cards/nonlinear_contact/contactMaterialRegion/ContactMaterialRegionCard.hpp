#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <vector>

namespace oor::model
{

// One ContactMaterialRegion card: a 3D contact region of SOL 700 made of all the elements that have one of the listed
// materials; the BSID of a ContactBody names it. It cannot define a region of composite elements.
//
// Card layout: ContactMaterialRegion  ID  IM1  IM2  IM3  ...  over as many continuation lines as needed (at least one
//                                     material).
struct ContactMaterialRegionCard
{
    // unique among ContactElemSurface, ContactBoxRegion, ContactPropertyRegion and ContactMaterialRegion
    base::EntityId id = 0;
    std::vector<base::EntityId> materials; // the material IDs
};

} // namespace oor::model
