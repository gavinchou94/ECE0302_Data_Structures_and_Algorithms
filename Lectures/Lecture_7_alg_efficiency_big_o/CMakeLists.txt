cmake_minimum_required(VERSION 3.10)
project(alg_efficiency_big_o)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE 
        test_array.cpp
        ArrayBagInt.hpp
        catch.hpp)

add_executable(alg_eff ${SOURCE})

enable_testing()

add_test(alg_eff alg_eff)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec7.zip" --format=zip
       ${SOURCE} CMakeLists.txt
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})