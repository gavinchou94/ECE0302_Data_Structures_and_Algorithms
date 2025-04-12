cmake_minimum_required(VERSION 3.10)
project(balanced_tree)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE AVLTree.hpp BinaryNode.hpp BinaryNode.tpp test_avl.cpp catch.hpp)

add_executable(test_avl ${SOURCE})

enable_testing()

add_test(test-avl test_avl)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec21.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})