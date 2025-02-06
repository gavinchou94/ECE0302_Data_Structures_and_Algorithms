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

TEST_CASE("Test prefix expression complex", "[prefix]")
{
  std::string s = "+-/abc*+def*gh";

  // if a valid prefix expression starts at a, it must end at a, since a is an operand
  REQUIRE(find_prefix_end(s, 3) == 3);

  // if a valid prefix expression starts at b, it must end at b, since b is an operand
  REQUIRE(find_prefix_end(s, 4) == 4);

  // if a valid prefix expression starts at c, it must end at c, since c is an operand
  REQUIRE(find_prefix_end(s, 5) == 5);

  // if a valid prefix expression starts at the first slash, it must end at b,
  // since b ends the two consecutive valid prefix expressions after the slash
  REQUIRE(find_prefix_end(s, 2) == 4);

  // if a valid prefix expression starts at the only minus, it must end at c,
  // since c ends the two consecutive valid prefix expression after the minus
  REQUIRE(find_prefix_end(s, 1) == 5);

  // now we know -/abc is a valid prefix expression

  // if a valid prefix expression starts at d, it must end at d, since d is an operand
  REQUIRE(find_prefix_end(s, 8) == 8);

  // if a valid prefix expression starts at e, it must end at e, since e is an operand
  REQUIRE(find_prefix_end(s, 9) == 9);

  // if a valid prefix expression starts at f, it must end at f, since f is an operand
  REQUIRE(find_prefix_end(s, 10) == 10);

  // if a valid prefix expression starts at the second plus, it must end at e,
  // since e ends the two consecutive valid prefix expressions after the second plus
  REQUIRE(find_prefix_end(s, 7) == 9);

  // if a valid prefix expression starts at the first star, it must end at f,
  // since f ends the two consecutive valid prefix expressions after the first star
  REQUIRE(find_prefix_end(s, 6) == 10);

  // now we know *+def is also a valid prefix expression

  // if a valid prefix expression starts at the first plus, it must end at f,
  // since f ends the two consecutive valid prefix expressions after the first plus
  REQUIRE(find_prefix_end(s, 0) == 10);

  // now we know +-/abc*+def is a valid prefix expression

  // we would use the same logic to verify that final substring *gh is a valid prefix expression
  REQUIRE(find_prefix_end(s, 12) == 12); // g ends at g
  REQUIRE(find_prefix_end(s, 13) == 13); // h ends at h
  REQUIRE(find_prefix_end(s, 11) == 13); // last star ends at h too

  // given that original s is just two valid prefix expressions concatenated together,
  // it is not a valid prefix expression itself
  REQUIRE(is_valid(s) == false); // this is also verified by find_prefix_end(s, 0) = 10 not 13

  // what and where can we append something to s to make it valid? Fill in the following REQUIRE
  // REQUIRE(is_valid(?+s)); or REQUIRE_FALSE(is_valid(?+s));
  // REQUIRE(is_valid(s+?)); or REQUIRE_FALSE(is_valid(s+?));
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
