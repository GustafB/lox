#ifndef INCLUDED_TOKEN
#define INCLUDED_TOKEN

#include <string>
#include <memory>

namespace LoxInterpreter {

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
    const T& data() const { return d_data; }

    // setter
    T& data() { return d_data; }

    virtual std::unique_ptr<Literal_> clone() { return std::make_unique<Literal<T>>(d_data); }

  private:
    T d_data;
};


class Token {
  public:
    enum TOKEN_TYPE {
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

  public:
    template <typename T>
    Token(TOKEN_TYPE tokenType, const std::string& lexeme, const T& literal, int lineNum):
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
    Token& operator=(const Token& rhs)
    {
        if (&rhs == this)
            return *this;

        d_literal.reset();

        d_literal = rhs.d_literal->clone();

        return *this;
    }

    // ~Token() { d_literal.reset(); }

    const TOKEN_TYPE tokenType() const { return d_tokenType;  }
    const int lineNum() const { return d_lineNum;  };
    const std::string& lexeme() const { return d_lexeme; }
    const std::unique_ptr<Literal_>& literal() const { return d_literal;  };

    TOKEN_TYPE tokenType() { return d_tokenType;  }
    int lineNum() { return d_lineNum;  };
    std::unique_ptr<Literal_>& literal() { return d_literal;  };
    std::string& lexeme() { return d_lexeme; }

  private:
    TOKEN_TYPE d_tokenType;
    int d_lineNum;
    std::string d_lexeme;
    std::unique_ptr<Literal_> d_literal;

};

}

#endif
