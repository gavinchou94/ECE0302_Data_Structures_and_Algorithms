cmake_minimum_required(VERSION 3.10)
project(twothree_trees)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE TwoThreeTree.hpp TwoThreeTree.tpp 
    TriNode.hpp TriNode.tpp
    TreePrinter.hpp 
    test_twothree_trees.cpp catch.hpp)

add_executable(test_twothree_trees ${SOURCE})

enable_testing()

add_test(test-twothree-trees test_twothree_trees)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec22.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})