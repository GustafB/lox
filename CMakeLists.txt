cmake_minimum_required(VERSION 2.8)

project(lox-interpreter)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")
set (CMAKE_BUILD_TYPE Debug)

enable_testing()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)
