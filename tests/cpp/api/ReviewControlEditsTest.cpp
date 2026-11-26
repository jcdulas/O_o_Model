#include "oor/api/ControlEdits.hpp"
#include "oor/api/Deck.hpp"
#include "oor/base/errors/Errors.hpp"

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

// The case sections edited through the API at their edges: substeps directly in a subcase, what removing a section
// keeps and refuses, and the header of an output block in a complete replacement.

using namespace oor;

namespace
{

using Records = std::vector<api::ControlRecord>;
using Lines = std::vector<std::string>;

api::ControlRecord record(std::string name, std::vector<std::string> fields)
{
    return {std::move(name), std::move(fields), {}};
}

// The case records of a deck, one text per record: its name and its fields with ';' between them.
Lines caseLines(const api::Deck& deck)
{
    Lines lines;
    for (const api::ControlRecord& item : api::caseRecords(deck))
    {
        std::string line = item.name;
        for (const std::string& field : item.fields)
            line += ";" + field;
        lines.push_back(std::move(line));
    }
    return lines;
}

const model::CaseControl& caseControl(const api::Deck& deck)
{
    return std::as_const(*deck.model()).control().caseControl;
}

// The message a replacement of the case records is refused with; empty when it is accepted.
std::string refusal(const api::Deck& deck, const Records& records)
{
    try
    {
        api::setCaseControl(deck, records);
    }
    catch (const base::UsageError& error)
    {
        return error.what();
    }
    return {};
}

bool contains(const std::string& text, const std::string& part)
{
    return text.find(part) != std::string::npos;
}

} // namespace

TEST_CASE("substeps added directly to a subcase are siblings again after their records replace the case sections",
          "[api][builder][controls][review]")
{
    const auto deck = api::Deck::createModel();
    const auto first = api::addCaseSection(*deck, "subcase", 1, 0);
    for (const std::int64_t id : {1, 2, 3})
        api::addCaseSection(*deck, "substep", id, first);
    const auto second = api::addCaseSection(*deck, "subcase", 2, 0);
    const auto step = api::addCaseSection(*deck, "step", 1, second);
    api::addCaseSection(*deck, "substep", 1, step);
    api::addCaseSection(*deck, "substep", 2, step);

    const Lines before = caseLines(*deck);
    REQUIRE(before == Lines{"SubcaseStart;1", "SubstepStart;1", "SubstepStart;2", "SubstepStart;3", "SubcaseStart;2",
                            "StepStart;1", "SubstepStart;1", "SubstepStart;2"});

    // The records the deck gives are accepted back: the substeps are not read one inside the other.
    const Records records = api::caseRecords(*deck);
    REQUIRE_NOTHROW(api::setCaseControl(*deck, records));
    const model::CaseControl& control = caseControl(*deck);
    REQUIRE(control.segments().size() == 3);
    REQUIRE(control.segments()[1].children.size() == 3);
    for (const model::Subcase& substep : control.segments()[1].children)
    {
        REQUIRE(substep.kind == model::SubcaseKind::Substep);
        REQUIRE(substep.children.empty());
    }
    REQUIRE(control.segments()[2].children.size() == 1);
    REQUIRE(control.segments()[2].children[0].children.size() == 2);
    REQUIRE(caseLines(*deck) == before);
}

TEST_CASE("removing the last subcase through the API keeps the plot block at the end of the case sections",
          "[api][builder][controls][review]")
{
    const auto deck = api::Deck::createModel();
    api::setCaseControl(*deck, Records{record("SubcaseStart", {"1"}), record("StaticLoadSelection", {"10"}),
                                       record("OutputBlock", {"", "Plot"}), record("PlotDraw", {"SET 1"})});
    const Lines before = caseLines(*deck);
    REQUIRE(before == Lines{"SubcaseStart;1", "StaticLoadSelection;10", "OutputBlock;;Plot", "PlotDraw;SET 1"});

    const auto second =
        api::addCaseSection(*deck, "subcase", 2, 0, std::array{record("StaticLoadSelection", {"20"})});
    REQUIRE(caseLines(*deck) == Lines{"SubcaseStart;1", "StaticLoadSelection;10", "SubcaseStart;2",
                                      "StaticLoadSelection;20", "OutputBlock;;Plot", "PlotDraw;SET 1"});
    REQUIRE(api::removeCaseSection(*deck, second));
    REQUIRE(caseLines(*deck) == before);
}

TEST_CASE("an auxiliary case is removed through the API only once no subcase follows it in its scope",
          "[api][builder][controls][review]")
{
    const auto deck = api::Deck::createModel();
    api::addCaseSection(*deck, "subcase", 1, 0);
    const auto auxiliary = api::addCaseSection(*deck, "auxiliaryCase", 0, 0);
    const auto auxiliarySubcase = api::addCaseSection(*deck, "subcase", 1, 0); // number 1 again: another scope
    const Lines before = caseLines(*deck);
    REQUIRE(before == Lines{"SubcaseStart;1", "AuxiliaryCase", "SubcaseStart;1"});

    // Refused, nothing changes: the two subcases 1 would be in one scope.
    REQUIRE_FALSE(api::removeCaseSection(*deck, auxiliary));
    REQUIRE(caseLines(*deck) == before);
    REQUIRE(api::caseSection(*deck, auxiliary).kind == model::SubcaseKind::AuxiliaryCase);

    REQUIRE(api::removeCaseSection(*deck, auxiliarySubcase));
    REQUIRE(api::removeCaseSection(*deck, auxiliary));
    REQUIRE(caseLines(*deck) == Lines{"SubcaseStart;1"});
}

TEST_CASE("a replacement of the case sections refuses an output block header that names no known kind",
          "[api][builder][controls][review]")
{
    const auto deck = api::Deck::createModel();
    const Records valid{record("SubcaseStart", {"1"}), record("OutputBlock", {"", "CurvePlot"}),
                        record("XyXTitle", {"TIME"})};
    REQUIRE(refusal(*deck, valid).empty());
    const Lines before = caseLines(*deck);
    REQUIRE(before == Lines{"SubcaseStart;1", "OutputBlock;;CurvePlot", "XyXTitle;TIME"});

    // The kind in the value field.
    const std::string misplaced =
        refusal(*deck, Records{record("SubcaseStart", {"1"}), record("OutputBlock", {"Plot"})});
    REQUIRE(contains(misplaced, "OutputBlock;;Plot"));
    REQUIRE(contains(misplaced, "Plot, Postprocessing, CurvePlot or CurveOutput"));
    // A word that is no kind of block.
    const std::string unknown =
        refusal(*deck, Records{record("SubcaseStart", {"1"}), record("OutputBlock", {"", "Anything"})});
    REQUIRE(contains(unknown, "\"Anything\" is not a kind of output block"));
    // A refused replacement changes nothing.
    REQUIRE(caseLines(*deck) == before);
}
