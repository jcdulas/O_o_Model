#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <optional>
#include <string>
#include <vector>

namespace oor::model
{

// One DesignElemRelation2 card: a field of an element as the value of a DesignEquation equation of design variables and
// constants.
//
// Card layout: DesignElemRelation2  ID  TYPE  EID  CPNAME  CPMIN  CPMAX  EQID    fields 1 to 7
//                                  DesignVar  DVID1  DVID2  ...                     the lines after, from field 9
//                                  DTABLE  LABL1  LABL2  ...
// The equation receives the DVIDs and then the constants named by the LABLs, in that order, as its arguments.
// TYPE is the name of the element card (Bar2, ShellQuad4, SpringDofInline, ...), CPNAME the name of the field and CPMIN
// and CPMAX its limits, as in the DesignElemRelation1 (CPMIN blank is 1.0E-15 for a field that can only be positive,
// else -1.0E35: it depends on the field, so it stays blank here).
struct DesignElemRelation2Card
{
    static constexpr double NO_UPPER_LIMIT = 1.0e20;

    base::EntityId id = 0;     // unique among the DesignElemRelation2 cards
    std::string kind;          // upper case
    base::EntityId elemId = 0; // an element
    std::string name;          // CPNAME, upper case
    std::optional<double> minValue;
    double maxValue = NO_UPPER_LIMIT;
    base::EntityId equationId = 0;            // the DesignEquation
    std::vector<base::EntityId> designVarIds; // DVIDi
    // LABLi: constants of a DesignConstants or DesignFieldConstants card, matched without regard to case
    std::vector<std::string> labels;
};

} // namespace oor::model
