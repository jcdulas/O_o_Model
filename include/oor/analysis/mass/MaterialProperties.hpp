#pragma once

#include "oor/model/core/Model.hpp"

#include <array>
#include <optional>
#include <string>

namespace oor::analysis
{

// The plane stress behaviour of a material, in its own axes (axis 1 along the fibres of an OrthoMat2D).
//
//   stiffness  the 3 x 3 matrix Q between the stresses (s1, s2, t12) and the engineering strains (e1, e2, g12), row by
//              row
//   shear      the transverse shear moduli G1z and G2z (the planes 1-z and 2-z); infinite for an OrthoMat2D that has no
//              transverse shear flexibility (G1Z or G2Z blank or zero)
//   density    the mass density
struct PlaneMaterial
{
    std::array<double, 9> stiffness = {};
    std::array<double, 2> shear = {};
    double density = 0.0;
};

// What the analysis needs to know of the material cards: the mass density of every kind of material that has one, and
// the plane stress law of the materials a shell ply can be made of.
class MaterialProperties
{
public:
    [[nodiscard]] static std::optional<double> density(const model::Model& model, base::EntityId mid);

    // The plane stress law of an IsoMat (E, NU, G), AnisoMat2D (the matrix G11 ... G33 itself), OrthoMat2D (E1, E2,
    // NU12, G12), or AnisoMat3D (the three-dimensional matrix reduced to plane stress: the stress through the thickness
    // is zero). nullopt for another card type or a missing material. An AnisoMat2D has one shear modulus, G33, which is
    // used for G1z and G2z.
    [[nodiscard]] static std::optional<PlaneMaterial> planeStress(const model::Model& model, base::EntityId mid);

    [[nodiscard]] static std::string planeStressCards(const model::Model& model);
};

} // namespace oor::analysis
