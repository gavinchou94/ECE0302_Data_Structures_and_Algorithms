cmake_minimum_required(VERSION 3.10)
project(bags)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIMITED_SIZE_BAG_SOURCE limited_size_bag.hpp limited_size_bag.tpp)
set(DYNAMIC_BAG_SOURCE dynamic_bag.hpp dynamic_bag.tpp)

# create unit tests
add_executable(test-bags catch.hpp abstract_bag.hpp test_bags.cpp ${LIMITED_SIZE_BAG_SOURCE} ${DYNAMIC_BAG_SOURCE})

enable_testing()

# unit tests
add_test(test-bags test-bags)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem2_submission.zip" --format=zip
    ${DYNAMIC_BAG_SOURCE}
    ${LIMITED_SIZE_BAG_SOURCE}
    test_bags.cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../problem2_bags.zip" --format=zip
    ${DYNAMIC_BAG_SOURCE}
    ${LIMITED_SIZE_BAG_SOURCE}
    catch.hpp CMakeLists.txt abstract_bag.hpp test_bags.cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})