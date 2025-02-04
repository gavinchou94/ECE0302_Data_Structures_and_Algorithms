/** @file test_prefix.cpp
 * @author Frank M. Carrano, Tim Henry
 * @copyright 2017 Pearson Education
 * @version 2.0, modified in 2025 by G. Zhou for ECE0302
 */

#define CATCH_CONFIG_MAIN

#include "evaluate_prefix.hpp"
#include "writeBackward.hpp"
#include "catch.hpp"
#include <iostream>
#include <string>

TEST_CASE("Test writeBackward_re", "[writeBackward_re]")
{
  std::string s = "Hello";
  writeBackward_re(s);
  std::cout << std::endl;
}

TEST_CASE("Test writeBackward_it", "[writeBackward_it]")
{
  std::string s = "abcd";
  writeBackward_it(s);
  std::cout << std::endl;
}

TEST_CASE("Test prefix expression ending char", "[prefix]")
{
  std::string s = "*+132";
  REQUIRE(find_prefix_end(s, 0) == 4); // * would include operand until '2', which is s[4]
  REQUIRE(find_prefix_end(s, 1) == 3); // + would include operand until '3', which is s[3]
  // for find_prefix_end, what is not tested yet?
}

TEST_CASE("Test prefix expression validity", "[prefix]")
{
  std::string s = "*+132";
  REQUIRE(is_valid(s) == true);
  s = "*+132+";
  REQUIRE(is_valid(s) == false);
  s = "7";
  REQUIRE(is_valid(s) == true);
  s = "+";
  REQUIRE(is_valid(s) == false);
}

TEST_CASE("Test prefix expression evaluation", "[prefix]")
{
  std::string s = "*+132";
  REQUIRE(evaluate_prefix(s) == 8); // 1 + 3 = 4, 4 * 2 = 8
}

TEST_CASE("Test prefix expression evaluation complex", "[prefix]")
{
  std::string s = "*-+1323";
  REQUIRE(evaluate_prefix(s) == 6); // 1 + 3 = 4, 4 - 2 = 2, 2 * 3 = 6
}
