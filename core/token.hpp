#ifndef INCLUDED_TOKEN
#define INCLUDED_TOKEN

#include <string>
#include <memory>

namespace LoxInterpreter {

enum class Token_Type {
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

class Literal_ {
  public:
    virtual ~Literal_() { };
};

template <typename T>
class Literal : public Literal_ {
  public:
    Literal(const T& data): d_data(data) { }
    auto data() const -> const T&;
    auto data() -> T&;
  private:
    T d_data;
};

class Token {
  public:
    template <typename T>
    Token(Token_Type tokenType, const std::string& lexeme, const T& literal, std::size_t lineNum):
      d_tokenType(tokenType)
    , d_lineNum(lineNum)
    , d_lexeme(lexeme)
    , d_literal(std::make_unique<Literal<T>>(literal)) { }

    Token(const Token&) = delete;
    auto operator=(const Token&) = delete;

    auto tokenType() const -> Token_Type;
    auto lineNum() const -> int;
    auto lexeme() const -> const std::string&;
    auto literal() const -> const std::unique_ptr<Literal_>&;

    auto tokenType() -> Token_Type;
    auto lineNum() -> int;
    auto literal() -> std::unique_ptr<Literal_>&;
    auto lexeme() -> std::string&;

  private:
    Token_Type d_tokenType;
    int d_lineNum;
    std::string d_lexeme;
    std::unique_ptr<Literal_> d_literal;

};

template <typename T>
inline auto
Literal<T>::data() const
    -> const T&
{
    return d_data;
}

template <typename T>
inline auto
Literal<T>::data()
    -> T&
{
    return d_data;
}

inline auto
Token::tokenType() const
    -> Token_Type
{
    return d_tokenType;
}

inline auto
Token::lineNum() const
    -> int
{
    return d_lineNum;
}

inline auto
Token::lexeme() const
    -> const std::string&
{
    return d_lexeme;
}

inline auto
Token::literal() const
    -> const std::unique_ptr<Literal_>&
{
    return d_literal;
}


inline auto
Token::tokenType()
    -> Token_Type
{
    return d_tokenType;
}

inline auto
Token::lineNum()
    -> int
{
    return d_lineNum;
}

inline auto
Token::literal()
    -> std::unique_ptr<Literal_>&
{
    return d_literal;
}

inline auto
Token::lexeme()
    -> std::string&
{
    return d_lexeme;
}


}

#endif
