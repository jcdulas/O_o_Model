#pragma once

#include "oor/analysis/validation/engine/CheckRegistry.hpp"

// The aero family (aeroelasticity: AeroLiftingPanel1 to AeroPistonPanel5, AeroLiftingPanelProp1 to AeroPistonProp5, the
// splines, AeroControlSurface, the lists and factors, AeroTrim, AeroFlutter, AeroGust, ...). What the cards say that
// the reference checks do not see: a card that names something that does not exist is `ref.unresolved` (the cards say
// what they refer to, and a Case Control TRIM, FMETHOD, AeroGust, AeroDivergence, AeroControlSchedule or AEUXREF that
// names no card is `case.unresolved-reference`), and a repeated ID of one card type is `ref.duplicate-id`. The checks
// here are about what the numbers of the boxes, the labels of the trim variables and the values of the cards mean:
// panels whose boxes share IDs, a spline that names boxes its panel does not have, a label no card defines. One class
// per check, as in the other families; the order below is the order they run in.

namespace oor::analysis
{

// Two CAERO panels whose boxes take the same IDs.
void addPanelOverlapCheck(CheckRegistry& registry);
// A CAERO that names a PAERO of another kind.
void addPanelPropertyCheck(CheckRegistry& registry);
// A division list (AeroFactorList) of a CAERO with fewer than two points or not increasing.
void addDivisionListCheck(CheckRegistry& registry);
// An AeroBoxList item that no panel owns and no aerodynamic mesh has.
void addListBoxCheck(CheckRegistry& registry);
// A spline that names boxes its CAERO does not own.
void addSplineBoxCheck(CheckRegistry& registry);
// A SPLINE of one kind with the ID of a SPLINE of another kind.
void addSplineIdRepeatedCheck(CheckRegistry& registry);
// An AeroTrim and an AeroTrim2 with the same SID.
void addTrimIdRepeatedCheck(CheckRegistry& registry);
// An AeroControlSurface, AeroRigidTrimVariable or AeroController with the label of another one.
void addLabelRepeatedCheck(CheckRegistry& registry);
// A label of an AeroTrim, AeroTrim2, AeroTrimLink or AeroControlVector that no AeroControlSurface,
// AeroRigidTrimVariable or AeroController defines.
void addLabelUndefinedCheck(CheckRegistry& registry);
// A variable that two AeroTrimLink cards of the same subcases both make dependent.
void addLinkDependentRepeatedCheck(CheckRegistry& registry);
// An AeroControlSurfaceNodes whose label no AeroControlSurface has.
void addSurfaceLabelCheck(CheckRegistry& registry);
// An AeroComponent or AeroComponentUnion with the name of another component.
void addComponentNameRepeatedCheck(CheckRegistry& registry);
// An AeroComponentUnion that joins a component no card defines.
void addComponentLabelUndefinedCheck(CheckRegistry& registry);
// A MonitorIntegratedLoad1 or MonitorDisplacement whose COMP names no component.
void addMonitorComponentUndefinedCheck(CheckRegistry& registry);
// A PKNL or PKNLS FLUTTER whose three AeroFlutterFactors lists differ in length.
void addFlutterFactorCountCheck(CheckRegistry& registry);
// An AeroGust whose velocity is not the one of the AeroUnsteadyParams card.
void addGustVelocityCheck(CheckRegistry& registry);
// A subcase that runs an aeroelastic analysis in a deck with no AeroUnsteadyParams or AeroStaticParams card.
void addAeroCardMissingCheck(CheckRegistry& registry);
// A body of an AeroLiftingPanelProp1 that is not an AeroBody2, and one in another interference group than the panel.
void addAeroLiftingPanelPropBodyKindCheck(CheckRegistry& registry);
void addAeroLiftingPanelPropBodyGroupCheck(CheckRegistry& registry);
// An AeroBody2 with fewer than two slender body elements or no interference element, and one whose group no panel has.
void addBodyElementsCheck(CheckRegistry& registry);
void addBodyGroupCheck(CheckRegistry& registry);
// An AeroFactorList list of an AeroMachBoxPanel3 with an odd number of values (the (x, y) pairs).
void addAeroMachBoxPanel3ListsCheck(CheckRegistry& registry);
// A strip of an AeroStripPanel4 or AeroPistonPanel5 that has the number of a point of the model.
void addStripIdsCheck(CheckRegistry& registry);
// An AeroSplineEquation3 component the kind of its CAERO does not allow.
void addAeroSplineEquation3ComponentCheck(CheckRegistry& registry);
// An AeroFiniteSurfaceSpline6 or AeroFiniteBeamSpline7 that names an AeroBody2 body.
void addSplineBodyCheck(CheckRegistry& registry);
// A spline whose set of grid points is smaller than the spline needs.
void addSplineSetSizeCheck(CheckRegistry& registry);
// A control surface whose lower limit is above its upper limit.
void addSurfaceLimitsCheck(CheckRegistry& registry);
// An AeroTrimLink whose positive ID is the SID of no AeroTrim or AeroTrim2.
void addLinkTrimCheck(CheckRegistry& registry);
// The Mach number 1.0 on an AeroMachFreqTable1 or AeroMachFreqPairs2 in a model with no AeroStripPanel4.
void addMachOneCheck(CheckRegistry& registry);
// An AeroUnsteadyParams or AeroStaticParams coordinate system that is not rectangular.
void addSystemRectangularCheck(CheckRegistry& registry);

// Adds the checks of the family, in the order they run.
void registerAeroChecks(CheckRegistry& registry);

} // namespace oor::analysis
