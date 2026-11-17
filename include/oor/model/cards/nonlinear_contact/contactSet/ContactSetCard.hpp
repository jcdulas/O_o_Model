#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <vector>

namespace oor::model
{

// One contact pair of a ContactSet: the source (contactor) and target regions, the friction and the search distances.
struct ContactSetPair
{
    base::EntityId sourceRegionId = 0; // SIDi: the source region
    base::EntityId targetRegionId = 0; // TIDi: the target region
    double friction = 0.0;             // FRICi: static friction coefficient, not negative
    double minimumDistance = 0.0;      // MINDi: minimum search distance
    double maximumDistance = 0.0;      // MAXDi: maximum search distance

    [[nodiscard]] bool operator==(const ContactSetPair&) const noexcept = default;
};

// One ContactSet card: a contact set of the older contact definition (SOLs 101, 601 and 701 of other implementations of
// the format: the contact pairs between regions, with a friction and a search distance each). A Case Control BCSET
// command selects the set directly or through a ContactSetUnion, a ContactControlParams or ContactSurfaceParams with
// the same number gives it parameters. The format reference does not describe this card; it is read as below.
//
// Layout: ContactSet  CSID  SID1  TID1  FRIC1  MIND1  MAXD1  (blank)  (blank)   fields 1 to 6
//         (line 2)  (blank)  SID2  TID2  FRIC2  MIND2  MAXD2  (blank)  (blank)   fields 10 to 14
//         and so on: a pair is five fields starting at field 2, 10, 18 ... (field 8 + 8k + 2), eight fields apart.
// CSID is the number of the set. The regions are numbers of ContactElemSurface cards (or of the BSURFS card of another
// implementation, which the library does not type), so they are not looked up. A blank FRIC, MIND or MAXD is 0.0;
// every field of a line that is not part of a pair is blank. The card needs at least one pair.
struct ContactSetCard
{
    base::EntityId id = 0;
    std::vector<ContactSetPair> pairs;
};

} // namespace oor::model
