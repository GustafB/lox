#include "token.h"

namespace LoxInterpreter {

auto
Token::type() const
    -> TokenType
{
    return d_type;
}

auto
Token::linum() const
    -> std::size_t
{
    return d_linum;
}

auto
Token::lexeme() const
    -> const std::string&
{
    return d_lexeme;
}

auto
Token::literal() const
    -> const std::variant<double, std::string>&
{
    return d_literal;
}

}
