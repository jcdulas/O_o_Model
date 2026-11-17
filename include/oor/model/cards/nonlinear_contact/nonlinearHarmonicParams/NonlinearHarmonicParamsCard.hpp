#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstdint>

namespace oor::model
{

// One NonlinearHarmonicParams card: the parameters of a nonlinear harmonic response analysis (selected by the
// NonlinearHarmonicParams Case Control command).
//
// Card layout: NonlinearHarmonicParams  ID  SUBFAC  NHARM  NLFREQ
// NLFREQ names the NonlinearHarmonicFreqList, NonlinearHarmonicFreqSteps or NonlinearHarmonicFreqContinuation card that
// lists the forcing frequencies.
struct NonlinearHarmonicParamsCard
{
    base::EntityId id = 0;
    std::int32_t subharmonicFactor = 1; // the factor that captures sub-harmonic response (1 is none)
    std::int32_t harmonicCount = 0;     // the number of harmonics of the solution
    base::EntityId freqListId = 0;
};

} // namespace oor::model
