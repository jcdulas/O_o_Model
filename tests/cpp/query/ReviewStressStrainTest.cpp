// The stress and strain tables of the result queries on tables made by hand: the shell strains written as membrane
// strains and curvatures (a curvature is never listed as a strain), and the combined extremes of the ends of a bar.

#include "oor/base/threading/ThreadPool.hpp"
#include "oor/query/named/NamedQueryRegistry.hpp"
#include "oor/query/named/common/ColumnHelpers.hpp"
#include "oor/query/operators/ExecutionContext.hpp"
#include "oor/query/results/ResultSets.hpp"
#include "oor/query/table/QueryTable.hpp"
#include "oor/results/attach/ResultAttachment.hpp"
#include "support/ModelTestSupport.hpp"
#include "support/ResultTestTables.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

using namespace oor;
namespace q = oor::query;
using Catch::Approx;
using oor::testing::makeTable;
using oor::testing::makeTables;
using oor::testing::MemoryResultFile;
using oor::testing::readModelText;
using oor::testing::TableSpec;

namespace
{

// One ShellQuad4 of thickness 0.1 with blank fibre distances: its fibres are at -0.05 and +0.05.
const char* const PLATE = "IsoMat;1;2.1E+5;;0.3\n"
                          "ShellProp;1;1;0.1\n"
                          "Node;1;;0;0;0\n"
                          "Node;2;;1;0;0\n"
                          "Node;3;;1;1;0\n"
                          "Node;4;;0;1;0\n"
                          "ShellQuad4;10;1;1;2;3;4\n";

// Runs a result query on tables made by hand, attached to `model` when there is one.
std::shared_ptr<const q::QueryTable> runOnTables(const std::string& name, const std::vector<TableSpec>& specs,
                                                 const std::shared_ptr<model::Model>& model)
{
    std::vector<std::shared_ptr<results::ResultTable>> tables;
    for (const TableSpec& spec : specs)
        tables.push_back(makeTable(spec));
    q::ResultSet set;
    set.analysis = "memory";
    set.tables = makeTables(tables);
    if (model)
        set.attachment = results::ResultAttachment::attach(model, std::make_shared<MemoryResultFile>(), set.tables);
    base::ThreadPool pool(1);
    q::ExecutionContext context(&pool, nullptr, nullptr);
    const q::QueryArguments arguments;
    const q::QueryRun run{model, arguments, context, nullptr, {set}};
    return q::NamedQueryRegistry::instance().run(name, run);
}

// The strains of the centre of element 10 in the membrane-and-curvature layout: the membrane row (flag 0), then the
// curvature row (flag -1). The scalars the table stores (9 and 7) are not those of any fibre.
TableSpec membraneAndCurvature()
{
    TableSpec spec;
    spec.kind = results::ResultKind::Strain;
    spec.elementName = "ShellQuad4";
    spec.ids = {10, 10};
    spec.layers = {1, 2};
    spec.components = {"fiberCurvature", "exx", "eyy", "exy", "angle", "emax", "emin", "vonMises"};
    spec.values = {0.0,  1.0e-3, 2.0e-3,  4.0e-4, 0.0, 9.0, 9.0, 9.0,  // membrane strains
                   -1.0, 0.02,   -0.01,   0.004,  0.0, 7.0, 7.0, 7.0}; // curvatures
    return spec;
}

// The row of a table whose text column `name` holds `text`; the number of rows when there is none.
std::size_t rowWhere(const q::QueryTable& table, const std::string& name, const std::string& text)
{
    const q::QueryColumn& column = table.column(name);
    for (std::size_t row = 0; row < column.size(); ++row)
    {
        if (column.textAt(row) == text)
            return row;
    }
    return column.size();
}

} // namespace

TEST_CASE("shell strains written as membrane strains and curvatures give the strains of the two fibres",
          "[queries][results][review]")
{
    const auto model = std::make_shared<model::Model>(readModelText(PLATE));
    const auto table = runOnTables("strainTable", {membraneAndCurvature()}, model);
    REQUIRE(table->rowCount() == 2);
    const auto layers = table->column("layer").as<std::int32_t>();
    REQUIRE(layers[0] == 1);
    REQUIRE(layers[1] == 2);
    const std::vector<double> fibre = q::asDoubles(table->column("fiberDistance"));
    const std::vector<double> exx = q::asDoubles(table->column("exx"));
    const std::vector<double> eyy = q::asDoubles(table->column("eyy"));
    const std::vector<double> exy = q::asDoubles(table->column("exy"));
    // e(z) = e_membrane - z * curvature, at z = -0.05 and z = +0.05
    CHECK(fibre[0] == Approx(-0.05));
    CHECK(fibre[1] == Approx(0.05));
    CHECK(exx[0] == Approx(1.0e-3 + 0.05 * 0.02));
    CHECK(eyy[0] == Approx(2.0e-3 - 0.05 * 0.01));
    CHECK(exy[0] == Approx(4.0e-4 + 0.05 * 0.004));
    CHECK(std::fabs(exx[1]) < 1.0e-12); // 1.0e-3 - 0.05 * 0.02
    CHECK(eyy[1] == Approx(2.0e-3 + 0.05 * 0.01));
    CHECK(exy[1] == Approx(4.0e-4 - 0.05 * 0.004));
    // the principal strains and the equivalent strain are those of the fibre, computed from its components: not the
    // scalars the table stores for the membrane row (9) or for the curvature row (7)
    const std::vector<double> first = q::asDoubles(table->column("e1"));
    const std::vector<double> second = q::asDoubles(table->column("e2"));
    const std::vector<double> equivalent = q::asDoubles(table->column("vonMises"));
    for (std::size_t row = 0; row < 2; ++row)
    {
        const double centre = 0.5 * (exx[row] + eyy[row]);
        const double radius = std::hypot(0.5 * (exx[row] - eyy[row]), 0.5 * exy[row]); // exy is an engineering shear
        CHECK(first[row] == Approx(centre + radius));
        CHECK(second[row] == Approx(centre - radius).margin(1.0e-12));
        CHECK(equivalent[row] > 0.0);
        CHECK(equivalent[row] < 1.0);
    }
}

TEST_CASE("without the model the membrane strain is listed alone and the curvature never is",
          "[queries][results][review]")
{
    const auto table = runOnTables("strainTable", {membraneAndCurvature()}, nullptr);
    REQUIRE(table->rowCount() == 1);
    CHECK(table->column("layer").as<std::int32_t>()[0] == 1);
    CHECK(q::asDoubles(table->column("fiberDistance"))[0] == Approx(0.0).margin(1.0e-15)); // the reference plane
    CHECK(q::asDoubles(table->column("exx"))[0] == Approx(1.0e-3));
    CHECK(q::asDoubles(table->column("eyy"))[0] == Approx(2.0e-3));
    CHECK(q::asDoubles(table->column("exy"))[0] == Approx(4.0e-4));
    CHECK(q::asDoubles(table->column("vonMises"))[0] == Approx(9.0)); // the scalar of the membrane row, as stored
}

TEST_CASE("the o1 and o2 of a bar are the combined extremes of each end, the axial stress included",
          "[queries][results][review]")
{
    // the four values of an end are its bending stresses; the axial stress is 100
    TableSpec stored;
    stored.kind = results::ResultKind::Stress;
    stored.elementName = "Bar2";
    stored.ids = {5};
    stored.layers = {1};
    stored.components = {"s1a", "s2a", "s3a", "s4a", "axial", "smaxa", "smina", "msTension",
                         "s1b", "s2b", "s3b", "s4b", "smaxb", "sminb", "msCompression"};
    stored.values = {10.0, -10.0, 5.0, -5.0, 100.0, 110.0, 90.0, 0.0, 20.0, -20.0, 0.0, 0.0, 120.0, 80.0, 0.0};
    // the same bar in a table that does not store the extremes: they are the axial stress plus the extreme bending one
    TableSpec plain = stored;
    plain.components = {"s1a", "s2a", "s3a", "s4a", "axial", "s1b", "s2b", "s3b", "s4b"};
    plain.values = {10.0, -10.0, 5.0, -5.0, 100.0, 20.0, -20.0, 0.0, 0.0};
    for (const TableSpec& spec : {stored, plain})
    {
        const auto table = runOnTables("stressTable", {spec}, nullptr);
        REQUIRE(table->rowCount() == 2);
        const std::size_t endA = rowWhere(*table, "location", "endA");
        const std::size_t endB = rowWhere(*table, "location", "endB");
        REQUIRE(endA < 2);
        REQUIRE(endB < 2);
        const std::vector<double> largest = q::asDoubles(table->column("o1"));
        const std::vector<double> smallest = q::asDoubles(table->column("o2"));
        const std::vector<double> axial = q::asDoubles(table->column("axial"));
        CHECK(largest[endA] == Approx(110.0));
        CHECK(smallest[endA] == Approx(90.0));
        CHECK(largest[endB] == Approx(120.0));
        CHECK(smallest[endB] == Approx(80.0));
        CHECK(axial[endA] == Approx(100.0));
        CHECK(axial[endB] == Approx(100.0));
    }
}
