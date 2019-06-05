#include "scanner.hpp"
#include "token.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <cctype>
#include <unordered_map>

namespace {

}

namespace LoxInterpreter {

    auto
    Scanner::scanTokens() -> void
    {
        while (!endOfFile())
        {
            d_start = d_current;
            scanToken();
        }

        d_tokens.push_back(Token(Token_Type::END_OF_FILE, "", NULL, 0));
        return;
    }

    auto
    Scanner::scanToken() -> void
    {
        std::cout << "scanToken\n";
        char c = advance();
        switch (c) {
        case '(': addToken(Token_Type::LEFT_PAREN); break;
        case ')': addToken(Token_Type::RIGHT_PAREN); break;
        case '{': addToken(Token_Type::LEFT_BRACE); break;
        case '}': addToken(Token_Type::RIGHT_BRACE); break;
        case ',': addToken(Token_Type::COMMA); break;
        case '.': addToken(Token_Type::DOT); break;
        case '-': addToken(Token_Type::MINUS); break;
        case '+': addToken(Token_Type::PLUS); break;
        case ';': addToken(Token_Type::SEMICOLON); break;
        case '*': addToken(Token_Type::STAR); break;
        case '!': addToken(matchChar('=') ? Token_Type::BANG_EQUAL : Token_Type::BANG); break;
        case '=': addToken(matchChar('=') ? Token_Type::EQUAL_EQUAL : Token_Type::EQUAL); break;
        case '<': addToken(matchChar('=') ? Token_Type::LESS_EQUAL : Token_Type::LESS); break;
        case '>': addToken(matchChar('=') ? Token_Type::GREATER_EQUAL : Token_Type::GREATER); break;
        case '/':
            if (matchChar('/'))
                while (peek() != '\n' && !endOfFile())
                    advance();
            else if (matchChar('*'))
                readBlockComment();
            else
                addToken(Token_Type::SLASH);
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
            if (std::isdigit(c))
                readNumber();
            else if (std::isalpha(c))
                readIdentifier();
            else
            {
                std::cerr << "Error: invalid character: " << peek() << "\n"; break;
            }
        }
    }

    auto
    Scanner::advance() -> char
    {
        d_current++;
        return d_source[d_current - 1];
    }

    auto
    Scanner::addToken(const Token_Type type) -> void
    {
        addToken(type, NULL);
    }

    template <typename T>
    auto
    Scanner::addToken(const Token_Type type, const T& literal) -> void
    {
        std::string text = d_source.substr(d_start, d_current - d_start);
        std::cout << "addToken | " << text << " | " << literal << '\n';
        d_tokens.push_back(Token(type, text, literal, d_line));
        return;
    }

    auto
    Scanner::matchChar(const char expected) -> bool
    {
        if (endOfFile()) return false;
        if (d_source[d_current] != expected) return false;

        d_current++;

        return true;
    }

    auto
    Scanner::peek() const -> char
    {
        if (endOfFile()) return '\0';
        return d_source[d_current];
    }

    auto
    Scanner::peekNext() const -> char
    {
        if (endOfFile()) return '\0';
        return d_source[d_current + 1];
    }

    auto
    Scanner::readString() -> void
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

        std::string stringLiteral = d_source.substr(d_start + 1, d_current - 1 - (d_start + 1));
        addToken(Token_Type::STRING, stringLiteral);
    }

    auto
    Scanner::readNumber() -> void
    {
        std::cout << "readNumber\n";
        while (std::isdigit(peek()))
            advance();

        if (peek() == '.' && std::isdigit(peekNext()))
            advance();

        while (std::isdigit(peek()))
            advance();

        addToken(Token_Type::NUMBER, std::stod(d_source.substr(d_start, d_current - d_start)));
    }

    auto
    Scanner::readIdentifier() -> void
    {
        std::cout << "readIdentifier\n";
        while (std::isalnum(peek()))
            advance();

        std::string text = d_source.substr(d_start, d_current - d_start);
        auto type_itr = d_identifiers.find(text);

        Token_Type type;

        if (type_itr == d_identifiers.end())
            type = Token_Type::IDENTIFIER;
        else
            type = type_itr->second;

        addToken(type);
    }

    auto
    Scanner::readBlockComment() -> void
    {
        std::cout << "readBlockComment" << std::endl;
        if (endOfFile())
        {
            std::cerr << "Error: unterminated string\n";
            return;
        }
        else if (peek() == '*' && peekNext() == '/')
        {
            std::cout << "Exit:" << peek() << peekNext() << std::endl;
            return;
        }
        else {
            advance();
            readBlockComment();
        }

        advance(); advance();
    }

    auto
    Scanner::loadIdentifiers() -> void
    {
        d_identifiers = {
            { "and",    Token_Type::AND },
            { "class",  Token_Type::CLASS },
            { "else",   Token_Type::ELSE },
            { "false",  Token_Type::FALSE },
            { "for",    Token_Type::FOR },
            { "fun",    Token_Type::FUN },
            { "if",     Token_Type::IF },
            { "nil",    Token_Type::NIL },
            { "or",     Token_Type::OR },
            { "print",  Token_Type::PRINT },
            { "return", Token_Type::RETURN },
            { "super",  Token_Type::SUPER },
            { "this",   Token_Type::THIS },
            { "true",   Token_Type::TRUE },
            { "var",    Token_Type::VAR },
            { "while",  Token_Type::WHILE }
        };
    }

}
