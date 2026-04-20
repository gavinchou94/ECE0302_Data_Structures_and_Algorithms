cmake_minimum_required(VERSION 3.10)
project(map)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_map.cpp ArrayMap.hpp ArrayMap.tpp TreeMap.hpp TreeMap.tpp
                        HashedMap.hpp HashedMap.tpp 
                        Entry.hpp Entry.tpp)

add_executable(test-map catch.hpp abstract_map.hpp ${SOURCE})

enable_testing()

add_test(test-map test-map)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec20.zip" --format=zip
    ${SOURCE} CMakeLists.txt catch.hpp abstract_map.hpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})