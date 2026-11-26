// The components several SuperelementReleasedDofs cards release at one exterior point of a list superelement, on a
// deck whose answer is worked out by hand.

#include "oor/analysis/superelements/ListSuperelementPartition.hpp"
#include "oor/analysis/superelements/SuperelementCatalogue.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

using namespace oor;
using namespace oor::analysis;
using oor::testing::readModelText;

TEST_CASE("the release cards that name one exterior point release the components of all of them",
          "[analysis][superelements]")
{
    // Grid point 1 is the interior point of the list superelement 5; the rods from it make 2, 3, 4 and 6 its exterior
    // points. Point 2 is released of 4, then of 56; point 3 of 123, then of 456; point 4 of 123456 by one card; point
    // 6 of nothing.
    const model::Model model = readModelText("IsoMat;1;2.1E+5;;0.3\n"
                                             "RodProp;3;1;1.\n"
                                             "Node;1;;0.;0.;0.\n"
                                             "Node;2;;1.;0.;0.\n"
                                             "Node;3;;2.;0.;0.\n"
                                             "Node;4;;3.;0.;0.\n"
                                             "Node;6;;4.;0.;0.\n"
                                             "Rod2;10;3;1;2\n"
                                             "Rod2;11;3;1;3\n"
                                             "Rod2;12;3;1;4\n"
                                             "Rod2;13;3;1;6\n"
                                             "SuperelementInteriorNodes;5;1\n"
                                             "SuperelementReleasedDofs;5;4;2\n"
                                             "SuperelementReleasedDofs;5;56;2\n"
                                             "SuperelementReleasedDofs;5;123;3\n"
                                             "SuperelementReleasedDofs;5;456;3\n"
                                             "SuperelementReleasedDofs;5;123456;4\n");
    const SuperelementCatalogue catalogue(model);
    const ListSuperelementPartition partition(catalogue);
    REQUIRE(partition.problems().empty());
    std::vector<base::EntityId> exterior;
    for (const BoundaryLink& link : partition.links())
    {
        CHECK(link.upstream.seid == 5);
        exterior.push_back(link.upstream.nid);
    }
    REQUIRE(exterior == std::vector<base::EntityId>{2, 3, 4, 6});

    CHECK(partition.dofOf(SuperelementPoint{5, 6}) == "123456");
    // 4 and 56 leave 123
    CHECK(partition.dofOf(SuperelementPoint{5, 2}) == "123");
    // 123 and 456 leave what the one card 123456 leaves: no component
    CHECK(partition.dofOf(SuperelementPoint{5, 4}).empty());
    CHECK(partition.dofOf(SuperelementPoint{5, 3}) == partition.dofOf(SuperelementPoint{5, 4}));
}
