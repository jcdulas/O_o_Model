#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstdint>

namespace oor::model
{

// One WettedElemSide card (SOL 400): a wetted element of an external fluid-structure simulation, given as a side of a
// structural element.
//
// Card layout: WettedElemSide  WEID  EID  SIDE                           fields 1 to 3
// EID is a shell (ShellQuad4, ShellQuad8, ShellQuad4Drilling, ShellTria3, ShellTria6, ShellTria3Drilling) or a solid
// (SolidTetra, SolidPenta, SolidHexa) and SIDE, from 1 to 6, is the side of it that is wetted, numbered as the sides of
// a HeatSurfaceSide. The card does not know which kind of element EID names; that is a rule between cards.
//
// The WEID is a number that a WettedSurface names. WettedElemSide and WettedElemNodes share one WEID space, in the
// category WettedElement: each type is unique on its own (IdSpace::PerCardType, the way the five module moves of
// ModuleTranslation to ModuleMirror2 share one number), and the check `compat.wetted-element-id-repeated` reports a
// number that both types have. PerCardType was chosen over IdSpace::Group because Group lets a number repeat even
// within one type, which the format does not allow (each WEID is the ID of a wetted element).
struct WettedElemSideCard
{
    static constexpr std::int32_t FIRST_SIDE = 1;
    static constexpr std::int32_t LAST_SIDE = 6;

    base::EntityId id = 0;
    base::EntityId elemId = 0;
    std::int32_t sideCode = 0; // 1 to 6; the format gives no default
};

} // namespace oor::model
