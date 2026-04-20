cmake_minimum_required(VERSION 3.10)
project(ADT_bag_list_exception)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE 
        test_bag.cpp
        BagInterface.hpp
        ArrayBag.hpp ArrayBag.tpp
        catch.hpp)

add_executable(test_bag ${SOURCE})

enable_testing()

add_test(test-bag test_bag)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec3.zip" --format=zip
       ${SOURCE} CMakeLists.txt
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})