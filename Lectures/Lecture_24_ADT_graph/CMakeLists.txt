cmake_minimum_required(VERSION 3.10)
project(graph)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE abstract_graph.hpp
    Edge.hpp Edge.tpp
    Vertex.hpp Vertex.tpp
    LinkedGraph.hpp LinkedGraph.tpp
    test_graph.cpp catch.hpp)

add_executable(test_graph ${SOURCE})

enable_testing()

add_test(test-graph test_graph)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec24.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})