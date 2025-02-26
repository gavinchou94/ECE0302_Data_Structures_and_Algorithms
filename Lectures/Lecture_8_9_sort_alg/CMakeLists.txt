cmake_minimum_required(VERSION 3.10)
project(sort_alg)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_sort.cpp sort.hpp list.hpp list.tpp catch.hpp)

add_executable(test_sort ${SOURCE})

enable_testing()

add_test(test-sort test_sort)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec8_9.zip" --format=zip
       ${SOURCE} abstract_list.hpp CMakeLists.txt
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})