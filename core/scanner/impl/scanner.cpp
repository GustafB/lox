#include "scanner.h"
#include "token.h"

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <cctype>
#include <unordered_map>

namespace LoxInterpreter {

auto
Scanner::tokens() const
    -> const std::list<Token>&
{
    return d_tokens;
}

auto
Scanner::source() const
    -> const InputSource&
{
    return d_source;
}

auto
Scanner::run()
    -> void
{
    while (!d_source.eof())
    {
        d_source.reset_start();
        scan_token();
    }
    d_tokens.emplace_back(TokenType::END_OF_FILE, "", NULL, 0);
}

auto
Scanner::scan_token()
    -> void
{
    std::cout << "scan_token\n";
    char c = d_source.advance();
    switch (c) {
      case '(': add_token(TokenType::LEFT_PAREN); break;
      case ')': add_token(TokenType::RIGHT_PAREN); break;
      case '{': add_token(TokenType::LEFT_BRACE); break;
      case '}': add_token(TokenType::RIGHT_BRACE); break;
      case ',': add_token(TokenType::COMMA); break;
      case '.': add_token(TokenType::DOT); break;
      case '-': add_token(TokenType::MINUS); break;
      case '+': add_token(TokenType::PLUS); break;
      case ';': add_token(TokenType::SEMICOLON); break;
      case '*': add_token(TokenType::STAR); break;
      case '!': add_token(match_char('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
      case '=': add_token(match_char('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
      case '<': add_token(match_char('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
      case '>': add_token(match_char('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
      case '/':
        if (match_char('/'))
            while (d_source.peek() != '\n' && !d_source.eof())
                d_source.advance();
        else if (match_char('*'))
            read_block_comment();
        else
            add_token(TokenType::SLASH);
        break;
        // Ignore whitespace.
      case ' ':
      case '\r':
      case '\t':
        break;
      case '\n':
        // d_line++;
        break;
      case '"': read_string(); break;
      default:
        if (std::isdigit(c))
            read_number();
        else if (std::isalpha(c))
            read_identifier();
        else
        {
            std::cerr << "Error: invalid character: " << d_source.peek() << "\n"; break;
        }
    }
}

auto
Scanner::add_token(const TokenType type)
    -> void
{
    add_token(type, NULL);
}

template <typename T>
auto
Scanner::add_token(const TokenType type, const T& literal)
    -> void
{
    d_tokens.emplace_back(type, d_source.extract(), literal, d_source.linum());
    return;
}

auto
Scanner::match_char(const char expected)
    -> bool
{
    if (d_source.eof() || d_source.peek() != expected)
        return false;
    d_source.advance();
    return true;
}

auto
Scanner::read_string()
    -> void
{
    std::cout << "read_string\n";
    while (d_source.peek() != '"' && !d_source.eof())
    {
        // if (d_source.peek() == '\n')
        //     ++d_source.linum();
        d_source.advance();
    }

    if (d_source.eof())
    {
        std::cerr << "Error: unterminated string\n";
        return;
    }

    d_source.advance();

    std::string literal{d_source.extract()};
    add_token(TokenType::STRING, literal);
}

auto
Scanner::read_number()
    -> void
{
    std::cout << "read_number\n";
    while (std::isdigit(d_source.peek()))
        d_source.advance();

    if (d_source.peek() == '.' && std::isdigit(d_source.peek_n(1)))
        d_source.advance();

    while (std::isdigit(d_source.peek()))
        d_source.advance();

    add_token(TokenType::NUMBER, std::stod(d_source.extract()));
}

auto
Scanner::read_identifier()
    -> void
{
    std::cout << "read_identifier\n";
    while (std::isalnum(d_source.peek()))
            d_source.advance();

    auto type_itr = d_identifiers.find(d_source.extract());
    TokenType type = type_itr == std::end(d_identifiers)
        ? TokenType::IDENTIFIER
        : type_itr->second;

    std::cout << "type="<<(int)type<<"\n";

    add_token(type);
}

auto
Scanner::read_block_comment()
    -> void
{
    std::cout << "read_block_comment" << std::endl;
    if (d_source.eof())
    {
        std::cerr << "Error: unterminated string\n";
        return;
    }
    else if (d_source.peek() == '*' && d_source.peek_n() == '/')
    {
        std::cout << "Exit:" << d_source.peek() << d_source.peek_n() << std::endl;
        return;
    }
    else {
        d_source.advance();
        read_block_comment();
    }

    d_source.advance(); d_source.advance();
}

 auto
Scanner::load_identifiers()
     -> std::unordered_map<std::string, TokenType>
{
    return std::unordered_map<std::string, TokenType> {
        { "and",    TokenType::AND },
        { "class",  TokenType::CLASS },
        { "else",   TokenType::ELSE },
        { "false",  TokenType::FALSE },
        { "for",    TokenType::FOR },
        { "fun",    TokenType::FUN },
        { "if",     TokenType::IF },
        { "nil",    TokenType::NIL },
        { "or",     TokenType::OR },
        { "print",  TokenType::PRINT },
        { "return", TokenType::RETURN },
        { "super",  TokenType::SUPER },
        { "this",   TokenType::THIS },
        { "true",   TokenType::TRUE },
        { "var",    TokenType::VAR },
        { "while",  TokenType::WHILE }
    };
}
}
