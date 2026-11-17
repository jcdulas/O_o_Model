#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace oor::model
{

enum class AeroComponentListType : std::uint8_t
{
    // aerodynamic: the IDs are aerodynamic elements (AeroLiftingPanel1 to AeroPistonPanel5), the component is all their
    // boxes
    AeroPanel,
    // aerodynamic: the IDs are AeroBoxList cards (the boxes of a DLM model; an AeroControlSurface may share the list)
    AeroBoxList,
    ComponentId, // aerodynamic: the IDs are component numbers of the AeroQuad4 and AeroTria3 elements of a mesh
    NodeSet      // structural: the IDs are IdListSet1 cards that list grid points
};

inline constexpr std::array<std::string_view, 4> AERO_COMPONENT_LIST_TYPE_WORDS{"AeroPanels", "AeroBoxList",
                                                                                "ComponentId", "IdListSet1"};

// One AeroComponent card: a component of the aerodynamic or structural model that a monitor point
// (MonitorIntegratedLoad1, MonitorDisplacement) or an external spline integrates over.
//
// Card layout: AeroComponent  NAME  LISTTYPE  LISTID1  LISTID2  LISTID3  LISTID4  LISTID5  LISTID6
//                            LISTID7  -etc.-
// The list runs from field 3 to the last field used, with no blank between two IDs; the IDs are on the continuation
// lines from LISTID7 on and the format reference draws no limit. A THRU is not part of the layout, so the card refuses
// one. At least one ID is given. A card has one LISTTYPE, so a card is either structural (IdListSet1) or aerodynamic
// (the other three); the format reference forbids mixing the two in one component, which a single card cannot do
// (AeroComponentUnion joins components, and keeping the two classes apart there is a check between cards).
//
// The component has no number: its NAME (one to eight characters, kept as written and matched without regard to the
// case) is its key, and the COMP of a MonitorIntegratedLoad1 or a MonitorDisplacement and the labels of an
// AeroComponentUnion must match one. The name must be unique among all the AeroComponent and AeroComponentUnion cards;
// the card does not refuse a repeat, a check between cards does. The IDs name the card of the LISTTYPE: IdListSet1 an
// IdListSet1 card, AeroBoxList an AeroBoxList card, CAERO an aerodynamic element. CMPID names nothing a card of the
// model owns, so those IDs are plain numbers: not visited and not looked up.
struct AeroComponentCard
{
    std::string name; // up to eight characters
    AeroComponentListType listKind = AeroComponentListType::AeroPanel;
    std::vector<base::EntityId> ids;

    [[nodiscard]] bool operator==(const AeroComponentCard&) const noexcept = default;
};

} // namespace oor::model
