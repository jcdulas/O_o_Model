// The geometry declaration cards: SurfaceEdge (the surface is smooth or folds across a mesh edge), SurfaceFacet (a
// shell element is a flat facet) and SurfaceLine (a mesh line goes on or ends at a grid point). Per card: the fields
// of its record, the defaults, the references it lists and the number it owns, the refused values and the round trip
// through a model file. The generic tests of CardRoundTripTest.cpp read, write and copy the samples of each card.

#include "oor/model/cards/elements/shellQuad4/ShellQuad4Table.hpp"
#include "oor/model/cards/nodes/surfaceEdge/SurfaceEdgeTable.hpp"
#include "oor/model/cards/nodes/surfaceFacet/SurfaceFacetTable.hpp"
#include "oor/model/cards/nodes/surfaceLine/SurfaceLineTable.hpp"
#include "support/ExplicitTestSupport.hpp"

#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

using namespace oor;
using namespace oor::model;
using namespace oor::testing;

// ---------------------------------------------------------------------------------------------------------------------
// SurfaceEdge
// ---------------------------------------------------------------------------------------------------------------------

TEST_CASE("a SurfaceEdge declares an edge Smooth, Sharp or Raw, for the whole edge or for one element",
          "[model][cards][surface]")
{
    Model model = readBulk("Node;101\nNode;102\nNode;201\nNode;202\nNode;301\nNode;302\n"
                           "ShellQuad4;5012;1;201;202;302;301\n"
                           "SurfaceEdge;1;301;302;Smooth\nSurfaceEdge;3;201;202;Sharp;5012\nSurfaceEdge;4;101;102;Raw");
    const SurfaceEdgeCard smooth = cardAt<SurfaceEdgeTable>(model, 0);
    REQUIRE((smooth.id == 1 && smooth.node1Id == 301 && smooth.node2Id == 302));
    REQUIRE(smooth.state == "Smooth");
    REQUIRE(smooth.elementId == 0); // blank: the whole edge
    const SurfaceEdgeCard sharp = cardAt<SurfaceEdgeTable>(model, 1);
    REQUIRE((sharp.id == 3 && sharp.node1Id == 201 && sharp.node2Id == 202));
    REQUIRE((sharp.state == "Sharp" && sharp.elementId == 5012));
    const SurfaceEdgeCard raw = cardAt<SurfaceEdgeTable>(model, 2);
    REQUIRE((raw.id == 4 && raw.state == "Raw" && raw.elementId == 0));
    REQUIRE((SurfaceEdgeTable::INFO.category == CardCategory::Other &&
             SurfaceEdgeTable::INFO.idSpace == base::IdSpace::PerCardType));
    requireRoundTrip(model);

    // The two grid points are references, and the element when the card names one.
    RecordingVisitor whole;
    model.table<SurfaceEdgeTable>().visitReferences(0, whole);
    REQUIRE(whole.fields == std::vector<std::string>{"node1Id", "node2Id"});
    REQUIRE(whole.targets == std::vector<ReferenceTarget>{ReferenceTarget::Node, ReferenceTarget::Node});
    RecordingVisitor oneElement;
    model.table<SurfaceEdgeTable>().visitReferences(1, oneElement);
    REQUIRE(oneElement.fields == std::vector<std::string>{"node1Id", "node2Id", "elementId"});
    REQUIRE(oneElement.targets ==
            std::vector<ReferenceTarget>{ReferenceTarget::Node, ReferenceTarget::Node, ReferenceTarget::Element});
    // Everything the three cards name is defined; only the property of the ShellQuad4 is missing.
    REQUIRE(unresolvedIn(model) == 1);

    // A renumbering of the nodes or of the elements moves what the card names, not its own ID.
    Renumbering::apply(model, RenumberSpace::Node, Renumbering::offset(1000));
    Renumbering::apply(model, RenumberSpace::Element, Renumbering::offset(100));
    const SurfaceEdgeCard moved = cardAt<SurfaceEdgeTable>(model, 1);
    REQUIRE((moved.id == 3 && moved.node1Id == 1201 && moved.node2Id == 1202 && moved.elementId == 5112));
    REQUIRE(cardAt<SurfaceEdgeTable>(model, 0).elementId == 0); // a blank element stays blank
    REQUIRE(cardAt<ShellQuad4Table>(model).id == 5112);
    REQUIRE(unresolvedIn(model) == 1);
}

TEST_CASE("a SurfaceEdge that names missing grid points or a missing element has unresolved references",
          "[model][cards][surface]")
{
    Model model = readBulk("SurfaceEdge;1;11;12;Sharp;9");
    REQUIRE(unresolvedIn(model) == 3);
}

TEST_CASE("a SurfaceEdge refuses a missing field, an unknown state, an element with Raw and a repeated ID",
          "[model][cards][surface]")
{
    expectInvalid("SurfaceEdge", "id");
    expectInvalid("SurfaceEdge;0;301;302;Smooth", "id");
    expectInvalid("SurfaceEdge;1", "node1Id");
    expectInvalid("SurfaceEdge;1;301", "node2Id");
    expectInvalid("SurfaceEdge;1;301;-302;Smooth", "node2Id");
    expectInvalid("SurfaceEdge;1;301;301;Smooth", "node1Id"); // the two grid points are different
    expectInvalid("SurfaceEdge;1;301;302", "state");          // the state is required
    expectInvalid("SurfaceEdge;1;301;302;Rounded", "state");
    expectInvalid("SurfaceEdge;1;301;302;smooth", "state"); // a word is exact
    expectInvalid("SurfaceEdge;1;301;302;Smooth;-5", "elementId");
    expectInvalid("SurfaceEdge;1;301;302;Smooth;x", "elementId");
    expectInvalid("SurfaceEdge;4;101;102;Raw;5012", "elementId"); // a Raw edge takes no element
    expectInvalid("SurfaceEdge;1;301;302;Smooth;5012;7");         // one field too many
    // One card for an ID, whatever other cards have the number.
    REQUIRE_THROWS_AS(readBulk("SurfaceEdge;1;301;302;Smooth\nSurfaceEdge;1;201;202;Sharp"), base::DeckError);
    REQUIRE_NOTHROW(readBulk("Node;1\nSurfaceEdge;1;301;302;Smooth\nSurfaceLine;1;301;302"));
    // The same edge may be declared for the whole edge and for one of its elements: the cards have their own IDs.
    REQUIRE_NOTHROW(readBulk("SurfaceEdge;1;301;302;Smooth\nSurfaceEdge;2;301;302;Sharp;5012"));
}

// ---------------------------------------------------------------------------------------------------------------------
// SurfaceFacet
// ---------------------------------------------------------------------------------------------------------------------

TEST_CASE("a SurfaceFacet declares an element a flat facet and has one card per element", "[model][cards][surface]")
{
    Model model = readBulk("ShellQuad4;7;1;1;2;3;4\nSurfaceFacet;7\nSurfaceFacet;8");
    REQUIRE(cardAt<SurfaceFacetTable>(model, 0).elementId == 7);
    REQUIRE(cardAt<SurfaceFacetTable>(model, 1).elementId == 8);
    REQUIRE((SurfaceFacetTable::INFO.category == CardCategory::Other &&
             SurfaceFacetTable::INFO.idSpace == base::IdSpace::PerCardType));
    requireRoundTrip(model);

    // It refers to the element whose ID it carries; it does not define an element of that ID.
    RecordingVisitor visitor;
    model.table<SurfaceFacetTable>().visitReferences(0, visitor);
    REQUIRE(visitor.fields == std::vector<std::string>{"elementId"});
    REQUIRE(visitor.targets == std::vector<ReferenceTarget>{ReferenceTarget::Element});
    // The SurfaceFacet of the element 7 resolves; the one of the element 8 does not, and the ShellQuad4 misses its
    // property and its four grid points.
    REQUIRE(unresolvedIn(model) == 1 + 5);

    // A renumbering of the elements moves the card with its element.
    Renumbering::apply(model, RenumberSpace::Element, Renumbering::offset(100));
    REQUIRE(cardAt<ShellQuad4Table>(model).id == 107);
    REQUIRE(cardAt<SurfaceFacetTable>(model, 0).elementId == 107);
    REQUIRE(cardAt<SurfaceFacetTable>(model, 1).elementId == 108);
    REQUIRE(unresolvedIn(model) == 1 + 5);

    expectInvalid("SurfaceFacet", "elementId");
    expectInvalid("SurfaceFacet;0", "elementId");
    expectInvalid("SurfaceFacet;-7", "elementId");
    expectInvalid("SurfaceFacet;x", "elementId");
    expectInvalid("SurfaceFacet;7;8"); // one field too many
    REQUIRE_THROWS_AS(readBulk("SurfaceFacet;7\nSurfaceFacet;7"), base::DeckError);
}

// ---------------------------------------------------------------------------------------------------------------------
// SurfaceLine
// ---------------------------------------------------------------------------------------------------------------------

TEST_CASE("a SurfaceLine says where a mesh line goes on at a grid point, or that it ends there",
          "[model][cards][surface]")
{
    Model model = readBulk("Node;501\nNode;502\nNode;503\nSurfaceLine;1;501;502;503\nSurfaceLine;2;601;602");
    const SurfaceLineCard through = cardAt<SurfaceLineTable>(model, 0);
    REQUIRE((through.id == 1 && through.node1Id == 501 && through.throughNodeId == 502 && through.node2Id == 503));
    const SurfaceLineCard end = cardAt<SurfaceLineTable>(model, 1);
    REQUIRE((end.id == 2 && end.node1Id == 601 && end.throughNodeId == 602));
    REQUIRE(end.node2Id == 0); // blank: the mesh line ends at throughNodeId
    REQUIRE((SurfaceLineTable::INFO.category == CardCategory::Other &&
             SurfaceLineTable::INFO.idSpace == base::IdSpace::PerCardType));
    requireRoundTrip(model);

    // The grid points are references; a blank last one is not looked up.
    RecordingVisitor visitor;
    model.table<SurfaceLineTable>().visitReferences(0, visitor);
    REQUIRE(visitor.fields == std::vector<std::string>{"node1Id", "throughNodeId", "node2Id"});
    REQUIRE(visitor.targets ==
            std::vector<ReferenceTarget>{ReferenceTarget::Node, ReferenceTarget::Node, ReferenceTarget::Node});
    RecordingVisitor endVisitor;
    model.table<SurfaceLineTable>().visitReferences(1, endVisitor);
    REQUIRE(endVisitor.fields == std::vector<std::string>{"node1Id", "throughNodeId"});
    REQUIRE(unresolvedIn(model) == 2); // the grid points 601 and 602 are not defined

    // A renumbering of the nodes moves the grid points, not the ID of the card.
    Renumbering::apply(model, RenumberSpace::Node, Renumbering::offset(1000));
    const SurfaceLineCard moved = cardAt<SurfaceLineTable>(model, 0);
    REQUIRE((moved.id == 1 && moved.node1Id == 1501 && moved.throughNodeId == 1502 && moved.node2Id == 1503));
    REQUIRE(cardAt<SurfaceLineTable>(model, 1).node2Id == 0);
    REQUIRE(unresolvedIn(model) == 2);
}

TEST_CASE("a SurfaceLine refuses a missing field, a repeated grid point and a repeated ID", "[model][cards][surface]")
{
    expectInvalid("SurfaceLine", "id");
    expectInvalid("SurfaceLine;0;501;502;503", "id");
    expectInvalid("SurfaceLine;1", "node1Id");
    expectInvalid("SurfaceLine;1;501", "throughNodeId");
    expectInvalid("SurfaceLine;1;501;501;503", "node1Id"); // the first two grid points are different
    expectInvalid("SurfaceLine;1;501;502;501", "node2Id"); // the last one is a third grid point
    expectInvalid("SurfaceLine;1;501;502;502", "node2Id");
    expectInvalid("SurfaceLine;1;501;502;-3", "node2Id");
    expectInvalid("SurfaceLine;1;501;502;x", "node2Id");
    expectInvalid("SurfaceLine;1;501;502;503;504"); // one field too many
    REQUIRE_THROWS_AS(readBulk("SurfaceLine;1;501;502;503\nSurfaceLine;1;601;602"), base::DeckError);
    // Two mesh lines may pass through the same grid point: the cards have their own IDs.
    REQUIRE_NOTHROW(readBulk("SurfaceLine;1;501;502;503\nSurfaceLine;2;511;502;513"));
}
