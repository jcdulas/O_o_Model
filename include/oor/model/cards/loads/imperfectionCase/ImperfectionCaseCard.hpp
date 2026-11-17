#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/sets/DofLists.hpp"

#include <vector>

namespace oor::model
{

// One ImperfectionCase card (SOL 400): a collection of imperfections, selected by the Case Control command IMPERFECT,
// that lists the IDs of ImperfectionGeometry entries.
//
// Card layout: ImperfectionCase  ID  IMPFID1  IMPFID2  -etc.-  IMPFIDi  fields 1 to 8, and on the continuation lines
// An item is the ID of an ImperfectionGeometry or "first THRU last", kept as written in `imperfections`. The IDs name
// the ImperfectionGeometry cards (category ImperfectionGeometry, `loads/impgeom`), so the references of the list
// resolve to them. Where a range names IDs that no ImperfectionGeometry has, only its two ends are looked at (the
// format reference does not say that the IDs between them exist, as for the nodes of a THRU list). The ID is
// ImperfectionCase's own: IdSpace::PerCardType (the Case Control IMPERFECT names it).
struct ImperfectionCaseCard
{
    base::EntityId id = 0;
    std::vector<IdRun> imperfections;

    [[nodiscard]] bool operator==(const ImperfectionCaseCard&) const noexcept = default;
};

} // namespace oor::model
