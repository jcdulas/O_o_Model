#include <oor/api/CardEdits.hpp>
#include <oor/formats/oos.hpp>
#include <oos/api/ModelFromDeck.hpp>
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <numeric>

using Clock = std::chrono::steady_clock;
using Field = oor::model::FieldValue;
Field real(double x) { return {Field::Kind::Real, 0, x, {}}; }

int main(int argc, char** argv)
{
    const bool shell = argc == 2;
    std::vector<std::int32_t> ids(shell ? 20301 : 200000), selected(1000);
    std::iota(ids.begin(), ids.end(), 1);
    std::vector<double> x(ids.size()), xyz(3 * selected.size());
    for (std::size_t i = 0; i < ids.size(); ++i)
        x[i] = i * 0.00123456789;
    for (std::size_t i = 0; i < selected.size(); ++i) {
        const auto row = (shell ? 19 : 199)*i;
        selected[i] = ids[row];
        xyz[3*i] = shell ? static_cast<double>(row % 201) : -static_cast<double>(i+1);
        if (shell) {
            xyz[3*i+1] = static_cast<double>(row / 201);
            xyz[3*i+2] = 0.001;
        }
    }
    auto start = Clock::now();
    auto deck = shell ? oor::formats::oos::read(argv[1], {.strict = true}) : oor::api::Deck::createModel();
    if (!shell) oor::api::insertCardBatch(*deck, "Node", ids.size(), [&](std::size_t i) {
        return oor::api::CardInput{"Node", {{Field::Kind::Integer, ids[i], 0., {}}, {}, real(x[i]), real(0), real(0)}};
    });
    auto built = Clock::now();
    auto trial = deck->copy();
    auto copied = Clock::now();
    oor::api::setNodePositions(*trial, selected, xyz);
    auto edited = Clock::now();
    auto snapshot = oos::api::modelFromDeck(trial);
    auto end = Clock::now();
    auto ms = [](auto a, auto b) { return std::chrono::duration<double, std::milli>(b-a).count(); };
    std::array<double, 7> repeated{};
    for (auto& elapsed : repeated) {
        snapshot.reset();
        xyz[2] += 0.001;
        oor::api::setNodePositions(*trial, selected, xyz);
        const auto begin = Clock::now();
        snapshot = oos::api::modelFromDeck(trial);
        elapsed = ms(begin, Clock::now());
    }
    std::sort(repeated.begin(), repeated.end());
    std::cout << "{\"build_ms\":" << ms(start,built) << ",\"copy_ms\":" << ms(built,copied)
              << ",\"edit_ms\":" << ms(copied,edited) << ",\"snapshot_ms\":" << ms(edited,end)
              << ",\"repeat_snapshot_ms\":" << repeated[repeated.size()/2] << "}\n";
}
