#ifndef INCLUDED_TOKEN
#define INCLUDED_TOKEN

#include <string>
#include <memory>
#include <variant>

namespace LoxInterpreter {

enum class TokenType {
	// Single-character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  END_OF_FILE
};

class Token {
  public:
    template <typename T>
    Token(TokenType type, const std::string& lexeme, const T& literal, std::size_t linum) noexcept
    : d_type{type}
    , d_linum{linum}
    , d_lexeme{lexeme}
    , d_literal{literal} { }

    Token(const Token&) = delete;
    auto operator=(const Token&) = delete;

    auto type() const -> TokenType;
    auto linum() const -> std::size_t;
    auto linpos() const -> std::size_t;
    auto lexeme() const -> const std::string&;
    auto literal() const -> const std::variant<double, std::string>&;

  private:
    TokenType d_type;
    std::size_t d_linum;
    std::size_t d_linpos;
    std::string d_lexeme;
    std::variant<double, std::string> d_literal;
};

}

#endif
