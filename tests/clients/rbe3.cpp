#include <oor/api/CardEdits.hpp>
#include <oor/formats/oos.hpp>
#include <oos/api/ModelFromDeck.hpp>
#include <array>
#include <iomanip>
#include <iostream>
#include <stdexcept>

auto evaluate(const std::shared_ptr<oor::api::Deck>& deck)
{
    oos::api::OptimizationSettings settings;
    settings.analyses.statics.reset();
    settings.analyses.aeroelastic = std::vector<std::int32_t>{1};
    settings.analyses.buckling = std::vector<std::int32_t>{2};
    auto problem = oos::api::prepareOptimization(deck, settings);
    return problem->evaluate(problem->problem().initialValues());
}

std::array<double, 2> measure(oos::api::OptimizationEvaluation& point)
{
    for (const auto& response : point.evaluation().responses)
        if (response.id == 4)
            return {response.values.at(0), point.nodalCoordinateGradient(4, std::array{6}).values.at(0)};
    throw std::runtime_error("missing hinge moment");
}

int main(int argc, char** argv)
{
    if (argc != 2) return 2;
    auto source = oor::formats::oos::read(argv[1], {.strict = true});
    auto point = evaluate(source);
    const auto before = measure(*point);
    auto trial = source->copy();
    oor::api::setNodePositions(*trial, std::array{6}, std::array{.181, 1.75, 0.});
    if (!trial->checkReferences().empty()) return 1;
    const std::array results{before, measure(*evaluate(trial)), measure(*point), measure(*evaluate(source))};
    std::cout << std::setprecision(17) << '[';
    for (std::size_t i = 0; i < results.size(); ++i)
        std::cout << (i ? ",[" : "[") << results[i][0] << ',' << results[i][1] << ']';
    std::cout << "]\n";
}
