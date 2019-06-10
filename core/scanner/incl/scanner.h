#ifndef INCLUDED_SCANNER
#define INCLUDED_SCANNER

#include "token.h"
#include "input_source.h"

#include <string>
#include <list>
#include <unordered_map>

namespace LoxInterpreter {

class Scanner {
  public:
    explicit Scanner(InputSource& source)
    : d_source{source},
      d_tokens{},
      d_identifiers{load_identifiers()} { run(); }

    explicit Scanner(InputSource&& source)
    : d_source(source),
      d_tokens{},
      d_identifiers{load_identifiers()} { run(); }

    auto tokens() const -> const std::list<Token>&;
    auto source() const -> const InputSource&;

  private:

    auto run() -> void;
    auto scan_token() -> void;
    auto add_token(const TokenType type) -> void;
    template <typename T> auto add_token(const TokenType type, const T& literal) -> void;
    auto match_char(const char expected) -> bool;
    auto read_string() -> void;
    auto read_number() -> void;
    auto read_identifier() -> void;
    auto read_block_comment() -> void;
    auto load_identifiers() -> std::unordered_map<std::string, TokenType>;

    InputSource& d_source;
    std::list<Token> d_tokens;
    std::unordered_map<std::string, TokenType> d_identifiers;
};

}

#endif
