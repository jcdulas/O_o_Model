#include "oor/analysis/validation/compatibility/CompatibilityChecks.hpp"
#include "oor/analysis/validation/engine/ValidationSupport.hpp"
#include "oor/model/cards/materials/isoMat/IsoMatTable.hpp"

namespace oor::analysis
{

namespace
{

// The range of the Poisson's ratio of a stable isotropic material: above -1, up to 0.5. At 0.5 the material is
// incompressible, which a deck may ask for (the elements made for it take it), so 0.5 itself is accepted.
constexpr double POISSON_ABOVE = -1.0;
constexpr double POISSON_UP_TO = 0.5;

bool isStablePoisson(double poissonRatio) noexcept
{
    return poissonRatio > POISSON_ABOVE && poissonRatio <= POISSON_UP_TO;
}

// Poisson's ratio that an IsoMat gives outside the range of a stable isotropic material. A card that leaves NU blank
// holds a value derived from E and G (or zero): that one is not what the deck wrote, and IsoMatDerivedPoissonCheck
// looks at it.
class IsoMatPoissonCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"compat.iso-mat-poisson", base::Severity::Error, "compatibility",
                                    "The Poisson ratio given by an isotropic material is above 0.5, or -1 or less."};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        forEachCard<model::IsoMatTable>(
            context.model(),
            [&](const model::IsoMatCard& card, model::CardLocation where)
            {
                const bool given = (card.blankFields & model::IsoMatCard::BLANK_POISSON_RATIO) == 0;
                if (given && !isStablePoisson(card.poissonRatio))
                    sink.reportCard(where, "poissonRatio",
                                    std::string("poissonRatio") + " is " + std::to_string(card.poissonRatio) +
                                        ": it must be above -1 and not above 0.5",
                                    "use a Poisson's ratio of 0.5 or less");
            });
    }
};

// An IsoMat that gives E and G and leaves NU blank: NU is then E / (2 G) - 1 (IsoMatFormat::resolve), and a pair of
// moduli far from one another (E above 3 G) gives a ratio above 0.5. A warning, not an error: the card wrote no such
// ratio, and a bar or a beam uses E and G alone; a shell, which uses the ratio, is not stable with it.
class IsoMatDerivedPoissonCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"compat.iso-mat-poisson-derived", base::Severity::Warning, "compatibility",
                                    "The Young and shear moduli of an isotropic material with a blank Poisson ratio "
                                    "give a ratio above 0.5."};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        constexpr std::uint8_t MODULI =
            model::IsoMatCard::BLANK_YOUNGS_MODULUS | model::IsoMatCard::BLANK_SHEAR_MODULUS;
        forEachCard<model::IsoMatTable>(
            context.model(),
            [&](const model::IsoMatCard& card, model::CardLocation where)
            {
                const bool derived = (card.blankFields & model::IsoMatCard::BLANK_POISSON_RATIO) != 0 &&
                                     (card.blankFields & MODULI) == 0;
                // A modulus that is not positive has its own error, and gives no ratio worth a second finding.
                if (!derived || !(card.youngsModulus > 0.0) || !(card.shearModulus > 0.0) ||
                    isStablePoisson(card.poissonRatio))
                    return;
                sink.reportCard(where, "poissonRatio",
                                std::string("youngsModulus") + " and " + std::string("shearModulus") +
                                    " give a Poisson's ratio of " + std::to_string(card.poissonRatio) +
                                    " (E / (2 G) - 1): a stable material has one above -1 and not above 0.5",
                                "check the two moduli, or give " + std::string("poissonRatio"));
            });
    }
};

} // namespace

void addIsoMatPoissonCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<IsoMatPoissonCheck>());
}

void addIsoMatDerivedPoissonCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<IsoMatDerivedPoissonCheck>());
}

} // namespace oor::analysis
