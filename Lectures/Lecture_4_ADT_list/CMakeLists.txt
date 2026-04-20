cmake_minimum_required(VERSION 3.10)
project(list_implementations)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE 
        test_list.cpp
        ListInterface.hpp
        Node.hpp Node.tpp
        ArrayList.hpp ArrayList.tpp
        LinkedList.hpp LinkedList.tpp
        catch.hpp)

add_executable(test_list ${SOURCE})

enable_testing()

add_test(test-list test_list)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec4.zip" --format=zip
       ${SOURCE} CMakeLists.txt
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})