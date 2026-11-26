#include "oor/analysis/validation/constraints/ConstraintChecks.hpp"
#include "oor/analysis/validation/engine/ValidationSupport.hpp"
#include "oor/model/cards/nodes/node/NodeTable.hpp"
#include "oor/model/parameters/ParameterValues.hpp"

namespace oor::analysis
{

namespace
{

// A static solution (101, 105, 106, 144) of a model with no constraint at all: no SinglePointConstr,
// SinglePointConstrList, FreeBodySupport, GeomSinglePointConstr, SinglePointConstrAxisym card, no ring or point of a
// conical shell (AxisymConeRing and AxisymConePoint: the PS of a ring and the harmonics are constraints the check does
// not judge) and no PS on any grid point, and no inertia relief (PARAM,InertiaRelief). The stiffness matrix is
// singular.
class NoConstraintCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"constraint.none-in-static-model",
                                    base::Severity::Warning,
                                    "constraints",
                                    "A static solution has no constraint in the model (and no inertia relief).",
                                    false,
                                    CheckScope::Deck};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        const std::optional<std::int64_t> solution = context.solution();
        if (!solution || !isStaticSolution(*solution))
            return;
        const model::Model& model = context.model();
        if (isHeatTransfer(model))
            return; // the constraints of a thermal analysis are temperatures: nothing is singular without them
        // PARAM,InertiaRelief (inertia relief): a negative value, else the format reference default (0).
        if (const std::optional<std::int32_t> relief = model::integerParameter(model, "InertiaRelief");
            relief && *relief < 0)
            return;
        // Nothing to judge in a model with no card at all (a deck whose Bulk Data is in a file not read).
        if (model.cardCount() == 0)
            return;
        // Cards that carry constraints, or that describe the boundary of the model by sets the check does not follow
        // (the boundary sets of a modal synthesis, the exclusions from the automatic constraints), and that the library
        // keeps as text because it could not read them (tolerant mode): the check cannot tell what they fix. A card
        // kept as text has the name the deck gives it, which is the neutral name of its type.
        for (const model::Model* each : context.allModels())
        {
            for (const std::string& name : unknownCardNames(*each))
            {
                if (isConstraintCard(name) ||
                    isOneOf(name, {"FixedBoundaryDofs", "FixedBoundaryDofs1", "FreeBoundaryDofs", "FreeBoundaryDofs1",
                                   "AutoConstrExclusion", "AutoConstrExclusionList"}))
                    return;
            }
        }
        const model::CardRegistry& registry = model::CardRegistry::instance();
        bool pinned = false;
        // The parts (superelements) have constraints of their own.
        for (const model::Model* each : context.allModels())
        {
            for (std::uint16_t type = 1; type < registry.size(); ++type)
            {
                const model::CardTable* table = each->findTable(type);
                if (table == nullptr || table->rows().aliveCount() == 0)
                    continue;
                if (isConstraintCard(registry.entry(type).info.name))
                    return;
            }
            forEachCard<model::NodeTable>(*each, [&](const model::NodeCard& grid, model::CardLocation)
                                          { pinned = pinned || grid.permanentConstraints > 0; });
        }
        if (!pinned)
            sink.reportStatement("SolutionSequence", *solution,
                                 "the model has no single point constraint, no " + std::string("FreeBodySupport") +
                                     " and no " + std::string("permanentConstraints") +
                                     " field: the stiffness matrix is singular",
                                 "add " + std::string("SinglePointConstr") + " cards, or " + std::string("Parameter") +
                                     "," + std::string("InertiaRelief") + ",-1 for inertia relief");
    }

private:
    // True for the card types that constrain the model (or support it, or hold the constraints of a conical shell):
    // one card of these is enough for the check to say nothing.
    static bool isConstraintCard(std::string_view name) noexcept
    {
        return isOneOf(name, {"SinglePointConstr", "SinglePointConstrList", "EnforcedMotionConstr", "FreeBodySupport",
                              "FreeBodySupportSet", "GeomSinglePointConstr", "SinglePointConstrAxisym",
                              "AxisymConeRing", "AxisymConePoint"});
    }
};

} // namespace

void addNoConstraintCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<NoConstraintCheck>());
}

} // namespace oor::analysis
