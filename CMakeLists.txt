cmake_minimum_required(VERSION 3.15)
project(cool)

set(CMAKE_CXX_STANDARD 14)

add_executable(cool cmake-build-debug/run_facts.cpp cmake-build-debug/state_facts.h cmake-build-debug/state_facts.cpp)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wconversion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )