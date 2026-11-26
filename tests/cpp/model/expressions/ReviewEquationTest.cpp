// The equations of a DesignEquation, the cases a review found: a chain of thousands of operators (A+A+A+... is a tree
// as deep as it is long) is parsed, evaluated, flattened into a program and printed without a recursion over its
// length, with the operations in the order of the text; and the message about a reserved word says what the word is.

#include "oor/model/expressions/EquationEvaluator.hpp"
#include "oor/model/expressions/EquationProgram.hpp"
#include "oor/model/expressions/EquationSet.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <span>
#include <string>
#include <vector>

using namespace oor;
using namespace oor::model;
using Catch::Approx;

namespace
{

// The longest chains of the tests: with one character for each operand and each operator the text stays under the
// 32 000 characters an equation may have.
constexpr std::size_t MANY_TERMS = 15000;

EquationSet parsed(const std::string& text)
{
    EquationParse result = parseEquations(text);
    const std::string problem = result.problem ? result.problem->message : std::string();
    INFO(problem);
    REQUIRE(result.ok());
    return std::move(*result.equations);
}

// "F(X)=X" followed by `count - 1` times `link` (an operator and its right operand).
std::string chainText(const std::string& link, std::size_t count)
{
    std::string text = "F(X)=X";
    text.reserve(text.size() + link.size() * count);
    for (std::size_t term = 1; term < count; ++term)
        text += link;
    return text;
}

// Runs a program the way its contract says (EquationProgram.hpp), for the instructions these tests make: an argument,
// a constant and the four operators. `x` is the value of the one argument.
double runProgram(const EquationProgram& program, double x)
{
    std::vector<double> stack;
    for (const EquationInstruction& instruction : program.instructions())
    {
        if (instruction.opcode == EquationOpcode::Argument)
        {
            stack.push_back(x);
            continue;
        }
        if (instruction.opcode == EquationOpcode::RealConstant || instruction.opcode == EquationOpcode::IntegerConstant)
        {
            stack.push_back(instruction.value);
            continue;
        }
        REQUIRE(stack.size() >= 2);
        const double b = stack.back();
        stack.pop_back();
        const double a = stack.back();
        stack.pop_back();
        switch (instruction.opcode)
        {
        case EquationOpcode::Add:
            stack.push_back(a + b);
            break;
        case EquationOpcode::Subtract:
            stack.push_back(a - b);
            break;
        case EquationOpcode::Multiply:
            stack.push_back(a * b);
            break;
        case EquationOpcode::Divide:
            stack.push_back(a / b);
            break;
        default:
            FAIL("an instruction the tests do not expect: " << opcodeName(instruction.opcode));
        }
    }
    REQUIRE(stack.size() == 1);
    return stack.back();
}

// Everything that walks the tree of an equation, on one text: the evaluator, the program builder and the printer, and
// the parser again on what the printer wrote. `expected` is the value at `x`, to the last bit when `exact`.
void requireEveryWalk(const std::string& text, double x, double expected, bool exact)
{
    const EquationSet set = parsed(text);
    const std::vector<double> arguments{x};
    const double value = evaluateEquations(set, std::span<const double>(arguments));
    if (exact)
    {
        REQUIRE(value == expected);
    }
    else
    {
        REQUIRE(value == Approx(expected));
    }

    // The program computes the same number with the same operations in the same order.
    const EquationProgramBuild build = buildEquationProgram(set);
    REQUIRE(build.ok());
    REQUIRE(runProgram(*build.program, x) == value);

    // The text is already in the canonical form, so the printer writes it back as it is; and what it wrote parses to
    // the same value.
    const std::string canonical = set.canonicalText();
    REQUIRE(canonical == text);
    const EquationSet again = parsed(canonical);
    REQUIRE(evaluateEquations(again, std::span<const double>(arguments)) == value);
}

} // namespace

TEST_CASE("a sum of 15 000 terms is evaluated, flattened and printed", "[model][expressions][review]")
{
    const double x = 0.1; // not a power of two: every addition rounds, so the order of the additions shows
    double expected = x;
    for (std::size_t term = 1; term < MANY_TERMS; ++term)
        expected = expected + x;
    requireEveryWalk(chainText("+X", MANY_TERMS), x, expected, true);
}

TEST_CASE("a product of 15 000 factors is evaluated, flattened and printed", "[model][expressions][review]")
{
    const double x = 1.0001; // 1.0001 ** 15000 is about 4.48: no overflow
    double expected = x;
    for (std::size_t factor = 1; factor < MANY_TERMS; ++factor)
        expected = expected * x;
    requireEveryWalk(chainText("*X", MANY_TERMS), x, expected, true);
}

TEST_CASE("long chains of subtractions and divisions group from the left", "[model][expressions][review]")
{
    {
        // X-X-X-... is (((X-X)-X)-...): -(count - 2) X, where X-(X-(X-...)) would be 0 or X.
        const double x = 0.1;
        double expected = x;
        for (std::size_t term = 1; term < MANY_TERMS; ++term)
            expected = expected - x;
        requireEveryWalk(chainText("-X", MANY_TERMS), x, expected, true);
    }
    {
        // X/X/X/... is (((X/X)/X)/...): X ** -(count - 2). 500 factors of 1.01 stay far from underflow.
        const double x = 1.01;
        const std::size_t count = 500;
        double expected = x;
        for (std::size_t factor = 1; factor < count; ++factor)
            expected = expected / x;
        requireEveryWalk(chainText("/X", count), x, expected, true);
    }
}

TEST_CASE("a long chain whose operands are chains and parentheses keeps its parentheses",
          "[model][expressions][review]")
{
    {
        // X-(X+1)-(X+1)-...: the right operand of each subtraction is a sum, which needs its parentheses.
        const double x = 0.3;
        const std::size_t count = 5000;
        double expected = x;
        for (std::size_t term = 1; term < count; ++term)
            expected = expected - (x + 1.0);
        requireEveryWalk(chainText("-(X+1)", count), x, expected, true);
    }
    {
        // X+X*X*X+X*X*X+...: a sum of products, each product a chain of its own. X + (count - 1) X**3.
        const double x = 0.5;
        const std::size_t count = 5000;
        const double expected = x + static_cast<double>(count - 1) * x * x * x;
        requireEveryWalk(chainText("+X*X*X", count), x, expected, false);
    }
    {
        // (X+X+...+X)*X: the chain is the left operand of a product, in parentheses. count X * X.
        const double x = 0.25;
        const std::size_t count = 5000;
        const std::string sum = chainText("+X", count).substr(std::string("F(X)=").size());
        requireEveryWalk("F(X)=(" + sum + ")*X", x, static_cast<double>(count) * x * x, false);
    }
}

TEST_CASE("an equation of thousands of statements, each a long chain, is evaluated", "[model][expressions][review]")
{
    // F(X)=X+X+...; G=F+F+...: two statements of 5000 terms each. G = 5000 * (5000 X).
    const std::size_t count = 5000;
    const std::string first = chainText("+X", count);
    std::string second = "G=F";
    for (std::size_t term = 1; term < count; ++term)
        second += "+F";
    const EquationSet set = parsed(first + ";" + second);
    const std::vector<double> arguments{2.0};
    REQUIRE(evaluateEquations(set, std::span<const double>(arguments)) == Approx(5000.0 * 5000.0 * 2.0));
    const EquationProgramBuild build = buildEquationProgram(set);
    REQUIRE(build.ok());
    // Each statement: `count` operands and `count - 1` additions.
    REQUIRE(build.program->instructions().size() == 2 * (2 * count - 1));
    REQUIRE(build.program->instructions().back().opcode == EquationOpcode::Add);
    REQUIRE(set.canonicalText() == first + ";" + second);
}

TEST_CASE("the limit on nesting still holds for parentheses, and what it allows is walked as before",
          "[model][expressions][review]")
{
    // X+(X+(...+(X+X)...)): each parenthesis is the right operand of a sum, which the walkers reach by recursion. 90
    // levels are within the limit of the parser.
    const std::size_t levels = 90;
    std::string text = "F(X)=";
    for (std::size_t level = 0; level < levels; ++level)
        text += "X+(";
    text += "X+X";
    text += std::string(levels, ')');
    const double x = 0.1;
    double expected = x + x;
    for (std::size_t level = 0; level < levels; ++level)
        expected = x + expected;
    requireEveryWalk(text, x, expected, true);

    // 150 levels are more than the parser allows: a problem, not a crash.
    std::string deep = "F(X)=";
    for (std::size_t level = 0; level < 150; ++level)
        deep += "X+(";
    deep += "X+X";
    deep += std::string(150, ')');
    const EquationParse refused = parseEquations(deep);
    REQUIRE_FALSE(refused.ok());
    REQUIRE(refused.problem.has_value());
    REQUIRE(refused.problem->message.find("nested") != std::string::npos);
}

TEST_CASE("a reserved word used as a name is refused in the words of the format", "[model][expressions][review]")
{
    for (const std::string word : {"NOT", "AND", "OR", "XOR", "XQV"})
    {
        const EquationParse result = parseEquations("F(" + word + ")=" + word);
        INFO(word);
        REQUIRE_FALSE(result.ok());
        REQUIRE(result.problem.has_value());
        const std::string& message = result.problem->message;
        INFO(message);
        REQUIRE(message.find("\"" + word + "\" is a reserved word") != std::string::npos);
        REQUIRE(message.find("cannot be the name of a variable") != std::string::npos);
    }
}
