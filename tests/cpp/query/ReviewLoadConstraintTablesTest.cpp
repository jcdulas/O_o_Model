// The tables of constraints and line loads on small models: a range of a SinglePointConstrList reaches the scalar
// points that lie in it, and a blank P2 of a BeamDistributedLoad is P1.

#include "oor/query/named/NamedQueryRegistry.hpp"
#include "oor/query/named/common/ColumnHelpers.hpp"
#include "oor/query/operators/ExecutionContext.hpp"
#include "oor/query/table/QueryTable.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

using namespace oor;
namespace q = oor::query;
using Catch::Approx;
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

std::vector<std::int32_t> intsOf(const q::QueryTable& table, const std::string& name)
{
    const auto values = table.column(name).as<std::int32_t>();
    return {values.begin(), values.end()};
}

} // namespace

TEST_CASE("a range of a SinglePointConstrList reaches the scalar points in it when its components are blank",
          "[queries][constraints][review]")
{
    // set 7 constrains a range of scalar points (component 0); set 8 the components 123 of a range that holds the
    // three grid points and, by their IDs, the scalar points: a scalar point has no component 1, 2 or 3
    const auto table = runNamed("singlePointConstrTable", "Node;1;;0.;0.;0.\n"
                                                          "Node;2;;1.;0.;0.\n"
                                                          "Node;3;;2.;0.;0.\n"
                                                          "ScalarPoint;101;102;103\n"
                                                          "SinglePointConstrList;7;0;101;Through;103\n"
                                                          "SinglePointConstrList;8;123;1;Through;200\n");
    REQUIRE(table->rowCount() == 6);
    CHECK(intsOf(*table, "setId") == std::vector<std::int32_t>{7, 7, 7, 8, 8, 8});
    CHECK(intsOf(*table, "nodeId") == std::vector<std::int32_t>{101, 102, 103, 1, 2, 3});
    const q::QueryColumn& dof = table->column("dof");
    CHECK(dof.textAt(0).empty()); // the one degree of freedom of a scalar point
    CHECK(dof.textAt(3) == "123");
}

TEST_CASE("a blank P2 of a BeamDistributedLoad is P1: a uniform load", "[queries][loads][review]")
{
    // set 28 leaves P2 blank with X2 given; set 29 gives P2 = 0, a load that falls to nothing
    const auto table = runNamed("lineLoadsTable", "BeamDistributedLoad;28;12;MomentZ;ProjectedLength;0.5;1.;2.5\n"
                                                  "BeamDistributedLoad;29;12;ForceZ;ActualLength;0.;3.;2.;0.\n");
    REQUIRE(table->rowCount() == 2);
    CHECK(intsOf(*table, "setId") == std::vector<std::int32_t>{28, 29});
    const std::vector<double> first = q::asDoubles(table->column("p1"));
    const std::vector<double> second = q::asDoubles(table->column("p2"));
    CHECK(first[0] == Approx(1.0));
    CHECK(second[0] == Approx(1.0));
    CHECK(first[1] == Approx(3.0));
    CHECK(second[1] == Approx(0.0).margin(1.0e-15));
    CHECK_FALSE(table->column("isConcentrated").boolAt(0));
}
