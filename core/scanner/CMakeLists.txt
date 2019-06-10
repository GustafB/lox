add_library(
  scanner
  impl/scanner.cpp
  impl/input_source.cpp
  impl/token.cpp
  )

target_include_directories(
  scanner
  PUBLIC
  $<INSTALL_INTERFACE:incl>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/incl>
  )

target_compile_options(
  scanner
  PUBLIC
  -Wall
  -Werror
  -Wpedantic
  )

export(PACKAGE scanner)
