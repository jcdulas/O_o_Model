#include "oor/base/diagnostics/DiagnosticSink.hpp"
#include "oor/deck/records/RecordText.hpp"
#include "oor/model/control/ControlRecords.hpp"
#include "oor/model/control/case_control/CaseControl.hpp"
#include "oor/model/control/case_control/CaseSet.hpp"
#include "oor/model/control/case_control/CommandCatalogue.hpp"
#include "oor/model/control/executive_control/SolutionSequences.hpp"
#include "oor/model/control/statement/ControlStatementList.hpp"
#include "support/ControlTestSupport.hpp"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cstdint>
#include <limits>
#include <set>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// The control sections at their edges: the nesting of the case records, what removing a section keeps and refuses, the
// limits of a set, the header of an output block, the keys of a replaced statement list and the solution names.

using namespace oor;
using namespace oor::model;

namespace
{

const CommandDefinition& command(const char* name)
{
    const CommandDefinition* definition = CommandCatalogue::instance().findByName(name);
    REQUIRE(definition != nullptr);
    return *definition;
}

// The items of the records of a [case] section given as text, one record per line.
std::vector<deck::ModelItem> itemsOf(const std::string& records)
{
    std::vector<deck::ModelItem> items;
    std::size_t start = 0;
    while (start < records.size())
    {
        const std::size_t end = std::min(records.find('\n', start), records.size());
        deck::ModelItem item;
        std::string problem;
        REQUIRE(deck::RecordText::split(records.substr(start, end - start), item.values, problem));
        item.line = static_cast<std::uint32_t>(items.size() + 1);
        items.push_back(std::move(item));
        start = end + 1;
    }
    return items;
}

// The Case Control of these records; the problems of the records go to `sink`.
CaseControl read(const std::string& records, base::DiagnosticSink& sink)
{
    const std::vector<deck::ModelItem> items = itemsOf(records);
    return ControlRecords::readCase(items, {"(test)"}, sink);
}

// The Case Control of records that have no problem.
CaseControl parse(const std::string& records)
{
    base::DiagnosticSink sink;
    CaseControl control = read(records, sink);
    if (const auto error = sink.firstError())
        FAIL(error->message);
    return control;
}

// The message of the one problem these records have.
std::string problemOf(const std::string& records)
{
    base::DiagnosticSink sink;
    (void)read(records, sink);
    REQUIRE(sink.errorCount() == 1);
    return sink.firstError()->message;
}

std::string textOf(const CaseControl& control)
{
    return testing::caseText(control);
}

std::string refusedSet(const std::string& text)
{
    std::string problem;
    REQUIRE_FALSE(CaseSet::parse(text, problem).has_value());
    return problem;
}

bool contains(const std::string& text, const std::string& part)
{
    return text.find(part) != std::string::npos;
}

} // namespace

// --------------------------------------------------------------------------------------------- nesting of the records

TEST_CASE("substeps written one after the other are siblings, in a subcase and in a step",
          "[control][records][review]")
{
    const std::string text =
        "SubcaseStart;1\nSubstepStart;1\nStaticLoadSelection;4\nSubstepStart;2\nSubstepStart;3\n"
        "SubcaseStart;2\nStepStart;1\nSubstepStart;1\nSubstepStart;2\nStepStart;2\nSubstepStart;1\n";
    const CaseControl control = parse(text);
    REQUIRE(control.segments().size() == 3);

    // Directly in a subcase: three substeps of the subcase, none inside another.
    const Subcase& first = control.segments()[1];
    REQUIRE(first.children.size() == 3);
    for (std::size_t index = 0; index < first.children.size(); ++index)
    {
        REQUIRE(first.children[index].kind == SubcaseKind::Substep);
        REQUIRE(first.children[index].id == static_cast<std::int64_t>(index + 1));
        REQUIRE(first.children[index].children.empty());
    }
    REQUIRE(first.children[0].entries.size() == 1); // the command written after the first substep is its own
    REQUIRE(control.parentOf(first.children[2].key) == &first);

    // In a step: the substeps of that step, and the next step closes them.
    const Subcase& second = control.segments()[2];
    REQUIRE(second.children.size() == 2);
    REQUIRE(second.children[0].kind == SubcaseKind::Step);
    REQUIRE(second.children[0].children.size() == 2);
    REQUIRE(second.children[0].children[1].kind == SubcaseKind::Substep);
    REQUIRE(second.children[0].children[1].children.empty());
    REQUIRE(second.children[1].kind == SubcaseKind::Step);
    REQUIRE(second.children[1].children.size() == 1);

    // The records written from the structure give the same structure again.
    REQUIRE(textOf(control) == text);
    const CaseControl again = parse(textOf(control));
    REQUIRE(again.segments()[1].children.size() == 3);
    REQUIRE(again.segments()[2].children[0].children.size() == 2);
    REQUIRE(textOf(again) == text);
}

TEST_CASE("a step after the substeps of a subcase is a child of the subcase and takes the substeps after it",
          "[control][records][review]")
{
    const std::string text = "SubcaseStart;1\nSubstepStart;1\nSubstepStart;2\nStepStart;1\nSubstepStart;1\n"
                             "SubstepStart;2\nStepStart;2\n";
    const CaseControl control = parse(text);
    const Subcase& subcase = control.segments()[1];
    REQUIRE(subcase.children.size() == 4);
    REQUIRE(subcase.children[0].kind == SubcaseKind::Substep);
    REQUIRE(subcase.children[1].kind == SubcaseKind::Substep);
    REQUIRE(subcase.children[2].kind == SubcaseKind::Step);
    REQUIRE(subcase.children[2].children.size() == 2);
    REQUIRE(subcase.children[3].kind == SubcaseKind::Step);
    REQUIRE(subcase.children[3].children.empty());
    REQUIRE(textOf(control) == text);
}

// ------------------------------------------------------------------------------------------------ removing a section

TEST_CASE("removing the last subcase keeps the plot block that came to it from the one before",
          "[control][edit][review]")
{
    CaseControl control = parse("SubcaseStart;1\nSinglePointConstrSelection;1\nOutputBlock;;Plot\nPlotDraw;SET 1\n");
    const std::string before = textOf(control);
    const std::vector<std::uint32_t> blocks = control.blockKeys();
    REQUIRE(blocks.size() == 1);

    const std::uint32_t added = control.addSubcase(SubcaseKind::Subcase, 2).key;
    control.setCommand(*control.findSubcase(added), command("StaticLoadSelection"), "", {}, CaseValue::ofInteger(5));
    REQUIRE(control.segments()[1].entries.size() == 1); // the block is in the new subcase
    REQUIRE(control.segments()[2].entries.size() == 3);

    REQUIRE(control.removeSubcase(added));
    REQUIRE(textOf(control) == before);      // the block and its command are back at the end of subcase 1
    REQUIRE(control.blockKeys() == blocks); // the same entries: a handle to the block still names it
    REQUIRE(control.findSubcase(added) == nullptr);
}

TEST_CASE("the plot block of a removed step or subcase goes to the end of the section that is then last",
          "[control][edit][review]")
{
    CaseControl control = parse("SubcaseStart;1\nStepStart;1\nSubcaseStart;2\nStepStart;1\nStepStart;2\n"
                                "StaticLoadSelection;5\nOutputBlock;;Plot\nPlotDraw;SET 1\n");
    // The last step goes: the block is at the end of the step before it.
    REQUIRE(control.removeSubcase(control.segments()[2].children[1].key));
    REQUIRE(textOf(control) ==
            "SubcaseStart;1\nStepStart;1\nSubcaseStart;2\nStepStart;1\nOutputBlock;;Plot\nPlotDraw;SET 1\n");
    // The last subcase goes, with its step: the block is in the last step of the subcase before it.
    REQUIRE(control.removeSubcase(control.segments()[2].key));
    REQUIRE(textOf(control) == "SubcaseStart;1\nStepStart;1\nOutputBlock;;Plot\nPlotDraw;SET 1\n");
    // No subcase is left: the block is in the global section.
    REQUIRE(control.removeSubcase(control.segments()[1].key));
    REQUIRE(textOf(control) == "OutputBlock;;Plot\nPlotDraw;SET 1\n");
    REQUIRE(control.blockKeys().size() == 1);
}

TEST_CASE("a plot block written in a subcase that is not the last is kept when that subcase is removed",
          "[control][edit][review]")
{
    // The command after the plot command ends the block: it is a command of subcase 1 and goes with it, as does the
    // postprocessing block, which belongs to the subcase it is written in.
    CaseControl control = parse("SubcaseStart;1\nOutputBlock;;Postprocessing\nOutputBlock;;Plot\nPlotDraw;SET 1\n"
                                "StaticLoadSelection;3\nSubcaseStart;2\nStaticLoadSelection;4\n");
    REQUIRE(control.removeSubcase(control.segments()[1].key));
    REQUIRE(textOf(control) == "SubcaseStart;2\nStaticLoadSelection;4\nOutputBlock;;Plot\nPlotDraw;SET 1\n");
    // A command added to the last subcase still goes before the block.
    control.setCommand(control.segments()[1], command("SinglePointConstrSelection"), "", {}, CaseValue::ofInteger(9));
    REQUIRE(textOf(control) ==
            "SubcaseStart;2\nStaticLoadSelection;4\nSinglePointConstrSelection;9\nOutputBlock;;Plot\nPlotDraw;SET 1\n");
}

TEST_CASE("an auxiliary case is not removed while subcases of its model follow it", "[control][edit][review]")
{
    CaseControl control = parse("SubcaseStart;1\nAuxiliaryCase\nAuxiliaryModelSelection;5\nSubcaseStart;1\n"
                                "AuxiliaryCase\nAuxiliaryModelSelection;7\n");
    const std::string before = textOf(control);
    REQUIRE(control.segments().size() == 5);
    const std::uint32_t firstAuxiliary = control.segments()[2].key;
    const std::uint32_t auxiliarySubcase = control.segments()[3].key;
    const std::uint32_t lastAuxiliary = control.segments()[4].key;

    // Removed, its subcase 1 would join the primary subcase 1 in one scope and inherit the global commands.
    REQUIRE_FALSE(control.removeSubcase(firstAuxiliary));
    REQUIRE(textOf(control) == before);
    REQUIRE(control.auxiliaryCaseOf(auxiliarySubcase) == control.findSubcase(firstAuxiliary));

    // An auxiliary case with no subcase after it goes, with its own commands.
    REQUIRE(control.removeSubcase(lastAuxiliary));
    REQUIRE(textOf(control) == "SubcaseStart;1\nAuxiliaryCase\nAuxiliaryModelSelection;5\nSubcaseStart;1\n");
    // Its subcases first, then the auxiliary case.
    REQUIRE(control.removeSubcase(auxiliarySubcase));
    REQUIRE(control.removeSubcase(firstAuxiliary));
    REQUIRE(textOf(control) == "SubcaseStart;1\n");
}

TEST_CASE("an auxiliary case followed by another auxiliary case has no subcase and is removed",
          "[control][edit][review]")
{
    CaseControl control = parse("SubcaseStart;1\nAuxiliaryCase\nAuxiliaryModelSelection;5\nAuxiliaryCase\n"
                                "AuxiliaryModelSelection;7\nSubcaseStart;1\n");
    REQUIRE(control.removeSubcase(control.segments()[2].key));
    REQUIRE(textOf(control) == "SubcaseStart;1\nAuxiliaryCase\nAuxiliaryModelSelection;7\nSubcaseStart;1\n");
}

// ------------------------------------------------------------------------------------------------ sets

TEST_CASE("a range over every 64-bit integer is refused as too long, before anything is expanded",
          "[control][set][review]")
{
    // 2^64 members: one more than a 64-bit count holds.
    REQUIRE(contains(refusedSet("-9223372036854775808 Through 9223372036854775807"), "more than"));
    REQUIRE(contains(refusedSet("-9223372036854775808 Through 9223372036854775807 By 1"), "more than"));
    REQUIRE(contains(refusedSet("5, -9223372036854775808 Through 9223372036854775807"), "more than"));
    // The limit itself: MAX_MEMBERS members pass, one more does not, alone or with the members before the range.
    REQUIRE(CaseSet::MAX_MEMBERS == 5'000'000);
    REQUIRE(contains(refusedSet("1 Through 5000001"), "more than 5000000 members"));
    REQUIRE(contains(refusedSet("7000000, 1 Through 5000000"), "more than 5000000 members"));
    std::string problem;
    const auto atLimit = CaseSet::parse("1 Through 5000000", problem);
    REQUIRE(atLimit.has_value());
    REQUIRE(atLimit->integers.size() == CaseSet::MAX_MEMBERS);
    REQUIRE(atLimit->integers.back() == 5'000'000);
    // A long range with a long step has few members.
    const auto sparse =
        CaseSet::parse("-9223372036854775808 Through 9223372036854775807 By 9223372036854775807", problem);
    REQUIRE(sparse.has_value());
    REQUIRE(sparse->integers == std::vector<std::int64_t>{std::numeric_limits<std::int64_t>::min(), -1,
                                                          9223372036854775806});
}

TEST_CASE("the runs of a set are found without passing the largest integer", "[control][set][review]")
{
    using Items = std::vector<std::string>;
    const std::int64_t top = std::numeric_limits<std::int64_t>::max();
    const std::int64_t bottom = std::numeric_limits<std::int64_t>::min();
    // The largest integer has no next one: the smallest after it starts another item.
    REQUIRE(CaseSet::ofIntegers({top, bottom, bottom + 1}).items() ==
            Items{"9223372036854775807", "-9223372036854775808", "-9223372036854775807"});
    REQUIRE(CaseSet::ofIntegers({top, 5}).items() == Items{"9223372036854775807", "5"});
    REQUIRE(CaseSet::ofIntegers({top - 2, top - 1, top}).items() ==
            Items{"9223372036854775805 Through 9223372036854775807"});
    REQUIRE(CaseSet::ofIntegers({bottom, bottom + 1, bottom + 2, 9}).items() ==
            Items{"-9223372036854775808 Through -9223372036854775806", "9"});
}

// ------------------------------------------------------------------------------------------------ output block headers

TEST_CASE("an output block header names one of the block kinds in the field after the empty value",
          "[control][records][review]")
{
    for (const char* kind : {"Plot", "Postprocessing", "CurvePlot", "CurveOutput"})
    {
        const std::string text = std::string("SubcaseStart;1\nOutputBlock;;") + kind + "\n";
        const CaseControl control = parse(text);
        const CaseEntry& header = control.segments()[1].entries.front();
        REQUIRE(header.kind == EntryKind::OutputBlock);
        // CurveOutput is the other word of the curve-plot block.
        REQUIRE(header.variant == (std::string(kind) == "CurveOutput" ? "CurvePlot" : kind));
        REQUIRE(control.blockKeys().size() == 1);
        REQUIRE(textOf(control) == text);
    }
    // The plot commands after a header are its block.
    const CaseControl control = parse("SubcaseStart;1\nOutputBlock;;Plot\nPlotDraw;SET 1\nPlotDraw;SET 2\n");
    const CaseControl::Extent block = CaseControl::blockExtent(control.segments()[1], 0);
    REQUIRE(block.first == 1);
    REQUIRE(block.last == 3);
    REQUIRE(textOf(control) == "SubcaseStart;1\nOutputBlock;;Plot\nPlotDraw;SET 1\nPlotDraw;SET 2\n");
}

TEST_CASE("an output block header with its kind in the value field or with an unknown kind is a problem",
          "[control][records][review]")
{
    // The kind where the value goes: it was read as a command with no kind and written back without the word.
    const std::string misplaced = problemOf("SubcaseStart;1\nOutputBlock;Plot\nPlotDraw;SET 1\n");
    REQUIRE(contains(misplaced, "OutputBlock;;Plot"));
    REQUIRE(contains(misplaced, "Plot, Postprocessing, CurvePlot or CurveOutput"));
    REQUIRE(contains(misplaced, "the value \"Plot\""));

    const std::string unknown = problemOf("SubcaseStart;1\nOutputBlock;;Anything\n");
    REQUIRE(contains(unknown, "\"Anything\" is not a kind of output block"));
    REQUIRE(contains(unknown, "Plot, Postprocessing, CurvePlot or CurveOutput"));
    // The kinds are exact words.
    REQUIRE(contains(problemOf("OutputBlock;;plot\n"), "is not a kind of output block"));
    // An empty kind field before another word.
    REQUIRE(contains(problemOf("OutputBlock;;;Plot\n"), "is missing"));

    // The refused header is not kept as anything.
    base::DiagnosticSink sink;
    const CaseControl control = read("SubcaseStart;1\nOutputBlock;Plot\n", sink);
    REQUIRE(sink.hasErrors());
    REQUIRE(control.segments()[1].entries.empty());
    REQUIRE(control.blockKeys().empty());
}

TEST_CASE("an output block command with no field opens no block, and the sets block needs no kind",
          "[control][records][review]")
{
    // A divider line: a plain command, written back as it was read.
    const CaseControl divider = parse("OutputBlock\nDisplacementOutput;All\n");
    REQUIRE(divider.global().entries.front().kind == EntryKind::Command);
    REQUIRE(divider.blockKeys().empty());
    REQUIRE(textOf(divider) == "OutputBlock\nDisplacementOutput;All\n");

    const CaseControl sets = parse("SetsBlock\n");
    REQUIRE(sets.global().entries.front().kind == EntryKind::OutputBlock);
    REQUIRE(sets.global().entries.front().variant == "Postprocessing");
    REQUIRE(textOf(sets) == "SetsBlock\n");
}

// ------------------------------------------------------------------------------------------------ statement keys

TEST_CASE("a replaced statement list gives keys it never gave before", "[control][executive][review]")
{
    ControlStatement statement;
    statement.kind = ControlKind::Keyword;
    statement.name = "ApplicationKind";

    ControlStatementList list;
    const std::uint32_t firstKey = list.insertAt(0, statement).key;
    const std::uint32_t secondKey = list.insertAt(1, statement).key;
    REQUIRE(firstKey != secondKey);

    ControlStatementList other;
    other.insertAt(0, statement);
    other.insertAt(1, statement);
    other.insertAt(2, statement);

    list.replaceWith(other);
    REQUIRE(list.entries().size() == 3);
    // A handle to a statement the list held finds nothing: its key is not the key of a new statement.
    REQUIRE(list.find(firstKey) == nullptr);
    REQUIRE(list.find(secondKey) == nullptr);
    std::set<std::uint32_t> keys{firstKey, secondKey};
    for (const ControlStatement& entry : list.entries())
    {
        REQUIRE(keys.insert(entry.key).second);
        REQUIRE(list.find(entry.key) == &entry);
    }
    // And again: the keys of the first replacement are not given a second time.
    list.replaceWith(other);
    for (const ControlStatement& entry : list.entries())
        REQUIRE(keys.insert(entry.key).second);
    REQUIRE(keys.insert(list.newKey()).second);
}

// ------------------------------------------------------------------------------------------------ solution names

TEST_CASE("every solution sequence has a name and a number of its own", "[control][executive][review]")
{
    std::set<std::string_view> names;
    std::set<std::string_view> numberNames;
    std::set<std::int64_t> numbers;
    for (const SolutionSequence& sequence : SolutionSequences::all())
    {
        INFO(sequence.number);
        REQUIRE(names.insert(sequence.name).second);
        REQUIRE(numberNames.insert(sequence.numberName).second);
        REQUIRE(numbers.insert(sequence.number).second);
        // The name gives the number and the number the name.
        REQUIRE(SolutionSequences::numberOf(sequence.name) == sequence.number);
        REQUIRE(SolutionSequences::nameOf(sequence.number) == sequence.name);
        REQUIRE(sequence.numberName == std::string(sequence.name) + "Number");
    }
    REQUIRE(SolutionSequences::nameOf(700) == "ExplicitNonlinear");
    REQUIRE(SolutionSequences::numberOf("ExplicitNonlinear") == 700);
    REQUIRE(SolutionSequences::numberOf("NonlinearTransient") == 129);
    REQUIRE(SolutionSequences::nameOf(129) == "NonlinearTransient");
}
