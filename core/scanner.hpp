#ifndef INCLUDED_SCANNER
#define INCLUDED_SCANNER

#include "token.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <cctype>
#include <unordered_map>

namespace {

    bool isDigit(char c)
    {
        return (c>='0' && c<='9');
    }

    bool isAlpha(char c)
    {
        return ((c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                c == '_');
    }

    bool isAlphanumeric(char c)
    {
        return isDigit(c) || isAlpha(c);
    }

}

namespace LoxInterpreter {

    class Scanner {
    public:
        Scanner(std::string source):
            d_source(source), d_current(0), d_start(0), d_line(0) { loadIdentifiers(); };
        void scanTokens(std::list<Token>&);
        void scanToken();
        char advance();
        void addToken(Token::TOKEN_TYPE type);

        template <typename T>
        void addToken(Token::TOKEN_TYPE type, const T& literal);

        const std::list<Token>& tokens() const { return d_tokens; }

    private:

        bool endOfFile() const { return d_current >= d_source.size(); }
        bool matchChar(char expected);
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
        std::unordered_map<std::string, Token::TOKEN_TYPE> d_identifiers;
    };

    void
    Scanner::scanTokens(std::list<Token>&)
    {
        while (!endOfFile())
        {
            d_start = d_current;
            scanToken();
        }

        d_tokens.push_back(Token(Token::END_OF_FILE, "", NULL, 0));
        return;
    }

    void
    Scanner::scanToken()
    {
        char c = advance();
        switch (c) {
        case '(': addToken(Token::LEFT_PAREN); break;
        case ')': addToken(Token::RIGHT_PAREN); break;
        case '{': addToken(Token::LEFT_BRACE); break;
        case '}': addToken(Token::RIGHT_BRACE); break;
        case ',': addToken(Token::COMMA); break;
        case '.': addToken(Token::DOT); break;
        case '-': addToken(Token::MINUS); break;
        case '+': addToken(Token::PLUS); break;
        case ';': addToken(Token::SEMICOLON); break;
        case '*': addToken(Token::STAR); break;
        case '!': addToken(matchChar('=') ? Token::BANG_EQUAL : Token::BANG); break;
        case '=': addToken(matchChar('=') ? Token::EQUAL_EQUAL : Token::EQUAL); break;
        case '<': addToken(matchChar('=') ? Token::LESS_EQUAL : Token::LESS); break;
        case '>': addToken(matchChar('=') ? Token::GREATER_EQUAL : Token::GREATER); break;
        case '/':
            if (matchChar('/'))
                while (peek() != '\n' && !endOfFile())
                    advance();
            else if (matchChar('*'))
                readBlockComment();
            else
                addToken(Token::SLASH);
            break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;
        case '\n':
            d_line++;
            break;
        case '"': readString(); break;
        default:
            if (isDigit(c))
                readNumber();
            else if (isAlpha(c))
                readIdentifier();
            else
            {
                std::cerr << "Error: invalid character: " << peek() << "\n"; break;
            }
        }
    }

    char
    Scanner::advance()
    {
        d_current++;
        return d_source[d_current - 1];
    }

    void
    Scanner::addToken(Token::TOKEN_TYPE type)
    {
        addToken(type, NULL);
    }

    template <typename T>
    void
    Scanner::addToken(Token::TOKEN_TYPE type, const T& literal)
    {
        std::string text = d_source.substr(d_start, d_current - d_start);
        std::cout << "addToken | " << text << " | " << literal << "\n";
        std::cout << "start: " << d_start << " | current: " << d_current << std::endl;
        d_tokens.push_back(Token(type, text, literal, d_line));
        return;
    }

    bool
    Scanner::matchChar(char expected)
    {
        if (endOfFile()) return false;
        if (d_source[d_current] != expected) return false;

        d_current++;

        return true;
    }

    char
    Scanner::peek() const
    {
        if (endOfFile()) return '\0';
        return d_source[d_current];
    }

    char
    Scanner::peekNext() const
    {
        if (endOfFile()) return '\0';
        return d_source[d_current + 1];
    }

    void
    Scanner::readString()
    {
        std::cout << "readString\n";
        while (peek() != '"' && !endOfFile())
        {
            if (peek() == '\n')
                d_line++;
            advance();
        }

        if (endOfFile())
        {
            std::cerr << "Error: unterminated string\n";
            return;
        }

        advance();

        std::string stringLiteral = d_source.substr(d_start + 1, d_current - 1 - d_start);
        addToken(Token::STRING, stringLiteral);
    }

    void
    Scanner::readNumber()
    {
        std::cout << "readNumber\n";
        while (isDigit(peek()))
            advance();

        if (peek() == '.' && isDigit(peekNext()))
        {
            std::cout << "Peek: " << peek() << " Next:" << peekNext() << std::endl;
            advance();
        }

        while (isDigit(peek()))
            advance();

        addToken(Token::NUMBER, std::stod(d_source.substr(d_start, d_current - d_start)));
    }

    void
    Scanner::readIdentifier()
    {
        std::cout << "readIdentifier\n";
        while (isAlphanumeric(peek()))
            advance();

        std::string text = d_source.substr(d_start, d_current - d_start);
        auto type_itr = (d_identifiers.find(text));

        Token::TOKEN_TYPE type;

        if (type_itr == d_identifiers.end())
            type = Token::IDENTIFIER;
        else
            type = type_itr->second;

        addToken(type);
    }

    void
    Scanner::readBlockComment()
    {
        while (peek() != '*' && peekNext() != '/')
        {
            if (peek() == '\n')
                d_line++;

            if (endOfFile())
            {
                std::cerr << "Error: unterminated string\n";
                return;
            }

            advance();
        }

        advance(); advance();
    }

    void
    Scanner::loadIdentifiers()
    {
        d_identifiers = {
            {"and",    Token::AND},
            {"class",  Token::CLASS},
            {"else",   Token::ELSE},
            {"false",  Token::FALSE},
            {"for",    Token::FOR},
            {"fun",    Token::FUN},
            {"if",     Token::IF},
            {"nil",    Token::NIL},
            {"or",     Token::OR},
            {"print",  Token::PRINT},
            {"return", Token::RETURN},
            {"super",  Token::SUPER},
            {"this",   Token::THIS},
            {"true",   Token::TRUE},
            {"var",    Token::VAR},
            {"while",  Token::WHILE}
        };
    }


}

#endif
