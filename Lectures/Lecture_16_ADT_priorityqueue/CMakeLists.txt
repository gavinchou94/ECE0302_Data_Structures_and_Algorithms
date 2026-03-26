cmake_minimum_required(VERSION 3.10)
project(priorityqueue)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE abstract_priority_queue.hpp
            ArrayPQ.hpp ArrayPQ.tpp
            test_pq.cpp catch.hpp)

add_executable(test_pq ${SOURCE})

enable_testing()

add_test(test-pq test_pq)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec16.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})