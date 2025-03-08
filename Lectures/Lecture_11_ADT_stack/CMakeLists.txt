cmake_minimum_required(VERSION 3.10)
project(stack)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ARRAY_SOURCE StackInterface.hpp ArrayStack.hpp ArrayStack.tpp test_array_stack.cpp catch.hpp)
set(LINKED_SOURCE StackInterface.hpp LinkedStack.hpp LinkedStack.tpp test_linked_stack.cpp Node.hpp Node.tpp catch.hpp)

add_executable(test_array_stack ${ARRAY_SOURCE})
add_executable(test_linked_stack ${LINKED_SOURCE})

enable_testing()

add_test(test-array-stack test_array_stack)
add_test(test-linked-stack test_linked_stack)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec11.zip" --format=zip
    ${ARRAY_SOURCE} ${LINKED_SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})