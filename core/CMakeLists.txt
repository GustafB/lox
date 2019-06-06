set(HEADER_FILES scanner.hpp token.hpp lox.hpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(scanner STATIC scanner.cpp ${HEADER_FILFES})
add_library(token STATIC token.cpp ${HEADER_FILFES})
add_library(lox STATIC lox.cpp ${HEADER_FILFES})

set(LIBRARIES lox scanner token)

add_executable(lox-repl lox.m.cpp ${LIBRARIES} ${HEADER_FILES})
