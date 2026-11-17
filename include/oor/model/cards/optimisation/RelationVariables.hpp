#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/core/CardProblem.hpp"
#include "oor/model/format/FieldReader.hpp"
#include "oor/model/format/FieldWriter.hpp"

#include <optional>
#include <string>
#include <vector>

namespace oor::model
{

// The arguments of the equation of a DesignPropRelation2, a DesignMatRelation2 or a DesignElemRelation2: the design
// variables ("DesignVar" line) and then the constants of the DesignConstants and DesignFieldConstants cards
// ("DesignConstants" line), which the equation receives in that order as its first, second,
// ... arguments. DesignVar must come before DesignConstants.
//
//   DesignPropRelation2  ID  TYPE  PID  PNAME/FID  PMIN  PMAX  EQID      fields 1 to 7
//                        DesignVar  DVID1  DVID2  ...                                fields 9 to 16 and the lines after
//                        DTABLE  LABL1  LABL2  ...

// Reads the lines from `firstField` to the end of the card.
void readRelationVariables(FieldReader& reader, int firstField, std::vector<base::EntityId>& designVarIds,
                           std::vector<std::string>& labels);

// Writes them the way readRelationVariables reads them.
void writeRelationVariables(FieldWriter& writer, int firstField, const std::vector<base::EntityId>& designVarIds,
                            const std::vector<std::string>& labels);

// The problem with the arguments of a relation, if there is one: no argument at all, a design variable that is not a
// positive ID, a label that would not read back.
[[nodiscard]] std::optional<CardProblem> checkRelationVariables(const std::vector<base::EntityId>& designVarIds,
                                                                const std::vector<std::string>& labels);

} // namespace oor::model
