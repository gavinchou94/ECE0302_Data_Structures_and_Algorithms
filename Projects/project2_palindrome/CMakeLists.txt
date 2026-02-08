cmake_minimum_required(VERSION 3.10)
project(project2_palindrome)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE FindPalindrome.cpp FindPalindrome.hpp test_FindPalindrome.cpp)

# create unit tests
add_executable(test-FindPalindrome catch.hpp ${SOURCE})

enable_testing()

# unit tests
add_test(test-FindPalindrome test-FindPalindrome)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/project2_submission.zip" --format=zip
    ${SOURCE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../project2_palindrome.zip" --format=zip
    ${SOURCE} catch.hpp CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})