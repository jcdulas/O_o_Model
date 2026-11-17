// The tables of the named queries a companion solver reads, on small models: the face a FacePressureLoad names on
// each solid shape (pressureTable, loadResultant), and the type of the columns of materialsTable whatever materials
// the model holds.

#include "oor/query/named/NamedQueryRegistry.hpp"
#include "oor/query/operators/ExecutionContext.hpp"
#include "oor/query/table/QueryTable.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

using namespace oor;
namespace q = oor::query;
using oor::testing::readModelText;

namespace
{

std::shared_ptr<const q::QueryTable> runNamed(const std::string& name, const std::string& modelText)
{
    const auto model = std::make_shared<model::Model>(readModelText(modelText));
    q::ExecutionContext context;
    const q::QueryArguments arguments;
    const q::QueryRun run{model, arguments, context, nullptr, {}};
    return q::NamedQueryRegistry::instance().run(name, run);
}

// The grid points of the face of row `row` of pressureTable.
std::vector<std::int32_t> faceOf(const q::QueryTable& table, std::size_t row)
{
    const q::QueryColumn& faces = table.column("faceNodes");
    const auto nodes = faces.child()->as<std::int32_t>();
    const auto begin = static_cast<std::size_t>(faces.listBegin(row));
    const auto length = static_cast<std::size_t>(faces.listLength(row));
    return std::vector<std::int32_t>(nodes.begin() + static_cast<std::ptrdiff_t>(begin),
                                     nodes.begin() + static_cast<std::ptrdiff_t>(begin + length));
}

using Face = std::vector<std::int32_t>;

// A pyramid on the unit square, its apex 5 above the centre, and the start of a FacePressureLoad on it.
const std::string PYRAMID = "Node;1;;0.;0.;0.\n"
                            "Node;2;;1.;0.;0.\n"
                            "Node;3;;1.;1.;0.\n"
                            "Node;4;;0.;1.;0.\n"
                            "Node;5;;0.5;0.5;1.\n"
                            "SolidPyramid;1;1;1;2;3;4;5\n"
                            "SolidProp;1;1\n"
                            "IsoMat;1;200000000000.;;0.3;7800.\n";
const std::string ON_PYRAMID = "FacePressureLoad;2;1;1000000.;;;;";

} // namespace

TEST_CASE("a FacePressureLoad names each of the five faces of a pyramid", "[queries][named][pressure]")
{
    // The base by two opposite corners, each triangle by the two corners of its edge on the base, in either order.
    const auto table = runNamed("pressureTable", PYRAMID + ON_PYRAMID + "1;3\n" + ON_PYRAMID + "4;2\n" + ON_PYRAMID +
                                                     "1;2\n" + ON_PYRAMID + "3;2\n" + ON_PYRAMID + "3;4\n" +
                                                     ON_PYRAMID + "1;4\n");
    REQUIRE(table->rowCount() == 6);
    // The corners turn for the outward normal: the base seen from below, a triangle from its base edge to the apex.
    CHECK(faceOf(*table, 0) == Face{1, 4, 3, 2});
    CHECK(faceOf(*table, 1) == Face{1, 4, 3, 2});
    CHECK(faceOf(*table, 2) == Face{1, 2, 5});
    CHECK(faceOf(*table, 3) == Face{2, 3, 5});
    CHECK(faceOf(*table, 4) == Face{3, 4, 5});
    CHECK(faceOf(*table, 5) == Face{4, 1, 5});
}

TEST_CASE("a corner and the apex of a pyramid name no face", "[queries][named][pressure]")
{
    // Their edge belongs to two triangles: the two grid points are given back as they are, not a face of the element.
    const auto table = runNamed("pressureTable", PYRAMID + ON_PYRAMID + "1;5\n" + ON_PYRAMID + "5;3\n" + ON_PYRAMID +
                                                     "2;2\n" + ON_PYRAMID + "1;9\n");
    REQUIRE(table->rowCount() == 4);
    CHECK(faceOf(*table, 0) == Face{1, 5});
    CHECK(faceOf(*table, 1) == Face{5, 3});
    CHECK(faceOf(*table, 2) == Face{2, 2});
    CHECK(faceOf(*table, 3) == Face{1, 9});
}

TEST_CASE("the same pressure on the five faces of a pyramid has no resultant", "[queries][named][pressure]")
{
    const auto table = runNamed("loadResultant", PYRAMID + ON_PYRAMID + "1;3\n" + ON_PYRAMID + "1;2\n" + ON_PYRAMID +
                                                     "2;3\n" + ON_PYRAMID + "3;4\n" + ON_PYRAMID + "4;1\n");
    REQUIRE(table->rowCount() == 1);
    const double pressure = 1.0e6;
    for (const char* name : {"fx", "fy", "fz", "mx", "my", "mz"})
    {
        INFO(name);
        CHECK(std::fabs(table->column(name).as<double>()[0]) < 1.0e-9 * pressure);
    }
}

TEST_CASE("a FacePressureLoad names the faces of the other solids as before", "[queries][named][pressure]")
{
    const std::string model = "Node;1;;0.;0.;0.\n"
                              "Node;2;;1.;0.;0.\n"
                              "Node;3;;1.;1.;0.\n"
                              "Node;4;;0.;1.;0.\n"
                              "Node;5;;0.;0.;1.\n"
                              "Node;6;;1.;0.;1.\n"
                              "Node;7;;1.;1.;1.\n"
                              "Node;8;;0.;1.;1.\n"
                              "SolidHexa;1;1;1;2;3;4;5;6;7;8\n"
                              "SolidPenta;2;1;1;2;3;5;6;7\n"
                              "SolidTetra;3;1;1;2;3;5\n"
                              "SolidProp;1;1\n"
                              "IsoMat;1;200000000000.;;0.3;7800.\n"
                              // a hexahedron: two opposite corners of the face
                              "FacePressureLoad;2;1;1.;;;;1;3\n"
                              "FacePressureLoad;2;1;1.;;;;2;7\n"
                              // a pentahedron: a triangle by one corner, a quadrilateral by two opposite corners
                              "FacePressureLoad;2;2;1.;;;;1;\n"
                              "FacePressureLoad;2;2;1.;;;;6;\n"
                              "FacePressureLoad;2;2;1.;;;;1;6\n"
                              // a tetrahedron: a corner of the face and the corner that is not on it
                              "FacePressureLoad;2;3;1.;;;;1;5\n"
                              "FacePressureLoad;2;3;1.;;;;2;1\n";
    const auto table = runNamed("pressureTable", model);
    REQUIRE(table->rowCount() == 7);
    CHECK(faceOf(*table, 0) == Face{1, 4, 3, 2});
    CHECK(faceOf(*table, 1) == Face{2, 3, 7, 6});
    CHECK(faceOf(*table, 2) == Face{1, 3, 2});
    CHECK(faceOf(*table, 3) == Face{5, 6, 7});
    CHECK(faceOf(*table, 4) == Face{1, 2, 6, 5});
    CHECK(faceOf(*table, 5) == Face{1, 3, 2});
    CHECK(faceOf(*table, 6) == Face{2, 3, 5});
}

namespace
{

const std::string ANISOTROPIC_3D =
    "AnisoMat3D;1;270000000000.;115000000000.;115000000000.;0.;0.;0.;270000000000.;115000000000.;0.;0.;0.;"
    "270000000000.;0.;0.;0.;77000000000.;0.;0.;77000000000.;0.;77000000000.;7800.;1.e-5;1.e-5;1.e-5;0.;0.;0.\n";
const std::string ANISOTROPIC_2D = "AnisoMat2D;2;80000000000.;25000000000.;0.;80000000000.;0.;30000000000.;2700.;"
                                   "2.e-5;2.e-5;0.\n";
const std::string ISOTROPIC = "IsoMat;3;200000000000.;;0.3;7800.;1.2e-5;20.\n";

// The value of a column of numbers at a row, NaN for a null.
double numberAt(const q::QueryTable& table, const char* name, std::size_t row)
{
    const q::QueryColumn& column = table.column(name);
    REQUIRE(column.type() == q::ColumnType::Float64);
    return column.isNull(row) ? std::nan("") : column.as<double>()[row];
}

} // namespace

TEST_CASE("the constants of materialsTable are numbers whatever materials the model holds", "[queries][named]")
{
    // An AnisoMat3D keeps six expansion coefficients and an AnisoMat2D three under the name an IsoMat gives to its
    // one coefficient: the column `a` stays a column of numbers, with none for the anisotropic materials.
    for (const std::string& materials :
         {ANISOTROPIC_3D, ANISOTROPIC_2D, ANISOTROPIC_3D + ANISOTROPIC_2D, ANISOTROPIC_3D + ANISOTROPIC_2D + ISOTROPIC})
    {
        INFO(materials);
        const auto table = runNamed("materialsTable", materials);
        const auto rows = static_cast<std::size_t>(table->rowCount());
        REQUIRE(rows >= 1);
        for (const char* name : {"e", "g", "nu", "density", "a", "referenceTemperature", "structuralDamping", "e1",
                                 "e2", "nu12", "g12"})
        {
            INFO(name);
            CHECK(table->column(name).type() == q::ColumnType::Float64);
        }
        const auto ids = table->column("matId").as<std::int32_t>();
        for (std::size_t row = 0; row < rows; ++row)
        {
            if (ids[row] == 3)
            {
                CHECK(numberAt(*table, "a", row) == Catch::Approx(1.2e-5));
                CHECK(numberAt(*table, "e", row) == Catch::Approx(2.0e11));
            }
            else
            {
                CHECK(std::isnan(numberAt(*table, "a", row)));
                CHECK(numberAt(*table, "density", row) == Catch::Approx(ids[row] == 1 ? 7800.0 : 2700.0));
            }
        }
    }
}
