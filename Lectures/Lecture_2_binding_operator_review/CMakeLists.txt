cmake_minimum_required(VERSION 3.10)
project(binding_operator_review)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE 
        test_boxes.cpp
        BoxInterface.hpp
        PlainBox.hpp PlainBox.tpp
        ToyBox.hpp ToyBox.tpp
        MagicBox.hpp MagicBox.tpp
        AddingBox.hpp AddingBox.tpp
        catch.hpp)

add_executable(test_boxes ${SOURCE})

enable_testing()

add_test(test-boxes test_boxes)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec2.zip" --format=zip
       ${SOURCE} CMakeLists.txt
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})