#pragma once

#include <cstdint>
#include <string>

namespace oor::model
{

// One DesignConstrScreen card: the screening of the constraints of one response type, to the most critical ones.
//
// Card layout: DesignConstrScreen  RTYPE  TRS  NSTR                       fields 1 to 3
// RTYPE is a response type of the DesignResp1 cards (DISP, STRESS, FREQ, ...), EQUA for the constraints of DesignResp2
// cards, DesignResp3 for those of DesignResp3 cards, or ALL for every type (then the other DesignConstrScreen cards are
// ignored). A constraint is kept only if it is above the truncation threshold TRS, and at most NSTR constraints are
// kept for each region of each load case.
struct DesignConstrScreenCard
{
    static constexpr double DEFAULT_THRESHOLD = -0.5;
    static constexpr std::int32_t DEFAULT_MAX_RETAINED = 20;

    std::string responseKind; // upper case
    double threshold = DEFAULT_THRESHOLD;
    std::int32_t maxRetained = DEFAULT_MAX_RETAINED; // > 0
};

} // namespace oor::model
