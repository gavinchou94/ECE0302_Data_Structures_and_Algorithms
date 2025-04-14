cmake_minimum_required(VERSION 3.10)
project(bonus)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_database.cpp Database.hpp Database.tpp 
        binary_search_tree.hpp binary_search_tree.tpp list.hpp list.tpp)

if(EXISTS "${PROJECT_SOURCE_DIR}/Node.tpp" AND EXISTS "${PROJECT_SOURCE_DIR}/Node.hpp")
    set(SOURCE ${SOURCE} Node.tpp Node.hpp)
endif()

add_executable(test-database catch.hpp abstract_list.hpp ${SOURCE})

enable_testing()

add_test(test-database test-database)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/projectX_submission.zip" --format=zip
    ${SOURCE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}) 

add_custom_target(starter_download COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../projectX_starter.zip" --format=zip
  ${SOURCE} CMakeLists.txt catch.hpp abstract_list.hpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})