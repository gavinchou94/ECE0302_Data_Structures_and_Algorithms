cmake_minimum_required(VERSION 3.10)
project(dict)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_dict.cpp ArrayDictionary.hpp ArrayDictionary.hpp 
                        HashedDictionary.hpp HashedDictionary.tpp 
                        Entry.hpp Entry.tpp)

add_executable(test-dict catch.hpp abstract_dictionary.hpp ${SOURCE})

enable_testing()

add_test(test-dict test-dict)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec20.zip" --format=zip
    ${SOURCE} CMakeLists.txt catch.hpp abstract_dictionary.hpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})