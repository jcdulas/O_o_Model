#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/cards/optimisation/DesignField.hpp"

#include <optional>
#include <string>
#include <vector>

namespace oor::model
{

// One DesignPropRelation2 card: a field of a property as the value of a DesignEquation equation of design variables and
// constants.
//
// Card layout: DesignPropRelation2  ID  TYPE  PID  PNAME/FID  PMIN  PMAX  EQID      fields 1 to 7
//                                  DesignVar  DVID1  DVID2  ...                       the lines after, from field 9
//                                  DTABLE  LABL1  LABL2  ...
// The equation receives the DVIDs and then the constants named by the LABLs, in that order, as its arguments.
// TYPE, PID, PNAME/FID, PMIN and PMAX are those of the DesignPropRelation1 (a PMIN left blank is 1.0E-15, or -1.0E35
// for a field that is a stress recovery location: it depends on the field, so it stays blank here). The format
// reference says that CurvedBeamProp, BarShapeProp and BeamShapeProp are not supported by this card; the card does not
// refuse them.
struct DesignPropRelation2Card
{
    static constexpr double NO_UPPER_LIMIT = 1.0e20;

    base::EntityId id = 0;     // unique among the DesignPropRelation2 cards
    std::string kind;          // upper case
    base::EntityId propId = 0; // the property
    DesignField field;
    std::optional<double> minValue;
    double maxValue = NO_UPPER_LIMIT;
    base::EntityId equationId = 0;            // the DesignEquation
    std::vector<base::EntityId> designVarIds; // DVIDi
    // LABLi: constants of a DesignConstants or DesignFieldConstants card, matched without regard to case
    std::vector<std::string> labels;
};

} // namespace oor::model
