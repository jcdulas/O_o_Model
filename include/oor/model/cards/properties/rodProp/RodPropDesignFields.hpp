#pragma once

#include "oor/model/design/DesignableCard.hpp"

namespace oor::model
{

// The fields of a RodProp that a DesignPropRelation1 or DesignPropRelation2 drives: A (field 4), J (5), C (6) and NSM
// (7).
[[nodiscard]] const DesignableCard& rodPropDesignFields();

} // namespace oor::model
