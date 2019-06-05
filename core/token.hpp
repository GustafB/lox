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
    virtual std::unique_ptr<Literal_> clone() = 0;
    virtual ~Literal_() { };
};

template <typename T>
class Literal : public Literal_ {
  public:
    Literal(const T& data): d_data(data) { }

    // getter
    auto data() const -> const T& { return d_data; }

    // setter
    auto data() -> T& { return d_data; }

    virtual auto clone() -> std::unique_ptr<Literal_> { return std::make_unique<Literal<T>>(d_data); }

  private:
    T d_data;
};


class Token {
  public:

  public:
    template <typename T>
    Token(Token_Type tokenType, const std::string& lexeme, const T& literal, int lineNum):
      d_tokenType(tokenType)
    , d_lineNum(lineNum)
    , d_lexeme(lexeme)
    , d_literal(std::make_unique<Literal<T>>(literal)) { }

    Token(const Token& token):
      d_tokenType(token.d_tokenType)
    , d_lineNum(token.d_lineNum)
    , d_lexeme(token.d_lexeme)
    , d_literal(token.d_literal->clone()) { }

    template <typename T>
    auto operator=(const Token& rhs) -> Token&
    {
        if (&rhs == this)
            return *this;

        d_literal.reset();

        d_literal = rhs.d_literal->clone();

        return *this;
    }

    // ~Token() { d_literal.reset(); }

    auto tokenType() const -> Token_Type { return d_tokenType;  }
    auto lineNum() const -> int { return d_lineNum;  };
    auto lexeme() const -> const std::string& { return d_lexeme; }
    auto literal() const -> const std::unique_ptr<Literal_>& { return d_literal;  };

    auto tokenType() -> Token_Type { return d_tokenType;  }
    auto lineNum() -> int { return d_lineNum;  };
    auto literal() -> std::unique_ptr<Literal_>& { return d_literal;  };
    auto lexeme() -> std::string& { return d_lexeme; }

  private:
    Token_Type d_tokenType;
    int d_lineNum;
    std::string d_lexeme;
    std::unique_ptr<Literal_> d_literal;

};

}

#endif
