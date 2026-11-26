// The references that no card field holds directly: the members of the sets (an IdListSet1, a SET of the Case Control),
// which are grid points or elements only because of the card or the output request that names the set; the parameters
// whose value is the ID of a card; and the renumbering by an offset that takes an ID out of the range of the IDs.

#include "oor/base/errors/Errors.hpp"
#include "oor/model/cards/materials/gasketMat/GasketMatTable.hpp"
#include "oor/model/cards/parameters/parameter/ParameterTable.hpp"
#include "oor/model/cards/sets/idListSet1/IdListSet1Table.hpp"
#include "oor/model/cards/sets/typedListSet3/TypedListSet3Table.hpp"
#include "oor/model/references/ReferenceChecker.hpp"
#include "oor/model/references/Renumbering.hpp"
#include "oor/model/references/SetMemberUses.hpp"
#include "support/ControlTestSupport.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string>
#include <utility>
#include <vector>

using namespace oor;
using namespace oor::model;
using oor::testing::caseText;
using oor::testing::readModelText;
using oor::testing::writeModelText;

namespace
{

// Six grid points and two quadrilaterals, with their property and material so that every reference of the mesh
// resolves.
const std::string MESH =
    "Node;101;;0.;0.;0.\n"
    "Node;102;;1.;0.;0.\n"
    "Node;103;;2.;0.;0.\n"
    "Node;104;;0.;1.;0.\n"
    "Node;105;;1.;1.;0.\n"
    "Node;106;;2.;1.;0.\n"
    "ShellQuad4;1;9000;101;102;105;104\n"
    "ShellQuad4;2;9000;102;103;106;105\n"
    "ShellProp;9000;9000;0.1\n"
    "IsoMat;9000;2.1E+11;;0.3\n";

// A set of grid points (20: an ID and a range) and a set of elements (30), named as such by a free-body subsystem
// (its GRIDSET and its ELEMSET).
const std::string SETS =
    "IdListSet1;20;101;102;Through;104\n"
    "IdListSet1;30;1;2\n"
    "FreeBodyLoadSubcase;FLAP;20;30\n";

// A Case Control with a SET of grid points (9, named by a displacement request) and a SET of elements (8, named by a
// stress request).
const std::string CASE =
    "[executive]\n"
    "SolutionSequence;101\n"
    "[case]\n"
    "SetDefinition;9;101;102\n"
    "SetDefinition;8;1;2\n"
    "DisplacementOutput;9;PrintListing\n"
    "StressOutput;8\n"
    "[model]\n";

// What was reported when the deck of a test was read, shown when an assertion of the test fails.
std::string readingProblems(const Model& model)
{
    std::string text = "reading reported:";
    for (const base::Diagnostic& diagnostic : model.diagnostics().diagnostics())
        text += "\n  " + diagnostic.code + ": " + diagnostic.message;
    return text;
}

// The members of the IdListSet1 card of a row, as the card keeps them.
std::vector<IdRun> setMembers(const Model& model, std::uint32_t row)
{
    return model.findTable<IdListSet1Table>()->card(row).ids;
}

// The members of the SET `number` that a section of the Case Control defines.
std::vector<std::int64_t> caseSetMembers(const Subcase& section, std::int64_t number)
{
    const CaseEntry* entry = CaseControl::ownSet(section, number);
    REQUIRE(entry != nullptr);
    return entry->set.integers;
}

// The message of the UsageError that a renumbering throws; empty when it throws nothing.
std::string refusal(Model& model, RenumberSpace space, const MappingFactory& mapping)
{
    try
    {
        Renumbering::apply(model, space, mapping);
    }
    catch (const base::UsageError& error)
    {
        return error.what();
    }
    return {};
}

// Keeps what a card shows to a reference visitor.
struct Visits final : ReferenceVisitor
{
    std::vector<std::string> fields;
    std::vector<ReferenceTarget> targets;
    base::EntityId visit(std::string_view field, ReferenceTarget target, base::EntityId id) override
    {
        fields.emplace_back(field);
        targets.push_back(target);
        return id;
    }
};

template <typename TableT>
Visits visitsOf(Model& model, std::uint32_t row)
{
    Visits visits;
    model.table<TableT>().visitReferences(row, visits);
    return visits;
}

std::size_t unresolvedCount(Model& model)
{
    base::DiagnosticSink sink;
    return ReferenceChecker::check(model, sink);
}

} // namespace

// ---------------------------------------------------------------------------------------------------------------------
// C1: the members of the sets follow a renumbering
// ---------------------------------------------------------------------------------------------------------------------

TEST_CASE("the users of a set say what its members are", "[model][references][review]")
{
    REQUIRE(memberKindOfSetField("AeroSurfaceSpline1", "nodeSetId") == SetMemberKind::Node);
    REQUIRE(memberKindOfSetField("FreeBodyLoadSubcase", "elementSetId") == SetMemberKind::Element);
    REQUIRE(memberKindOfSetField("FreeBodyLoadSubcase", "names") == SetMemberKind::Unknown);
    REQUIRE(memberKindOfSetField("TransferPathSetup", "nodeSetId") == SetMemberKind::Unknown); // a TypedListSet3 only
    REQUIRE(memberKindOfOutputSet("DisplacementOutput") == SetMemberKind::Node);
    REQUIRE(memberKindOfOutputSet("StressOutput") == SetMemberKind::Element);
    REQUIRE(memberKindOfOutputSet("TitleText") == SetMemberKind::Unknown);

    Model model = readModelText(MESH + SETS + "IdListSet1;40;101;102\n"); // set 40 has no user
    INFO(readingProblems(model));
    const BulkSetUses uses = bulkSetUses(model);
    REQUIRE(uses.size() == 2);
    REQUIRE(uses.at(20).kind() == SetMemberKind::Node);
    REQUIRE(uses.at(20).user().find("nodeSetId of FreeBodyLoadSubcase") == 0);
    REQUIRE(uses.at(30).kind() == SetMemberKind::Element);
    REQUIRE(uses.at(30).set == "IdListSet1 30");
}

TEST_CASE("renumbering the nodes takes the members of the sets of grid points, and leaves the sets of elements",
          "[model][references][review]")
{
    Model model = readModelText(CASE + MESH + SETS);
    INFO(readingProblems(model));
    REQUIRE(unresolvedCount(model) == 0);

    REQUIRE(Renumbering::apply(model, RenumberSpace::Node, Renumbering::offset(1000)) == 6);
    // The single ID and the two ends of the range of the set of grid points; the set of elements is as it was.
    REQUIRE(setMembers(model, 0) == std::vector<IdRun>{{1101, 1101}, {1102, 1104}});
    REQUIRE(setMembers(model, 1) == std::vector<IdRun>{{1, 1}, {2, 2}});
    const CaseControl& control = std::as_const(model).control().caseControl;
    REQUIRE(caseSetMembers(control.global(), 9) == std::vector<std::int64_t>{1101, 1102});
    REQUIRE(caseSetMembers(control.global(), 8) == std::vector<std::int64_t>{1, 2});
    const std::string text = caseText(control);
    REQUIRE(text.find("SetDefinition;9;1101;1102\n") != std::string::npos);
    REQUIRE(text.find("SetDefinition;8;1;2\n") != std::string::npos);
    // Every member still names a grid point or an element.
    REQUIRE(unresolvedCount(model) == 0);
}

TEST_CASE("renumbering the elements takes the members of the sets of elements, and leaves the sets of grid points",
          "[model][references][review]")
{
    Model model = readModelText(CASE + MESH + SETS);
    INFO(readingProblems(model));

    REQUIRE(Renumbering::apply(model, RenumberSpace::Element, Renumbering::offset(500)) == 2);
    REQUIRE(setMembers(model, 0) == std::vector<IdRun>{{101, 101}, {102, 104}});
    REQUIRE(setMembers(model, 1) == std::vector<IdRun>{{501, 501}, {502, 502}});
    const CaseControl& control = std::as_const(model).control().caseControl;
    REQUIRE(caseSetMembers(control.global(), 9) == std::vector<std::int64_t>{101, 102});
    REQUIRE(caseSetMembers(control.global(), 8) == std::vector<std::int64_t>{501, 502});
    REQUIRE(unresolvedCount(model) == 0);
}

TEST_CASE("the members of a set that no known user names are left alone by a renumbering",
          "[model][references][review]")
{
    Model model = readModelText(MESH + "IdListSet1;40;101;102\n");
    INFO(readingProblems(model));
    Renumbering::apply(model, RenumberSpace::Node, Renumbering::offset(1000));
    REQUIRE(setMembers(model, 0) == std::vector<IdRun>{{101, 101}, {102, 102}});
}

TEST_CASE("a set named both as a set of grid points and as a set of elements stops a renumbering of either",
          "[model][references][review]")
{
    // The second subsystem names the sets the other way round.
    Model model = readModelText(MESH + SETS + "FreeBodyLoadSubcase;LOW;30;20\n");
    INFO(readingProblems(model));
    const std::string before = writeModelText(model);

    const std::string message = refusal(model, RenumberSpace::Node, Renumbering::offset(1000));
    INFO(message);
    REQUIRE(message.find("IdListSet1 20") != std::string::npos);
    REQUIRE(message.find("nodeSetId of FreeBodyLoadSubcase") != std::string::npos);
    REQUIRE(message.find("elementSetId of FreeBodyLoadSubcase") != std::string::npos);
    REQUIRE(writeModelText(model) == before); // nothing changed
    REQUIRE_THROWS_AS(Renumbering::apply(model, RenumberSpace::Element, Renumbering::offset(500)), base::UsageError);
    REQUIRE(writeModelText(model) == before);

    // The other spaces are not concerned, and the set IDs themselves still renumber.
    REQUIRE_NOTHROW(Renumbering::apply(model, RenumberSpace::Property, Renumbering::offset(10)));
    REQUIRE(Renumbering::apply(model, RenumberSpace::Set, Renumbering::offset(1000)) == 2);
    // Such a set is not judged by the reference check: which of the two meanings a member has cannot be told.
    REQUIRE(unresolvedCount(model) == 0);
}

TEST_CASE("a Case Control SET named by a grid point request and by an element request stops a renumbering of either",
          "[model][references][review]")
{
    Model model = readModelText("[case]\n"
                                "SetDefinition;8;1;2\n"
                                "DisplacementOutput;8;PrintListing\n"
                                "StressOutput;8\n"
                                "[model]\n" +
                                MESH);
    INFO(readingProblems(model));
    const std::string before = caseText(std::as_const(model).control().caseControl);

    const std::string message = refusal(model, RenumberSpace::Element, Renumbering::offset(500));
    INFO(message);
    REQUIRE(message.find("SetDefinition 8") != std::string::npos);
    REQUIRE(message.find("DisplacementOutput") != std::string::npos);
    REQUIRE(message.find("StressOutput") != std::string::npos);
    REQUIRE_THROWS_AS(Renumbering::apply(model, RenumberSpace::Node, Renumbering::offset(1000)), base::UsageError);
    REQUIRE(caseText(std::as_const(model).control().caseControl) == before);
    REQUIRE(model.locate(base::IdSpace::Element, 1).has_value()); // the elements kept their IDs
    REQUIRE(unresolvedCount(model) == 0);                          // and the set is not judged
}

TEST_CASE("a SET written again in a subcase is the one the requests of that subcase name",
          "[model][references][review]")
{
    // The global SET 9 lists grid points (the displacement request, which subcase 1 inherits); subcase 2 has its own
    // SET 9, of elements, and a displacement request that names no set.
    Model model = readModelText("[case]\n"
                                "SetDefinition;9;101;102\n"
                                "DisplacementOutput;9;PrintListing\n"
                                "SubcaseStart;1\n"
                                "LabelText;first\n"
                                "SubcaseStart;2\n"
                                "SetDefinition;9;1;2\n"
                                "DisplacementOutput;All;PlotOnly\n"
                                "StressOutput;9\n"
                                "[model]\n" +
                                MESH);
    INFO(readingProblems(model));
    REQUIRE(std::as_const(model).control().caseControl.segments().size() == 3);

    Renumbering::apply(model, RenumberSpace::Node, Renumbering::offset(1000));
    {
        const CaseControl& control = std::as_const(model).control().caseControl;
        REQUIRE(caseSetMembers(control.global(), 9) == std::vector<std::int64_t>{1101, 1102});
        REQUIRE(caseSetMembers(control.segments()[2], 9) == std::vector<std::int64_t>{1, 2});
    }
    Renumbering::apply(model, RenumberSpace::Element, Renumbering::offset(500));
    {
        const CaseControl& control = std::as_const(model).control().caseControl;
        REQUIRE(caseSetMembers(control.global(), 9) == std::vector<std::int64_t>{1101, 1102});
        REQUIRE(caseSetMembers(control.segments()[2], 9) == std::vector<std::int64_t>{501, 502});
    }
    REQUIRE(unresolvedCount(model) == 0);
}

TEST_CASE("a range of a Case Control SET stays a range under an offset, and a gap is dropped when a card takes its "
          "number",
          "[model][references][review]")
{
    const std::string deck = "[case]\n"
                             "SetDefinition;9;1;Through;4\n"
                             "DisplacementOutput;9;PrintListing\n"
                             "[model]\n"
                             "Node;1;;0.;0.;0.\n"
                             "Node;5;;1.;0.;0.\n"
                             "Node;10;;2.;0.;0.\n"
                             "Node;20;;3.;0.;0.\n";
    // An offset moves the IDs of the range that name nothing too: the set is still one range.
    Model shifted = readModelText(deck);
    INFO(readingProblems(shifted));
    Renumbering::apply(shifted, RenumberSpace::Node, Renumbering::offset(1000));
    REQUIRE(caseText(std::as_const(shifted).control().caseControl).find("SetDefinition;9;1001;Through;1004\n") !=
            std::string::npos);

    // Numbered 1, 2, 3, 4 in file order, the nodes 5, 10 and 20 take the numbers 2, 3 and 4, which the set listed as
    // gaps of its range: kept, they would select three nodes the set never had.
    Model packed = readModelText(deck);
    Renumbering::apply(packed, RenumberSpace::Node, Renumbering::consecutive(RenumberSpace::Node, 1, 1));
    REQUIRE(packed.locate(base::IdSpace::Node, 4).has_value());
    REQUIRE(caseSetMembers(std::as_const(packed).control().caseControl.global(), 9) == std::vector<std::int64_t>{1});
}

TEST_CASE("a member of a Case Control SET that only a part has exists, and stays when the residual structure is "
          "renumbered",
          "[model][references][review]")
{
    Model model = readModelText("[case]\n"
                                "SetDefinition;9;101;201\n"
                                "DisplacementOutput;9;PrintListing\n"
                                "[model]\n"
                                "Node;101;;0.;0.;0.\n"
                                "[model;SuperelementPart;1]\n"
                                "Node;201;;5.;0.;0.\n");
    INFO(readingProblems(model));
    REQUIRE(model.parts().size() == 1);
    REQUIRE(unresolvedCount(model) == 0); // 201 is a grid point of the part

    Renumbering::apply(model, RenumberSpace::Node, Renumbering::offset(1000));
    REQUIRE(caseSetMembers(std::as_const(model).control().caseControl.global(), 9) ==
            std::vector<std::int64_t>{1101, 201});
    REQUIRE(model.parts()[0]->locate(base::IdSpace::Node, 201).has_value());
}

TEST_CASE("the SETs of a plot block are not the SETs the output requests name", "[model][references][review]")
{
    // SET 9, a displacement request that names it, then a plot block with its own SET 9.
    CaseControl control;
    const auto add = [&control](CaseEntry entry)
    {
        entry.key = control.newKey();
        control.global().entries.push_back(std::move(entry));
        return control.global().entries.back().key;
    };
    CaseEntry outputSet;
    outputSet.kind = EntryKind::Set;
    outputSet.name = std::string(SET_COMMAND);
    outputSet.number = 9;
    outputSet.set = CaseSet::ofIntegers({101, 102});
    CaseEntry request;
    request.kind = EntryKind::Output;
    request.name = "DisplacementOutput";
    request.value = CaseValue::ofInteger(9);
    CaseEntry block;
    block.kind = EntryKind::OutputBlock;
    block.name = std::string(OUTPUT_BLOCK_COMMAND);
    block.variant = "Plot";
    CaseEntry plotSet = outputSet;
    plotSet.set = CaseSet::ofIntegers({1, 2});

    const std::uint32_t outputSetKey = add(outputSet);
    add(request);
    add(block);
    const std::uint32_t plotSetKey = add(plotSet);

    const CaseSetUses uses = caseSetUses(control);
    REQUIRE(uses.size() == 1);
    REQUIRE(uses.contains(outputSetKey));
    REQUIRE_FALSE(uses.contains(plotSetKey));
    REQUIRE(uses.at(outputSetKey).kind() == SetMemberKind::Node);
    REQUIRE(uses.at(outputSetKey).set == "SetDefinition 9");
    REQUIRE(uses.at(outputSetKey).user().find("DisplacementOutput") == 0);
}

TEST_CASE("the members of a Case Control SET written alone are those outside the runs of three or more",
          "[model][references][review]")
{
    REQUIRE(singleMembers(CaseSet::ofIntegers({1, 2, 5, 6, 7, 9})) == std::vector<std::int64_t>{1, 2, 9});
    REQUIRE(singleMembers(CaseSet::ofIntegers({4, 5, 6})).empty());
    REQUIRE(singleMembers(CaseSet::ofAll()).empty());
}

// ---------------------------------------------------------------------------------------------------------------------
// C1: the reference check looks at the members of the sets
// ---------------------------------------------------------------------------------------------------------------------

TEST_CASE("the reference check reports a member of a set that names no grid point or no element",
          "[model][references][review]")
{
    Model model = readModelText(MESH + "IdListSet1;20;101;999\n"           // 999 is no grid point
                                       "IdListSet1;21;101;Through;5000\n" // the end of a range may name nothing
                                       "IdListSet1;30;1;77\n"            // 77 is no element
                                       "IdListSet1;40;55555\n"           // no user: not judged
                                       "FreeBodyLoadSubcase;A;20;30\n"
                                       "FreeBodyLoadSubcase;B;21\n");
    INFO(readingProblems(model));
    base::DiagnosticSink sink;
    REQUIRE(ReferenceChecker::check(model, sink) == 2);
    REQUIRE(sink.diagnostics().size() == 2);
    const base::Diagnostic& node = sink.diagnostics()[0];
    INFO(node.message);
    REQUIRE(node.severity == base::Severity::Error);
    REQUIRE(node.code == "model.unresolved-reference");
    REQUIRE(node.message.find("field ids of IdListSet1 20 refers to 999, which does not exist") != std::string::npos);
    REQUIRE(node.message.find("grid points") != std::string::npos);
    const base::Diagnostic& element = sink.diagnostics()[1];
    INFO(element.message);
    REQUIRE(element.message.find("field ids of IdListSet1 30 refers to 77") != std::string::npos);
    REQUIRE(element.message.find("elements") != std::string::npos);
}

TEST_CASE("the reference check reports a member of a Case Control SET that names no grid point",
          "[model][references][review]")
{
    // 777 is no grid point; the IDs of the range of the SET of elements are not judged one by one.
    Model model = readModelText("[case]\n"
                                "SetDefinition;9;101;777\n"
                                "SetDefinition;8;1;Through;50\n"
                                "DisplacementOutput;9;PrintListing\n"
                                "StressOutput;8\n"
                                "[model]\n" +
                                MESH);
    INFO(readingProblems(model));
    base::DiagnosticSink sink;
    REQUIRE(ReferenceChecker::check(model, sink) == 1);
    REQUIRE(sink.diagnostics().size() == 1);
    INFO(sink.diagnostics()[0].message);
    REQUIRE(sink.diagnostics()[0].severity == base::Severity::Warning);
    REQUIRE(sink.diagnostics()[0].code == "model.unresolved-case-control-reference");
    REQUIRE(sink.diagnostics()[0].message.find("SetDefinition 9") != std::string::npos);
    REQUIRE(sink.diagnostics()[0].message.find("refers to 777, which does not exist") != std::string::npos);
    REQUIRE(sink.diagnostics()[0].message.find("grid points") != std::string::npos);
}

// ---------------------------------------------------------------------------------------------------------------------
// C2: the reference fields that were not registered
// ---------------------------------------------------------------------------------------------------------------------

TEST_CASE("the grid point of the WeightReferenceNode parameter follows the nodes and may name nothing",
          "[model][references][review]")
{
    Model model = readModelText("Node;101;;0.;0.;0.\n"
                                "Parameter;WeightReferenceNode;101\n"
                                "Parameter;WeightReferenceNode;0\n"
                                "Parameter;WeightReferenceNode;-1\n"
                                "Parameter;WeightToMass;0.00259\n");
    INFO(readingProblems(model));
    const Visits visits = visitsOf<ParameterTable>(model, 0);
    REQUIRE(visits.fields == std::vector<std::string>{"value1"});
    REQUIRE(visits.targets == std::vector<ReferenceTarget>{ReferenceTarget::NodeInRange});
    // Zero and -1 are options of the parameter, and the other parameters hold no ID.
    REQUIRE(visitsOf<ParameterTable>(model, 1).fields.empty());
    REQUIRE(visitsOf<ParameterTable>(model, 2).fields.empty());
    REQUIRE(visitsOf<ParameterTable>(model, 3).fields.empty());

    Renumbering::apply(model, RenumberSpace::Node, Renumbering::offset(1000));
    const ParameterTable& parameters = *model.findTable<ParameterTable>();
    REQUIRE(parameters.card(0).integerValue == 1101);
    REQUIRE(parameters.card(1).integerValue == 0);
    REQUIRE(parameters.card(2).integerValue == -1);

    // A number that names no grid point is a valid value (the reference point is then the origin): not reported.
    Model origin = readModelText("Node;101;;0.;0.;0.\nParameter;WeightReferenceNode;555\n");
    REQUIRE(unresolvedCount(origin) == 0);
}

TEST_CASE("the property of the AcousticInfinitePropId parameter is a reference", "[model][references][review]")
{
    Model missing = readModelText("Parameter;AcousticInfinitePropId;77\n");
    INFO(readingProblems(missing));
    REQUIRE(visitsOf<ParameterTable>(missing, 0).targets == std::vector<ReferenceTarget>{ReferenceTarget::Property});
    REQUIRE(unresolvedCount(missing) == 1);

    Model model = readModelText("Parameter;AcousticInfinitePropId;77\n"
                                "ShellProp;77;9000;0.1\n"
                                "IsoMat;9000;2.1E+11;;0.3\n");
    REQUIRE(unresolvedCount(model) == 0);
    Renumbering::apply(model, RenumberSpace::Property, Renumbering::offset(100));
    REQUIRE(model.findTable<ParameterTable>()->card(0).integerValue == 177);
    REQUIRE(unresolvedCount(model) == 0);
}

TEST_CASE("the parameters of the Case Control that hold an ID are references too", "[model][references][review]")
{
    Model model = readModelText("[case]\n"
                                "SubcaseParameter;WeightReferenceNode;101\n"
                                "SubcaseParameter;AcousticInfinitePropId;77\n"
                                "[model]\n"
                                "Node;101;;0.;0.;0.\n");
    INFO(readingProblems(model));
    // No property 77: a warning, as for the commands of the Case Control.
    base::DiagnosticSink sink;
    REQUIRE(ReferenceChecker::check(model, sink) == 1);
    REQUIRE(sink.diagnostics().size() == 1);
    INFO(sink.diagnostics()[0].message);
    REQUIRE(sink.diagnostics()[0].code == "model.unresolved-case-control-reference");
    REQUIRE(sink.diagnostics()[0].message.find("AcousticInfinitePropId") != std::string::npos);

    Renumbering::apply(model, RenumberSpace::Node, Renumbering::offset(1000));
    const CaseControl& control = std::as_const(model).control().caseControl;
    REQUIRE(CaseControl::ownParam(control.global(), "WeightReferenceNode")->value.integer == 1101);
    REQUIRE(CaseControl::ownParam(control.global(), "AcousticInfinitePropId")->value.integer == 77);
    REQUIRE(caseText(control).find("SubcaseParameter;WeightReferenceNode;1101\n") != std::string::npos);
}

TEST_CASE("the ends of a range of properties of a TypedListSet3 follow the properties", "[model][references][review]")
{
    Model model = readModelText("TypedListSet3;7;Property;7;Through;9\n"
                                "ShellProp;7;9000;0.1\n"
                                "IsoMat;9000;2.1E+11;;0.3\n");
    INFO(readingProblems(model));
    REQUIRE(visitsOf<TypedListSet3Table>(model, 0).targets ==
            std::vector<ReferenceTarget>{ReferenceTarget::PropertyInRange, ReferenceTarget::PropertyInRange});
    REQUIRE(unresolvedCount(model) == 0); // the end 9 names no property: a range may have gaps

    Renumbering::apply(model, RenumberSpace::Property, Renumbering::offset(100));
    REQUIRE(model.findTable<TypedListSet3Table>()->card(0).ids == std::vector<IdRun>{{107, 109}});
}

TEST_CASE("the four last tables of a GasketMat are stress tables", "[model][references][review]")
{
    // Every table given: the loading path 2001, the ten unloading paths, then the tables 3001 to 3004 of the yield
    // pressure, the tensile modulus, the transverse shear modulus and the initial gap.
    Model model = readModelText(
        "GasketMat;101;11;0;2001;2002;2003;2004;2005;2006;2007;2008;2009;2010;2011;200.;3.E+3;500.;0.1;3001;3002;"
        "3003;3004\n"
        "TableStress1;3001;;0.;0.;0.01;1.2E+4;0.02;1.7E+4;EndTable\n");
    INFO(readingProblems(model));
    const Visits visits = visitsOf<GasketMatTable>(model, 0);
    REQUIRE(visits.fields.size() == 16);
    REQUIRE(std::vector<std::string>(visits.fields.end() - 4, visits.fields.end()) ==
            std::vector<std::string>{"yieldPressureTableId", "tensileModulusTableId", "transverseShearModulusTableId",
                                     "initialGapTableId"});
    REQUIRE(std::vector<ReferenceTarget>(visits.targets.end() - 4, visits.targets.end()) ==
            std::vector<ReferenceTarget>(4, ReferenceTarget::StressTable));

    Renumbering::apply(model, RenumberSpace::StressTable, Renumbering::offset(100));
    const GasketMatCard card = model.findTable<GasketMatTable>()->card(0);
    REQUIRE(card.yieldPressureTableId == 3101);
    REQUIRE(card.initialGapTableId == 3104);

    // A blank table is not a reference: the material and the loading path only.
    Model bare = readModelText("GasketMat;102;11;0;2001;;;;;;;;;;;200.;3.E+3;500.\n");
    INFO(readingProblems(bare));
    REQUIRE(visitsOf<GasketMatTable>(bare, 0).fields == std::vector<std::string>{"membraneMatId", "loadingTableId"});
}

// ---------------------------------------------------------------------------------------------------------------------
// C3: an offset that takes an ID out of the range of the IDs
// ---------------------------------------------------------------------------------------------------------------------

TEST_CASE("an offset that takes the ID of a card out of range stops the renumbering", "[model][references][review]")
{
    Model model = readModelText("Node;1;;0.;0.;0.\nNode;200000000;;1.;0.;0.\n");
    INFO(readingProblems(model));
    const std::string before = writeModelText(model);

    // 200 000 000 + 2 000 000 000 does not fit in an ID: the first node must not move while the second stays.
    const std::string message = refusal(model, RenumberSpace::Node, Renumbering::offset(2'000'000'000));
    INFO(message);
    REQUIRE(message.find("200000000") != std::string::npos);
    REQUIRE(writeModelText(model) == before);
    REQUIRE(model.locate(base::IdSpace::Node, 1).has_value());
    REQUIRE_FALSE(model.locate(base::IdSpace::Node, 2'000'000'001).has_value());

    // An offset that every ID takes still renumbers.
    REQUIRE(Renumbering::apply(model, RenumberSpace::Node, Renumbering::offset(1000)) == 2);
    REQUIRE(model.locate(base::IdSpace::Node, 200'001'000).has_value());
}

TEST_CASE("a number that names no card and that an offset cannot move stays as it is", "[model][references][review]")
{
    // The member 2 000 000 000 of the set of grid points names nothing; with the offset it would pass the largest ID.
    Model model = readModelText("Node;1;;0.;0.;0.\n"
                                "IdListSet1;20;1;2000000000\n"
                                "FreeBodyLoadSubcase;FLAP;20\n");
    INFO(readingProblems(model));
    REQUIRE(Renumbering::apply(model, RenumberSpace::Node, Renumbering::offset(500'000'000)) == 1);
    REQUIRE(model.locate(base::IdSpace::Node, 500'000'001).has_value());
    REQUIRE(setMembers(model, 0) == std::vector<IdRun>{{500'000'001, 500'000'001}, {2'000'000'000, 2'000'000'000}});
}

TEST_CASE("a consecutive numbering that passes the largest ID stops the renumbering", "[model][references][review]")
{
    Model model = readModelText("Node;1;;0.;0.;0.\nNode;2;;1.;0.;0.\n");
    INFO(readingProblems(model));
    const std::string before = writeModelText(model);
    // The second node would get the largest ID plus one.
    REQUIRE_THROWS_AS(Renumbering::apply(model, RenumberSpace::Node,
                                         Renumbering::consecutive(RenumberSpace::Node, base::MAX_ENTITY_ID, 1)),
                      base::UsageError);
    REQUIRE(writeModelText(model) == before);
}
