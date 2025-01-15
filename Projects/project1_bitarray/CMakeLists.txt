cmake_minimum_required(VERSION 3.10)
project(project1_bitarray)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_bitarray.cpp bitset.hpp bitarray.hpp bitarray.cpp)

# create unit tests
add_executable(test-bitarray catch.hpp ${SOURCE})

enable_testing()

# unit tests
add_test(test-bitarray test-bitarray)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/project1_submission.zip" --format=zip
       ${SOURCE}
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../project1_starter.zip" --format=zip
       ${SOURCE} catch.hpp CMakeLists.txt
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})