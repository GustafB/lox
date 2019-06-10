#include "repl.h"
#include "scanner.h"
#include "token.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <forward_list>

namespace LoxInterpreter {

// void
// Repl::runFile(const std::string filePath) const
// {
//     std::vector<char> inputChars;
//     readFile(filePath, &inputChars);
//     return;
// }

void
Repl::run_prompt()
{
    for (;;)
    {
        std::cout << "> ";
        std::string s;
        std::getline(std::cin, s);
        std::stringstream ss(s);
        run(ss);
        std::cin.clear();
        d_hadError = false;
    }
    return;
}


// void
// Repl::readFile(const std::string filePath,
//               std::vector<char>* bytes) const
// {
//     try
//     {
//         std::ifstream input;
//         input.open(filePath);

//         char c;
//         while (input.get(c))
//             bytes->push_back(c);
//     }
//     catch (std::ios_base::failure& e)
//     {
//         throw e.what();
//     }
// }

void
Repl::run(std::istream& source) const
{
    if (d_hadError == true)
        std::cerr << "Error: system malfunction, exiting gracefully\n";

    Scanner scanner{InputSource{source}};
    std::cout << "Printing tokens: \n" ;
    for (auto &token: scanner.tokens())
    {
        std::cout << token.lexeme() << "|";

        if (token.type() == TokenType::NUMBER)
            std::cout << std::get<double>(token.literal());

        else if( token.type() == TokenType::STRING)
            std::cout << std::get<std::string>(token.literal());

        std::cout << "\n";
    }
}

// void
// Repl::error(std::string errorMessage, int line)
// {
//     d_hadError = true;
//     std::cerr << errorMessage << "\n";
// }

}
