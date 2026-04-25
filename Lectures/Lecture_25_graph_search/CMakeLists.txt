cmake_minimum_required(VERSION 3.10)
project(graphsearch)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE abstract_graph.hpp
    Edge.hpp Edge.tpp
    Vertex.hpp Vertex.tpp
    LinkedGraph.hpp LinkedGraph.tpp
    GraphSearch.hpp GraphSearch.tpp
    test_graph_search.cpp catch.hpp)

add_executable(test_graphsearch ${SOURCE})

enable_testing()

add_test(test-graphsearch test_graphsearch)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec25.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})