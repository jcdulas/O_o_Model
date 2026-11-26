#pragma once

#include "oor/analysis/validation/engine/ValidationSupport.hpp"

#include <cstdint>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// The degrees of freedom the constraint checks compare: which ones the rigid elements and the MPC equations make
// dependent, and which ones the single point constraints fix.

namespace oor::analysis
{

// A degree of freedom (a grid point and a component from 1 to 6, 0 for a scalar point) as one number.
[[nodiscard]] constexpr std::uint64_t dofKey(base::EntityId node, unsigned component) noexcept
{
    return (static_cast<std::uint64_t>(static_cast<std::uint32_t>(node)) << 3U) | component;
}
[[nodiscard]] constexpr base::EntityId nodeOfDof(std::uint64_t key) noexcept
{
    return static_cast<base::EntityId>(key >> 3U);
}
[[nodiscard]] constexpr unsigned componentOfDof(std::uint64_t key) noexcept
{
    return static_cast<unsigned>(key & 7U);
}

// A degree of freedom and the card that puts it in a set.
struct DofUse
{
    std::uint64_t key = 0;
    model::CardLocation where;
};

// The degrees of freedom a component number names at a node: the digits 1 to 6 of 123, or the one scalar degree of
// freedom (0) when the number is 0.
void appendDofs(base::EntityId node, std::int32_t components, model::CardLocation where, std::vector<DofUse>& out);

// The degrees of freedom that the rigid elements make dependent: RigidBodyStar (the GM at the components CM),
// RigidInterpolation (the reference grid, or the UM list when there is one), RigidBar and RigidRod (the CMA and CMB
// ends), RigidBodyMulti (the dependent list).
[[nodiscard]] std::vector<DofUse> rigidDependentDofs(const model::Model& model);

// A rigid element that makes a degree of freedom depend on another: every dependent degree of freedom of the element on
// every independent one (RigidBodyStar: the GM at CM on the six of GN; RigidInterpolation: the reference degrees of
// freedom, or the UM list, on the degrees of freedom of the weighted groups; RigidBodyMulti and RigidBar: the dependent
// set on the independent set; RigidRod: the dependent translation on the other translations of both ends).
struct DofLink
{
    std::uint64_t dependent = 0;
    std::uint64_t independent = 0;
    model::CardLocation where;
};
[[nodiscard]] std::vector<DofLink> rigidDofLinks(const model::Model& model);

// The degrees of freedom of the cards of each constraint set, by the set ID of the cards. The cards are read once
// for all the selections of the Case Control: a check then takes the sets of each selection with dofsOfSets().
using DofUsesBySet = std::unordered_map<base::EntityId, std::vector<DofUse>>;

// The dependent degree of freedom (the first term) of every MultiPointConstr card, by set, in row order.
[[nodiscard]] DofUsesBySet mpcDependentDofsBySet(const model::Model& model);

// The degrees of freedom fixed by the SinglePointConstr then the SinglePointConstrList cards, by set, in row order.
// Only the ones in `wanted` are kept (the dependent degrees of freedom a check compares them with): a
// SinglePointConstrList over every grid point of a large model is then not six entries a grid point. The nodes of a
// SinglePointConstrList range are the grid points that exist in it (`nodes` is the sorted list of the node IDs).
[[nodiscard]] DofUsesBySet spcDofsBySet(const model::Model& model, const std::vector<base::EntityId>& nodes,
                                        const std::unordered_set<std::uint64_t>& wanted);

// The degrees of freedom fixed by the PS field of the grid points, among `wanted`. They belong to no set: they are
// fixed whatever the Case Control selects.
[[nodiscard]] std::vector<DofUse> permanentConstraintDofs(const model::Model& model,
                                                          const std::unordered_set<std::uint64_t>& wanted);

// The degrees of freedom of the sets of one selection (sorted set IDs), set after set.
[[nodiscard]] std::vector<DofUse> dofsOfSets(const DofUsesBySet& bySet, const std::vector<base::EntityId>& sets);

} // namespace oor::analysis
