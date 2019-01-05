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

    void
    Scanner::scanTokens()
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
        std::cout << "scanToken\n";
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

    char
    Scanner::advance()
    {
        d_current++;
        return d_source[d_current - 1];
    }

    void
    Scanner::addToken(const Token::TOKEN_TYPE type)
    {
        addToken(type, NULL);
    }

    template <typename T>
    void
    Scanner::addToken(const Token::TOKEN_TYPE type, const T& literal)
    {
        std::string text = d_source.substr(d_start, d_current - d_start);
        std::cout << "addToken | " << text << " | " << literal << '\n';
        d_tokens.push_back(Token(type, text, literal, d_line));
        return;
    }

    bool
    Scanner::matchChar(const char expected)
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

        std::string stringLiteral = d_source.substr(d_start + 1, d_current - 1 - (d_start + 1));
        addToken(Token::STRING, stringLiteral);
    }

    void
    Scanner::readNumber()
    {
        std::cout << "readNumber\n";
        while (std::isdigit(peek()))
            advance();

        if (peek() == '.' && std::isdigit(peekNext()))
            advance();

        while (std::isdigit(peek()))
            advance();

        addToken(Token::NUMBER, std::stod(d_source.substr(d_start, d_current - d_start)));
    }

    void
    Scanner::readIdentifier()
    {
        std::cout << "readIdentifier\n";
        while (std::isalnum(peek()))
            advance();

        std::string text = d_source.substr(d_start, d_current - d_start);
        auto type_itr = d_identifiers.find(text);

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

    void
    Scanner::loadIdentifiers()
    {
        d_identifiers = {
            { "and",    Token::AND },
            { "class",  Token::CLASS },
            { "else",   Token::ELSE },
            { "false",  Token::FALSE },
            { "for",    Token::FOR },
            { "fun",    Token::FUN },
            { "if",     Token::IF },
            { "nil",    Token::NIL },
            { "or",     Token::OR },
            { "print",  Token::PRINT },
            { "return", Token::RETURN },
            { "super",  Token::SUPER },
            { "this",   Token::THIS },
            { "true",   Token::TRUE },
            { "var",    Token::VAR },
            { "while",  Token::WHILE }
        };
    }

}
