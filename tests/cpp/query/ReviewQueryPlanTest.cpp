// The query engine on small tables made by hand: a left join on a column of lists keeps the rows that hold no ID, a
// query on a table keeps the contract version of the table, and a list that holds a null follows the three-valued
// logic.

#include "QueryTestSupport.hpp"
#include "oor/query/QueryErrors.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <cstdint>
#include <memory>
#include <vector>

namespace q = oor::query;
using q::testing::runOn;

namespace
{

// Three rows whose `refs` lists hold two IDs, none and one.
std::shared_ptr<const q::QueryTable> rowsWithLists()
{
    auto table = std::make_shared<q::QueryTable>();
    table->addColumn("id", q::QueryColumn::primitive(std::vector<std::int32_t>{1, 2, 3}));
    q::QueryColumn refs = q::QueryColumn::list(q::ColumnBuffer::adopt(std::vector<std::int64_t>{0, 2, 2, 3}),
                                               q::QueryColumn::primitive(std::vector<std::int32_t>{10, 20, 30}), 3);
    table->addColumn("refs", std::move(refs));
    return table;
}

// The table the IDs of `refs` are looked up in.
std::shared_ptr<const q::QueryTable> weights()
{
    auto table = std::make_shared<q::QueryTable>();
    table->addColumn("key", q::QueryColumn::primitive(std::vector<std::int32_t>{10, 20, 30}));
    table->addColumn("weight", q::QueryColumn::primitive(std::vector<double>{1.5, 2.5, 3.5}));
    return table;
}

std::vector<std::int32_t> idsOf(const q::QueryTable& table)
{
    const auto values = table.column("id").as<std::int32_t>();
    return {values.begin(), values.end()};
}

// A table of one column `x`: 1, 2, 3 and a null.
std::shared_ptr<const q::QueryTable> numbersWithNull()
{
    auto table = std::make_shared<q::QueryTable>();
    table->addColumn("id", q::QueryColumn::primitive(std::vector<std::int32_t>{1, 2, 3, 4}));
    const std::vector<std::uint8_t> valid{1, 1, 1, 0};
    std::int64_t nullCount = 0;
    q::ColumnBuffer bits = q::validityFromFlags(valid, nullCount);
    table->addColumn("x",
                     q::QueryColumn::primitive(std::vector<std::int32_t>{1, 2, 3, 0}).withValidity(bits, nullCount));
    return table;
}

std::vector<std::int32_t> idsWhere(const std::string& condition)
{
    const q::Query query(std::make_shared<q::TableSource>(numbersWithNull()));
    return idsOf(*runOn(query.where(q::Expression::parse(condition)), 1));
}

} // namespace

TEST_CASE("a left join on a column of lists keeps a row that holds no ID, an inner join drops it",
          "[query][join][review]")
{
    q::JoinStep step;
    step.on = {"refs"};
    step.table = weights();
    step.tableKey = "key";
    step.how = q::JoinKind::Left;
    const q::Query query(std::make_shared<q::TableSource>(rowsWithLists()));
    const auto left = runOn(query.join(step), 1);
    // a row for each ID of a list, and one row for the list that holds none
    REQUIRE(left->rowCount() == 4);
    CHECK(idsOf(*left) == std::vector<std::int32_t>{1, 1, 2, 3});
    const q::QueryColumn& weight = left->column("weight");
    CHECK(weight.as<double>()[0] == 1.5);
    CHECK(weight.as<double>()[1] == 2.5);
    CHECK(weight.isNull(2)); // no ID: no match, the joined columns are null
    CHECK(weight.as<double>()[3] == 3.5);
    const q::QueryColumn& position = left->column("joinedPosition");
    CHECK(position.as<std::int32_t>()[0] == 1);
    CHECK(position.as<std::int32_t>()[1] == 2);
    CHECK(position.isNull(2)); // and it has no place in a list
    CHECK(position.as<std::int32_t>()[3] == 1);

    step.how = q::JoinKind::Inner;
    const auto inner = runOn(query.join(step), 1);
    REQUIRE(inner->rowCount() == 3);
    CHECK(idsOf(*inner) == std::vector<std::int32_t>{1, 1, 3});
    CHECK_FALSE(inner->column("weight").hasNulls());
    CHECK_FALSE(inner->column("joinedPosition").hasNulls());
}

TEST_CASE("a query on a table gives a table of the same data contract version", "[query][review]")
{
    auto table = std::make_shared<q::QueryTable>();
    table->addColumn("id", q::QueryColumn::primitive(std::vector<std::int32_t>{3, 1, 2}));
    table->setContractVersion(42);
    const q::Query query(std::make_shared<q::TableSource>(table));
    CHECK(runOn(query.sortBy({{"id", false}}).limit(2), 1)->contractVersion() == 42);
    // a table that says nothing of its contract stays so
    auto plain = std::make_shared<q::QueryTable>();
    plain->addColumn("id", q::QueryColumn::primitive(std::vector<std::int32_t>{3, 1, 2}));
    CHECK(runOn(q::Query(std::make_shared<q::TableSource>(plain)).limit(1), 1)->contractVersion() == 0);
}

TEST_CASE("a list that holds a null follows the three-valued logic", "[query][where][review]")
{
    // a value found is in the list; a value not found may be the null: the answer is null, and the row is not kept
    CHECK(idsWhere("x in (1, null)") == std::vector<std::int32_t>{1});
    CHECK(idsWhere("x not in (1, null)").empty());
    CHECK(idsWhere("not (x in (1, null))").empty());
    // a list without a null: the row whose x is null is not kept either way
    CHECK(idsWhere("x in (1, 2)") == std::vector<std::int32_t>{1, 2});
    CHECK(idsWhere("x not in (1, 2)") == std::vector<std::int32_t>{3});
    CHECK(idsWhere("x is null") == std::vector<std::int32_t>{4});
}

TEST_CASE("null is not a value to compare with: the message says how to ask", "[query][where][review]")
{
    CHECK_THROWS_AS(q::Expression::parse("x == null"), q::QueryError);
    CHECK_THROWS_WITH(q::Expression::parse("x == null"), Catch::Matchers::ContainsSubstring("x is null"));
    CHECK_THROWS_AS(q::Expression::parse("null + 1"), q::QueryError);
}
