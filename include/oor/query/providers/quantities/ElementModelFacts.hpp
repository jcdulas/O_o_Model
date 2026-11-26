#pragma once

#include "oor/query/results/ResultSets.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <map>
#include <optional>
#include <string>

namespace oor::query
{

// What the model says of the elements of a result set that the recomputations of a stress, a strain or a force need:
// the thickness and the isotropic material of a shell, the area of a rod, the material of a solid. Looked up by the
// element ID the file uses, through the attachment (so the answer follows a renumbering of the model). An element the
// model cannot describe for the purpose says why (`why`).
struct ShellFacts
{
    bool ok = false;
    std::string why;
    double thickness = 0.0;
    double z1 = 0.0; // the fibre distances of the property
    double z2 = 0.0;
    double e = 0.0;
    double nu = 0.0;
    double g = 0.0;
    std::int32_t pid = 0;
};

// The fibre distances Z1 and Z2 of a shell at one of its places (the centre or a corner), from the reference plane.
struct ShellFibres
{
    bool ok = false;
    double z1 = 0.0;
    double z2 = 0.0;
};

struct RodFacts
{
    bool ok = false;
    std::string why;
    double area = 0.0;
    double torsion = 0.0;     // J
    double coefficient = 0.0; // C
    double e = 0.0;
    double g = 0.0;
    std::int32_t pid = 0;
};

struct SolidFacts
{
    bool ok = false;
    std::string why;
    double e = 0.0;
    double nu = 0.0;
    double g = 0.0;
    std::int32_t pid = 0;
};

class ElementModelFacts
{
public:
    ElementModelFacts(const ResultQueryContext& context, std::size_t set);

    // True when the result set has a model at all.
    [[nodiscard]] bool hasModel() const noexcept { return m_model != nullptr; }
    // Plain shells whose property is a ShellProp with one isotropic IsoMat for membrane and bending (and no coupling).
    [[nodiscard]] const ShellFacts& shell(std::int32_t resultEid);
    // The fibre distances of a shell at its centre (`nodeId` 0) or at the corner of the grid point `nodeId`, whatever
    // its material: Z1 and Z2 of a ShellProp, a blank one -t/2 or +t/2 of the thickness at the place (the corner
    // thickness of the element card, the mean of the corners at the centre, else the thickness of the property); -T/2
    // and +T/2 of the total thickness of a laminate. Not ok when the model does not say (no model, an element that is
    // not linked, another property, no thickness, a grid point that is not a corner of the element).
    [[nodiscard]] ShellFibres shellFibres(std::int32_t resultEid, std::int32_t nodeId);
    // Rods (Rod2, Rod2InlineSection) with a RodProp and an IsoMat.
    [[nodiscard]] const RodFacts& rod(std::int32_t resultEid);
    // Solids with a SolidProp and an IsoMat.
    [[nodiscard]] const SolidFacts& solid(std::int32_t resultEid);

private:
    // What shellFibres needs of an element, read once: the fibre distances the property gives, and the thickness at
    // each corner (the thickness of the property where the element card gives none).
    struct ShellPlaces
    {
        bool ok = false;
        std::optional<double> z1;
        std::optional<double> z2;
        std::size_t cornerCount = 0;
        std::array<std::int32_t, 4> cornerNodes{};
        std::array<double, 4> cornerThickness{};
    };
    [[nodiscard]] const ShellPlaces& shellPlaces(std::int32_t resultEid);

    const ResultQueryContext& m_context;
    std::size_t m_set;
    const model::Model* m_model;
    std::map<std::int32_t, ShellPlaces> m_places;
    std::map<std::int32_t, ShellFacts> m_shells;
    std::map<std::int32_t, RodFacts> m_rods;
    std::map<std::int32_t, SolidFacts> m_solids;
};

} // namespace oor::query
