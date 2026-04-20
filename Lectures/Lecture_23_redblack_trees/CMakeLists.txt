cmake_minimum_required(VERSION 3.10)
project(more_trees)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE TwoThreeFourTree.hpp 
    TreePrinter.hpp Convert234ToRB.hpp
    RedBlackTree.hpp RedBlackTree.tpp
    RBNode.hpp RBNode.tpp
    test_more_trees.cpp catch.hpp)

add_executable(test_more_trees ${SOURCE})

enable_testing()

add_test(test-more-trees test_more_trees)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec23.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})