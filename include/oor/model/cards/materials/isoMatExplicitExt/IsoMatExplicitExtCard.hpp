#pragma once

#include "oor/base/ids/EntityId.hpp"

namespace oor::model
{

// One IsoMatExplicitExt card: the additional properties of an IsoMat for solid elements (SOL 700): the equation of
// state.
//
// Card layout:
//   IsoMatExplicitExt  MID  EID                                                  fields 1 and 2
// MID is the IsoMat that the card extends and EID the ID of an equation of state card (EOSxxx: the category
// EquationOfState). An IsoMatExplicitExt is always needed for solid elements when an ElastoPlasticMat is used, except
// when the RYIELD option of the ElastoPlasticMat is VMISES, ORTHOCR or SOIL.
struct IsoMatExplicitExtCard
{
    base::EntityId id = 0; // the IsoMat that the card extends
    base::EntityId equationOfStateId = 0;
};

} // namespace oor::model
