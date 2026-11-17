#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/nonlinear_contact/ContactRuns.hpp"

#include <vector>

namespace oor::model
{

// One ContactElemSurface card: a contact body or surface made of elements, named by the BSID of a ContactBody or
// ContactBody1.
//
// Card layout: ContactElemSurface  ID  ELID1  ELID2  ELID3  ...  or, with ranges,  BSURF  ID  ELID1  THRU  ELID2  BY
//                                  INC  ...
// over as many continuation lines as needed. A range may go down; BY is 1 for a rising range and -1 for a falling one
// when it is left out (stored resolved in each run).
struct ContactElemSurfaceCard
{
    // unique among ContactElemSurface, ContactBoxRegion, ContactPropertyRegion and ContactMaterialRegion
    base::EntityId id = 0;
    std::vector<ContactRun> elements; // the element IDs, single or in ranges
};

} // namespace oor::model
