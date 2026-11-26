// The free faces of a collapsed solid, on one element whose answer is worked out by hand.

#include "oor/analysis/adjacency/MeshAdjacency.hpp"
#include "oor/base/math/Vec3.hpp"
#include "oor/model/cards/elements/solidHexa/SolidHexaTable.hpp"
#include "support/ModelRecord.hpp"
#include "support/ModelTestSupport.hpp"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <map>
#include <string>

using namespace oor;
using namespace oor::analysis;
using namespace oor::model;
using oor::testing::modelRecord;
using oor::testing::readModelText;

TEST_CASE("the triangular free faces of a hexahedron collapsed to a wedge keep the outward order",
          "[analysis][adjacency]")
{
    // A SolidHexa with G3 = G4 and G7 = G8: a wedge between the triangles z = 0 (grid points 1, 2, 3) and z = 1 (grid
    // points 7, 6, 5 above them). The IDs are such that neither triangle is outward in increasing order: 1 2 3 turns
    // towards +z (inward for the bottom), 5 6 7 towards -z (inward for the top).
    const std::map<base::EntityId, base::Vec3> points = {{1, {0.0, 0.0, 0.0}}, {2, {1.0, 0.0, 0.0}},
                                                         {3, {0.0, 1.0, 0.0}}, {7, {0.0, 0.0, 1.0}},
                                                         {6, {1.0, 0.0, 1.0}}, {5, {0.0, 1.0, 1.0}}};
    std::string deck = "IsoMat;1;2.1E+5;;0.3\nSolidProp;2;1\n";
    base::Vec3 centre;
    for (const auto& [id, point] : points)
    {
        deck += modelRecord("Node", id, "", point.x, point.y, point.z);
        centre += point * (1.0 / 6.0);
    }
    Model model = readModelText(deck);
    // The card is added directly: a model file with a grid point named twice by an element is reported by its reader.
    SolidHexaCard card;
    card.id = 10;
    card.propId = 2;
    card.nodes = {1, 2, 3, 3, 7, 6, 5, 5};
    model.add<SolidHexaTable>(card);

    const FreeFaces faces = MeshAdjacency::freeFaces(model);
    // The two triangles and three quadrilaterals; the side G3 G4 G8 G7 is a line and no face.
    REQUIRE(faces.nodes.size() == 5);
    REQUIRE(faces.elements.size() == 5);
    using Face = std::array<base::EntityId, 4>;
    // The bottom is G1 G4 G3 G2 and the top G5 G6 G7 G8, each with its repeated grid point once.
    CHECK(std::find(faces.nodes.begin(), faces.nodes.end(), Face{1, 3, 2, 0}) != faces.nodes.end());
    CHECK(std::find(faces.nodes.begin(), faces.nodes.end(), Face{7, 6, 5, 0}) != faces.nodes.end());

    // Every face turns around its outward normal: the cross product of its first two sides points away from the
    // centre of the element.
    for (std::size_t index = 0; index < faces.nodes.size(); ++index)
    {
        const Face& face = faces.nodes[index];
        INFO("face " << face[0] << " " << face[1] << " " << face[2] << " " << face[3]);
        CHECK(faces.elements[index] == 10);
        const std::size_t count = face[3] == 0 ? 3 : 4;
        base::Vec3 middle;
        for (std::size_t corner = 0; corner < count; ++corner)
        {
            REQUIRE(points.contains(face[corner]));
            middle += points.at(face[corner]) * (1.0 / static_cast<double>(count));
        }
        const base::Vec3 normal =
            base::cross(points.at(face[1]) - points.at(face[0]), points.at(face[2]) - points.at(face[0]));
        CHECK(base::dot(normal, middle - centre) > 0.1);
    }
}
