#pragma once

#include "oor/model/core/Model.hpp"
#include "oor/query/named/common/CardFacts.hpp"

#include <optional>

namespace oor::query
{

// The heat transfer material (a HeatIsoMat or HeatAnisoMat) of the conduction element at `element`: the material of its
// property, or its own for a Rod2InlineSection. Nothing when the element has no thermal material.
[[nodiscard]] std::optional<model::CardLocation> thermalMaterialOfElement(CardFacts& facts, const model::Model& model,
                                                                          model::CardLocation element);

// The multiplier HGEN of the thermal material of the element: the HeatVolumeSourceLoad of a heat load is multiplied by
// it. 1.0 (the default of the cards) when the element has no thermal material.
[[nodiscard]] double heatGenerationMultiplier(CardFacts& facts, const model::Model& model, model::CardLocation element);

// The conductivity K of a HeatIsoMat (nothing for a HeatAnisoMat, whose conductivity is a matrix in the material
// system, or a HeatIsoMat with a blank K).
[[nodiscard]] std::optional<double> isotropicConductivity(const model::Model& model, model::CardLocation material);

// True when a HeatIsoMatTemperature of the same MID gives the conductivity of the HeatIsoMat a table of the
// temperature.
[[nodiscard]] bool conductivityDependsOnTemperature(const model::Model& model, base::EntityId mid);

} // namespace oor::query
