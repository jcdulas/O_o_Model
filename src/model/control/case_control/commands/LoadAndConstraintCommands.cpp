#include "oor/model/control/case_control/commands/CommandFamilies.hpp"

namespace oor::model
{

// format reference "Data Selection": static and dynamic loads, constraints, thermal fields, static solution conditions.
void defineLoadAndConstraintCommands(CommandCatalogue& commands)
{
    // Static and dynamic load selection.
    // DEFORM, LOADSET and NONLINEAR select typed cards: the DEFORM set, the StaticLoadSequence set (a
    // StaticLoadSequence is a card of the Load category) and the NonlinearTableLoad1 to NonlinearNegativePowerLoad4 set
    // (the DynamicLoad category).
    commands.integer("DeformationLoadSelection").refersTo(ReferenceTarget::LoadCombinationSet);
    commands.integer("SuperelementLoadCombinationSelection")
        // a SuperelementLoadCombination (category Load), selected by its CID
        .refersTo(ReferenceTarget::LoadCombinationSet);
    commands.integer("StaticLoadSelection").refersTo(ReferenceTarget::LoadCombinationSet);
    commands.text("LoadNameText");
    commands.integer("DynamicLoadSelection").refersTo(ReferenceTarget::DynamicLoadSet);
    commands.integer("LoadSequenceSelection").refersTo(ReferenceTarget::LoadCombinationSet);
    commands.integer("NonlinearLoadSelection").refersTo(ReferenceTarget::DynamicLoadSet);
    commands.keyword("AxisymmetricBoundary");

    // Constraint selection. AUTOSPC(NOPRINT) = YES keeps its option in the entry's options.
    commands.keyword("AutoSingularityConstrSelection");
    commands.integer("BoundaryConditionSelection");
    commands.keyword("DihedralSymmetry");
    commands.integer("MultiPointConstrSelection").refersTo(ReferenceTarget::ConstraintSet);
    commands.integer("SinglePointConstrSelection").refersTo(ReferenceTarget::ConstraintSet);
    // the SID of the FreeBodySupportSet cards
    commands.integer("FreeBodySupportSelection").refersTo(ReferenceTarget::ConstraintSet);

    // Static solution conditions (the FreeBodySupportSet of a deck may be written FreeBodySupport: the abbreviation
    // rule covers it).
    commands.integer("StaticSubcaseSelection");

    // format reference: TEMPERATURE(INITIAL), (LOAD), (MATERIAL) and (BOTH) select a temperature set for different
    // uses: each is an attribute of its own. All of them name a set of NodeTemperatureLoad cards.
    commands.integer("TemperatureSelection")
        .variant("InitialTemperature")
        .variant("TemperatureLoadPart")
        .variant("MaterialTemperature")
        .variant("BothLoadAndInitial")
        .refersTo(ReferenceTarget::LoadCombinationSet);
    commands.integer("StructuralTemperatureSelection");
}

} // namespace oor::model
