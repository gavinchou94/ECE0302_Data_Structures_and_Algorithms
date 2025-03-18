/** @file test_iterator.cpp
 * @author G. Zhou
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "iterator.hpp"

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <typeinfo>

TEST_CASE("Using iterator to traverse vector", "[vector]")
{
  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::vector<int>::iterator it;
  int sum = 0;
  for (it = vec.begin(); it != vec.end(); ++it)
  {
    sum += *it;
    std::cout << "It now points to " << *it << std::endl;
    std::cout << "Its address is " << &(*it) << std::endl;
    std::cout << std::endl;
  }
  REQUIRE(sum == 15);
  std::cout << typeid(it).name() << std::endl;
}

TEST_CASE("Using reverse iterator to traverse vector", "[vector]")
{
  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::vector<int>::reverse_iterator rit;
  int product = 1;
  for (rit = vec.rbegin(); rit != vec.rend(); ++rit)
  {
    product *= *rit;
    std::cout << "It now points to " << *rit << std::endl;
    std::cout << "Its address is " << &(*rit) << std::endl;
    std::cout << std::endl;
  }
  REQUIRE(product == 120);
}

TEST_CASE("Iterator increment and decrement", "[vector]")
{
  std::vector<int> vec = {10, 20, 30, 40, 50};
  std::vector<int>::iterator it = vec.begin();

  REQUIRE(*it == 10);

  ++it;
  REQUIRE(*it == 20);

  it++;
  REQUIRE(*it == 30);

  --it;
  REQUIRE(*it == 20);

  it--;
  REQUIRE(*it == 10);
}

TEST_CASE("Iterator arithmetic operations", "[vector]")
{
  std::vector<int> vec = {10, 20, 30, 40, 50};
  std::vector<int>::iterator it = vec.begin();

  REQUIRE(*(it + 2) == 30);
  REQUIRE(*(it + 4) == 50);

  it += 3;
  REQUIRE(*it == 40);

  it -= 2;
  REQUIRE(*it == 20);
}

TEST_CASE("Iterator comparison", "[vector]")
{
  std::vector<int> vec = {10, 20, 30, 40, 50};
  std::vector<int>::iterator it1 = vec.begin();
  std::vector<int>::iterator it2 = vec.begin() + 2;

  REQUIRE(it1 != it2);
  REQUIRE(it1 < it2);
  REQUIRE(*it1 != *it2);

  ++it1;
  ++it1;
  REQUIRE(it1 == it2);
  REQUIRE(*it1 == *it2);
}

TEST_CASE("Iterator erase and insert", "[vector]")
{
  std::vector<int> vec = {10, 20, 30, 40, 50};
  std::vector<int>::iterator it = vec.begin();

  // Erase the second element (20)
  it = vec.erase(it + 1);
  REQUIRE(vec.size() == 4);
  REQUIRE(vec[1] == 30);

  // Insert 25 at the position of the erased element
  it = vec.insert(it, 25);
  REQUIRE(vec.size() == 5);
  REQUIRE(vec[1] == 25);

  // Insert 15 at the beginning
  it = vec.insert(vec.begin(), 15);
  REQUIRE(vec.size() == 6);
  REQUIRE(vec[0] == 15);

  // Erase the last element (50)
  it = vec.erase(vec.end() - 1);
  REQUIRE(vec.size() == 5);
  REQUIRE(vec.back() == 40);
}
// TODO: based on the above lines, what are the return type of erase and insert?
// Test yourself what are the return value if erase and insert on vector get invalid?

TEST_CASE("Using while loop to traverse vector and measure time", "[vector]")
{
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<int> vec(1000, 1);
  std::vector<int>::iterator it = vec.begin();
  int sum = 0;
  while (it != vec.end())
  {
    sum += *it;
    ++it;
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "1000 items added, Time taken: " << elapsed.count() << " seconds" << std::endl;
  REQUIRE(sum == 1000);

  start = std::chrono::high_resolution_clock::now();
  std::vector<int> vec2(100000, 1);
  it = vec2.begin();
  sum = 0;
  while (it != vec2.end())
  {
    sum += *it;
    ++it;
  }
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "100000 items added, Time taken: " << elapsed.count() << " seconds" << std::endl;
  REQUIRE(sum == 100000);

  start = std::chrono::high_resolution_clock::now();
  std::vector<int> vec3(10000000, 1);
  it = vec3.begin();
  sum = 0;
  while (it != vec3.end())
  {
    sum += *it;
    ++it;
  }
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "10000000 items added, Time taken: " << elapsed.count() << " seconds" << std::endl;
  REQUIRE(sum == 10000000);
}
// Verify that the time increases by around 100 times and confirms to be O(n)
// More time complexity could incur if complex module is placed inside iterator loop

TEST_CASE("Using iterator to copy vector", "[vector]")
{
  auto start = std::chrono::high_resolution_clock::now();

  const int SIZE = 500; // change to 50 or 5000 to see the time difference
  std::vector<int> vec1(SIZE, 1);
  std::vector<int>::iterator it1 = vec1.begin();

  std::vector<int> vec2(vec1.size());
  std::vector<int>::iterator it2 = vec2.begin() + vec2.size() - 1;

  while (it1 - vec1.begin() < vec1.size())
  {
    int copied_item = *it1;
    *it2 = copied_item;
    it1 = it1 + 2; // Skip every other item
    it2 = it2 - 2;
    // it1 = it1 + (it1 - vec1.begin() + 1); // equivalent to it1 = it1 * 2;
    // it2 = it2 - (it1 - vec1.begin() + 1); //
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Time taken to copy some items in vector: " << elapsed.count() << " seconds" << std::endl;
  REQUIRE(vec2[SIZE - 1] == 1);
}

TEST_CASE("Using iterator to traverse string", "[string]")
{
  std::string str = "hello";
  std::string::iterator it;
  std::string result;
  for (it = str.begin(); it != str.end(); ++it)
  {
    result += *it;
  }
  REQUIRE(result == "hello");
}

TEST_CASE("Using reverse iterator to traverse string", "[string]")
{
  std::string str = "hello";
  std::string::reverse_iterator rit;
  std::string result;
  for (rit = str.rbegin(); rit != str.rend(); ++rit)
  {
    result += *rit;
  }
  REQUIRE(result == "olleh");
}