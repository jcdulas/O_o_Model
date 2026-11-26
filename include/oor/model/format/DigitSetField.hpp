#pragma once

#include "oor/base/text/DigitSets.hpp"
#include "oor/model/format/FieldReader.hpp"

#include <cstdint>
#include <string>

namespace oor::model
{

// True when the decimal digits of a positive value hold a digit twice or a zero: the two things base::sortedDigits
// removes without a word. (A positive value starts with a digit that is not zero, so a zero is always a zero among
// other digits.)
[[nodiscard]] constexpr bool hasRepeatedOrZeroDigit(std::int32_t value) noexcept
{
    bool seen[10] = {};
    for (std::int32_t rest = value; rest > 0; rest /= 10)
    {
        const std::int32_t digit = rest % 10;
        if (digit == 0 || seen[digit])
            return true;
        seen[digit] = true;
    }
    return false;
}

// The digits of a set written as one integer (the components of a degree-of-freedom list, pin flags, permanent
// constraints), sorted: `321` is kept as `123`. `raw` is the field as the reader gave it, `name` its field name.
//
// A digit given twice, or a zero among other digits, is reported on the field before the sort, which would hide both:
// `1123` is not the set {1, 2, 3} and `10` is not the set {1}. The raw value is then returned as it is; the reader has
// failed, so the card is dropped.
// 0 alone and a negative value pass through unchanged, and a digit outside the range of the field (a 7 among
// components) is not judged here: the check() of each card decides those.
[[nodiscard]] inline std::int32_t sortedDigitSet(FieldReader& reader, std::int32_t raw, const char* name)
{
    if (raw > 0 && hasRepeatedOrZeroDigit(raw))
    {
        reader.error("card.bad-value",
                     reader.fieldLabel(name) + " must give each digit at most once, and no zero among other digits (" +
                         std::to_string(raw) + " given)",
                     name);
        return raw;
    }
    return base::sortedDigits(raw);
}

} // namespace oor::model
