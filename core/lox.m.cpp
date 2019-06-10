#include "repl.h"

#include <stdexcept>
#include <iostream>

int main(int argv, char* argc[])
{
    using namespace LoxInterpreter;
    Repl interpreter;

    interpreter.run_prompt();
    // if (argv > 2)
    // {
    //     std::cout << "Usage: jlox [script]" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
    // else if (argv == 2)
    // {
    //     interpreter.runFile(argc[0]);
    // }
    // else
    // {
    //     interpreter.runPrompt();
    // }

    // return 0;
}
