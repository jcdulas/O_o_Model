#pragma once

#include "oor/model/references/ReferenceVisitor.hpp"

#include <string_view>

namespace oor::model
{

// A parameter whose integer value is the ID of a card: its neutral name (exactly, as the Parameter card and the Case
// Control keep it) and what the ID names.
struct ParameterReference
{
    std::string_view parameter;
    ReferenceTarget target = ReferenceTarget::Other;
};

// The parameters that hold the ID of a card. Only a positive value is an ID (zero and the negative values are options
// of these parameters). Used by the Parameter card and for the parameters written in the Case Control.
//  - WeightReferenceNode: the grid point about which the weight of the model is printed. A number that names no grid
//    point is valid (the reference point is then the origin of the basic system), so the value follows a renumbering
//    of the nodes and is never reported: NodeInRange, the node reference that is allowed not to exist.
//  - AcousticInfinitePropId: the property of the acoustic infinite elements, an ID of the property space.
inline constexpr ParameterReference PARAMETER_REFERENCES[] = {
    {"WeightReferenceNode", ReferenceTarget::NodeInRange},
    {"AcousticInfinitePropId", ReferenceTarget::Property},
};

// The entry of PARAMETER_REFERENCES of this parameter; null for a parameter whose value is not the ID of a card.
[[nodiscard]] constexpr const ParameterReference* findParameterReference(std::string_view parameter) noexcept
{
    for (const ParameterReference& known : PARAMETER_REFERENCES)
    {
        if (known.parameter == parameter)
            return &known;
    }
    return nullptr;
}

} // namespace oor::model
