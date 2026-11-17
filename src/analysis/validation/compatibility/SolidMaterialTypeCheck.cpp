#include "TypeRules.hpp"
#include "oor/analysis/validation/compatibility/CompatibilityChecks.hpp"

namespace oor::analysis
{

namespace
{

// A SolidProp or SolidPropHyperelastic with a material of the shell class (AnisoMat2D, AxisymOrthoMat, OrthoMat2D): the
// format reference gives IsoMat, HeatIsoMat, HeatAnisoMat, AnisoMat3D, FluidMat, HyperelasticPolynomialMat,
// HyperelasticMat for a solid.
class SolidMaterialTypeCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"compat.solid-material-type", base::Severity::Error, "compatibility",
                                    "A solid or hyperelastic solid property uses a material of the shell class (2D "
                                    "anisotropic, axisymmetric orthotropic or 2D orthotropic)."};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        reportRefusedMaterial(context, sink, {"SolidProp", "SolidPropHyperelastic"},
                              {"AnisoMat2D", "AxisymOrthoMat", "OrthoMat2D"},
                              {"IsoMat", "AnisoMat3D", "FluidMat", "HyperelasticPolynomialMat", "HyperelasticMat"});
    }
};

} // namespace

void addSolidMaterialTypeCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<SolidMaterialTypeCheck>());
}

} // namespace oor::analysis
