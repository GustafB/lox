#ifndef INCLUDED_SCANNER
#define INCLUDED_SCANNER

#include "token.hpp"

#include <string>
#include <list>
#include <unordered_map>

namespace LoxInterpreter {

class Scanner {
  public:
    Scanner(std::string source):
    d_source(source)
    , d_current(std::begin(source))
    , d_start(std::begin(source))
    , d_line(0) { loadIdentifiers(); };
    void scanTokens();
    void scanToken();
    char advance();
    void addToken(const Token_Type type);

    template <typename T>
    void addToken(const Token_Type type, const T& literal);

    const std::list<Token>& tokens() const { return d_tokens; }

  private:
    using StringIterator = std::string::iterator;

    auto endOfFile() const -> bool;
    auto matchChar(const char expected) -> bool;
    auto peek() const -> char ;
    auto peekNext() const -> char ;
    auto readString() -> void;
    auto readNumber() -> void;
    auto readIdentifier() -> void;
    auto readBlockComment() -> void;
    auto loadIdentifiers() -> void;

    std::string d_source;
    StringIterator d_current;
    StringIterator d_start;
    size_t d_line;
    std::list<Token> d_tokens;
    std::unordered_map<std::string, Token_Type> d_identifiers;
};




}

#endif
