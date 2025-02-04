cmake_minimum_required(VERSION 3.10)
project(prefix CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE 
        test_prefix.cpp
        evaluate_prefix.hpp
        writeBackward.hpp
        catch.hpp)

add_executable(evaluate_prefix ${SOURCE})

enable_testing()

add_test(evaluate-prefix evaluate_prefix)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec6.zip" --format=zip
       ${SOURCE} CMakeLists.txt solve_maze.cpp
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})