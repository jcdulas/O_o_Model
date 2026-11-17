#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/explicit/EulerRegionType.hpp"

namespace oor::model
{

// One InitialConditionRegion card (SOL 700): one Eulerian region (a shape and a material) with the set of initial
// values that its material starts with. The cards that share a TSID form the group of regions that an
// EulerInitialRegions names, so the TSID of field 2 is the ID the model files the card under (IdSpace::Group, category
// EulerInitialRegions) and the TRID is only the number of the card, as the ERID of an EulerForceRegion is.
//
// Card layout: InitialConditionRegion  TRID  TSID  TYPE  VID  MID  TSID  LEVEL          fields 1 to 7
// The format gives two fields the name TSID. The first (field 2) is the group an EulerInitialRegions names; the second
// (field 6, called `tsid2` here, as an EulerRegionProp has a SID2) is the InitialConditionValues that holds the initial
// values of this material. TYPE says what VID is, as for an EulerForceRegion (the two cards share EulerRegionType): the
// number of an InitialSurfaceVolume, SphereShape or CylinderShape (category EulerRegionShape), of a ContactBoxRegion
// (BOX, the contact surface category) or of an IdListSet1 (ELEM). MID is an EulerMat (0 or blank: none) and TSID2 an
// InitialConditionValues (0 or blank: none), and LEVEL is the level indicator of this material and its initial values
// (default 0.0). The card has one region: the format draws no second group, and the reader refuses a field after LEVEL.
struct InitialConditionRegionCard
{
    base::EntityId id = 0;      // the number of the card
    base::EntityId groupId = 0; // the group of regions, which an EulerInitialRegions names
    EulerRegionType type = EulerRegionType::Surface;
    base::EntityId shapeId = 0;  // the shape, as TYPE says
    base::EntityId matId = 0;    // an EulerMat, 0 for none
    base::EntityId valuesId = 0; // an InitialConditionValues with the initial values, 0 for none
    double level = 0.0;          // the level indicator of the region
};

} // namespace oor::model
