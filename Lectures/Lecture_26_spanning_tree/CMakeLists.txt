cmake_minimum_required(VERSION 3.10)
project(graph_search)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE abstract_graph.hpp
    Edge.hpp Edge.tpp
    Vertex.hpp Vertex.tpp
    LinkedGraph.hpp LinkedGraph.tpp
    SpanningTree.hpp SpanningTree.tpp
    TreePrinter.hpp
    test_spanning_tree.cpp catch.hpp)

add_executable(test_spanning_tree ${SOURCE})

enable_testing()

add_test(test-spanning-tree test_spanning_tree)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec26.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})