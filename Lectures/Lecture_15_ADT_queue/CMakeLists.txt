cmake_minimum_required(VERSION 3.10)
project(queue)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE abstract_queue.hpp abstract_deque.hpp
            ArrayQueue.hpp ArrayQueue.tpp
            RingDeque.hpp RingDeque.tpp
            LinkedDeque.hpp LinkedDeque.tpp
            DoubleLinkNode.hpp DoubleLinkNode.tpp
            evaluate_postfix.hpp
            test_queue.cpp catch.hpp)

add_executable(test_queue ${SOURCE})

enable_testing()

add_test(test-queue test_queue)

add_custom_target(direct_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../Lec15.zip" --format=zip
    ${SOURCE} CMakeLists.txt
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Apple leaks tool for memory leak detection (macOS only)
# find_program(LEAKS "leaks")
# if(LEAKS)
#     add_custom_target(leaks
#         COMMAND leaks --atExit -- $<TARGET_FILE:test_queue>
#         DEPENDS test_queue
#         COMMENT "Running Apple leaks on test_queue")
# endif()