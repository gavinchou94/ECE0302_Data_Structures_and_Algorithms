cmake_minimum_required(VERSION 3.10)
project(smart_ptr)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_smart_ptr.cpp catch.hpp)

add_executable(test_smart_ptr ${SOURCE})

enable_testing()

add_test(test-smart-ptr test_smart_ptr)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec12.zip" --format=zip
       ${SOURCE} CMakeLists.txt
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})