add_subdirectory(scanner)
add_subdirectory(repl)

add_executable(lox lox.m.cpp)

target_include_directories(
  lox
  PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/scanner/incl>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/repl/incl>
  )

target_link_libraries(lox repl scanner)
