#pragma once

#include "oor/model/design/DesignableCard.hpp"

namespace oor::model
{

// The fields of a ShearPanelProp that a DesignPropRelation1 or DesignPropRelation2 drives: T (field 4), NSM (5), F1 (6)
// and F2 (7).
[[nodiscard]] const DesignableCard& shearPanelPropDesignFields();

} // namespace oor::model
