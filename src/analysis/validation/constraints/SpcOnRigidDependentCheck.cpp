#include "ConstraintDofs.hpp"
#include "oor/analysis/validation/constraints/ConstraintChecks.hpp"

#include <set>
#include <unordered_set>

namespace oor::analysis
{

namespace
{

// A degree of freedom that a rigid element makes dependent and that a single point constraint fixes as well: the solver
// refuses it (a degree of freedom cannot be in the m-set and the s-set). The SinglePointConstr and
// SinglePointConstrList sets are the ones the Case Control selects; the PS field of a grid point always applies.
class SpcOnRigidDependentCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"constraint.spc-on-rigid-dependent", base::Severity::Error, "constraints",
                                    "A degree of freedom is constrained (single-point constraint or permanent "
                                    "constraint of a grid point) and dependent in a rigid element."};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        const model::Model& model = context.model();
        std::unordered_set<std::uint64_t> dependent;
        for (const DofUse& use : rigidDependentDofs(model))
            dependent.insert(use.key);
        if (dependent.empty())
            return;
        std::set<std::pair<std::uint32_t, std::uint32_t>> reported;
        // `fixed` holds dependent degrees of freedom only (the ones asked for): each is a clash.
        const auto report = [&](const std::vector<DofUse>& fixed)
        {
            for (const DofUse& use : fixed)
            {
                if (!reported.emplace(use.where.table, use.where.row).second)
                    continue;
                sink.reportCard(use.where, "",
                                "degree of freedom " + std::to_string(componentOfDof(use.key)) + " of grid point " +
                                    std::to_string(nodeOfDof(use.key)) + " is dependent in a rigid element",
                                "remove the constraint, or the dependency");
            }
        };
        report(permanentConstraintDofs(model, dependent));
        const DofUsesBySet fixedBySet = spcDofsBySet(model, context.sortedNodeIds(), dependent);
        for (const std::vector<base::EntityId>& sets :
             constraintSelections(context.root(), model, model::SINGLE_POINT_CONSTR_SELECTION))
            report(dofsOfSets(fixedBySet, sets));
    }
};

} // namespace

void addSpcOnRigidDependentCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<SpcOnRigidDependentCheck>());
}

} // namespace oor::analysis
