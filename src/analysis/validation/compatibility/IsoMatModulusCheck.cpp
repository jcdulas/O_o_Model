#include "oor/analysis/validation/compatibility/CompatibilityChecks.hpp"
#include "oor/analysis/validation/engine/ValidationSupport.hpp"
#include "oor/model/cards/materials/isoMat/IsoMatTable.hpp"

namespace oor::analysis
{

namespace
{

// Young's modulus that an IsoMat gives and that is zero or negative. A card may leave E blank and give G: the material
// of a shear panel, the transverse shear material of a shell. The card then holds a value derived from G and NU, or
// zero, which is not what the deck wrote and is not judged here.
class IsoMatModulusCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"compat.iso-mat-modulus", base::Severity::Error, "compatibility",
                                    "The Young modulus given by an isotropic material is zero or negative."};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        forEachCard<model::IsoMatTable>(
            context.model(),
            [&](const model::IsoMatCard& card, model::CardLocation where)
            {
                const bool given = (card.blankFields & model::IsoMatCard::BLANK_YOUNGS_MODULUS) == 0;
                if (given && !(card.youngsModulus > 0.0))
                    sink.reportCard(where, "youngsModulus",
                                    std::string("youngsModulus") + " is " + std::to_string(card.youngsModulus) +
                                        ": Young's modulus must be positive",
                                    "give a positive modulus of elasticity, or leave " + std::string("youngsModulus") +
                                        " blank and give " + std::string("shearModulus"));
            });
    }
};

} // namespace

void addIsoMatModulusCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<IsoMatModulusCheck>());
}

} // namespace oor::analysis
