cmake_minimum_required(VERSION 3.10)
project(project4_pathfinder)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INTERFACE abstract_list.hpp abstract_queue.hpp)

set(QUEUE_SOURCE list.hpp list.tpp queue.hpp queue.tpp)

if(EXISTS "${PROJECT_SOURCE_DIR}/Node.tpp" AND EXISTS "${PROJECT_SOURCE_DIR}/Node.hpp")
    set(QUEUE_SOURCE ${QUEUE_SOURCE} Node.tpp Node.hpp)
endif()

set(PATHFINDER_SOURCE PathFinder.cpp PathFinder.hpp test_pathfinder.cpp)

set(IMAGE_RESOURCE lib/image.cpp lib/image.h lib/lodepng.cpp lib/lodepng.h lib/gif.cpp lib/gif.h tests/)

set(SOURCE ${QUEUE_SOURCE} ${PATHFINDER_SOURCE} ${IMAGE_RESOURCE})

# create unit tests
add_executable(test-pathfinder catch.hpp abstract_list.hpp abstract_queue.hpp ${SOURCE})

enable_testing()

# unit tests
add_test(test-pathfinder test-pathfinder)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/project4_submission.zip" --format=zip
  ${QUEUE_SOURCE} ${PATHFINDER_SOURCE}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../project4_starter.zip" --format=zip
  ${SOURCE} ${INTERFACE} ${IMAGE_RESOURCE} CMakeLists.txt catch.hpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})