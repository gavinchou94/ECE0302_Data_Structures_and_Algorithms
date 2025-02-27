cmake_minimum_required(VERSION 3.10)
project(midterm)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_midterm.cpp Midterm.hpp Midterm.cpp Midterm.tpp ExamInterface.hpp catch.hpp)

add_executable(midterm ${SOURCE})

enable_testing()

add_test(test-midterm midterm)

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../midterm_starter.zip" --format=zip
    ${SOURCE} 
    CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})  