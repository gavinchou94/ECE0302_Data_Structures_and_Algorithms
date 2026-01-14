cmake_minimum_required(VERSION 3.10)
project(add)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(STUDENT_SOURCE test_add.cpp add.hpp add.tpp)
set(SOURCE abstract_operator.hpp ${STUDENT_SOURCE})

# create unit tests
add_executable(test-add catch.hpp ${SOURCE})

enable_testing()

# unit tests
add_test(test-add test-add)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem1_submission.zip" --format=zip
       ${STUDENT_SOURCE}
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../problem1_starter.zip" --format=zip
       ${STUDENT_SOURCE} abstract_operator.hpp catch.hpp CMakeLists.txt
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})