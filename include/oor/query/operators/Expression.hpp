#pragma once

#include "oor/query/table/QueryColumn.hpp"

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace oor::query
{

// The types an expression works with: a column of any numeric type is an Int or a Double, a Bool column is a Bool, a
// text column is Text.
enum class ValueType : std::uint8_t
{
    Bool,
    Int,
    Double,
    Text
};

[[nodiscard]] std::string_view valueTypeName(ValueType type) noexcept;

// A constant of an expression.
struct Literal
{
    enum class Kind : std::uint8_t
    {
        Null,
        Bool,
        Int,
        Double,
        Text
    };

    Kind kind = Kind::Null;
    bool boolean = false;
    std::int64_t integer = 0;
    double real = 0.0;
    std::string text;

    [[nodiscard]] static Literal null() { return Literal{}; }
    [[nodiscard]] static Literal ofBool(bool value);
    [[nodiscard]] static Literal ofInt(std::int64_t value);
    [[nodiscard]] static Literal ofDouble(double value);
    [[nodiscard]] static Literal ofText(std::string value);
    [[nodiscard]] std::string toString() const;
};

// An expression over the columns of a table: the condition of a `where`, or the formula of a computed column.
//
// Text: area > 2.0 and pid in (1, 2) and not (type == 'ShellQuad4' or t <= 0.5)
//
// Values: numbers (1, 2.5, 1e-3), texts ('ShellQuad4' or "ShellQuad4"), true, false, and the names of columns.
//
// Arithmetic: + - * / % ** and unary minus, with the usual precedence (** binds tighter than unary minus on its left).
//
// Comparison: == != < <= > >= (a single = means ==, <> means !=).
//
// Logic: and, or, not (words, any case); a comparison is above `not`, `not` above `and`, `and` above `or`.
//
// Membership: x in (1, 2, 3), x not in ('A', 'B'); lists of constants only (numbers, texts, true, false, null).
//
// Null: x is null, x is not null. The word `null` is not a value to compute or compare with (`x == null` is refused,
// with the message that says to write `x is null`); it may stand in a list.
//
// Functions: abs(x), sqrt(x), isnull(x), isnan(x).
//
// A missing value (null) makes an arithmetic result or a comparison null; and/or follow the three-valued logic (false
// and null is false, true or null is true); a condition keeps the rows where it is true. A list that holds a null
// follows the same logic: a value found in it is in the list, a value not found gives a null (`x not in (1, null)`
// keeps no row). A NaN is a number: any comparison of it is false except !=.
//
// An Expression is a value (cheap to copy): the parse is shared.
class Expression
{
public:
    Expression() = default;

    // Parses `text`. Throws QueryError naming the position when it does not parse.
    [[nodiscard]] static Expression parse(std::string_view text);
    // `column == value` (a null value gives `column is null`) and `column in (values)` (a null among the values
    // follows the logic of a list that holds a null, above), built without text.
    [[nodiscard]] static Expression equals(const std::string& column, const Literal& value);
    [[nodiscard]] static Expression isIn(const std::string& column, const std::vector<Literal>& values);
    // All of `parts` must hold.
    [[nodiscard]] static Expression allOf(const std::vector<Expression>& parts);

    [[nodiscard]] bool isEmpty() const noexcept { return m_root == nullptr; }
    // The names of the columns the expression reads, once each, in order of first use.
    [[nodiscard]] const std::vector<std::string>& columns() const noexcept { return m_columns; }
    // The conditions joined by the top-level `and` (the whole expression when there is none).
    [[nodiscard]] std::vector<Expression> conjuncts() const;
    // The expression as text, fully parenthesised.
    [[nodiscard]] std::string toString() const;
    // True when the expression is only a column name.
    [[nodiscard]] std::optional<std::string> asColumnName() const;

    // The type of the result, given the type of each column (nullopt for a column that is not usable in an expression:
    // a list). Throws QueryTypeError when an operator gets operands it cannot take.
    [[nodiscard]] ValueType resultType(
        const std::function<std::optional<ColumnType>(const std::string&)>& typeOfColumn) const;

    struct Node;
    [[nodiscard]] const std::shared_ptr<const Node>& root() const noexcept { return m_root; }

private:
    std::shared_ptr<const Node> m_root;
    std::vector<std::string> m_columns;
};

} // namespace oor::query
