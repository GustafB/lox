#ifndef INCLUDED_LOX
#define INCLUDED_LOX

#include <string>
#include <vector>

namespace LoxInterpreter {

class Lox {
public:
    enum ERROR_CODES {
        SYNTAX_ERROR,
        UNKNOWN_ERROR
    };

public:
    Lox(): d_hadError(false) { }
    // ~Lox();

    void runFile(std::string);
    void runPrompt();
    void run(std::string);
private:
    void readFile(std::string, std::vector<char>*);

    bool d_hadError;


};

}

#endif
