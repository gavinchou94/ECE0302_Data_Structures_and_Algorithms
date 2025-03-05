cmake_minimum_required(VERSION 3.10)
project(sorted_list)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_sorted_list.cpp list.hpp list.tpp sorted_list.hpp sorted_list.tpp) 

# include Node if present
if(EXISTS "${PROJECT_SOURCE_DIR}/Node.tpp" AND EXISTS "${PROJECT_SOURCE_DIR}/Node.hpp")
    set(SOURCE ${SOURCE} Node.tpp Node.hpp)
endif()

# build the test
add_executable(test-sorted-list catch.hpp abstract_list.hpp abstract_sorted_list.hpp ${SOURCE})

enable_testing()
add_test(test-sorted-list test-sorted-list)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem5_submission.zip" --format=zip
    ${SOURCE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../problem5_starter.zip" --format=zip
    ${SOURCE} CMakeLists.txt catch.hpp abstract_list.hpp abstract_sorted_list.hpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})