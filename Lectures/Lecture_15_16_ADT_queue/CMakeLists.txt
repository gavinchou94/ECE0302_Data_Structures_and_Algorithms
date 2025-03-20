cmake_minimum_required(VERSION 3.10)
project(queue)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE abstract_queue.hpp abstract_deque.hpp abstract_priority_queue.hpp
            ArrayQueue.hpp ArrayQueue.tpp
            RingDeque.hpp RingDeque.tpp
            ArrayPQ.hpp ArrayPQ.tpp
            test_queue.cpp catch.hpp)

add_executable(test_queue ${SOURCE})

enable_testing()

add_test(test-queue test_queue)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec15_16.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})