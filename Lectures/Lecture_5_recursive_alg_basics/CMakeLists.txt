cmake_minimum_required(VERSION 3.10)
project(recursive_alg)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE 
        test_tracker.cpp
        OperationTracker.hpp
        FactorialTracker.hpp
        GCDTracker.hpp
        TowerOfHanoiTracker.hpp
        BinarySearchTracker.hpp
        catch.hpp)

add_executable(test_tracker ${SOURCE})

enable_testing()

add_test(test-tracker test_tracker)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec5.zip" --format=zip
       ${SOURCE} CMakeLists.txt
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})