#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <string>

namespace oor::model
{

// One AeroRigidTrimVariable card: a rigid body motion that is a variable of a static aeroelastic trim (the angle of
// attack, a rate, an acceleration of the aircraft).
//
// Card layout: AeroRigidTrimVariable  ID  LABEL
// LABEL names the variable: ANGLEA, SIDES, ROLL, PITCH, YAW, URDD1 to URDD6 are the labels the program knows; any other
// label is allowed when the user supplies the forces. An AeroTrim card fixes a variable by its LABEL, an
// AeroTrimLink ties it to others and an AeroControlVector gives it a magnitude, so the label (not the ID) is what the
// other cards match, without regard to the case, against the labels of every AeroRigidTrimVariable, AeroControlSurface
// and AeroController. The ID is ignored by the solver: two cards may have the same one, and the card is filed under it
// only because the format reference makes it a field. The label is kept as written.
struct AeroRigidTrimVariableCard
{
    base::EntityId id = 0;
    std::string label; // up to eight characters

    [[nodiscard]] bool operator==(const AeroRigidTrimVariableCard&) const noexcept = default;
};

} // namespace oor::model
