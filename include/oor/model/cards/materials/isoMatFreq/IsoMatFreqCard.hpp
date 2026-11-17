#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One IsoMatFreq card: the frequency dependence of the properties of an IsoMat (an isotropic material). Each field
// holds the ID of a TABLEDi (0 when blank: the property does not depend on the frequency) that replaces the property of
// the IsoMat with the same MID.
//
// Card layout:
//   IsoMatFreq  MID  E  G  NU  (blank)  (blank)  (blank)  GE                   fields 1 to 8
// The format reference asks for tables for all of E, G and NU when one of them depends on the frequency, because a
// blank one of the three is computed from the other two on the IsoMat (G = E / (2 (1 + NU))); the card does not enforce
// it, a table of constant values is the way to satisfy it. GE must be blank or 0 when the GE of the IsoMat is 0.0.
struct IsoMatFreqCard
{
    base::EntityId id = 0; // the IsoMat that the card extends
    base::EntityId youngsModulusTableId = 0;
    base::EntityId shearModulusTableId = 0;
    base::EntityId poissonRatioTableId = 0;
    base::EntityId structuralDampingTableId = 0;
};

} // namespace oor::model
