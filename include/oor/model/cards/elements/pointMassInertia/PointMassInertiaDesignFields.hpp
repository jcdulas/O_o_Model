#pragma once

#include "oor/model/design/DesignableCard.hpp"

namespace oor::model
{

// The fields of a PointMassInertia that a DesignElemRelation1 or DesignElemRelation2 drives, by the name the format
// reference gives them (a DVCREL names a field by CPNAME and never by position): M, X1, X2, X3, I11, I21, I22, I31, I32
// and I33.
[[nodiscard]] const DesignableCard& pointMassInertiaDesignFields();

} // namespace oor::model
