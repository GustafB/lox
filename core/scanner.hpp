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
            , d_current(0)
            , d_start(0)
            , d_line(0) { loadIdentifiers(); };
        void scanTokens();
        void scanToken();
        char advance();
        void addToken(const Token_Type type);

        template <typename T>
        void addToken(const Token_Type type, const T& literal);

        const std::list<Token>& tokens() const { return d_tokens; }

    private:

        bool endOfFile() const { return d_current >= d_source.size(); }
        bool matchChar(const char expected);
        char peek() const;
        char peekNext() const;
        void readString();
        void readNumber();
        void readIdentifier();
        void readBlockComment();
        void loadIdentifiers();

        std::string d_source;
        size_t d_current;
        size_t d_start;
        size_t d_line;
        std::list<Token> d_tokens;
        std::unordered_map<std::string, Token_Type> d_identifiers;
    };




}

#endif
