#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstdint>
#include <vector>

namespace oor::model
{

// One AeroPistonProp5 card: the properties of the strips of an AeroPistonPanel5 panel (piston theory): the angle of
// attack, the chordwise coordinates and the thickness ratios that the AeroFactorList cards list, and the control
// surface chord of every strip.
//
// Card layout: AeroPistonProp5  PID  NALPHA  LALPHA  NXIS   LXIS   NTAUS  LTAUS  (blank)
//                              CAOC1  CAOC2   CAOC3  CAOC4  CAOC5  -etc.-
// Field 8 of the first line is not used and must be blank. The control surface chords start the continuation line
// (field 9) and run on without a gap, eight to a line; the format reference draws five of them and says there is one
// per strip, and this card reads them from field 9 to the end of the card. The continuation is required: at
// least one CAOC, and a blank inside the list is an error.
//
// Three groups say what the strips need, each a count and the AeroFactorList that holds the numbers:
//   NALPHA / LALPHA  the angles of attack per Mach number of the AeroMachFreqTable1 or AeroMachFreqPairs2 card. NALPHA
//                    is 1 when one angle is the same on every strip, or the number of strips when each strip has its
//                    own. Both are required (the format reference gives no default and the AeroFactorList is always
//                    needed), so NALPHA is positive and LALPHA a positive ID.
//   NXIS / LXIS      the dimensionless chord coordinates: 0 (the default) when the AeroPistonPanel5 gives the thickness
//                    integrals, 1 for one set shared by the strips, or the number of strips. LXIS is the
//                    AeroFactorList, required (> 0) when NXIS is not 0 and when some strip has a control surface (a
//                    CAOC other than 0.0), because the hinge position is then needed.
//   NTAUS / LTAUS    the thickness ratios, in the same way (0 by default); LTAUS is required when NTAUS is not 0.
// Which of the three AeroFactorList layouts a card needs also depends on the NTHICK of the AeroPistonPanel5 that names
// the property and on the number of strips of that panel, so the counts NALPHA, NXIS, NTAUS (1 or the number of strips)
// and the number of CAOC values are rules between the two cards, not of this one. A list ID given while its count is 0
// names a list that is not used and is kept (the count and the ID could not be changed one at a time otherwise).
//
// CAOCi is the chord of the control surface divided by the chord of the strip: not negative, 0.0 for a strip with no
// control surface.
struct AeroPistonProp5Card
{
    base::EntityId id = 0;
    std::int32_t angleOfAttackCount = 0;
    base::EntityId angleOfAttackListId = 0; // an AeroFactorList
    std::int32_t chordCoordCount = 0;
    base::EntityId chordCoordListId = 0; // an AeroFactorList (0 when blank)
    std::int32_t thicknessRatioCount = 0;
    base::EntityId thicknessRatioListId = 0; // an AeroFactorList (0 when blank)
    std::vector<double> controlChordRatios;  // CAOC1, CAOC2, ...: one per strip
};

} // namespace oor::model
