// The design model, the cases a review found: a relation whose first coefficient is the word PropertyValue and that is
// applied more than once, a field that holds no finite value (a blank transverse shear modulus, a blank corner
// thickness), a relation that gives no finite number, the stress points of a beam station that has none, and the names
// the messages give the cards. Every expected number is worked out in a comment next to it.

#include "oor/model/cards/elements/pointMassInertia/PointMassInertiaTable.hpp"
#include "oor/model/cards/elements/shellQuad4/ShellQuad4Table.hpp"
#include "oor/model/cards/elements/shellTria3/ShellTria3Table.hpp"
#include "oor/model/cards/materials/isoMat/IsoMatTable.hpp"
#include "oor/model/cards/materials/orthoMat2D/OrthoMat2DTable.hpp"
#include "oor/model/cards/optimisation/designElemRelation1/DesignElemRelation1Table.hpp"
#include "oor/model/cards/optimisation/designMatRelation1/DesignMatRelation1Table.hpp"
#include "oor/model/cards/optimisation/designPropRelation1/DesignPropRelation1Table.hpp"
#include "oor/model/cards/optimisation/designVar/DesignVarTable.hpp"
#include "oor/model/cards/properties/beamProp/BeamPropTable.hpp"
#include "oor/model/cards/properties/rodProp/RodPropTable.hpp"
#include "oor/model/cards/properties/shellProp/ShellPropTable.hpp"
#include "oor/model/design/DesignErrors.hpp"
#include "oor/model/design/DesignModel.hpp"
#include "oor/model/design/DesignUpdate.hpp"
#include "support/ExplicitTestSupport.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <cmath>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

using namespace oor;
using namespace oor::model;
using namespace oor::testing;
using Catch::Approx;
using Catch::Matchers::ContainsSubstring;

namespace
{

const std::string GRIDS = "Node;1;;0.;0.;0.\nNode;2;;1.;0.;0.\nNode;3;;1.;1.;0.\nNode;4;;0.;1.;0.\n";

// A rod, a material and a point mass, each with one field that a relation scales from the value it holds:
//   A of the RodProp 30            = A0 x1,                A0 = 5.0E-4     (DesignPropRelation1 11)
//   RHO of the IsoMat 3            = 10 + RHO0 x1 + 100 x2, RHO0 = 7850    (DesignMatRelation1 21, two terms)
//   M of the PointMassInertia 40   = M0 x1,                M0 = 2          (DesignElemRelation1 31)
const std::string PROPERTY_VALUE_DECK =
    "Node;1;;0.;0.;0.\n"
    "IsoMat;3;2.1E+11;;0.3;7850.\n"
    "RodProp;30;3;5.E-4\n"
    "PointMassInertia;40;1;;2.\n"
    "DesignVar;1;S;1.\n"
    "DesignVar;2;P;1.\n"
    "DesignPropRelation1;11;RodProp;30;area;;;;1;PropertyValue\n"
    "DesignMatRelation1;21;IsoMat;3;density;;;10.;1;PropertyValue;2;100.\n"
    "DesignElemRelation1;31;PointMassInertia;40;mass;;;;1;PropertyValue\n";

std::size_t relationIndex(const DesignModel& design, const std::string& card, base::EntityId id)
{
    for (std::size_t index = 0; index < design.relations().size(); ++index)
    {
        if (design.relations()[index].card == card && design.relations()[index].id == id)
            return index;
    }
    FAIL("no relation " << card << " " << id);
    return 0;
}

DesignPoint pointOf(const DesignModel& design, std::initializer_list<std::pair<base::EntityId, double>> values)
{
    DesignPoint point = design.initialPoint();
    for (const auto& [id, value] : values)
        point.values[*design.findVariable(id)] = value;
    return point;
}

} // namespace

TEST_CASE("a PropertyValue relation that is applied keeps the coefficient it used, so the model read again gives the "
          "same fields",
          "[model][design][review]")
{
    Model model = readBulk(PROPERTY_VALUE_DECK);
    const DesignModel design = DesignModel::read(model);
    DesignApplyOptions options;
    options.setInitialValues = true;
    const DesignUpdate update = applyDesign(model, design, pointOf(design, {{1, 1.2}, {2, 0.5}}), options);

    // A = 5.0E-4 * 1.2; RHO = 10 + 7850 * 1.2 + 100 * 0.5 = 10 + 9420 + 50; M = 2 * 1.2
    REQUIRE(cardAt<RodPropTable>(model).area == Approx(6.0e-4));
    REQUIRE(cardAt<IsoMatTable>(model).density == Approx(9480.0));
    REQUIRE(cardAt<PointMassInertiaTable>(model).mass == Approx(2.4));
    REQUIRE(cardAt<DesignVarTable>(model, 0).initialValue == 1.2);
    REQUIRE(cardAt<DesignVarTable>(model, 1).initialValue == 0.5);

    // The report: what the field held, what it holds, and that the card of the relation changed too.
    REQUIRE(update.changedFields == 3);
    const DesignFieldChange& rod = update.fields[relationIndex(design, "DesignPropRelation1", 11)];
    REQUIRE(rod.before == 5.0e-4);
    REQUIRE(rod.after == Approx(6.0e-4));
    REQUIRE(rod.changed);
    REQUIRE(rod.coefficientFrozen);

    // The cards of the relations: the word is gone and the first coefficient is the value the field held; the other
    // terms and the constant are as they were.
    const DesignPropRelation1Card property = cardAt<DesignPropRelation1Table>(model);
    REQUIRE_FALSE(property.fromProperty);
    REQUIRE(property.terms.size() == 1);
    REQUIRE(property.terms[0].coefficient == 5.0e-4);
    const DesignMatRelation1Card material = cardAt<DesignMatRelation1Table>(model);
    REQUIRE_FALSE(material.fromProperty);
    REQUIRE(material.constant0 == 10.0);
    REQUIRE(material.terms.size() == 2);
    REQUIRE(material.terms[0].coefficient == 7850.0);
    REQUIRE(material.terms[1].coefficient == 100.0);
    const DesignElemRelation1Card element = cardAt<DesignElemRelation1Table>(model);
    REQUIRE_FALSE(element.fromProperty);
    REQUIRE(element.terms[0].coefficient == 2.0);

    // The design read again, at the initial values that were saved: every relation gives the field the model holds.
    const DesignModel again = DesignModel::read(model);
    const DesignEvaluation evaluation = again.evaluate(model, again.initialPoint(), true);
    for (const DesignRelationValue& value : evaluation.relations)
    {
        REQUIRE(value.problem.empty());
        REQUIRE(value.requested == Approx(value.current));
    }
    REQUIRE(evaluation.relations[relationIndex(again, "DesignPropRelation1", 11)].requested == Approx(6.0e-4));
    REQUIRE(evaluation.relations[relationIndex(again, "DesignMatRelation1", 21)].requested == Approx(9480.0));
    REQUIRE(evaluation.relations[relationIndex(again, "DesignElemRelation1", 31)].requested == Approx(2.4));

    // The same point applied again changes nothing, not even the content version.
    const std::uint64_t version = model.contentVersion();
    const DesignUpdate second = applyDesign(model, again, pointOf(again, {{1, 1.2}, {2, 0.5}}), options);
    REQUIRE(second.changedFields == 0);
    REQUIRE(model.contentVersion() == version);
    REQUIRE(cardAt<RodPropTable>(model).area == Approx(6.0e-4));
    REQUIRE(cardAt<IsoMatTable>(model).density == Approx(9480.0));
    REQUIRE(cardAt<PointMassInertiaTable>(model).mass == Approx(2.4));
}

TEST_CASE("the model file written after a PropertyValue relation was applied carries the coefficient and starts from "
          "the design point",
          "[model][design][review]")
{
    Model model = readBulk(PROPERTY_VALUE_DECK);
    const DesignModel design = DesignModel::read(model);
    DesignApplyOptions options;
    options.setInitialValues = true;
    (void)applyDesign(model, design, pointOf(design, {{1, 1.2}, {2, 0.5}}), options);

    const std::string text = writeModelText(model);
    INFO(text);
    REQUIRE(text.find("PropertyValue") == std::string::npos);
    // The coefficient the relation used (the area 5.E-4 before the update), in the number form of the writer.
    REQUIRE(text.find("DesignPropRelation1;11;RodProp;30;area;;;;1;0.0005\n") != std::string::npos);

    // The file read as a new model: at its initial values the relations give the fields it holds.
    const Model reread = readBulk(text);
    const DesignModel design2 = DesignModel::read(reread);
    const DesignEvaluation evaluation = design2.evaluate(reread, design2.initialPoint(), true);
    REQUIRE(evaluation.relations.size() == 3);
    for (const DesignRelationValue& value : evaluation.relations)
    {
        REQUIRE(value.problem.empty());
        REQUIRE(value.requested == Approx(value.current));
    }
    REQUIRE(evaluation.relations[relationIndex(design2, "DesignPropRelation1", 11)].current == Approx(6.0e-4));
    REQUIRE(evaluation.relations[relationIndex(design2, "DesignMatRelation1", 21)].current == Approx(9480.0));
    REQUIRE(evaluation.relations[relationIndex(design2, "DesignElemRelation1", 31)].current == Approx(2.4));
}

TEST_CASE("a PropertyValue relation does not compound when a point is applied twice without saving the initial values",
          "[model][design][review]")
{
    Model model = readBulk(
        "IsoMat;3;2.1E+11;;0.3\n"
        "RodProp;30;3;5.E-4\n"
        "DesignVar;1;S;1.\n"
        "DesignPropRelation1;11;RodProp;30;area;;;;1;PropertyValue\n");
    // A = 5.0E-4 * 1.5, once: the second time the relation is 5.0E-4 x and the field already holds that.
    for (int pass = 0; pass < 3; ++pass)
    {
        const DesignModel design = DesignModel::read(model);
        const DesignUpdate update = applyDesign(model, design, pointOf(design, {{1, 1.5}}));
        REQUIRE(update.changedFields == (pass == 0 ? 1U : 0U));
        REQUIRE(cardAt<RodPropTable>(model).area == Approx(7.5e-4));
        REQUIRE(cardAt<DesignVarTable>(model).initialValue == 1.0); // not asked for: the initial value stays
    }
    REQUIRE_FALSE(cardAt<DesignPropRelation1Table>(model).fromProperty);
    REQUIRE(cardAt<DesignPropRelation1Table>(model).terms[0].coefficient == 5.0e-4);
}

TEST_CASE("a PropertyValue relation whose value is clipped is clipped to the same value when the point is applied "
          "again",
          "[model][design][review]")
{
    // PMAX 6.0E-4 on the area: 5.0E-4 * 1.5 = 7.5E-4 is brought to 6.0E-4, both times.
    Model model = readBulk(
        "IsoMat;3;2.1E+11;;0.3\n"
        "RodProp;30;3;5.E-4\n"
        "DesignVar;1;S;1.\n"
        "DesignPropRelation1;11;RodProp;30;area;;6.E-4;;1;PropertyValue\n");
    DesignApplyOptions options;
    options.setInitialValues = true;
    const DesignModel design = DesignModel::read(model);
    const DesignUpdate first = applyDesign(model, design, pointOf(design, {{1, 1.5}}), options);
    REQUIRE(first.fields[0].requested == Approx(7.5e-4));
    REQUIRE(first.fields[0].limit == DesignLimitHit::Maximum);
    REQUIRE(cardAt<RodPropTable>(model).area == Approx(6.0e-4));

    const DesignModel again = DesignModel::read(model);
    const DesignUpdate second = applyDesign(model, again, again.initialPoint(), options);
    REQUIRE(second.fields[0].requested == Approx(7.5e-4)); // the coefficient is the 5.0E-4 of the first time
    REQUIRE(second.changedFields == 0);
    REQUIRE(cardAt<RodPropTable>(model).area == Approx(6.0e-4));
}

TEST_CASE("a PropertyValue relation whose field is not written keeps its word", "[model][design][review]")
{
    // The rod is scaled by x1, which stays at 1; the thickness follows x2, which moves.
    Model model = readBulk(
        "IsoMat;3;2.1E+11;;0.3\n"
        "ShellProp;10;3;0.2\n"
        "RodProp;30;3;5.E-4\n"
        "DesignVar;1;S;1.\n"
        "DesignVar;2;T;0.2\n"
        "DesignPropRelation1;11;RodProp;30;area;;;;1;PropertyValue\n"
        "DesignPropRelation1;12;ShellProp;10;thickness;;;;2;1.\n");
    const DesignModel design = DesignModel::read(model);
    DesignApplyOptions options;
    options.setInitialValues = true;
    const DesignUpdate update = applyDesign(model, design, pointOf(design, {{2, 0.3}}), options);
    REQUIRE(update.changedFields == 1);
    REQUIRE(cardAt<ShellPropTable>(model).thickness == Approx(0.3));
    REQUIRE(cardAt<RodPropTable>(model).area == 5.0e-4);
    const std::size_t rod = relationIndex(design, "DesignPropRelation1", 11);
    REQUIRE_FALSE(update.fields[rod].changed);
    REQUIRE_FALSE(update.fields[rod].coefficientFrozen);
    REQUIRE(cardAt<DesignPropRelation1Table>(model, 0).fromProperty);
    REQUIRE(writeModelText(model).find("DesignPropRelation1;11;RodProp;30;area;;;;1;PropertyValue\n") !=
            std::string::npos);
}

TEST_CASE("a relation writes a transverse shear modulus that was blank", "[model][design][review]")
{
    // G1Z and G2Z are blank, which the card reads as infinite. G1Z = 5.0E+9 x, x = 1.
    Model model = readBulk(
        "OrthoMat2D;2;2.4E+7;2.E+6;0.2;3.E+6\n"
        "DesignVar;1;G;1.\n"
        "DesignMatRelation1;1;OrthoMat2D;2;shearModulus1Z;;;;1;5.E+9\n");
    REQUIRE_FALSE(cardAt<OrthoMat2DTable>(model).shearModulus1Z.has_value());
    const DesignModel design = DesignModel::read(model);
    REQUIRE(design.relations()[0].applicable);
    const DesignUpdate update = applyDesign(model, design, design.initialPoint());
    REQUIRE(update.changedFields == 1);
    REQUIRE(update.fields[0].changed);
    REQUIRE(update.fields[0].before == std::numeric_limits<double>::infinity());
    REQUIRE(update.fields[0].after == Approx(5.0e9));
    const OrthoMat2DCard material = cardAt<OrthoMat2DTable>(model);
    REQUIRE(material.shearModulus1Z.has_value());
    REQUIRE(*material.shearModulus1Z == Approx(5.0e9));
    REQUIRE_FALSE(material.shearModulus2Z.has_value()); // not designed: still blank

    // The modulus is a number now: the same point leaves it alone.
    const DesignModel again = DesignModel::read(model);
    REQUIRE(applyDesign(model, again, again.initialPoint()).changedFields == 0);
}

TEST_CASE("PropertyValue on a field that holds no finite value is refused with a message", "[model][design][review]")
{
    // A blank G1Z is infinite: there is no number for the relation to scale.
    Model model = readBulk(
        "OrthoMat2D;2;2.4E+7;2.E+6;0.2;3.E+6\n"
        "DesignVar;1;G;1.2\n"
        "DesignMatRelation1;1;OrthoMat2D;2;shearModulus1Z;;;;1;PropertyValue\n");
    const DesignModel design = DesignModel::read(model);
    const DesignEvaluation evaluation = design.evaluate(model, design.initialPoint(), true);
    REQUIRE_THAT(evaluation.relations[0].problem, ContainsSubstring("DesignMatRelation1 1"));
    REQUIRE_THAT(evaluation.relations[0].problem, ContainsSubstring("PropertyValue"));
    REQUIRE_THAT(evaluation.relations[0].problem, ContainsSubstring("OrthoMat2D 2 shearModulus1Z"));
    REQUIRE(std::isnan(evaluation.relations[0].value));

    const std::uint64_t before = model.contentVersion();
    REQUIRE_THROWS_AS(applyDesign(model, design, design.initialPoint()), DesignError);
    DesignApplyOptions options;
    options.skipUnapplicable = true;
    const DesignUpdate update = applyDesign(model, design, design.initialPoint(), options);
    REQUIRE(update.skipped == std::vector<std::size_t>{0});
    REQUIRE(model.contentVersion() == before);
    REQUIRE_FALSE(cardAt<OrthoMat2DTable>(model).shearModulus1Z.has_value());
}

TEST_CASE("a linear relation that gives no finite number has a problem and is never written, whatever the limits",
          "[model][design][review]")
{
    Model model = readBulk(
        "IsoMat;3;2.1E+11;;0.3\n"
        "ShellProp;10;3;0.01\n"
        "DesignVar;1;T;0.01\n"
        "DesignPropRelation1;1;ShellProp;10;thickness;;;;1;1.\n");
    const DesignModel design = DesignModel::read(model);
    for (const double value : {std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::infinity()})
    {
        const DesignPoint point = pointOf(design, {{1, value}});
        const DesignEvaluation evaluation = design.evaluate(model, point, false);
        REQUIRE_THAT(evaluation.relations[0].problem, ContainsSubstring("DesignPropRelation1 1"));
        REQUIRE_THAT(evaluation.relations[0].problem, ContainsSubstring("no finite number"));
        REQUIRE(std::isnan(evaluation.relations[0].requested));
        for (const DesignLimitMode limits : {DesignLimitMode::Clip, DesignLimitMode::Error, DesignLimitMode::Ignore})
        {
            DesignApplyOptions options;
            options.limits = limits;
            REQUIRE_THROWS_AS(applyDesign(model, design, point, options), DesignError);
            REQUIRE(cardAt<ShellPropTable>(model).thickness == 0.01);
        }
    }
    // A finite value is applied as before.
    (void)applyDesign(model, design, pointOf(design, {{1, 0.02}}));
    REQUIRE(cardAt<ShellPropTable>(model).thickness == Approx(0.02));
}

TEST_CASE("a blank corner thickness is not a value: PropertyValue cannot start from it, a coefficient writes it",
          "[model][design][review]")
{
    // The corners of both elements are blank (they take the thickness of the ShellProp). x = 1.2.
    //   T1 of the quadrilateral, T1 of the triangle: PropertyValue, which has no number to take
    //   T2 of the quadrilateral = 0.01 x = 0.012; T3 of the triangle = 0.02 x = 0.024
    Model model = readBulk(GRIDS +
                           "IsoMat;3;2.1E+11;;0.3\n"
                           "ShellProp;10;3;0.01\n"
                           "ShellQuad4;42;10;1;2;3;4\n"
                           "ShellTria3;43;10;1;2;3\n"
                           "DesignVar;1;X;1.2\n"
                           "DesignElemRelation1;1;ShellQuad4;42;cornerThickness1;;;;1;PropertyValue\n"
                           "DesignElemRelation1;2;ShellQuad4;42;cornerThickness2;;;;1;0.01\n"
                           "DesignElemRelation1;3;ShellTria3;43;cornerThickness1;;;;1;PropertyValue\n"
                           "DesignElemRelation1;4;ShellTria3;43;cornerThickness3;;;;1;0.02\n");
    const DesignModel design = DesignModel::read(model);
    const DesignEvaluation evaluation = design.evaluate(model, design.initialPoint(), true);
    for (const std::size_t index : {std::size_t{0}, std::size_t{2}})
    {
        REQUIRE(std::isnan(evaluation.relations[index].current)); // not the -1 that marks a blank
        REQUIRE_THAT(evaluation.relations[index].problem, ContainsSubstring("PropertyValue"));
        REQUIRE_THAT(evaluation.relations[index].problem, ContainsSubstring("cornerThickness1"));
    }
    REQUIRE(evaluation.relations[1].problem.empty());
    REQUIRE(evaluation.relations[1].requested == Approx(0.012));
    REQUIRE(evaluation.relations[3].problem.empty());
    REQUIRE(evaluation.relations[3].requested == Approx(0.024));

    // Nothing is written while a relation cannot be applied.
    REQUIRE_THROWS_AS(applyDesign(model, design, design.initialPoint()), DesignError);
    REQUIRE(cardAt<ShellQuad4Table>(model).cornerThickness[1] == ShellQuad4Card::NO_THICKNESS);

    DesignApplyOptions options;
    options.skipUnapplicable = true;
    const DesignUpdate update = applyDesign(model, design, design.initialPoint(), options);
    REQUIRE(update.skipped == std::vector<std::size_t>{0, 2});
    REQUIRE(update.changedFields == 2);
    const ShellQuad4Card quad = cardAt<ShellQuad4Table>(model);
    REQUIRE(quad.cornerThickness[0] == ShellQuad4Card::NO_THICKNESS); // still blank, not -1.2
    REQUIRE(quad.cornerThickness[1] == Approx(0.012));
    const ShellTria3Card tria = cardAt<ShellTria3Table>(model);
    REQUIRE(tria.cornerThickness[0] == ShellTria3Card::NO_THICKNESS);
    REQUIRE(tria.cornerThickness[2] == Approx(0.024));
}

TEST_CASE("PropertyValue scales a corner thickness that the element gives", "[model][design][review]")
{
    // T1 = 0.02 on the card: T1 = 0.02 x = 0.03 at x = 1.5.
    Model model = readBulk(GRIDS +
                           "IsoMat;3;2.1E+11;;0.3\n"
                           "ShellProp;10;3;0.01\n"
                           "ShellQuad4;42;10;1;2;3;4;;;;;0.02\n"
                           "DesignVar;1;X;1.\n"
                           "DesignElemRelation1;1;ShellQuad4;42;cornerThickness1;;;;1;PropertyValue\n");
    REQUIRE(cardAt<ShellQuad4Table>(model).cornerThickness[0] == 0.02);
    const DesignModel design = DesignModel::read(model);
    (void)applyDesign(model, design, pointOf(design, {{1, 1.5}}));
    REQUIRE(cardAt<ShellQuad4Table>(model).cornerThickness[0] == Approx(0.03));
}

TEST_CASE("a DesignFieldConstants constant that reads a blank corner thickness has no value", "[model][design][review]")
{
    Model model = readBulk(GRIDS +
                           "IsoMat;3;2.1E+11;;0.3\n"
                           "ShellProp;10;3;0.01\n"
                           "ShellQuad4;42;10;1;2;3;4\n"
                           "DesignVar;1;X;1.\n"
                           "DesignPropRelation2;5;ShellProp;10;thickness;;;1;DesignVar;1;1;DesignConstants;1;T1\n"
                           "DesignEquation;1;F(X,B)=B*X\n"
                           "DesignFieldConstants;T1;ShellQuad4;42;cornerThickness1\n");
    const DesignModel design = DesignModel::read(model);
    std::string reason;
    REQUIRE_FALSE(design.constant(model, "T1", &reason).has_value());
    REQUIRE_THAT(reason, ContainsSubstring("ShellQuad4 42 cornerThickness1"));
    REQUIRE_THAT(reason, ContainsSubstring("blank"));
    // The equation does not receive the -1 that marks a blank: the relation says why it has no value.
    const DesignEvaluation evaluation = design.evaluate(model, design.initialPoint(), true);
    REQUIRE_THAT(evaluation.relations[0].problem, ContainsSubstring("blank"));
    REQUIRE_THROWS_AS(applyDesign(model, design, design.initialPoint()), DesignError);
    REQUIRE(cardAt<ShellPropTable>(model).thickness == 0.01);
}

TEST_CASE("the stress points of a beam station are designed only where the station writes them",
          "[model][design][review]")
{
    // BeamProp 22: end A with its line of stress points, end B that takes the points of end A.
    // BeamProp 24: end A with its line of stress points, end B that recovers no stress.
    Model model = readBulk(
        "IsoMat;3;2.1E+11;;0.3\n"
        "BeamProp;22;3;1.;2.;3.;0.;4.;0.1;;;;;;;;;YesSameAsEndA;1.;5.;6.;7.;0.;8.;0.2\n"
        "BeamProp;24;3;1.;2.;3.;0.;4.;0.1;;;;;;;;;No;1.;5.;6.;7.;0.;8.;0.2\n"
        "DesignVar;1;X;2.\n"
        "DesignPropRelation1;1;BeamProp;22;stressPointCy(EndB);;;;1;0.1\n"
        "DesignPropRelation1;2;BeamProp;22;stressPointCy(EndA);;;;1;0.1\n"
        "DesignPropRelation1;3;BeamProp;22;area(EndB);;;;1;2.\n"
        "DesignPropRelation1;4;BeamProp;24;stressPointFz(2);;;;1;0.1\n");
    const DesignModel design = DesignModel::read(model);
    const auto relation = [&](base::EntityId id) -> const DesignRelation&
    { return design.relations()[relationIndex(design, "DesignPropRelation1", id)]; };
    REQUIRE_FALSE(relation(1).applicable);
    REQUIRE(relation(1).badField);
    REQUIRE_THAT(relation(1).problem, ContainsSubstring("stressPointCy(EndB)"));
    REQUIRE_THAT(relation(1).problem, ContainsSubstring("YesSameAsEndA"));
    REQUIRE_FALSE(relation(4).applicable);
    REQUIRE_THAT(relation(4).problem, ContainsSubstring("stressOutput of this station of the BeamProp is No"));
    INFO(relation(2).problem);
    REQUIRE(relation(2).applicable); // end A has stress points of its own
    INFO(relation(3).problem);
    REQUIRE(relation(3).applicable); // a section property is there at every station

    // What is designed survives the model file: C1 of end A = 0.1 x = 0.2, A of end B = 2 x = 4.
    DesignApplyOptions options;
    options.skipUnapplicable = true;
    (void)applyDesign(model, design, design.initialPoint(), options);
    const Model reread = readBulk(writeModelText(model));
    const BeamPropCard beam = cardAt<BeamPropTable>(reread, 0);
    REQUIRE(beam.id == 22);
    REQUIRE(beam.stations[0].stressPointC[0] == Approx(0.2));
    REQUIRE(beam.stations[1].area == Approx(4.0));
}

TEST_CASE("the messages of the design model name the cards as the format does", "[model][design][review]")
{
    {
        // The DesignVarLink 1 gives the variable 4, which is not defined.
        Model model = readBulk("DesignVar;1;X;1.\nDesignVarLink;1;4;0.;1.;1;1.\n");
        const DesignModel design = DesignModel::read(model);
        REQUIRE(design.problems().size() == 1);
        REQUIRE_THAT(design.problems()[0], ContainsSubstring("DesignVarLink 1"));
        REQUIRE_THAT(design.problems()[0], ContainsSubstring("no DesignVar defines it"));
    }
    {
        // The DesignVarLink 2 gives the variable 1 from the variable 9, which is not defined.
        Model model = readBulk("DesignVar;1;X;1.\nDesignVarLink;2;1;0.;1.;9;1.\n");
        const DesignModel design = DesignModel::read(model);
        REQUIRE(design.problems().size() == 1);
        REQUIRE_THAT(design.problems()[0], ContainsSubstring("design variable 9, which no DesignVar defines"));
    }
}
