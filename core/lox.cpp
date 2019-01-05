#include "lox.hpp"
#include "scanner.hpp"
#include "token.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <forward_list>

namespace LoxInterpreter {

void
Lox::runFile(const std::string filePath) const
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

        if (currentLine == "exit()" || currentLine == "exit")
            return;

        run(currentLine);

        d_hadError = false;
    }
    return;
}


void
Lox::readFile(const std::string filePath,
              std::vector<char>* bytes) const
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
Lox::run(const std::string source) const
{
    if (d_hadError == true)
        std::cerr << "Error: system malfunction, exiting gracefully\n";

    Scanner scanner = Scanner(source);
    std::forward_list<Token> tokens;

    scanner.scanTokens();
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
