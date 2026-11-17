#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <cstddef>
#include <string>
#include <string_view>

namespace oor::model
{

// The subroutine a PorousUserBoundary uses when UNAME is blank: the standard user defined flow boundary on the coupling
// surface.
inline constexpr std::string_view POROUS_USER_BOUNDARY_DEFAULT_ROUTINE_NAME = "ExternalPorosity";

// GROUP and UNAME are names of at most this many characters.

// One PorousUserBoundary card (SOL 700): a porosity model of an EulerLagrangeCoupling surface written by the user as a
// subroutine, served by a user defined service. A GasBagLeakage of PORTYPE PorousUserBoundary names it. The File
// Management Section connects the group to the service (CONNECT SERVICE group 'path of the service'): the card carries
// the group and the subroutine name only.
//
// Card layout: PorousUserBoundary  PID  GROUP  UNAME  fields 1 to 3
// GROUP is the group name of the CONNECT SERVICE statement; the format gives it no default and no "required", but a
// service with no group could not be connected, so the card requires it. UNAME is the name of the user subroutine,
// EXPOR when blank (the one subroutine the format lists). Both are words of 8 characters at most; the solver reads a
// field without regard to the case, so the card keeps them in capitals, which is also what Python's setters do. The
// name is stored resolved (EXPOR) and written even when it is the default.
struct PorousUserBoundaryCard
{
    base::EntityId id = 0; // unique among the PorousUserBoundary cards
    std::string groupName;
    std::string userRoutineName{POROUS_USER_BOUNDARY_DEFAULT_ROUTINE_NAME};
};

} // namespace oor::model
