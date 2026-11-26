#include "oor/analysis/validation/engine/ValidationSupport.hpp"

#include "oor/base/text/TextUtilities.hpp"
#include "oor/model/cards/constraints/multiPointConstr/MultiPointConstrTable.hpp"
#include "oor/model/cards/constraints/multiPointConstrUnion/MultiPointConstrUnionTable.hpp"
#include "oor/model/cards/constraints/singlePointConstr/SinglePointConstrTable.hpp"
#include "oor/model/cards/constraints/singlePointConstrList/SinglePointConstrListTable.hpp"
#include "oor/model/cards/constraints/singlePointConstrUnion/SinglePointConstrUnionTable.hpp"
#include "oor/model/cards/nodes/node/NodeTable.hpp"
#include "oor/model/cards/nodes/scalarPoint/ScalarPointTable.hpp"
#include "oor/model/cards/parameters/parameter/ParameterTable.hpp"
#include "oor/model/cards/superelements/superelementBulkOptions/SuperelementBulkOptionsTable.hpp"
#include "oor/model/core/UnknownCardTable.hpp"
#include "oor/model/format/CardLayouts.hpp"
#include "oor/model/parameters/ParameterValues.hpp"

#include <algorithm>
#include <set>

namespace oor::analysis
{

std::string_view describeTarget(model::ReferenceTarget target) noexcept
{
    using model::ReferenceTarget;
    switch (target)
    {
    case ReferenceTarget::Node:
    case ReferenceTarget::NodeInRange:
        return "grid point";
    case ReferenceTarget::ScalarOrGridPoint:
        return "grid or scalar point";
    case ReferenceTarget::Element:
    case ReferenceTarget::ElementInRange:
        return "element";
    case ReferenceTarget::SurfaceElement:
    case ReferenceTarget::SurfaceElementInRange:
        return "surface element";
    case ReferenceTarget::Property:
    case ReferenceTarget::PropertyInRange:
        return "property";
    case ReferenceTarget::Material:
        return "material";
    case ReferenceTarget::ThermalMaterial:
        return "thermal material";
    case ReferenceTarget::Coordinate:
        return "coordinate system";
    case ReferenceTarget::DynamicTable:
        return "dynamic table";
    case ReferenceTarget::MaterialTable:
        return "material table";
    case ReferenceTarget::StressTable:
        return "stress table";
    case ReferenceTarget::StressOrMultiDimensionalTable:
        return "stress or multi-dimensional table";
    case ReferenceTarget::HeatTable:
        return "heat table";
    case ReferenceTarget::HybridDampingRotorOptionsTable:
        return "damping table";
    case ReferenceTarget::RandomTable:
        return "random table";
    case ReferenceTarget::Method:
        return "eigenvalue method";
    case ReferenceTarget::LoadCombinationSet:
        return "load set";
    case ReferenceTarget::ConstraintSet:
        return "constraint set";
    case ReferenceTarget::DynamicLoadSet:
        return "dynamic load set";
    case ReferenceTarget::ExcitationSet:
    case ReferenceTarget::ExcitationDefined:
        return "excitation set";
    case ReferenceTarget::FrequencySet:
        return "frequency set";
    case ReferenceTarget::ComplexMethod:
        return "complex eigenvalue method";
    case ReferenceTarget::DelaySet:
        return "delay set";
    case ReferenceTarget::PhaseSet:
        return "phase lead set";
    case ReferenceTarget::TimeStepSet:
        return "time step set";
    case ReferenceTarget::NonlinearSet:
        return "nonlinear parameter set";
    case ReferenceTarget::RandomSet:
        return "random set";
    case ReferenceTarget::TransferFunctionSet:
        return "transfer function set";
    case ReferenceTarget::InitialConditionSet:
        return "initial condition set";
    case ReferenceTarget::Set:
        return "set";
    case ReferenceTarget::HeatBoundaryProperty:
        return "heat boundary property";
    case ReferenceTarget::ConvectionProperty:
        return "convection property";
    case ReferenceTarget::ForcedConvectionProperty:
        return "forced convection property";
    case ReferenceTarget::RadiationMaterial:
        return "radiation material";
    case ReferenceTarget::ViewFactorFaceFactor:
        return "view factor definition";
    case ReferenceTarget::RadiationCavity:
        return "radiation cavity";
    case ReferenceTarget::ContactBody:
        return "contact body";
    case ReferenceTarget::ContactSurface:
        return "contact surface";
    case ReferenceTarget::ContactRigid:
        return "rigid contact body";
    case ReferenceTarget::ContactBodyParameters:
        return "contact body parameter set";
    case ReferenceTarget::ContactGeometricParameters:
        return "contact geometric parameter set";
    case ReferenceTarget::ContactPhysicalParameters:
        return "contact physical parameter set";
    case ReferenceTarget::ContactPair:
        return "contact pair";
    case ReferenceTarget::ContactTable:
        return "contact table";
    case ReferenceTarget::ContactSelection:
        return "contact table or pair";
    case ReferenceTarget::TrimmingCurve:
        return "trimming curve";
    case ReferenceTarget::SlidelineSegments:
        return "slideline segment list";
    case ReferenceTarget::SlidelineContact:
        return "slideline contact region";
    case ReferenceTarget::SlidelineFriction:
        return "slideline friction";
    case ReferenceTarget::NonlinearStep:
        return "nonlinear step set";
    case ReferenceTarget::NonlinearHarmonic:
        return "nonlinear harmonic set";
    case ReferenceTarget::NonlinearFrequency:
        return "nonlinear frequency set";
    case ReferenceTarget::EquationOfState:
        return "equation of state";
    case ReferenceTarget::ShearModel:
        return "shear model";
    case ReferenceTarget::YieldModel:
        return "yield model";
    case ReferenceTarget::FailureModel:
        return "failure model";
    case ReferenceTarget::SpallModel:
        return "spall model";
    case ReferenceTarget::EulerMesh:
        return "Euler mesh";
    case ReferenceTarget::MeshBias:
        return "mesh bias";
    case ReferenceTarget::EulerBodyForce:
        return "Euler body force";
    case ReferenceTarget::EulerRegionSet:
        return "Euler region set";
    case ReferenceTarget::EulerRegionShape:
        return "Euler region shape";
    case ReferenceTarget::Coupling:
        return "coupling surface";
    case ReferenceTarget::CouplingOptions:
        return "coupling option set";
    case ReferenceTarget::CohesiveFriction:
        return "cohesive friction model";
    case ReferenceTarget::CohesiveFrictionSet:
        return "cohesive friction set";
    case ReferenceTarget::CouplingFailure:
        return "coupling failure";
    case ReferenceTarget::HydrostaticPreset:
        return "hydrostatic preset";
    case ReferenceTarget::GasBag:
        return "gas bag";
    case ReferenceTarget::Leakage:
        return "leakage set";
    case ReferenceTarget::Porosity:
        return "porosity model";
    case ReferenceTarget::InflatorSet:
        return "inflator set";
    case ReferenceTarget::Inflator:
        return "inflator model";
    case ReferenceTarget::InflatorGas:
        return "inflator gas";
    case ReferenceTarget::GasFractions:
        return "gas fraction table";
    case ReferenceTarget::InitialGas:
        return "initial gas composition";
    case ReferenceTarget::DesignVariable:
        return "design variable";
    case ReferenceTarget::DesignEquation:
        return "design equation";
    case ReferenceTarget::DesignResponse:
        return "design response";
    case ReferenceTarget::DesignConstraintSet:
        return "design constraint set";
    case ReferenceTarget::PropertyRelation:
        return "property relation";
    case ReferenceTarget::MaterialRelation:
        return "material relation";
    case ReferenceTarget::ConnectivityRelation:
        return "connectivity relation";
    case ReferenceTarget::AeroElement:
        return "aerodynamic element";
    case ReferenceTarget::AeroPanelOrComponent:
        return "aerodynamic panel or component";
    case ReferenceTarget::AeroBox:
        return "aerodynamic box";
    case ReferenceTarget::AeroProperty:
        return "aerodynamic property";
    case ReferenceTarget::AeroList:
        return "aerodynamic list";
    case ReferenceTarget::AeroFactor:
        return "aerodynamic factor list";
    case ReferenceTarget::AeroFlutterFactor:
        return "flutter factor list";
    case ReferenceTarget::AeroControlSurface:
        return "control surface";
    case ReferenceTarget::AeroTrimSet:
        return "trim set";
    case ReferenceTarget::AeroFlutterSet:
        return "flutter set";
    case ReferenceTarget::AeroGustSet:
        return "gust set";
    case ReferenceTarget::DivergenceSet:
        return "divergence set";
    case ReferenceTarget::ControlSchedule:
        return "control surface schedule";
    case ReferenceTarget::ControlVector:
        return "control vector";
    case ReferenceTarget::AeroNode:
        return "aerodynamic grid point";
    case ReferenceTarget::AeroScale:
        return "aerodynamic scale";
    case ReferenceTarget::Superelement:
        return "superelement";
    case ReferenceTarget::MassIncrement:
        return "mass increment";
    case ReferenceTarget::MassCombination:
        return "mass combination";
    case ReferenceTarget::AeroSpline:
        return "spline";
    case ReferenceTarget::HybridDampingRotorOptionsSpecification:
        return "damping specification";
    case ReferenceTarget::HybridDamping:
        return "hybrid damping";
    case ReferenceTarget::ElementList:
        return "element list";
    case ReferenceTarget::ModuleMove:
        return "module move";
    case ReferenceTarget::MultiDimensionalTable:
        return "multi-dimensional table";
    case ReferenceTarget::FatigueTable:
        return "fatigue table";
    case ReferenceTarget::ImperfectionCase:
        return "imperfection case";
    case ReferenceTarget::ImperfectionGeometry:
        return "imperfection";
    case ReferenceTarget::GeometricBoundary:
        return "geometric boundary";
    case ReferenceTarget::AdaptivityCriterion:
        return "adaptivity criterion";
    case ReferenceTarget::AdaptivitySet:
        return "adaptivity";
    case ReferenceTarget::Rotor:
        return "rotor";
    case ReferenceTarget::DiscreteValueSet:
        return "discrete value set";
    case ReferenceTarget::UserDefinedName:
        return "user defined file name";
    case ReferenceTarget::FatigueProperty:
        return "fatigue property";
    case ReferenceTarget::FatigueLoad:
        return "fatigue load";
    case ReferenceTarget::FatigueEvent:
        return "fatigue event";
    case ReferenceTarget::EulerInitialization:
        return "Euler initialization";
    case ReferenceTarget::EulerInitialRegions:
        return "Euler initial regions";
    case ReferenceTarget::InitialValueSet:
        return "initial value set";
    case ReferenceTarget::HeatLossSet:
        return "heat loss set";
    case ReferenceTarget::HeatTransferModel:
        return "heat transfer model";
    case ReferenceTarget::CosimulationGroup:
        return "co-simulation group";
    case ReferenceTarget::CosimulationInput:
        return "co-simulation input";
    case ReferenceTarget::CosimulationOutput:
        return "co-simulation output";
    case ReferenceTarget::CosimulationService:
        return "co-simulation service";
    case ReferenceTarget::WettedElement:
        return "wetted element";
    case ReferenceTarget::WettedSurface:
        return "wetted surface";
    case ReferenceTarget::BrakeProperty:
        return "brake property";
    case ReferenceTarget::BrakeMotion:
        return "brake motion";
    case ReferenceTarget::BrakeSqueal:
        return "brake squeal analysis";
    case ReferenceTarget::FrfComponent:
        return "FRF component";
    case ReferenceTarget::BushingForceSet:
        return "rotor bushing force set";
    case ReferenceTarget::LoadStepControl:
        return "load stepping control table";
    case ReferenceTarget::TemperatureGroup:
        return "temperature group";
    case ReferenceTarget::MonteCarloSet:
        return "Monte-Carlo set";
    case ReferenceTarget::DeactivatedElementSet:
        return "deactivated element set";
    case ReferenceTarget::TransferPathSet:
        return "transfer path analysis";
    case ReferenceTarget::IterativeSolver:
        return "iterative solver options";
    case ReferenceTarget::MetadataGroup:
        return "meta data group";
    case ReferenceTarget::Other:
        break;
    }
    return "card";
}

std::string_view cardNameAt(const model::Model& /*model*/, model::CardLocation location)
{
    return model::CardRegistry::instance().entry(location.table).info.name;
}

std::string cardLabels(const model::Model&, std::initializer_list<std::string_view> cardTypes,
                       std::string_view conjunction)
{
    std::string text;
    std::size_t index = 0;
    for (const std::string_view cardType : cardTypes)
    {
        if (index > 0)
            text += index + 1 == cardTypes.size() ? " " + std::string(conjunction) + " " : std::string(", ");
        text += std::string(cardType);
        ++index;
    }
    return text;
}

std::string idFieldAt(const model::Model& model, model::CardLocation location)
{
    const auto* layout = model::CardLayouts::standard()->find(cardNameAt(model, location));
    return layout && !layout->fields.empty() ? layout->fields.front().name : std::string("id");
}

bool isOneOf(std::string_view name, std::initializer_list<std::string_view> names) noexcept
{
    return std::ranges::find(names, name) != names.end();
}

std::optional<model::ParameterCard> findParameter(const model::Model& model, std::string_view name)
{
    std::optional<model::ParameterCard> found;
    forEachCard<model::ParameterTable>(model,
                                       [&](const model::ParameterCard& card, model::CardLocation)
                                       {
                                           if (card.name == name)
                                               found = card;
                                       });
    return found;
}

std::set<std::string> unknownCardNames(const model::Model& model)
{
    std::set<std::string> names;
    const model::CardTable* table = model.findTable(model::CardRegistry::UNKNOWN_TYPE);
    const auto* unknown = dynamic_cast<const model::UnknownCardTable*>(table);
    if (unknown == nullptr)
        return names;
    for (std::uint32_t row = 0; row < unknown->rows().rowCount(); ++row)
    {
        if (unknown->rows().isAlive(row))
            names.emplace(unknown->nameAt(row).view());
    }
    return names;
}

bool isHeatTransfer(const model::Model& root)
{
    const model::ControlStatement* app = root.control().executive.findLast("ApplicationKind");
    if (app == nullptr)
        return false;
    return std::ranges::any_of(
        app->parameters, [](const model::StatementParameter& parameter)
        { return parameter.isNamed("HeatTransferApplication") || ((parameter.value) == ("HeatTransferApplication")); });
}

bool isHeatThenStress(const model::Model& root)
{
    // PARAM,HeatStaticAnalysis: the last card, else the format reference default (No).
    const std::optional<model::ParameterValue> heatstat = model::parameterValue(root, "HeatStaticAnalysis");
    return heatstat && ((heatstat->card.textValue) == ("Yes"));
}

const model::Model* imageOfPart(const model::Model& model)
{
    const model::Model* owner = model.owner();
    const std::optional<model::PartInfo>& info = model.partInfo();
    if (owner == nullptr || !info || info->kind != "SuperelementPart" || info->massId != 0)
        return nullptr;
    const model::SuperelementBulkOptionsTable* bulks = owner->findTable<model::SuperelementBulkOptionsTable>();
    if (bulks == nullptr)
        return nullptr;
    for (std::uint32_t row = 0; row < bulks->rows().rowCount(); ++row)
    {
        if (!bulks->rows().isAlive(row) || bulks->idAtRow(row) != info->id)
            continue;
        const model::SuperelementBulkOptionsCard card = bulks->card(row);
        if ((card.partType != model::SuperelementBulkOptionsType::Repeat &&
             card.partType != model::SuperelementBulkOptionsType::Mirror) ||
            card.referenceSuperelementId <= 0)
            continue;
        const model::Model* original = &owner->superelementModel(card.referenceSuperelementId);
        return original == &model || original == owner ? nullptr : original;
    }
    return nullptr;
}

bool isGridPoint(const model::Model& model, base::EntityId nid)
{
    const std::optional<model::CardLocation> found = model.locate(base::IdSpace::Node, nid);
    return found && found->table == model::typeIndexOf<model::NodeTable>();
}

bool isScalarPoint(const model::Model& model, base::EntityId nid)
{
    const std::optional<model::CardLocation> found = model.locate(base::IdSpace::Node, nid);
    return found && found->table == model::typeIndexOf<model::ScalarPointTable>();
}

std::vector<const model::Subcase*> analysisSubcases(const model::CaseControl& caseControl)
{
    std::vector<const model::Subcase*> subcases;
    for (std::size_t index = 1; index < caseControl.segments().size(); ++index)
    {
        const model::Subcase& segment = caseControl.segments()[index];
        // format reference AUXCASE: the sections after the first AUXCASE analyse an auxiliary model, not this one.
        if (segment.kind == model::SubcaseKind::AuxiliaryCase)
            break;
        if (segment.kind != model::SubcaseKind::Global)
            subcases.push_back(&segment);
    }
    if (subcases.empty())
        subcases.push_back(&caseControl.global());
    return subcases;
}

std::vector<const model::Subcase*> auxiliarySubcases(const model::CaseControl& caseControl)
{
    std::vector<const model::Subcase*> subcases;
    const model::Subcase* section = nullptr;
    bool sectionHasSubcase = false;
    const auto closeSection = [&]()
    {
        if (section != nullptr && !sectionHasSubcase)
            subcases.push_back(section);
    };
    for (const model::Subcase& segment : caseControl.segments())
    {
        if (segment.kind == model::SubcaseKind::AuxiliaryCase)
        {
            closeSection();
            section = &segment;
            sectionHasSubcase = false;
        }
        else if (section != nullptr && segment.kind != model::SubcaseKind::Global)
        {
            subcases.push_back(&segment);
            sectionHasSubcase = true;
        }
    }
    closeSection();
    return subcases;
}

std::optional<std::int64_t> effectiveInteger(const model::CaseLineages& lineages, const model::Subcase& subcase,
                                             std::string_view command)
{
    const model::CaseEntry* entry = lineages.command(subcase.key, command);
    if (entry == nullptr || entry->value.kind != model::CaseValueKind::Integer)
        return std::nullopt;
    return entry->value.integer;
}

bool hasEffectiveCommand(const model::CaseLineages& lineages, const model::Subcase& subcase, std::string_view command)
{
    return lineages.command(subcase.key, command) != nullptr;
}

bool isStaticSolution(std::int64_t sol) noexcept
{
    return sol == 101 || sol == 105 || sol == 106 || sol == 144;
}

bool isDynamicSolution(std::int64_t sol) noexcept
{
    switch (sol)
    {
    case 103:
    case 107:
    case 108:
    case 109:
    case 110:
    case 111:
    case 112:
    case 115:
    case 116:
    case 118:
    case 129:
    case 146:
        return true;
    default:
        return false;
    }
}

namespace
{

// Adds `sid` and the sets it combines (SinglePointConstrUnion / MultiPointConstrUnion), down to the cards, a set met
// twice once.
template <typename AddTable>
void expand(const model::Model& model, base::EntityId sid, std::set<base::EntityId>& leaves)
{
    if (!leaves.insert(sid).second)
        return;
    forEachCard<AddTable>(model,
                          [&](const typename AddTable::CardType& add, model::CardLocation)
                          {
                              if (add.id != sid)
                                  return;
                              for (const base::EntityId member : add.sets)
                                  expand<AddTable>(model, member, leaves);
                          });
}

} // namespace

std::vector<base::EntityId> expandedConstraintSet(const model::Model& model, std::string_view command,
                                                  base::EntityId id)
{
    std::set<base::EntityId> leaves;
    if (command == model::SINGLE_POINT_CONSTR_SELECTION)
        expand<model::SinglePointConstrUnionTable>(model, id, leaves);
    else
        expand<model::MultiPointConstrUnionTable>(model, id, leaves);
    return std::vector<base::EntityId>(leaves.begin(), leaves.end());
}

namespace
{

// What the analysis subcases choose with one constraint command.
struct CommandChoices
{
    bool named = false; // a subcase has the command, its own or inherited
    // For each analysis subcase, in their order: the sets the command selects there (expanded, sorted); nothing for a
    // subcase without the command, or with one that does not name a set.
    std::vector<std::optional<std::vector<base::EntityId>>> bySubcase;
};

// `caseControl` is the one of the deck; the union cards that expand a selection are the ones of `model`.
CommandChoices choicesOf(const model::CaseControl& caseControl, const model::CaseLineages& lineages,
                         const model::Model& model, std::string_view command)
{
    CommandChoices choices;
    for (const model::Subcase* subcase : analysisSubcases(caseControl))
    {
        choices.bySubcase.emplace_back();
        const std::optional<std::int64_t> value = effectiveInteger(lineages, *subcase, command);
        if (!value)
            continue;
        choices.named = true;
        if (const std::optional<base::EntityId> id = base::toEntityId(*value))
            choices.bySubcase.back() = expandedConstraintSet(model, command, *id);
    }
    return choices;
}

// Every set ID a constraint command could name in the model: the ones of the Bulk Data cards of the command and the
// ones of the union cards that combine them.
std::set<base::EntityId> constraintSetIds(const model::Model& model, std::string_view command)
{
    std::set<base::EntityId> ids;
    if (command == model::SINGLE_POINT_CONSTR_SELECTION)
    {
        forEachCard<model::SinglePointConstrTable>(
            model, [&](const model::SinglePointConstrCard& card, model::CardLocation) { ids.insert(card.id); });
        forEachCard<model::SinglePointConstrListTable>(
            model, [&](const model::SinglePointConstrListCard& card, model::CardLocation) { ids.insert(card.id); });
        forEachCard<model::SinglePointConstrUnionTable>(
            model, [&](const model::SinglePointConstrUnionCard& card, model::CardLocation) { ids.insert(card.id); });
    }
    else
    {
        forEachCard<model::MultiPointConstrTable>(
            model, [&](const model::MultiPointConstrCard& card, model::CardLocation) { ids.insert(card.id); });
        forEachCard<model::MultiPointConstrUnionTable>(
            model, [&](const model::MultiPointConstrUnionCard& card, model::CardLocation) { ids.insert(card.id); });
    }
    return ids;
}

} // namespace

std::vector<std::vector<base::EntityId>> constraintSelections(const model::Model& root, const model::Model& model,
                                                              std::string_view command)
{
    const model::CaseControl& caseControl = root.control().caseControl;
    const model::CaseLineages lineages(caseControl);
    const CommandChoices choices = choicesOf(caseControl, lineages, model, command);
    std::set<std::vector<base::EntityId>> selections;
    if (choices.named)
    {
        for (const std::optional<std::vector<base::EntityId>>& sets : choices.bySubcase)
        {
            if (sets)
                selections.insert(*sets);
        }
    }
    else
    {
        // No command anywhere: nothing says which sets go together, so each set ID is judged alone (a union with the
        // sets it combines). All the sets in one selection would report two alternative sets as if they were active
        // at the same time.
        for (const base::EntityId id : constraintSetIds(model, command))
            selections.insert(expandedConstraintSet(model, command, id));
    }
    return std::vector<std::vector<base::EntityId>>(selections.begin(), selections.end());
}

std::vector<ConstraintCombination> constraintCombinations(const model::Model& root, const model::Model& model)
{
    const model::CaseControl& caseControl = root.control().caseControl;
    const model::CaseLineages lineages(caseControl);
    const CommandChoices spc = choicesOf(caseControl, lineages, model, model::SINGLE_POINT_CONSTR_SELECTION);
    const CommandChoices mpc = choicesOf(caseControl, lineages, model, model::MULTI_POINT_CONSTR_SELECTION);
    // (multipoint sets, single point sets): the order of the pairs is the order of the result.
    std::set<std::pair<std::vector<base::EntityId>, std::vector<base::EntityId>>> pairs;
    if (mpc.named)
    {
        // What each subcase selects with the two commands; a subcase without SPC has no single point constraint set
        // (and when no subcase names SPC, none is active).
        for (std::size_t index = 0; index < mpc.bySubcase.size(); ++index)
        {
            if (mpc.bySubcase[index])
                pairs.emplace(*mpc.bySubcase[index], spc.bySubcase[index].value_or(std::vector<base::EntityId>{}));
        }
    }
    else if (!spc.named)
    {
        // Neither command anywhere: every set of one with every set of the other (see the header for why all the sets
        // together give the clashes of every pair of one set of each).
        const std::set<base::EntityId> mpcIds = constraintSetIds(model, model::MULTI_POINT_CONSTR_SELECTION);
        const std::set<base::EntityId> spcIds = constraintSetIds(model, model::SINGLE_POINT_CONSTR_SELECTION);
        if (!mpcIds.empty())
            pairs.emplace(std::vector<base::EntityId>(mpcIds.begin(), mpcIds.end()),
                          std::vector<base::EntityId>(spcIds.begin(), spcIds.end()));
    }
    // Else only SPC is named: no multipoint constraint set is active, nothing to combine.
    std::vector<ConstraintCombination> combinations;
    combinations.reserve(pairs.size());
    for (const auto& [mpcSets, spcSets] : pairs)
        combinations.push_back(ConstraintCombination{mpcSets, spcSets});
    return combinations;
}

} // namespace oor::analysis
