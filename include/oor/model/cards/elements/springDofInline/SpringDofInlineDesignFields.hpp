#pragma once

#include "oor/model/design/DesignableCard.hpp"

namespace oor::model
{

// The fields of a SpringDofInline that a DesignElemRelation1 or DesignElemRelation2 drives, by name: K, GE and S.
[[nodiscard]] const DesignableCard& springDofInlineDesignFields();

} // namespace oor::model
