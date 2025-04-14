cmake_minimum_required(VERSION 3.10)
project(more_trees)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE Linked23.hpp Linked23.tpp 
    TriNode.hpp TriNode.tpp 
    LinkedRB.hpp LinkedRB.tpp
    RedBlackNode.hpp
    BinaryNode.hpp BinaryNode.tpp
    test_more_trees.cpp catch.hpp)

add_executable(test_more_trees ${SOURCE})

enable_testing()

add_test(test-more-trees test_more_trees)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec22_23.zip" --format=zip
    ${SOURCE} CMakeLists.txt "resources/*"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})