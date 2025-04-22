cmake_minimum_required(VERSION 3.10)
project(graph_search)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE AStar.hpp Dijkstra.hpp Prim.hpp
    test_graph_search.cpp catch.hpp)

add_executable(test_graph ${SOURCE})

enable_testing()

add_test(test-graph-search test_graph_search)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec25_26.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})