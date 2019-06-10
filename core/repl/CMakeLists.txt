add_library(
  repl
  impl/repl.cpp
  )

target_include_directories(
  repl
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/incl>
  PRIVATE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/core/scanner/incl>
  )

target_compile_options(
  repl
  PUBLIC
  -Wall
  -Werror
  -Wpedantic
  )

target_link_libraries(
  repl
  PRIVATE
  scanner
  )
