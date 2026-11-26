#include "ConstraintDofs.hpp"
#include "oor/analysis/validation/constraints/ConstraintChecks.hpp"

#include <set>
#include <unordered_set>

namespace oor::analysis
{

namespace
{

// A degree of freedom that is the dependent term of an MPC equation and is also fixed by a SinglePointConstr,
// SinglePointConstrList or the PS field of its grid point. The two commands are taken together for each subcase
// (constraintCombinations): the single point constraints of one subcase do not meet the multipoint constraints of
// another. The PS field of a grid point is fixed in every subcase.
class SpcOnMpcDependentCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"constraint.spc-on-mpc-dependent", base::Severity::Error, "constraints",
                                    "A degree of freedom is constrained (single-point constraint or permanent "
                                    "constraint of a grid point) and is the dependent term of a multipoint "
                                    "constraint."};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        const model::Model& model = context.model();
        const DofUsesBySet dependentBySet = mpcDependentDofsBySet(model);
        // The dependent terms of every set: a constraint on none of them cannot clash, and is not kept.
        std::unordered_set<std::uint64_t> anyDependent;
        for (const auto& [setId, uses] : dependentBySet)
        {
            for (const DofUse& use : uses)
                anyDependent.insert(use.key);
        }
        if (anyDependent.empty())
            return;
        const std::vector<DofUse> permanent = permanentConstraintDofs(model, anyDependent);
        const DofUsesBySet fixedBySet = spcDofsBySet(model, context.sortedNodeIds(), anyDependent);
        if (permanent.empty() && fixedBySet.empty())
            return;

        // The dependent terms of the multipoint sets of the combination being judged.
        std::unordered_set<std::uint64_t> dependent;
        std::set<std::pair<std::uint32_t, std::uint32_t>> reported;
        const auto judge = [&](const std::vector<DofUse>& fixed)
        {
            for (const DofUse& use : fixed)
            {
                if (!dependent.contains(use.key) || !reported.emplace(use.where.table, use.where.row).second)
                    continue;
                sink.reportCard(use.where, "",
                                "degree of freedom " + std::to_string(componentOfDof(use.key)) + " of grid point " +
                                    std::to_string(nodeOfDof(use.key)) + " is the dependent term of a " +
                                    std::string("MultiPointConstr"),
                                "remove the constraint, or the " + std::string("MultiPointConstr") + " equation");
            }
        };
        const std::vector<ConstraintCombination> combinations = constraintCombinations(context.root(), model);
        const std::vector<base::EntityId>* judgedMpcSets = nullptr;
        for (const ConstraintCombination& combination : combinations)
        {
            // The combinations are sorted by their multipoint sets: the dependent terms are gathered once for the
            // combinations that share them, and the PS fields, which every one of these has, are judged then.
            if (judgedMpcSets == nullptr || *judgedMpcSets != combination.mpcSets)
            {
                judgedMpcSets = &combination.mpcSets;
                dependent.clear();
                for (const DofUse& use : dofsOfSets(dependentBySet, combination.mpcSets))
                    dependent.insert(use.key);
                judge(permanent);
            }
            judge(dofsOfSets(fixedBySet, combination.spcSets));
        }
    }
};

} // namespace

void addSpcOnMpcDependentCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<SpcOnMpcDependentCheck>());
}

} // namespace oor::analysis
