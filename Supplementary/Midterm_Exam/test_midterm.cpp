#define CATCH_CONFIG_MAIN

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <memory>

#include "catch.hpp"
#include "Midterm.hpp"

TEST_CASE("Your Midterm Exam test case 1", "[final]")
{
    int course = 302;
    int course_copy = 202 + 100;
    std::cout << "Good luck with Midterm Exam of ECE " << course << std::endl;
    REQUIRE(course == course_copy);
}

TEST_CASE("Your Midterm Exam test case 2", "[final]")
{
}