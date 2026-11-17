#pragma once

#include "oor/model/design/DesignableCard.hpp"

namespace oor::model
{

// The fields of a BarShapeProp that a DesignPropRelation1 drives (the format reference does not let a
// DesignPropRelation2 name a BarShapeProp): DIM1, DIM2, ... as many as the section has, and NSM. By position DIM1 is
// field 12, DIM8 field 19, DIM9 field 22 (the continuation lines have eight data fields from the second column), and
// NSM follows the last dimension, so its field depends on the section.
[[nodiscard]] const DesignableCard& barShapePropDesignFields();

} // namespace oor::model
