cmake_minimum_required(VERSION 3.10)
project(binary_search_tree)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE abstract_binary_tree.hpp BinarySearchTree.hpp BinarySearchTree.tpp
           BinaryNode.hpp BinaryNode.tpp
            test_bst.cpp catch.hpp)

add_executable(test_bst ${SOURCE})

enable_testing()

add_test(test-bst test_bst)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec18.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})