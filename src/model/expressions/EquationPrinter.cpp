#include "oor/model/expressions/EquationSet.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace oor::model
{

namespace
{

// How tightly an operator binds, the lowest first. A child that binds less tightly than its place asks needs
// parentheses.
constexpr int SUM = 1;
constexpr int PRODUCT = 2;
constexpr int POWER = 3;

int precedenceOf(BinaryOperator op) noexcept
{
    switch (op)
    {
    case BinaryOperator::Add:
    case BinaryOperator::Subtract:
        return SUM;
    case BinaryOperator::Multiply:
    case BinaryOperator::Divide:
        return PRODUCT;
    case BinaryOperator::Power:
        break;
    }
    return POWER;
}

const char* symbolOf(BinaryOperator op) noexcept
{
    switch (op)
    {
    case BinaryOperator::Add:
        return "+";
    case BinaryOperator::Subtract:
        return "-";
    case BinaryOperator::Multiply:
        return "*";
    case BinaryOperator::Divide:
        return "/";
    case BinaryOperator::Power:
        break;
    }
    return "**";
}

// Writes a tree as text that reads back to the same tree. The tree has no node for a parenthesis, so the parentheses
// are found from the operators: the operators of a sum and of a product group from the left, the power from the right,
// and the sign that opens an expression takes the whole first term (-A*B is -(A*B)), so a negation anywhere else, and
// the negation of a factor, is written in parentheses.
class ExpressionPrinter
{
public:
    explicit ExpressionPrinter(const EquationSet& set) noexcept : m_set(set) {}

    // `parentPrecedence`: the precedence of the place the text goes in (0 for a whole expression); `atStart`: the text
    // opens an expression, where a sign needs no parentheses.
    [[nodiscard]] std::string print(std::int32_t index, int parentPrecedence, bool atStart) const
    {
        const ExpressionNode& node = m_set.node(index);
        switch (node.kind)
        {
        case ExpressionKind::Number:
        case ExpressionKind::Variable:
            return node.text;
        case ExpressionKind::Call:
            return printCall(node);
        case ExpressionKind::Negate:
            if (!(atStart && parentPrecedence <= SUM))
                return "(" + print(index, 0, true) + ")";
            return "-" + print(node.first, PRODUCT, false);
        case ExpressionKind::Binary:
            break;
        }
        return printChain(index, parentPrecedence, atStart);
    }

private:
    // One Binary node of a chain of left operands, and whether its text goes in parentheses.
    struct ChainLink
    {
        std::int32_t node = -1;
        bool inParentheses = false;
    };

    // The text of a Binary node. A+B+C+D is the tree ((A+B)+C)+D, as deep as the text is long, and a sum may have
    // thousands of terms: the left operands are walked in a loop, because a recursion over them would exhaust the
    // stack. Going down, each operator says where its left operand is written: a sum keeps `atStart` and asks for SUM,
    // a product asks for PRODUCT, a power for more than POWER (A**B**C groups from the right, so a power on the left
    // needs parentheses); an operator that binds less tightly than its place asks opens a parenthesis, which starts an
    // expression. Coming back up, each operator writes its symbol, its right operand (one level tighter for a sum and a
    // product, which group from the left) and its closing parenthesis.
    [[nodiscard]] std::string printChain(std::int32_t top, int parentPrecedence, bool atStart) const
    {
        std::vector<ChainLink> chain; // the Binary nodes from `top` down the left operands
        std::string text;
        std::int32_t bottom = top;
        while (m_set.node(bottom).kind == ExpressionKind::Binary)
        {
            const ExpressionNode& node = m_set.node(bottom);
            const int precedence = precedenceOf(node.op);
            const bool inParentheses = precedence < parentPrecedence;
            if (inParentheses)
            {
                text += "(";
                atStart = true;
            }
            chain.push_back(ChainLink{bottom, inParentheses});
            // The place of the left operand.
            parentPrecedence = precedence == POWER ? POWER + 1 : precedence;
            atStart = atStart && precedence == SUM;
            bottom = node.first;
        }
        text += print(bottom, parentPrecedence, atStart);
        for (auto link = chain.rbegin(); link != chain.rend(); ++link)
        {
            const ExpressionNode& node = m_set.node(link->node);
            const int precedence = precedenceOf(node.op);
            text += symbolOf(node.op);
            text += print(node.second, precedence == POWER ? POWER : precedence + 1, false);
            if (link->inParentheses)
                text += ")";
        }
        return text;
    }

    [[nodiscard]] std::string printCall(const ExpressionNode& node) const
    {
        std::string text = node.text + "(";
        for (std::size_t argument = 0; argument < node.arguments.size(); ++argument)
        {
            if (argument > 0)
                text += ",";
            text += print(node.arguments[argument], 0, true);
        }
        return text + ")";
    }

    const EquationSet& m_set;
};

} // namespace

std::string EquationSet::canonicalText() const
{
    const ExpressionPrinter printer(*this);
    std::string text;
    for (std::size_t index = 0; index < m_equations.size(); ++index)
    {
        if (index > 0)
            text += ";";
        text += m_equations[index].target;
        if (index == 0 && !m_parameters.empty())
        {
            text += "(";
            for (std::size_t parameter = 0; parameter < m_parameters.size(); ++parameter)
            {
                if (parameter > 0)
                    text += ",";
                text += m_parameters[parameter];
            }
            text += ")";
        }
        text += "=" + printer.print(m_equations[index].root, 0, true);
    }
    return text;
}

} // namespace oor::model
