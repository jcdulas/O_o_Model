#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/explicit/EulerSolverType.hpp"

namespace oor::model
{

// One EulerRegionProp card (SOL 700): the property of Eulerian elements whose initial conditions are given in geometric
// regions (an EulerInitialRegions) instead of one material, as an EulerProp does. Elements (SolidHexa and the elements
// an EulerMeshGenerator generates) name its PID. It shares the name of no other entry: EulerProp is the card with a
// single material.
//
// Card layout: EulerRegionProp  PID  TYPE  SID  SID2    fields 1 to 4
// TYPE is the same list of solver types as EulerProp (HYDRO when blank): the rules of the EulerProp apply here too.
// SID is the number of the EulerInitialRegions that gives the materials and the regions
// (ReferenceTarget::EulerInitialization: it is resolved and renumbered with the EulerInitialRegions cards). SID2 is the
// number of an EulerBodyForceSet that defines the acceleration field, 0 or blank for none.
struct EulerRegionPropCard
{
    base::EntityId id = 0; // unique among the properties
    EulerSolverType type = EulerSolverType::Hydro;
    base::EntityId initialRegionsId = 0; // an EulerInitialRegions
    base::EntityId bodyForceSetId = 0;   // an EulerBodyForceSet, 0 for none
};

} // namespace oor::model
