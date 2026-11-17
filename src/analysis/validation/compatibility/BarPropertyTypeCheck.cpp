#include "TypeRules.hpp"
#include "oor/analysis/validation/compatibility/CompatibilityChecks.hpp"

namespace oor::analysis
{

namespace
{

// A Bar2 whose property is not a BarProp or a BarShapeProp (a Bar2 with a ShellProp).
class BarPropertyTypeCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"compat.bar-property-type", base::Severity::Error, "compatibility",
                                    "A bar element uses a property that is not a bar, bar shape or bar arbitrary "
                                    "section property."};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        // format reference Bar2: PID names a BarProp, BarShapeProp or BarArbitrarySectionProp.
        reportWrongPropertyType(context, sink, {"Bar2"}, {"BarProp", "BarShapeProp", "BarArbitrarySectionProp"});
    }
};

} // namespace

void addBarPropertyTypeCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<BarPropertyTypeCheck>());
}

} // namespace oor::analysis
