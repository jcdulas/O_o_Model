#include "oor/model/references/SetMemberUses.hpp"

#include "oor/model/cards/sets/idListSet1/IdListSet1Table.hpp"
#include "oor/model/control/case_control/CaseLineages.hpp"
#include "oor/model/references/ParameterReferences.hpp"

#include <limits>
#include <span>
#include <unordered_set>

namespace oor::model
{

namespace
{

// One user of the Bulk Data sets: a field of a card type that names a set (ReferenceTarget::Set), and what the header
// of the card says the set lists.
struct SetField
{
    std::string_view cardType;
    std::string_view field;
    SetMemberKind kind;
};

// The users of the IdListSet1 sets whose content the card header states. A field is listed only when the set it names
// is always of one kind and may be an IdListSet1. Left out on purpose, so that their sets stay as they are:
//  - the fields that name a TypedListSet3 only, which says its own type and visits its own members (BoltPretension,
//    ConnectorSearchControl, ContactFaceRegion, CrackClosureCrack, DeactivatedElems, ModuleContactCandidates,
//    RadiatedPowerPanelSet, StepControlCriteria, TransferPathSetup, TrimLayeredComponent, the controlNodeSetId of a
//    HydrostaticLoad);
//  - the fields whose set lists grid points or elements (or properties) as other data of the card says
//    (InitialValuesUserRoutine, FluidStructureInterface, FluidStructurePanels, ContactAutoParams, DesignResp1);
//  - the sets of something else: the faces of a RadiationCavity, the section points of a BarArbitrarySectionProp or
//    BeamArbitrarySectionProp;
//  - the sets of another part of the deck (TrimComponentCoupling, TrimComponentCoupling1D).
constexpr SetField SET_FIELDS[] = {
    // SETG of the splines: the structural grid points
    {"AeroSurfaceSpline1", "nodeSetId", SetMemberKind::Node},
    {"AeroBeamSpline2", "nodeSetId", SetMemberKind::Node},
    {"AeroSurfaceSpline4", "nodeSetId", SetMemberKind::Node},
    {"AeroBeamSpline5", "nodeSetId", SetMemberKind::Node},
    {"AeroFiniteSurfaceSpline6", "nodeSetId", SetMemberKind::Node},
    {"AeroFiniteBeamSpline7", "nodeSetId", SetMemberKind::Node},
    // LIST1 and LIST2: the grid points of the two components of a control surface
    {"AeroControlSurfaceNodes", "nodeSetId1", SetMemberKind::Node},
    {"AeroControlSurfaceNodes", "nodeSetId2", SetMemberKind::Node},
    // the list of a structural component (its IDs are visited as sets only for the list type of grid point sets)
    {"AeroComponent", "listIds", SetMemberKind::Node},
    // GRIDSET and ELEMSET of a free-body subsystem and of a monitor point of grid point forces
    {"FreeBodyLoadSubcase", "nodeSetId", SetMemberKind::Node},
    {"FreeBodyLoadSubcase", "elementSetId", SetMemberKind::Element},
    {"MonitorNodeForceSum3", "nodeSetId", SetMemberKind::Node},
    {"MonitorNodeForceSum3", "elementSetId", SetMemberKind::Element},
    // SETE (the elements of the interface) and SETG (their grid points)
    {"HydrostaticLoad", "elementSetId", SetMemberKind::Element},
    {"HydrostaticLoad", "nodeSetId", SetMemberKind::Node},
    // SETID of the card and of each group: the grid points that take the imperfection
    {"ImperfectionGeometry", "nodeSetId", SetMemberKind::Node},
    // NGSET and DGSET: the grid points taken out of, and added to, the design regions
    {"DesignBeadRegion", "excludedNodeSetId", SetMemberKind::Node},
    {"DesignBeadRegion", "addedNodeSetId", SetMemberKind::Node},
    // ELSIDi and XELSIDi (elements), NDSIDi (the grid points of a seam line)
    {"FatigueDefinition", "elemSetIds", SetMemberKind::Element},
    {"FatigueDefinition", "excludedElemSetIds", SetMemberKind::Element},
    {"FatigueDefinition", "nodeSetIds", SetMemberKind::Node},
    // SETID: the elements that take the initial values
    {"InitialElemValues", "elementSetId", SetMemberKind::Element},
    // SET1ID: the Euler elements of the coupling surface
    {"EulerLagrangeCoupling", "elemSetId", SetMemberKind::Element},
    // the VID of a region of type "list of elements" (it is visited as a set only for that type)
    {"EulerForceRegion", "shapeId", SetMemberKind::Element},
    {"InitialConditionRegion", "shapeId", SetMemberKind::Element},
};

// One output request of the Case Control and what the SET it names lists.
struct OutputSet
{
    std::string_view command;
    SetMemberKind kind;
};

// The output requests whose SET is known to list grid points or elements. The command catalogue does not say what a
// request selects, so the list is kept here, limited to the requests that leave no doubt.
constexpr OutputSet OUTPUT_SETS[] = {
    {"DisplacementOutput", SetMemberKind::Node},
    {"VelocityOutput", SetMemberKind::Node},
    {"AccelOutput", SetMemberKind::Node},
    {"SinglePointConstrForceOutput", SetMemberKind::Node},
    {"MultiPointConstrForceOutput", SetMemberKind::Node},
    {"AppliedLoadOutput", SetMemberKind::Node},
    {"NodeForceOutput", SetMemberKind::Node},
    {"StressOutput", SetMemberKind::Element},
    {"StrainOutput", SetMemberKind::Element},
    {"ElemForceOutput", SetMemberKind::Element},
    {"ElemStrainEnergyOutput", SetMemberKind::Element},
    {"ElemKineticEnergyOutput", SetMemberKind::Element},
    {"ElemDampingEnergyOutput", SetMemberKind::Element},
};

// A run of this many consecutive IDs, or more, of a Case Control SET is written "first Through last" (CaseSet::items).
constexpr std::size_t SHORTEST_RANGE = 3;

// True when a field of this card type is in the table of the users of the sets.
bool namesKnownSets(std::string_view cardType) noexcept
{
    for (const SetField& known : SET_FIELDS)
    {
        if (known.cardType == cardType)
            return true;
    }
    return false;
}

// Notes one use of a set: the first user of each kind is kept, for the messages.
void noteUse(SetMemberUse& use, SetMemberKind kind, const std::function<std::string()>& userText)
{
    std::string& user = kind == SetMemberKind::Node ? use.nodeUser : use.elementUser;
    if (user.empty())
        user = userText();
}

// Notes the sets that the fields of the table name, card by card. Only the set IDs of `listed` (those an IdListSet1
// card has) are noted: a field of the table may also name a TypedListSet3, which is not a set of this kind.
class SetUseCollector final : public ReferenceVisitor
{
public:
    SetUseCollector(BulkSetUses& uses, const std::unordered_set<base::EntityId>& listed)
        : m_uses(uses), m_listed(listed)
    {
    }

    // The card whose references come next: its type (the neutral name) and its ID (0 for a card that has none).
    void setCard(std::string_view type, base::EntityId id)
    {
        m_cardType = type;
        m_cardId = id;
    }

    // A set of another superelement or part (visitInSuperelement, visitInPart) is not followed: the defaults leave it.
    base::EntityId visit(std::string_view field, ReferenceTarget target, base::EntityId id) override
    {
        if (target != ReferenceTarget::Set || !m_listed.contains(id))
            return id;
        const SetMemberKind kind = memberKindOfSetField(m_cardType, field);
        if (kind == SetMemberKind::Unknown)
            return id;
        SetMemberUse& use = m_uses[id];
        if (use.set.empty())
            use.set = std::string(IdListSet1Table::NAME) + " " + std::to_string(id);
        noteUse(use, kind, [&] { return userText(field); });
        return id;
    }

private:
    // "nodeSetId of AeroSurfaceSpline1 60"
    [[nodiscard]] std::string userText(std::string_view field) const
    {
        std::string text = std::string(field) + " of " + std::string(m_cardType);
        if (m_cardId != 0)
            text += " " + std::to_string(m_cardId);
        return text;
    }

    BulkSetUses& m_uses;
    const std::unordered_set<base::EntityId>& m_listed;
    std::string_view m_cardType;
    base::EntityId m_cardId = 0;
};

void visitSections(const Subcase& section, const std::function<void(const Subcase&)>& visit)
{
    visit(section);
    for (const Subcase& child : section.children)
        visitSections(child, visit);
}

void visitSections(Subcase& section, const std::function<void(Subcase&)>& visit)
{
    visit(section);
    for (Subcase& child : section.children)
        visitSections(child, visit);
}

// The SET `number` that a section defines for its output requests: the last one written outside the OUTPUT(PLOT),
// OUTPUT(XYPLOT) and OUTPUT(POST) blocks, whose SETs are those of the plotter (the entries of a block follow its
// line: CaseControl::blockExtent).
const CaseEntry* ownOutputSet(const Subcase& section, std::int64_t number)
{
    const CaseEntry* found = nullptr;
    for (std::size_t index = 0; index < section.entries.size(); ++index)
    {
        const CaseEntry& entry = section.entries[index];
        if (entry.kind == EntryKind::OutputBlock)
        {
            // The loop goes on with the entry after the block (`last` is at least the entry after the block line).
            index = CaseControl::blockExtent(section, index).last - 1;
            continue;
        }
        if (entry.kind == EntryKind::Set && entry.number == number)
            found = &entry;
    }
    return found;
}

// The SET `number` that the requests of a section name: the one of the nearest section of its lineage that has one.
const CaseEntry* outputSetIn(std::span<const Subcase* const> lineage, std::int64_t number)
{
    for (const Subcase* section : lineage)
    {
        if (const CaseEntry* set = ownOutputSet(*section, number))
            return set;
    }
    return nullptr;
}

// True when a section of the Case Control defines a SET of integers (most Case Controls have none: nothing to look
// for).
bool hasIntegerSets(const CaseControl& caseControl)
{
    bool found = false;
    forEachCaseSection(caseControl,
                       [&found](const Subcase& section)
                       {
                           for (const CaseEntry& entry : section.entries)
                           {
                               if (entry.kind == EntryKind::Set && entry.set.kind == CaseSetKind::Integers)
                                   found = true;
                           }
                       });
    return found;
}

// "DisplacementOutput of SubcaseStart 2", "StressOutput of the GLOBAL section": the words of the reference check.
std::string requestText(const CaseEntry& request, const Subcase& section)
{
    const std::string label = subcaseLabel(section.kind);
    const std::string where = section.id == 0 ? "the " + label + " section" : label + " " + std::to_string(section.id);
    return request.name + " of " + where;
}

} // namespace

std::optional<SetMemberTargets> targetsOfSetMembers(SetMemberKind kind) noexcept
{
    switch (kind)
    {
    case SetMemberKind::Node:
        return SetMemberTargets{ReferenceTarget::Node, ReferenceTarget::NodeInRange};
    case SetMemberKind::Element:
        return SetMemberTargets{ReferenceTarget::Element, ReferenceTarget::ElementInRange};
    case SetMemberKind::Unknown:
    case SetMemberKind::Conflict:
        break;
    }
    return std::nullopt;
}

std::string_view setMemberWords(SetMemberKind kind) noexcept
{
    switch (kind)
    {
    case SetMemberKind::Node:
        return "grid points";
    case SetMemberKind::Element:
        return "elements";
    case SetMemberKind::Unknown:
    case SetMemberKind::Conflict:
        break;
    }
    return {};
}

SetMemberKind memberKindOfSetField(std::string_view cardType, std::string_view field) noexcept
{
    for (const SetField& known : SET_FIELDS)
    {
        if (known.cardType == cardType && known.field == field)
            return known.kind;
    }
    return SetMemberKind::Unknown;
}

SetMemberKind memberKindOfOutputSet(std::string_view command) noexcept
{
    for (const OutputSet& known : OUTPUT_SETS)
    {
        if (known.command == command)
            return known.kind;
    }
    return SetMemberKind::Unknown;
}

SetMemberKind SetMemberUse::kind() const noexcept
{
    if (!nodeUser.empty() && !elementUser.empty())
        return SetMemberKind::Conflict;
    if (!nodeUser.empty())
        return SetMemberKind::Node;
    if (!elementUser.empty())
        return SetMemberKind::Element;
    return SetMemberKind::Unknown;
}

BulkSetUses bulkSetUses(Model& model)
{
    BulkSetUses uses;
    const IdListSet1Table* sets = model.findTable<IdListSet1Table>();
    if (sets == nullptr)
        return uses; // no set whose members could follow or be looked up
    std::unordered_set<base::EntityId> listed;
    for (std::uint32_t row = 0; row < sets->rows().rowCount(); ++row)
    {
        if (sets->rows().isAlive(row))
            listed.insert(sets->idAt(row));
    }
    if (listed.empty())
        return uses;
    SetUseCollector collector(uses, listed);
    const CardRegistry& registry = CardRegistry::instance();
    for (std::uint16_t type = 1; type < registry.size(); ++type)
    {
        const std::string_view cardType = registry.entry(type).info.name;
        CardTable* table = model.findTable(type);
        if (table == nullptr || !namesKnownSets(cardType))
            continue;
        for (std::uint32_t row = 0; row < table->rows().rowCount(); ++row)
        {
            if (!table->rows().isAlive(row))
                continue;
            collector.setCard(cardType, table->idAt(row));
            table->visitReferences(row, collector);
        }
    }
    return uses;
}

CaseSetUses caseSetUses(const CaseControl& caseControl)
{
    CaseSetUses uses;
    if (!hasIntegerSets(caseControl))
        return uses;
    const CaseLineages lineages(caseControl);
    forEachCaseSection(
        caseControl,
        [&](const Subcase& section)
        {
            const std::span<const Subcase* const> lineage = lineages.of(section.key);
            for (const OutputSet& known : OUTPUT_SETS)
            {
                // The requests in effect in this section: its own, else the ones it inherits.
                for (const CaseEntry* request : lineages.outputs(section.key, known.command))
                {
                    if (request->value.kind != CaseValueKind::Integer)
                        continue; // All, None or no selection: no SET
                    const CaseEntry* set = outputSetIn(lineage, request->value.integer);
                    if (set == nullptr || set->set.kind != CaseSetKind::Integers)
                        continue;
                    SetMemberUse& use = uses[set->key];
                    if (use.set.empty())
                        use.set = std::string(SET_COMMAND) + " " + std::to_string(set->number);
                    noteUse(use, known.kind, [&] { return requestText(*request, section); });
                }
            }
        });
    return uses;
}

void forEachCaseSection(const CaseControl& caseControl, const std::function<void(const Subcase&)>& visit)
{
    for (const Subcase& segment : caseControl.segments())
        visitSections(segment, visit);
}

void forEachCaseSection(CaseControl& caseControl, const std::function<void(Subcase&)>& visit)
{
    for (Subcase& segment : caseControl.segments())
        visitSections(segment, visit);
}

std::vector<std::int64_t> singleMembers(const CaseSet& set)
{
    std::vector<std::int64_t> singles;
    if (set.kind != CaseSetKind::Integers)
        return singles;
    const std::vector<std::int64_t>& ids = set.integers;
    std::size_t first = 0;
    while (first < ids.size())
    {
        // The run of consecutive IDs that starts here (the largest integer has no next one).
        std::size_t last = first;
        while (last + 1 < ids.size() && ids[last] < std::numeric_limits<std::int64_t>::max() &&
               ids[last + 1] == ids[last] + 1)
            ++last;
        if (last - first + 1 < SHORTEST_RANGE)
            singles.insert(singles.end(), ids.begin() + static_cast<std::ptrdiff_t>(first),
                           ids.begin() + static_cast<std::ptrdiff_t>(last + 1));
        first = last + 1;
    }
    return singles;
}

void visitCaseParameterReferences(CaseControl& caseControl, ReferenceVisitor& visitor,
                                  const CaseControl::ScopeCallback& onScope)
{
    forEachCaseSection(caseControl,
                       [&](Subcase& section)
                       {
                           if (onScope)
                               onScope(section.kind, section.id);
                           for (CaseEntry& entry : section.entries)
                           {
                               if (entry.kind != EntryKind::Param || entry.value.kind != CaseValueKind::Integer ||
                                   entry.value.integer <= 0)
                                   continue;
                               const ParameterReference* known = findParameterReference(entry.variant);
                               const auto id = base::toEntityId(entry.value.integer);
                               if (known == nullptr || !id)
                                   continue;
                               const base::EntityId updated = visitor.visit(known->parameter, known->target, *id);
                               if (updated != *id)
                               {
                                   entry.value.integer = updated;
                                   entry.original.clear();
                               }
                           }
                       });
}

} // namespace oor::model
