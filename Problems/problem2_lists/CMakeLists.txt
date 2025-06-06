cmake_minimum_required(VERSION 3.10)
project(lists)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE abstract_list.hpp array_list.hpp array_list.tpp test_array_list.cpp linked_list.hpp linked_list.tpp test_linked_list.cpp)

add_executable(test-array-list catch.hpp abstract_list.hpp array_list.hpp array_list.tpp test_array_list.cpp)
add_executable(test-linked-list catch.hpp abstract_list.hpp linked_list.hpp linked_list.tpp test_linked_list.cpp)

enable_testing()

add_test(test-array-list test-array-list)
add_test(test-linked-list test-linked-list)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem2_submission.zip" --format=zip
    ${SOURCE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../problem2_starter.zip" --format=zip
    ${SOURCE}
    Node.hpp Node.tpp catch.hpp CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})  