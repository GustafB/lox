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

    void runFile(const std::string) const;
    void runPrompt();
    void run(const std::string) const;
private:
    void readFile(const std::string, std::vector<char>*) const;

    bool d_hadError;


};

}

#endif
