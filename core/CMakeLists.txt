set(HEADER_FILES scanner.hpp token.hpp lox.hpp)

add_library(scanner STATIC scanner.cpp ${HEADER_FILFES})
add_library(token STATIC token.cpp ${HEADER_FILFES})
add_library(lox STATIC lox.cpp ${HEADER_FILFES})

set(LIBRARIES lox scanner token)

add_executable(lox-repl lox.m.cpp ${LIBRARIES} ${HEADER_FILFES})
