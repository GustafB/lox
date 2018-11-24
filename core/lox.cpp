#include "lox.hpp"
#include "scanner.hpp"
#include "token.hpp"
#include "scanner.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <istream>

namespace LoxInterpreter {

void
Lox::runFile(std::string filePath)
{
    std::vector<char> inputChars;
    readFile(filePath, &inputChars);
    return;
}

void
Lox::runPrompt()
{
    for (;;)
    {
        std::cout << "> ";

        std::string currentLine;

        std::getline(std::cin, currentLine);
        std::cin.clear();
        run(currentLine);

        d_hadError = false;
    }
    return;
}


void
Lox::readFile(std::string filePath,
              std::vector<char>* bytes)
{
    try
    {
        std::ifstream input;
        input.open(filePath);

        char c;
        while (input.get(c))
            bytes->push_back(c);
    }
    catch (std::ios_base::failure& e)
    {
        throw e.what();
    }
}

void
Lox::run(std::string source)
{
    if (d_hadError == true)
        std::cerr << "Error: system malfunction, exiting gracefully\n";

    Scanner scanner = Scanner(source);
    std::list<Token> tokens;

    scanner.scanTokens(tokens);
    for (auto &token: scanner.tokens())
    {
        std::cout << token.lexeme() << "\n";
    }
}

// void
// Lox::error(std::string errorMessage, int line)
// {
//     d_hadError = true;
//     std::cerr << errorMessage << "\n";
// }

}
