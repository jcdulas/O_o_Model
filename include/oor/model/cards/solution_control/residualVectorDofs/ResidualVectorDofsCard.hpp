#pragma once

#include "oor/model/cards/sets/DofLists.hpp"

#include <vector>

namespace oor::model
{

// One ResidualVectorDofs card: degrees of freedom where unit loads are applied to get the static solutions that the
// residual vector computation uses.
//
// Card layout: ResidualVectorDofs  ID1  C1  ID2  C2  ID3  C3  ID4  C4
// and, for more than four points, the same pairs on the continuation lines. IDi is a grid or scalar point, Ci the
// digits of its components as one number (0 for a scalar point). The card has no ID: it adds to the degrees of freedom
// of the model (a ResidualVectorDofs and a ResidualVectorDofs1 are alike, as an AnalysisDofSet and an AnalysisDofSet1
// are). The format reference shows four pairs: the continuation lines of the DOF set cards are accepted too.
struct ResidualVectorDofsCard
{
    std::vector<DofPair> dofs;
};

} // namespace oor::model
