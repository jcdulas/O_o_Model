#include "oor/model/cards/elements/shellQuad4/ShellQuad4DesignFields.hpp"

#include "oor/model/cards/elements/shellQuad4/ShellQuad4Table.hpp"
#include "oor/model/design/DesignFieldNames.hpp"
#include "oor/model/design/TableDesignFields.hpp"

#include <limits>

namespace oor::model
{

namespace
{

enum ShellQuad4Kind : std::int32_t
{
    Offset,
    CornerThickness, // T1 to T4: `index` 0 to 3
};

// The neutral field descriptors a relation can drive.
constexpr const char* DESIGNABLE =
    "offset, cornerThickness1, cornerThickness2, cornerThickness3, "
    "cornerThickness4";

DesignFieldLookup findField(const ShellQuad4Card&, const DesignField& field)
{
    if (field.name == "offset")
        return DesignFieldLookup::found(designFacts(Offset, "offset", DesignLowerLimit::Signed));
    if (field.name == "cornerThickness1" || field.name == "cornerThickness2" || field.name == "cornerThickness3" ||
        field.name == "cornerThickness4")
        return DesignFieldLookup::found(designFacts(CornerThickness, field.name, DesignLowerLimit::Positive,
                                                    DesignMassEffect::Nonlinear, field.name.back() - '1'));
    return DesignFieldLookup::refused(refusalOfField("ShellQuad4", field, DESIGNABLE));
}

// A blank corner thickness is kept as NO_THICKNESS, which is a mark and not a thickness: the element then has the
// thickness of its property, which these functions do not see. It reads as NaN, the "no value" of DesignableCard::read,
// so that the mark never becomes the coefficient of a PropertyValue relation or the constant of an equation (both are
// refused with a message); a relation that gives the corner a thickness writes it as before.
double readField(const ShellQuad4Card& card, const DesignFieldFacts& facts)
{
    if (facts.kind == Offset)
        return card.offset;
    const double thickness = card.cornerThickness[static_cast<std::size_t>(facts.index)];
    return thickness == ShellQuad4Card::NO_THICKNESS ? std::numeric_limits<double>::quiet_NaN() : thickness;
}

void writeFields(ShellQuad4Card& card, std::span<const DesignFieldValue> values)
{
    for (const DesignFieldValue& item : values)
    {
        if (item.facts->kind == Offset)
            card.offset = item.value;
        else
            card.cornerThickness[static_cast<std::size_t>(item.facts->index)] = item.value;
    }
}

// The contract columns: offset (ZOFFS), and the vector cornerThickness (T1 to T4).
DesignColumn columnOf(const ShellQuad4Card&, const DesignFieldFacts& facts)
{
    if (facts.kind == Offset)
        return {"offset"};
    return {"cornerThickness", facts.index};
}

} // namespace

const DesignableCard& shellQuad4DesignFields()
{
    static const TableDesignFields<ShellQuad4Table> FIELDS("ShellQuad4",
                                                          {&findField, &readField, &writeFields, &columnOf});
    return FIELDS;
}

} // namespace oor::model
