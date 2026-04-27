cmake_minimum_required(VERSION 3.10)
project(final)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_final.cpp Final.hpp Final.tpp Final.cpp ExamInterface.hpp catch.hpp)

add_executable(final ${SOURCE})

# If not running on Codespace or not having the same file structure,
# you may need to just comment out the following line
target_include_directories(final PRIVATE
    ../../Lectures/Lecture_15_ADT_queue
    ../../Lectures/Lecture_16_ADT_priorityqueue
    ../../Lectures/Lecture_17_ADT_tree
    ../../Lectures/Lecture_18_ADT_bst
    ../../Lectures/Lecture_19_ADT_heap
    ../../Lectures/Lecture_20_ADT_map
    ../../Lectures/Lecture_21_balanced_search_tree
    ../../Lectures/Lecture_22_twothree_trees
    ../../Lectures/Lecture_23_redblack_trees
    ../../Lectures/Lecture_24_ADT_graph
    ../../Lectures/Lecture_25_graph_search
    ../../Lectures/Lecture_26_spanning_tree
)

enable_testing()

add_test(test-final final)

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../final_starter.zip" --format=zip
    ${SOURCE} 
    CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})  