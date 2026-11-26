#include "oor/analysis/validation/compatibility/CompatibilityChecks.hpp"
#include "oor/analysis/validation/engine/ValidationSupport.hpp"
#include "oor/model/cards/materials/isoMat/IsoMatTable.hpp"

#include <unordered_set>

namespace oor::analysis
{

namespace
{

// The materials used by a property that needs a shear modulus (everything but a rod).
std::unordered_set<base::EntityId> materialsNeedingShear(const ValidationContext& context)
{
    std::unordered_set<base::EntityId> needing;
    for (const CardReference& use : context.references().propertyMaterials)
    {
        if (!isOneOf(cardNameAt(context.model(), use.location), {"RodProp", "TubeProp"}))
            needing.insert(use.id);
    }
    return needing;
}

// The shear modulus that an IsoMat gives and that is negative, or zero when something that needs it uses the material.
// A card that leaves G blank holds a value derived from E and NU, or zero: that one is not what the deck wrote, and
// IsoMatBlankShearModulusCheck looks at it.
class IsoMatShearModulusCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"compat.iso-mat-shear-modulus", base::Severity::Error, "compatibility",
                                    "The shear modulus given by an isotropic material is zero or negative."};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        const std::unordered_set<base::EntityId> needing = materialsNeedingShear(context);
        forEachCard<model::IsoMatTable>(
            context.model(),
            [&](const model::IsoMatCard& card, model::CardLocation where)
            {
                const bool given = (card.blankFields & model::IsoMatCard::BLANK_SHEAR_MODULUS) == 0;
                if (given && !(card.shearModulus > 0.0) && (card.shearModulus < 0.0 || needing.contains(card.id)))
                    sink.reportCard(
                        where, "shearModulus",
                        std::string("shearModulus") + " is " + std::to_string(card.shearModulus) +
                            ": the shear modulus must be positive",
                        "give a positive shear modulus, or leave " + std::string("shearModulus") + " blank");
            });
    }
};

// An IsoMat given with E only (G and NU blank) has G = 0 and NU = 0 (IsoMatFormat::resolve): a material for rods and
// springs, which need no shear modulus. A property that needs one (a bar, a beam, a shell) and uses the material has
// no shear or torsional stiffness from it. A warning, not an error: the card wrote no zero, and a bar whose torsion
// and shear are not loaded may be meant that way.
class IsoMatBlankShearModulusCheck final : public ValidationCheck
{
public:
    static constexpr CheckInfo INFO{"compat.iso-mat-shear-modulus-blank", base::Severity::Warning, "compatibility",
                                    "An isotropic material with a blank shear modulus and a blank Poisson ratio (a "
                                    "zero shear modulus) is used by a property that needs a shear modulus."};

    [[nodiscard]] const CheckInfo& info() const noexcept override { return INFO; }

    void run(const ValidationContext& context, FindingSink& sink) const override
    {
        constexpr std::uint8_t SHEAR_AND_POISSON =
            model::IsoMatCard::BLANK_SHEAR_MODULUS | model::IsoMatCard::BLANK_POISSON_RATIO;
        const std::unordered_set<base::EntityId> needing = materialsNeedingShear(context);
        forEachCard<model::IsoMatTable>(
            context.model(),
            [&](const model::IsoMatCard& card, model::CardLocation where)
            {
                const bool bothBlank = (card.blankFields & SHEAR_AND_POISSON) == SHEAR_AND_POISSON;
                if (bothBlank && card.shearModulus == 0.0 && needing.contains(card.id))
                    sink.reportCard(where, "shearModulus",
                                    std::string("shearModulus") + " and " + std::string("poissonRatio") +
                                        " are blank: the shear modulus is zero for the property that uses the material",
                                    "give " + std::string("shearModulus") + " or " + std::string("poissonRatio"));
            });
    }
};

} // namespace

void addIsoMatShearModulusCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<IsoMatShearModulusCheck>());
}

void addIsoMatBlankShearModulusCheck(CheckRegistry& registry)
{
    registry.add(std::make_unique<IsoMatBlankShearModulusCheck>());
}

} // namespace oor::analysis
