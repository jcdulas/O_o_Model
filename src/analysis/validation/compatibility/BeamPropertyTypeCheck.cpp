#include "TypeRules.hpp"
#include "oor/analysis/validation/compatibility/CompatibilityChecks.hpp"

namespace oor::analysis
{

namespace
{

// A Beam2 whose property is not a BeamProp, BeamShapeProp or BeamLumpedAreaProp.
class BeamPropertyTypeCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"compat.beam-property-type", base::Severity::Error, "compatibility",
                                    "A beam element uses a property that is not a beam, beam shape, lumped area beam "
                                    "or beam arbitrary section property."};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        // format reference Beam2: PID names a BeamProp, BeamLumpedAreaProp, BeamShapeProp or BeamArbitrarySectionProp.
        reportWrongPropertyType(context, sink, {"Beam2"},
                                {"BeamProp", "BeamShapeProp", "BeamLumpedAreaProp", "BeamArbitrarySectionProp"});
    }
};

} // namespace

void addBeamPropertyTypeCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<BeamPropertyTypeCheck>());
}

} // namespace oor::analysis
