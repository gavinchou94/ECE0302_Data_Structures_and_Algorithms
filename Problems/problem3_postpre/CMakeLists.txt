cmake_minimum_required(VERSION 3.10)
project(postpre)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_postpre.cpp algebraic_expressions.hpp algebraic_expressions.cpp)

#add_executable(postpre-main postpre.cpp algebraic_expressions.hpp algebraic_expressions.cpp)
add_executable(postpre-test catch.hpp ${SOURCE})

enable_testing()

add_test(postpre-test postpre-test)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem3_submission.zip" --format=zip
    ${SOURCE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../problem3_starter.zip" --format=zip
    ${SOURCE} 
    catch.hpp CMakeLists.txt postpre.cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})  