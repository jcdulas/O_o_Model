#pragma once

#include "oor/base/ids/EntityId.hpp"
#include "oor/model/control/case_control/CaseControl.hpp"
#include "oor/model/core/Model.hpp"
#include "oor/model/references/ReferenceVisitor.hpp"

#include <cstdint>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace oor::model
{

// What the members of a set are. A set is a plain list of IDs: an IdListSet1 card of the Bulk Data, or a SET of the
// Case Control. Nothing in the set says whether the IDs are grid points or elements; the card field or the output
// request that names the set does. The renumbering and the reference check need to know, to follow or to look up the
// members.
enum class SetMemberKind : std::uint8_t
{
    Unknown,  // no user of the set that the library knows says what it lists: the members are left alone
    Node,     // grid points (any point of the node ID space)
    Element,  // elements
    Conflict  // named both as a set of grid points and as a set of elements: no single meaning
};

// The reference targets of the members of a set of grid points or of elements: a member written alone, and the end
// of a "first Through last" range (which may name nothing: the format skips the gaps of a range). Nothing for the
// other kinds.
struct SetMemberTargets
{
    ReferenceTarget single = ReferenceTarget::Other;
    ReferenceTarget range = ReferenceTarget::Other;
};
[[nodiscard]] std::optional<SetMemberTargets> targetsOfSetMembers(SetMemberKind kind) noexcept;

// "grid points" or "elements", for a message; empty for the other kinds.
[[nodiscard]] std::string_view setMemberWords(SetMemberKind kind) noexcept;

// What the members of the set named by the field `field` of a card of type `cardType` are (neutral names, as the card
// registry and the reference visitors give them: "AeroSurfaceSpline1", "nodeSetId"). This is the table of the users of
// the Bulk Data sets, written from the header of each card; Unknown for a field that is not in it: a field that names
// a TypedListSet3 only (which says its own type), a set whose content depends on other data of the card, or a set of
// something else than grid points and elements.
[[nodiscard]] SetMemberKind memberKindOfSetField(std::string_view cardType, std::string_view field) noexcept;

// What the members of the SET that an output request of the Case Control names are, by the neutral name of the
// request ("DisplacementOutput": grid points, "StressOutput": elements). Unknown for the requests the table does not
// list.
[[nodiscard]] SetMemberKind memberKindOfOutputSet(std::string_view command) noexcept;

// How one set is used: the first user that names it as a set of grid points and the first that names it as a set of
// elements (each as a text for a message: "nodeSetId of AeroSurfaceSpline1 60"), empty when there is none.
struct SetMemberUse
{
    std::string set; // the set, for a message: "IdListSet1 17", "SetDefinition 5"
    std::string nodeUser;
    std::string elementUser;

    [[nodiscard]] SetMemberKind kind() const noexcept;
    // The user that gives the set its kind (the grid point user of a set named both ways).
    [[nodiscard]] const std::string& user() const noexcept { return nodeUser.empty() ? elementUser : nodeUser; }
};

// The uses of the IdListSet1 sets of a model, by set ID: only the sets that a field of the table
// (memberKindOfSetField) of a live card of this model names. A set that no such field names is not in the map: its
// members are left alone. One pass over the cards of the card types of the table, and none when the model has no
// IdListSet1. The model is not changed (the visit gives back every ID as found), but it must not be read by another
// thread meanwhile, as for ReferenceChecker::scan.
using BulkSetUses = std::map<base::EntityId, SetMemberUse>;
[[nodiscard]] BulkSetUses bulkSetUses(Model& model);

// The uses of the SETs of a Case Control, by the key of the SET entry (CaseEntry::key): only the sets of integers
// that an output request of the table (memberKindOfOutputSet) names. A request names the SET that its section sees:
// the one of the section itself, else of the section it is in, else of the global section (a SET written again in a
// subcase replaces the global one there); the requests are the effective ones of each section (a subcase with no
// request of a kind inherits the ones above it). The SETs written in an OUTPUT(PLOT), OUTPUT(XYPLOT) or OUTPUT(POST)
// block are those of the plotter, which no output request names: they are never in the map.
using CaseSetUses = std::map<std::uint32_t, SetMemberUse>;
[[nodiscard]] CaseSetUses caseSetUses(const CaseControl& caseControl);

// Calls `visit` for every section of a Case Control, the steps and substeps after the section they are in.
void forEachCaseSection(const CaseControl& caseControl, const std::function<void(const Subcase&)>& visit);
void forEachCaseSection(CaseControl& caseControl, const std::function<void(Subcase&)>& visit);

// The members of a Case Control SET of integers that are written alone. The set is stored expanded and written with
// a run of three or more consecutive IDs as "first Through last" (CaseSet::items): such a run is a range, whose IDs
// may name nothing, and the other members are single IDs, which should each name something.
[[nodiscard]] std::vector<std::int64_t> singleMembers(const CaseSet& set);

// Shows the parameters of the Case Control that hold the ID of a card (ParameterReferences.hpp, a positive integer
// value) to the visitor, as CaseControl::visitReferences does for the commands: the field is the name of the
// parameter, a changed ID is stored and the original text of the entry dropped. `onScope` is called when a section is
// entered.
void visitCaseParameterReferences(CaseControl& caseControl, ReferenceVisitor& visitor,
                                  const CaseControl::ScopeCallback& onScope = {});

} // namespace oor::model
