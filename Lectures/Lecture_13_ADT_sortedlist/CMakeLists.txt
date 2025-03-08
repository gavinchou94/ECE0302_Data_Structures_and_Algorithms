cmake_minimum_required(VERSION 3.10)
project(sorted_list)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE abstract_list.hpp abstract_sorted_list.hpp 
            ArrayList.hpp ArrayList.tpp
            sorted_list.hpp sorted_list.tpp
            test_sorted_list.cpp catch.hpp)

add_executable(test_sorted_list ${SOURCE})

enable_testing()

add_test(test-sorted-list test_sorted_list)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec13.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})