#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <string>
#include <string_view>

namespace oor::model
{

// The subroutine an UserFailureModel names when its UNAME is blank: the standard user defined failure.
inline constexpr std::string_view USER_FAILURE_MODEL_DEFAULT_ROUTINE_NAME = "ExternalFailure";

// One UserFailureModel card (SOL 700): a failure model that a user subroutine computes. The FMS statement CONNECT
// SERVICE names the group of the routines; the card gives the group and the routine. The model is named by an EulerMat
// (the format reference adds an IsoMat and an OrthoMat3DNonlinear). The routines the format reference lists are EXFAIL
// (standard), EXFAIL1 (alternative 1, with OrthoMat3DNonlinear only) and EXFAIL2 (alternative 2, which keeps a damage
// variable between 0 and 1 and serves the multi-material Euler solver with strength only); the Lagrangian materials use
// EXFAIL and EXFAIL1.
//
// Card layout: UserFailureModel  FID  GROUP  UNAME   fields 1 to 3
// FID is the number of the failure model (the format reference calls it a unique output number). GROUP is required and
// UNAME is the name of the subroutine (EXFAIL when blank); both are names of eight characters at most
// (checkYieldUserWord). The card does not match UNAME against the list nor against the material that names the model:
// those are rules of the model.
struct UserFailureModelCard
{
    base::EntityId id = 0; // unique among the failure models
    std::string groupName; // the group of the CONNECT SERVICE statement
    std::string userRoutineName{USER_FAILURE_MODEL_DEFAULT_ROUTINE_NAME};
};

} // namespace oor::model
