cmake_minimum_required(VERSION 3.10)
project(bst)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_bst.cpp binary_search_tree.hpp binary_search_tree.tpp)

add_executable(test-bst catch.hpp ${SOURCE})

enable_testing()

add_test(test-bst test-bst)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem7_submission.zip" --format=zip
    ${SOURCE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../problem7_starter.zip" --format=zip
    ${SOURCE} CMakeLists.txt catch.hpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})