cmake_minimum_required(VERSION 3.10)
project(sort_alg)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE iterator.h test_iterator.cpp catch.hpp)

add_executable(test_iterator ${SOURCE})

enable_testing()

add_test(test-iterator test_iterator)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec8_9.zip" --format=zip
       ${SOURCE} CMakeLists.txt
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})