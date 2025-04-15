cmake_minimum_required(VERSION 3.10)
project(project5_puzzle)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_solver.cpp frontier_queue.hpp frontier_queue.tpp puzzle_solver.hpp puzzle_solver.cpp)
set(IMAGE_RESOURCE lib/image.cpp lib/image.h lib/lodepng.cpp lib/lodepng.h lib/gif.cpp lib/gif.h)

add_executable(test-solver test_solver.cpp catch.hpp
  puzzle.hpp puzzle.cpp state.hpp state.tpp
  ${SOURCE} ${IMAGE_RESOURCE})

enable_testing()
add_test(test-solver test-solver)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/project5_submission.zip" --format=zip
  ${SOURCE}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../project5_starter.zip" --format=zip
  test_solver.cpp catch.hpp puzzle.hpp puzzle.cpp state.hpp state.tpp ${SOURCE} ${IMAGE_RESOURCE} "lib/*"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})