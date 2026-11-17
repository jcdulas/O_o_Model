#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <string>
#include <vector>

namespace oor::model
{

// One panel of a RadiatedPowerPanelSet: its label and the TypedListSet3 that lists its elements or properties.
struct RadiatedPowerPanel
{
    std::string name;         // NAMEi: the label that a Case Control SET of panels (the ERP command) names, as written
    base::EntityId setId = 0; // SETIDi: a TypedListSet3

    [[nodiscard]] bool operator==(const RadiatedPowerPanel&) const noexcept = default;
};

// One RadiatedPowerPanelSet card (equivalent radiated power): any number of panels, each a label and the TypedListSet3
// of the elements or the properties that make it up.
//
// Card layout: RadiatedPowerPanelSet  NAME1  SETID1  NAME2  SETID2  NAME3  SETID3  NAME4  SETID4
//                                    NAME5  SETID5  -etc.-
// The pairs follow each other, four to a line (the fifth is in field 9). Both parts of a pair are required. A label has
// one to eight characters that every format can hold (no blank, comma, dollar sign or quote) and is kept as written;
// the format reference does not say that the labels of a deck differ, so two panels may share one. The TypedListSet3
// may be a set of properties or of elements: it is a reference to the sets (ReferenceTarget::Set), whatever the
// TypedListSet3 lists. The card has no ID of its own (IdSpace::None) and a deck may have several.
struct RadiatedPowerPanelSetCard
{
    std::vector<RadiatedPowerPanel> panels;

    [[nodiscard]] bool operator==(const RadiatedPowerPanelSetCard&) const noexcept = default;
};

} // namespace oor::model
