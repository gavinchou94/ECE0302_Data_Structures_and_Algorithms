cmake_minimum_required(VERSION 3.10)
project(binary_tree)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE abstract_binary_tree.hpp LinkedBT.hpp
            test_binary_tree.cpp catch.hpp)

add_executable(test_binary ${SOURCE})

enable_testing()

add_test(test-binary test_binary)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec17.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})