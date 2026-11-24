#pragma once

#include "oor/model/core/Model.hpp"
#include "oor/model/format/CardLayouts.hpp"

namespace oor::model
{
std::vector<std::string> cardValues(const Model& model, const CardTable& table, std::uint16_t type, std::uint32_t row,
                                    const CardLayouts& layouts, bool omitDefaults);
std::string cardRecord(const Model& model, CardLocation location,
                       const CardLayouts& layouts = *CardLayouts::standard());
} // namespace oor::model
