add_library(lox STATIC lox.cpp)
add_library(scanner STATIC scanner.cpp)
add_library(token STATIC token.cpp)

add_executable(lox-interpreter lox.m.cpp lox)
