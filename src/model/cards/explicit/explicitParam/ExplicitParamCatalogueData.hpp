#pragma once

#include "oor/model/cards/explicit/explicitParam/ExplicitParamCatalogue.hpp"

#include <vector>

namespace oor::model
{

// The typed table of the ExplicitParam entries (ExplicitParamCatalogueData.cpp). Read it through
// ExplicitParamCatalogue.
[[nodiscard]] const std::vector<ExplicitParamEntry>& explicitParamCatalogueEntries();

} // namespace oor::model
