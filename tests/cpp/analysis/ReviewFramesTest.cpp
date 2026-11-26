// The frame of a solid result table that says its frame itself: a table made in memory that declares a frame is turned
// from that frame, whatever the material system of the solid properties of its elements; a table that declares nothing
// keeps the frame the properties give.

#include "oor/analysis/frames/FrameCache.hpp"
#include "oor/analysis/frames/FrameConventions.hpp"
#include "oor/analysis/frames/FrameRotation.hpp"
#include "oor/analysis/frames/StoredFrames.hpp"
#include "support/ModelTestSupport.hpp"
#include "support/ResultTestTables.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cmath>
#include <memory>
#include <string>
#include <vector>

using namespace oor;
using namespace oor::analysis;
using Catch::Approx;
using oor::testing::makeTable;
using oor::testing::makeTables;
using oor::testing::MemoryResultFile;
using oor::testing::readModelText;
using oor::testing::TableSpec;

namespace
{

// A unit cube with two hexahedra on the same grid points. Element 30 has the solid property 4, whose material system
// is the rectangular system 5: the basic system turned 90 degrees about z (its x axis is the basic y axis, its y axis
// the basic -x axis). Element 32 has the solid property 6, whose material system is the element system (-1), which is
// not a frame the results are known to be stored in.
const char* const DECK =
    "IsoMat;1;2.1E+5;;0.3\n"
    "SolidProp;4;1;5\n"
    "SolidProp;6;1;-1\n"
    "RectFrame2;5;;0.;0.;0.;0.;0.;1.;0.;1.;0.\n"
    "Node;21;;0.;0.;0.\n"
    "Node;22;;1.;0.;0.\n"
    "Node;23;;1.;1.;0.\n"
    "Node;24;;0.;1.;0.\n"
    "Node;25;;0.;0.;1.\n"
    "Node;26;;1.;0.;1.\n"
    "Node;27;;1.;1.;1.\n"
    "Node;28;;0.;1.;1.\n"
    "SolidHexa;30;4;21;22;23;24;25;26;27;28\n"
    "SolidHexa;32;6;21;22;23;24;25;26;27;28\n";

constexpr std::size_t COMPONENTS = 6;
constexpr std::int32_t TURNED_SYSTEM = 5;

// The stress of every row of the tables, in the order of the components: xx, yy, zz, xy, yz, xz.
constexpr std::array<double, COMPONENTS> STRESS = {10.0, 20.0, 30.0, 4.0, 5.0, 6.0};
// The same tensor read in a frame turned 90 degrees about z from the frame of STRESS (x' = y, y' = -x, z' = z):
//   x'x' = yy = 20, y'y' = xx = 10, z'z' = zz = 30, x'y' = -xy = -4, y'z' = -xz = -6, x'z' = yz = 5.
constexpr std::array<double, COMPONENTS> TURNED_FORWARD = {20.0, 10.0, 30.0, -4.0, -6.0, 5.0};
// And read in the frame STRESS is turned 90 degrees about z from (x = -y', y = x', z = z'):
//   xx = y'y' = 20, yy = x'x' = 10, zz = z'z' = 30, xy = -x'y' = -4, yz = x'z' = 6, xz = -y'z' = -5.
constexpr std::array<double, COMPONENTS> TURNED_BACK = {20.0, 10.0, 30.0, -4.0, 6.0, -5.0};

// A stress table of the hexahedra `elements`, every row with the values of STRESS.
std::shared_ptr<results::ResultTable> stressTable(const std::vector<std::int32_t>& elements, std::int32_t subcase)
{
    TableSpec spec;
    spec.kind = results::ResultKind::Stress;
    spec.elementName = "SolidHexa";
    spec.ids = elements;
    spec.layers.assign(elements.size(), 1);
    spec.components = {"oxx", "oyy", "ozz", "txy", "tyz", "txz"};
    for (std::size_t row = 0; row < elements.size(); ++row)
        spec.values.insert(spec.values.end(), STRESS.begin(), STRESS.end());
    spec.subcase = subcase;
    return makeTable(spec);
}

// The same table, declaring the frame of its values as a program that makes results in memory does.
std::shared_ptr<results::ResultTable> declaring(const std::shared_ptr<results::ResultTable>& table,
                                                results::StoredFrame frame)
{
    results::ResultTableMeta meta = table->meta();
    meta.storedFrame = frame;
    meta.frameSystem = 0;
    return std::make_shared<results::ResultTable>(std::move(meta), table->data());
}

struct Case
{
    std::shared_ptr<model::Model> model;
    std::shared_ptr<results::ResultTables> tables;
    std::shared_ptr<results::ResultAttachment> attachment;
    std::shared_ptr<results::ResultTable> undeclared; // element 30: its frame is the model's to say
    std::shared_ptr<results::ResultTable> declared;   // elements 30 and 32: declared in the basic system
};

Case makeCase()
{
    Case result;
    result.model = std::make_shared<model::Model>(readModelText(DECK));
    result.undeclared = stressTable({30}, 1);
    result.declared = declaring(stressTable({30, 32}, 2), results::StoredFrame::Basic);
    result.tables = makeTables({result.undeclared, result.declared});
    result.attachment = attachResults(result.model, std::make_shared<MemoryResultFile>(), result.tables);
    return result;
}

TargetFrame basic()
{
    return TargetFrame{FrameTargetKind::Basic, 0, {}};
}

TargetFrame turnedSystem()
{
    return TargetFrame{FrameTargetKind::Coordinate, TURNED_SYSTEM, {}};
}

void requireRow(const std::shared_ptr<results::ResultTable>& table, std::size_t row,
                const std::array<double, COMPONENTS>& expected)
{
    const std::shared_ptr<const results::ResultData> data = table->data();
    REQUIRE(data->componentCount == COMPONENTS);
    REQUIRE(row < data->rowCount);
    for (std::size_t component = 0; component < COMPONENTS; ++component)
    {
        INFO("row " << row << ", component " << component);
        REQUIRE(data->values<double>()[row * COMPONENTS + component] == Approx(expected[component]).margin(1e-12));
    }
}

} // namespace

TEST_CASE("a solid table that declares the basic system is not turned by the material system of its property",
          "[analysis][frames]")
{
    const Case c = makeCase();
    REQUIRE(c.declared->meta().origin == "memory");
    const StoredFrameInfo stored = StoredFrames::describe(*c.model, *c.attachment, *c.declared);
    REQUIRE(stored.kind == results::StoredFrame::Basic);

    // to the basic system: the frame the table is in, so the values stay as they are, for the element whose property
    // names the turned system and for the one whose property names no frame of the results
    const auto same = FrameRotation::rotate(*c.model, *c.attachment, *c.declared, basic());
    requireRow(same, 0, STRESS);
    requireRow(same, 1, STRESS);

    // to the turned system: xx and yy change places, for both elements alike (the frame is the table's, not the
    // property's)
    const auto turned = FrameRotation::rotate(*c.model, *c.attachment, *c.declared, turnedSystem());
    requireRow(turned, 0, TURNED_FORWARD);
    requireRow(turned, 1, TURNED_FORWARD);

    // the stored frame of every row is the basic system
    const std::vector<base::Mat3> matrices = FrameRotation::storedMatrices(*c.model, *c.attachment, *c.declared);
    REQUIRE(matrices.size() == 2);
    for (const base::Mat3& matrix : matrices)
    {
        REQUIRE(matrix.column(0).x == Approx(1.0));
        REQUIRE(matrix.column(1).y == Approx(1.0));
        REQUIRE(matrix.column(2).z == Approx(1.0));
    }
}

TEST_CASE("a solid table that declares no frame is still in the material system of its property", "[analysis][frames]")
{
    const Case c = makeCase();
    const StoredFrameInfo stored = StoredFrames::describe(*c.model, *c.attachment, *c.undeclared);
    REQUIRE(stored.kind == results::StoredFrame::Coordinate);
    REQUIRE(stored.system == TURNED_SYSTEM);

    // its values are in the turned system: unchanged to that system, turned back to the basic one
    requireRow(FrameRotation::rotate(*c.model, *c.attachment, *c.undeclared, turnedSystem()), 0, STRESS);
    requireRow(FrameRotation::rotate(*c.model, *c.attachment, *c.undeclared, basic()), 0, TURNED_BACK);
    const std::vector<base::Mat3> matrices = FrameRotation::storedMatrices(*c.model, *c.attachment, *c.undeclared);
    REQUIRE(matrices.size() == 1);
    REQUIRE(matrices[0].column(0).y == Approx(1.0));  // the x axis of the system is the basic y axis
    REQUIRE(matrices[0].column(1).x == Approx(-1.0)); // its y axis the basic -x axis
}

TEST_CASE("one frame cache serves a declared and an undeclared solid table without mixing their frames",
          "[analysis][frames]")
{
    const Case c = makeCase();
    FrameCache cache;
    const auto turn = [&](const std::shared_ptr<results::ResultTable>& table, const TargetFrame& target)
    { return FrameRotation::rotate(*c.model, *c.attachment, *table, target, nullptr, {}, &cache); };
    // the same element and the same targets, twice over: each table keeps the frames of its own case, the first time
    // (the frames are computed) and the second (they are taken from the cache)
    for (int pass = 0; pass < 2; ++pass)
    {
        requireRow(turn(c.undeclared, basic()), 0, TURNED_BACK);
        requireRow(turn(c.declared, basic()), 0, STRESS);
        requireRow(turn(c.declared, turnedSystem()), 0, TURNED_FORWARD);
        requireRow(turn(c.undeclared, turnedSystem()), 0, STRESS);
    }
}
