#pragma once

#include "oor/base/ids/EntityId.hpp"

#include <array>
#include <vector>

namespace oor::model
{

// One KIND block of a FailureMatTemperature card: the variation of the failure properties of one criterion of the
// FailureMat. Each table is the ID of a TABLEMi (0 when blank: no variation).
struct FailureMatTemperatureBlock
{
    static constexpr std::size_t TABLES = 22;

    int kind = 12;     // the type of variation: 12 is the temperature
    int criterion = 0; // the criterion of the FailureMat (for reference only)
    // T(Xt) T(Xc) T(Yt) T(Yc) T(Zt) T(Zc)  T(Sxy) T(Syz) T(Szx) T(Find) T(Fxy) T(Fyz) T(Fzx) T(Ext)
    // T(Exc) T(Eyt) T(Eyc) T(Ezt) T(Ezc) T(Gxy) T(Gyz) T(Gzx)
    std::array<base::EntityId, TABLES> tables{};
};

// One FailureMatTemperature card: the variation (with the temperature) of the failure properties of the FailureMat with
// the same ID (SOL 400).
//
// Card layout (the fields are numbered across the lines, eight to a line):
//   FailureMatTemperature  MID  (blank)  T(SB)                                   fields 1 to 3
// then, for each KIND, three lines (the last line of the last KIND may be left out):
//   KIND   CRITERIA  T(Xt)  T(Xc)  T(Yt)  T(Yc)  T(Zt)  T(Zc)
//          T(Sxy)    T(Syz) T(Szx) T(Find) T(Fxy) T(Fyz) T(Fzx) T(Ext)
//          T(Exc)    T(Eyt) T(Eyc) T(Ezt) T(Ezc) T(Gxy) T(Gyz) T(Gzx)
// T(SB) is the variation of the allowable shear stress of the bonding material between layers. KIND is 12, the
// temperature, and CRITERIA the criterion of the FailureMat that the block belongs to (for reference only). The 22
// tables of a block are kept in `tables` in that order. MID is the ID of the FailureMat, which is the ID of the
// material it extends.
struct FailureMatTemperatureCard
{
    base::EntityId id = 0; // the FailureMat (the material) that the card extends
    base::EntityId bondShearAllowableTableId = 0;
    std::vector<FailureMatTemperatureBlock> blocks;
};

} // namespace oor::model
