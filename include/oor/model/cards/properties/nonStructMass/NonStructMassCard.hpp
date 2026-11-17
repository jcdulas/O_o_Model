#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/properties/NonStructMassFields.hpp"

#include <string>
#include <vector>

namespace oor::model
{

// One NonStructMass card: a set of non-structural mass, given per unit area or length on properties or elements.
//
// Card layout: NonStructMass  SID  TYPE  ID1  VALUE1  ID2  VALUE2  ID3  VALUE3
//                                 ID4  VALUE4  -etc.-
// TYPE is a property type (ShellProp, CompProp, CompPropGlobal, BarProp, BarShapeProp, BeamProp, BeamShapeProp,
// BeamLumpedAreaProp, RodProp, Rod2InlineSection, CurvedBeamProp, ShearPanelProp, TubeProp, ConicalShellProp,
// CrackTipProp2D) or ELEMENT, in upper case. VALUE is the mass per unit area for the shells and shear panels, per unit
// length for the bars, beams, rods and tubes, added to the NSM of the property. The set is selected by the Case Control
// command NSM = SID; several cards (of any of the NonStructMass cards) may share the SID.
struct NonStructMassCard
{
    base::EntityId id = 0;
    std::string type;
    std::vector<NonStructMassPair> pairs;
};

} // namespace oor::model
