// The propertyType column of nonStructMassTable: the property card a row on a property names, which a reader of the
// table matches with the property card of each element (an ID alone would also reach the elements of a card of
// another type).

#include "oor/query/named/NamedQueryRegistry.hpp"
#include "oor/query/operators/ExecutionContext.hpp"
#include "oor/query/table/QueryTable.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <string>

using namespace oor;
namespace q = oor::query;
using oor::testing::readModelText;

namespace
{

std::shared_ptr<const q::QueryTable> massTableOf(const std::string& modelText)
{
    const auto model = std::make_shared<model::Model>(readModelText(modelText));
    q::ExecutionContext context;
    const q::QueryArguments arguments;
    const q::QueryRun run{model, arguments, context, nullptr, {}};
    return q::NamedQueryRegistry::instance().run("nonStructMassTable", run);
}

// A bar on a BarProp (property 1), a rod on a RodProp (property 2) and a bar on a BarShapeProp (property 3).
const std::string LINES = "Node;1;;0.;0.;0.\n"
                          "Node;2;;1.;0.;0.\n"
                          "Node;3;;2.;0.;0.\n"
                          "Node;4;;3.;0.;0.\n"
                          "Bar2;1;1;1;2;0.;;1.;0.\n"
                          "Rod2;2;2;2;3\n"
                          "Bar2;3;3;3;4;0.;;1.;0.\n"
                          "BarProp;1;1;2.;1.;2.;1.;0.\n"
                          "RodProp;2;1;2.;;;0.\n"
                          "BarShapeProp;3;1;;Tube;3.;2.;0.5\n"
                          "IsoMat;1;1000.;;0.3;1.\n";

} // namespace

TEST_CASE("nonStructMassTable names the property card of each property target", "[queries][named][mass]")
{
    const auto table = massTableOf(LINES + "NonStructMass;20;BarProp;1;2.\n"    // the card of the type named
                                           "NonStructMass;20;RodProp;2;3.\n"   // the same, another type
                                           "NonStructMass;20;BarProp;3;4.\n"); // a card that counts as the type named
    REQUIRE(table->rowCount() == 3);
    const q::QueryColumn& cards = table->column("propertyType");
    for (std::size_t row = 0; row < 3; ++row)
        CHECK_FALSE(cards.isNull(row));
    CHECK(cards.textAt(0) == "BarProp");
    CHECK(cards.textAt(1) == "RodProp");
    CHECK(cards.textAt(2) == "BarShapeProp");
}

TEST_CASE("nonStructMassTable keeps the type named for a property ID of another card", "[queries][named][mass]")
{
    // Property 2 is a RodProp and no property has the ID 9: no element has a BarProp of these IDs, and the column
    // says BarProp, which a reader matches with no element.
    const auto table = massTableOf(LINES + "NonStructMass;20;BarProp;2;2.\n"
                                           "NonStructMass;20;BarProp;9;2.\n");
    REQUIRE(table->rowCount() == 2);
    const q::QueryColumn& cards = table->column("propertyType");
    CHECK(cards.textAt(0) == "BarProp");
    CHECK(cards.textAt(1) == "BarProp");
}

TEST_CASE("nonStructMassTable gives an element target no property card", "[queries][named][mass]")
{
    const auto table = massTableOf(LINES + "NonStructMass;20;Element;1;2.\n"
                                           "NonStructMass;20;BarProp;1;2.\n");
    REQUIRE(table->rowCount() == 2);
    const q::QueryColumn& cards = table->column("propertyType");
    CHECK(cards.isNull(0));
    CHECK_FALSE(cards.isNull(1));
    CHECK(cards.textAt(1) == "BarProp");
}

TEST_CASE("nonStructMassTable names the cards of the properties ALL stands for", "[queries][named][mass]")
{
    // ALL of BarProp: the BarProp and the BarShapeProp that counts as one, by increasing ID.
    const auto table = massTableOf(LINES + "NonStructMass1;20;BarProp;2.;All\n");
    REQUIRE(table->rowCount() == 2);
    const q::QueryColumn& cards = table->column("propertyType");
    CHECK(cards.textAt(0) == "BarProp");
    CHECK(cards.textAt(1) == "BarShapeProp");
}
