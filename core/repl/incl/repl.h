#ifndef INCLUDED_REPL
#define INCLUDED_REPL

#include <string>
#include <vector>

namespace LoxInterpreter {

class Repl {
public:
    enum ERROR_CODES {
        SYNTAX_ERROR,
        UNKNOWN_ERROR
    };

public:
    Repl(): d_hadError(false) { }

    void run_file(const std::string) const;
    void run_prompt();
    void run(std::istream&) const;
private:
    void read_file(const std::string, std::vector<char>*) const;

    bool d_hadError;


};

}

#endif
