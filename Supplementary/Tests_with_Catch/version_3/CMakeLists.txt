cmake_minimum_required(VERSION 3.10)
project(puzzle)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE puzzle_test.cpp puzzle.hpp catch.hpp)

add_executable(test_puzzle ${SOURCE})

enable_testing()

add_test(test-puzzle test_puzzle)