#pragma once

#include "oor/analysis/validation/engine/CheckRegistry.hpp"

// The design family (SOL 200 and the other design optimisation sequences): what the cards DesignVar, DesignVarLink,
// DesignConstants, DesignEquation, DesignPropRelation2, DesignMatRelation2, DesignElemRelation2, DesignResp1,
// DesignResp2 and DesignConstr say that the reference checks do not see. A design variable, an equation, a property, a
// material, an element or a response that does not exist is `ref.unresolved` (the cards say what they refer to), and a
// duplicated ID is `ref.duplicate-id`; the checks here are about the values: bounds that exclude the initial value, a
// label no DesignConstants defines, an equation that needs more arguments than its relation gives, responses that
// contain one another in a circle. One class per check, as in the other families. The relation checks read the design
// model (`model/design`: what each relation drives, and the functions of each card type that say which names are
// fields).

namespace oor::analysis
{

// A DesignResp1, DesignResp2 or DesignResp3 with the ID of a response of another card type.
void addResponseIdRepeatedCheck(CheckRegistry& registry);
// A DesignVar whose initial value is outside its bounds, or whose lower bound is above its upper bound.
void addVariableBoundsCheck(CheckRegistry& registry);
// A DesignVarLink whose independent variable is the dependent variable of a DesignVarLink (its own included).
void addLinkDependentCheck(CheckRegistry& registry);
// A label that two DesignConstants or DesignFieldConstants entries both define.
void addConstantRepeatedCheck(CheckRegistry& registry);
// A DesignEquation the library keeps as text because its equations do not parse.
void addEquationSyntaxCheck(CheckRegistry& registry);
// A DesignPropRelation2, DesignMatRelation2, DesignElemRelation2 or DesignResp2 that gives its DesignEquation fewer
// values than the equation has arguments.
void addEquationArgumentsCheck(CheckRegistry& registry);
// A constant that a DVxREL2, DesignResp2 or DesignResp3 names and no DesignConstants or DesignFieldConstants defines.
void addUndefinedConstantCheck(CheckRegistry& registry);
// A DesignPropRelation2 on a property card the format reference says it does not support (CurvedBeamProp, BarShapeProp,
// BeamShapeProp).
void addRelationTypeCheck(CheckRegistry& registry);
// A DesignResp1 of a response type that has no region, with a REGION.
void addResponseRegionCheck(CheckRegistry& registry);
// DesignResp2 cards that contain one another in a circle.
void addResponseCycleCheck(CheckRegistry& registry);
// A DesignConstr with a lower bound above its upper bound.
void addConstraintBoundsCheck(CheckRegistry& registry);
// A DesignConstr set that bounds the same response twice.
void addConstraintRepeatedCheck(CheckRegistry& registry);

// A relation that names a field the card it drives does not have or a relation cannot drive (the PNAME of a DVPREL, the
// MPNAME of a DVMREL, the CPNAME of a DVCREL), judged by the functions of `model/design`.
void addRelationTargetCheck(CheckRegistry& registry);
// A relation whose limits exclude the value it gives at the initial values of the design variables.
void addRelationBoundsCheck(CheckRegistry& registry);
// A DesignResp1 whose ATTA or ATTB does not fit its type of response.
void addResponseAttributesCheck(CheckRegistry& registry);
// A SOL 200 deck with design variables and constraints that has no DESOBJ.
void addNoObjectiveCheck(CheckRegistry& registry);
// A design variable no relation, link or response uses.
void addUnusedVariableCheck(CheckRegistry& registry);

// Adds the checks of the family, in the order they run.
void registerDesignChecks(CheckRegistry& registry);

} // namespace oor::analysis
