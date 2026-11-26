// The failure indices of a ply recomputed from its stresses: the same numbers as the solver writes in its failure index
// table (the interaction term of Hill by the sign of the product of the stresses, the F12 of Tsai-Wu as the card gives
// it), and gradients that are the derivatives of those indices.

#include "oor/query/providers/quantities/CompositeQuantities.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cmath>
#include <string>

namespace q = oor::query;
using Catch::Approx;

namespace
{

// A unidirectional ply whose compression allowables differ from the tension ones, with an interaction term.
q::PlyMaterial ply()
{
    q::PlyMaterial material;
    material.xt = 1000.0;
    material.xc = 500.0;
    material.yt = 40.0;
    material.yc = 200.0;
    material.s = 60.0;
    material.f12 = -2.0e-5;
    material.e1 = 140000.0;
    material.e2 = 10000.0;
    material.nu12 = 0.3;
    material.g12 = 5000.0;
    return material;
}

double indexOf(const std::string& theory, double s1, double s2, double t12, const q::PlyMaterial& material)
{
    return q::plyFailureIndex(theory, s1, s2, t12, material).index;
}

// The derivatives of the index by central differences.
std::array<double, 3> differences(const std::string& theory, double s1, double s2, double t12,
                                  const q::PlyMaterial& material)
{
    constexpr double STEP = 1.0e-3;
    return {(indexOf(theory, s1 + STEP, s2, t12, material) - indexOf(theory, s1 - STEP, s2, t12, material)) /
                (2.0 * STEP),
            (indexOf(theory, s1, s2 + STEP, t12, material) - indexOf(theory, s1, s2 - STEP, t12, material)) /
                (2.0 * STEP),
            (indexOf(theory, s1, s2, t12 + STEP, material) - indexOf(theory, s1, s2, t12 - STEP, material)) /
                (2.0 * STEP)};
}

} // namespace

TEST_CASE("the interaction term of Hill takes Xt or Xc by the sign of the product of the stresses",
          "[queries][composite][review]")
{
    const q::PlyMaterial m = ply();
    const double shear = (10.0 / m.s) * (10.0 / m.s);
    // tension along the fibres, compression across: the product is negative, the interaction term takes Xc
    CHECK(indexOf("hill", 100.0, -20.0, 10.0, m) ==
          Approx((100.0 / m.xt) * (100.0 / m.xt) - 100.0 * -20.0 / (m.xc * m.xc) + (20.0 / m.yc) * (20.0 / m.yc) +
                 shear));
    // both in compression: the product is positive, the interaction term takes Xt
    CHECK(indexOf("hill", -100.0, -20.0, 10.0, m) ==
          Approx((100.0 / m.xc) * (100.0 / m.xc) - 100.0 * 20.0 / (m.xt * m.xt) + (20.0 / m.yc) * (20.0 / m.yc) +
                 shear));
    // both in tension: Xt everywhere
    CHECK(indexOf("hill", 100.0, 20.0, 10.0, m) ==
          Approx((100.0 / m.xt) * (100.0 / m.xt) - 100.0 * 20.0 / (m.xt * m.xt) + (20.0 / m.yt) * (20.0 / m.yt) +
                 shear));
}

TEST_CASE("Tsai-Wu takes F12 as the card gives it, and Hoffman its interaction term over Xt Xc",
          "[queries][composite][review]")
{
    const q::PlyMaterial m = ply();
    const double s1 = 300.0;
    const double s2 = -30.0;
    const double t12 = 20.0;
    const double linear = (1.0 / m.xt - 1.0 / m.xc) * s1 + (1.0 / m.yt - 1.0 / m.yc) * s2;
    const double squares = s1 * s1 / (m.xt * m.xc) + s2 * s2 / (m.yt * m.yc) + t12 * t12 / (m.s * m.s);
    CHECK(indexOf("tsaiWu", s1, s2, t12, m) == Approx(linear + squares + 2.0 * m.f12 * s1 * s2));
    CHECK(indexOf("hoffman", s1, s2, t12, m) == Approx(linear + squares - s1 * s2 / (m.xt * m.xc)));
    // a blank F12 leaves no interaction term
    q::PlyMaterial plain = m;
    plain.f12 = 0.0;
    CHECK(indexOf("tsaiWu", s1, s2, t12, plain) == Approx(linear + squares));
}

TEST_CASE("a blank compression allowable is the tension one for the maximum strain and stress theories",
          "[queries][composite][review]")
{
    q::PlyMaterial m = ply();
    m.xc = 0.0;
    m.yc = 0.0;
    // compression along the fibres alone: the stress over Xt, as with Xc = Xt
    CHECK(indexOf("maxStress", -250.0, 0.0, 0.0, m) == Approx(250.0 / m.xt));
    // the strain along the fibres over the strain allowable Xt / E1 governs (the transverse strain of the Poisson
    // effect is a tension well below Yt / E2)
    CHECK(indexOf("maxStrain", -250.0, 0.0, 0.0, m) == Approx((250.0 / m.e1) / (m.xt / m.e1)));
}

TEST_CASE("the gradient of a failure index is the derivative of the index", "[queries][composite][review]")
{
    const q::PlyMaterial m = ply();
    for (const char* const theory : {"hill", "tsaiWu", "hoffman"})
    {
        // the two stress states where the interaction term of Hill does not take the allowable of s1
        for (const std::array<double, 3>& stress : {std::array<double, 3>{100.0, -20.0, 10.0},
                                                    std::array<double, 3>{-100.0, -20.0, 10.0},
                                                    std::array<double, 3>{300.0, 15.0, -25.0}})
        {
            const q::PlyGradient gradient = q::plyGradient(theory, stress[0], stress[1], stress[2], m);
            const std::array<double, 3> expected = differences(theory, stress[0], stress[1], stress[2], m);
            for (std::size_t k = 0; k < 3; ++k)
                CHECK(gradient.index[k] == Approx(expected[k]).epsilon(1.0e-6).margin(1.0e-12));
        }
    }
}
