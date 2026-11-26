#include "oor/analysis/validation/engine/ValidationEngine.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_test_macros.hpp>

#include <map>
#include <string>

using namespace oor;
using namespace oor::analysis;
using oor::testing::readModelText;

namespace
{

const char* const MODULUS = "compat.iso-mat-modulus";
const char* const POISSON = "compat.iso-mat-poisson";
const char* const POISSON_DERIVED = "compat.iso-mat-poisson-derived";
const char* const SHEAR_MODULUS = "compat.iso-mat-shear-modulus";
const char* const SHEAR_MODULUS_BLANK = "compat.iso-mat-shear-modulus-blank";

using Findings = std::map<std::string, base::Severity>;

// What the checks of the isotropic material say of a model file given as text: each code found, with its severity.
Findings materialFindings(const std::string& text)
{
    const model::Model model = readModelText(text);
    ValidationOptions options;
    options.select = {MODULUS, POISSON, POISSON_DERIVED, SHEAR_MODULUS, SHEAR_MODULUS_BLANK};
    Findings found;
    for (const ValidationFinding& finding : ValidationEngine::run(model, options).findings)
        found[finding.code] = finding.severity;
    return found;
}

const char* const SHELL = "ShellProp;1;1;0.1\n";
const char* const BAR = "BarProp;1;1;0.02;1.E-5;1.E-5;1.E-5\n";

} // namespace

TEST_CASE("an isotropic material given by its shear modulus alone is legal", "[validation][compatibility][review]")
{
    // E and NU blank: the material of a shear panel. The zero the card holds for E is not a value it gave.
    REQUIRE(materialFindings("IsoMat;1;;2.7E+4\nShearPanelProp;2;1;0.3\n").empty());
    // E blank with G and NU: E follows from them.
    REQUIRE(materialFindings(std::string("IsoMat;1;;2.7E+4;0.3\n") + SHELL).empty());
}

TEST_CASE("a Young modulus that the material gives must be positive", "[validation][compatibility][review]")
{
    // The shear modulus derived from the negative modulus is not judged as well.
    REQUIRE(materialFindings(std::string("IsoMat;1;-5.;;0.3\n") + SHELL) == Findings{{MODULUS, base::Severity::Error}});
    REQUIRE(materialFindings(std::string("IsoMat;1;0.;2.7E+4;0.3\n") + SHELL) ==
            Findings{{MODULUS, base::Severity::Error}});
}

TEST_CASE("a Poisson ratio that the material gives is accepted up to 0.5", "[validation][compatibility][review]")
{
    REQUIRE(materialFindings(std::string("IsoMat;1;2.1E+5;;0.5\n") + SHELL).empty());
    REQUIRE(materialFindings(std::string("IsoMat;1;2.1E+5;;0.\n") + SHELL).empty());
    REQUIRE(materialFindings(std::string("IsoMat;1;2.1E+5;;0.6\n") + SHELL) ==
            Findings{{POISSON, base::Severity::Error}});
    REQUIRE(materialFindings(std::string("IsoMat;1;2.1E+5;;-1.\n") + SHELL).contains(POISSON));
}

TEST_CASE("a Poisson ratio derived from the two moduli is a warning, not an error",
          "[validation][compatibility][review]")
{
    // E = 1000 and G = 50 with NU blank: NU = E / (2 G) - 1 = 9, on a field the card did not give.
    REQUIRE(materialFindings(std::string("IsoMat;1;1000.;50.\n") + BAR) ==
            Findings{{POISSON_DERIVED, base::Severity::Warning}});
    // Moduli that give a ratio in the range say nothing: E = 2.6 G gives 0.3, E = 3 G gives 0.5.
    REQUIRE(materialFindings(std::string("IsoMat;1;2.6E+5;1.E+5\n") + BAR).empty());
    REQUIRE(materialFindings(std::string("IsoMat;1;3.E+5;1.E+5\n") + BAR).empty());
}

TEST_CASE("a blank shear modulus is a warning where a property needs it, a zero one given is an error",
          "[validation][compatibility][review]")
{
    // E alone: G and NU are zero. Legal for a rod, a warning for a bar.
    REQUIRE(materialFindings("IsoMat;1;2.1E+5\nRodProp;3;1;1.\n").empty());
    REQUIRE(materialFindings(std::string("IsoMat;1;2.1E+5\n") + BAR) ==
            Findings{{SHEAR_MODULUS_BLANK, base::Severity::Warning}});
    // A shear modulus of zero written on the card, used by a shell; a negative one, used by nothing.
    REQUIRE(materialFindings(std::string("IsoMat;1;2.1E+5;0.;0.3\n") + SHELL) ==
            Findings{{SHEAR_MODULUS, base::Severity::Error}});
    REQUIRE(materialFindings("IsoMat;1;2.1E+5;-8.E+4;0.3\n") == Findings{{SHEAR_MODULUS, base::Severity::Error}});
}
