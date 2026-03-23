cmake_minimum_required(VERSION 3.10)
project(priorityqueue)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INTERFACES abstract_list.hpp abstract_sorted_list.hpp abstract_priority_queue.hpp)
set(SOURCE 
    test_priority_queue.cpp 
    list.hpp list.tpp
    sorted_list.hpp sorted_list.tpp
    priority_queue.hpp priority_queue.tpp
    )

# include Node if present
if(EXISTS "${PROJECT_SOURCE_DIR}/Node.tpp" AND EXISTS "${PROJECT_SOURCE_DIR}/Node.hpp")
    set(SOURCE ${SOURCE} Node.tpp Node.hpp)
endif()

# create unittests
add_executable(test-priority-queue test_priority_queue.cpp catch.hpp ${SOURCE} ${INTERFACES})
enable_testing()

# unit tests
add_test(test-priority-queue test-priority-queue)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem7_submission.zip" --format=zip
    ${SOURCE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../problem7_priorityqueue.zip" --format=zip
    ${SOURCE} ${INTERFACES} CMakeLists.txt catch.hpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})