#include "TypeRules.hpp"
#include "oor/analysis/validation/compatibility/CompatibilityChecks.hpp"

namespace oor::analysis
{

namespace
{

// A ply of a CompProp or CompPropGlobal made of a material that is not an IsoMat, AnisoMat2D or OrthoMat2D.
class PlyMaterialTypeCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"compat.ply-material-type", base::Severity::Error, "compatibility",
                                    "A ply of a composite property uses a material that is not isotropic, 2D "
                                    "anisotropic or 2D orthotropic (or a progressive failure material, and for a "
                                    "composite property without global ply IDs a fabric or user composite failure "
                                    "material)."};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        // format reference ProgressiveFailureMat: a ply of a CompProp, CompPropGlobal or CompSolidPropNonlinear may
        // name it; a ply of a CompProp may name the woven fabric of SOL 700; format reference UserCompositeFailureMat:
        // the user failure model of SOL 700 for shell composites.
        reportUnlistedMaterial(context, sink, {"CompProp"},
                               {"IsoMat", "AnisoMat2D", "OrthoMat2D", "HeatIsoMat", "HeatAnisoMat",
                                "ProgressiveFailureMat", "FabricMat", "UserCompositeFailureMat"},
                               {"IsoMat", "AnisoMat2D", "OrthoMat2D"});
        reportUnlistedMaterial(
            context, sink, {"CompPropGlobal"},
            {"IsoMat", "AnisoMat2D", "OrthoMat2D", "HeatIsoMat", "HeatAnisoMat", "ProgressiveFailureMat"},
            {"IsoMat", "AnisoMat2D", "OrthoMat2D"});
    }
};

} // namespace

void addPlyMaterialTypeCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<PlyMaterialTypeCheck>());
}

} // namespace oor::analysis
