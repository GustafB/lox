oopp#include "token.hpp"
#include <memory>

namespace LoxInterpreter {

class Expr {
  public:
    Expr(const Expr& left, const Expr& right, const Token& token):
      d_left(left)
    , d_right(right)
    , d_token(token) { }

    Token& token() { return d_token; }
    Expr& left() { return *d_left; }
    Expr& right() { return *d_right; }
    const Expr& left() { return *d_left; }
    const Expr& right() { return *d_right; }
    const Token& token() { return d_token; }

  private:
    std::unique_ptr<Expr> d_left;
    std::unique_ptr<Expr> d_right;
    Token d_token;
};

class Binary : public Expr {
  public:
    Binary(const Expr& left, const Expr& right, const Token& token):
    Expr(left, right, token) { }
};

}
