#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One AeroControlSchedule card: the schedule of a control surface, its deflection as a function of the Mach number and
// the angle of attack, for a trim.
//
// Card layout: AeroControlSchedule  SID  AESID  LALPHA  LMACH  LSCHD
// AESID is the ID of the AeroControlSurface card the schedule is attached to (not its label). LALPHA and LMACH are
// AeroFactorList cards that list the angles of attack (in radians) and the Mach numbers at which the schedule is given;
// LSCHD is the AeroFactorList of the deflections in radians, required. The deflections are a table with the angles of
// attack varying fastest: the first NALPHA numbers belong to the first Mach number, and so on. When LALPHA is blank the
// LSCHD list is a schedule over Mach numbers only, and when LMACH is blank over angles of attack only, so the two
// cannot both be blank. That a list has two numbers at least, and that LSCHD has the right count, are rules
// between cards.
//
// The Case Control AeroControlSchedule selects the card by its SID (ReferenceTarget::ControlSchedule). The
// AeroControlSurface of AESID must not also be fixed by an AeroTrimLink or an AeroTrim of the same subcase (a check
// between cards).
struct AeroControlScheduleCard
{
    base::EntityId id = 0;
    base::EntityId controlSurfaceId = 0;
    base::EntityId angleOfAttackListId = 0; // 0 when blank: no schedule over the angle of attack
    base::EntityId machListId = 0;          // 0 when blank: no schedule over the Mach number
    base::EntityId scheduleListId = 0;

    [[nodiscard]] bool operator==(const AeroControlScheduleCard&) const noexcept = default;
};

} // namespace oor::model
