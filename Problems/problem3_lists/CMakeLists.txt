cmake_minimum_required(VERSION 3.10)
project(lists)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE array_list.hpp array_list.tpp linked_list.hpp linked_list.tpp test_list.cpp)

add_executable(test-list catch.hpp abstract_list.hpp Node.hpp Node.tpp ${SOURCE})

enable_testing()

add_test(test-list test-list)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem3_submission.zip" --format=zip
    ${SOURCE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../problem3_lists.zip" --format=zip
    ${SOURCE}
    Node.hpp Node.tpp catch.hpp CMakeLists.txt abstract_list.hpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})