/** @file test_array.cpp
 * @author G. Zhou
 */

#define CATCH_CONFIG_MAIN

#include "ArrayBagInt.hpp"
#include "catch.hpp"

TEST_CASE("Test remove method", "[ArrayBagInt]")
{
  ArrayBagInt bag;
  REQUIRE(bag.isEmpty());
  for (int i = 0; i < 100; i++)
  {
    bag.add(i * i - 24 * i + 100); // just add 100 items, some of which are duplicates
                                   // 100, 77, 56, etc.
  }
  REQUIRE(bag.getCurrentSize() == 100);

  // test remove method
  REQUIRE(bag.remove(100)); // remove an item
  REQUIRE(bag.getCurrentSize() == 99);

  // test remove2 method
  REQUIRE(bag.remove2(77)); // remove an item
  REQUIRE(bag.getCurrentSize() == 98);
}

TEST_CASE("Test clear method", "[ArrayBagInt]")
{
  ArrayBagInt bag;
  REQUIRE(bag.isEmpty());

  // test clear method
  for (int i = 0; i < 100; i++)
  {
    bag.add(i * i - 24 * i + 100); // just add 100 items, some of which are duplicates
                                   // 100, 77, 56, etc.
  }
  REQUIRE(bag.getCurrentSize() == 100);
  bag.clear();
  REQUIRE(bag.isEmpty());

  // test clear2 method
  for (int i = 0; i < 100; i++)
  {
    bag.add(i * i - 24 * i + 100);
  }
  REQUIRE(bag.getCurrentSize() == 100);
  bag.clear2();
  REQUIRE(bag.isEmpty());

  // test clear3 method
  for (int i = 0; i < 100; i++)
  {
    bag.add(i * i - 24 * i + 100);
  }
  REQUIRE(bag.getCurrentSize() == 100);
  bag.clear3();
  REQUIRE(bag.isEmpty());

  // test clear4 method
  for (int i = 0; i < 100; i++)
  {
    bag.add(i * i - 24 * i + 100);
  }
  REQUIRE(bag.getCurrentSize() == 100);
  bag.clear4();
  REQUIRE(bag.isEmpty());
}

TEST_CASE("Test remove/clear with timestamp", "[ArrayBagInt]")
{
  ArrayBagInt bag;

  for (int i = 0; i < 100000; i++)
  {
    bag.add(i * i - 24 * i + 100);
  }
  REQUIRE(bag.getCurrentSize() == 100000);
  clock_t start = clock();
  bag.remove(500 * 500 - 24 * 500 + 100); // remove an item in the middle
  clock_t end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  std::cout << "remove() time used: " << seconds << " seconds" << std::endl;

  for (int i = 0; i < 100000; i++)
  {
    bag.add(i * i - 24 * i + 100);
  }
  start = clock();
  bag.remove2(500 * 500 - 24 * 500 + 100); // remove an item in the middle
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  std::cout << "remove2() time used: " << seconds << " seconds" << std::endl;

  bag.clear();
  for (int i = 0; i < 100000; i++)
  {
    bag.add(i * i - 24 * i + 100);
  }
  start = clock();
  bag.clear();
  end = clock();
  REQUIRE(bag.isEmpty());
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  std::cout << "clear() time used: " << seconds << " seconds" << std::endl;

  for (int i = 0; i < 100000; i++)
  {
    bag.add(i * i - 24 * i + 100);
  }
  start = clock();
  bag.clear2();
  end = clock();
  REQUIRE(bag.isEmpty());
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  std::cout << "clear2() time used: " << seconds << " seconds" << std::endl;

  for (int i = 0; i < 100000; i++)
  {
    bag.add(i * i - 24 * i + 100);
  }
  start = clock();
  bag.clear3();
  end = clock();
  REQUIRE(bag.isEmpty());
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  std::cout << "clear3() time used: " << seconds << " seconds" << std::endl;

  for (int i = 0; i < 100000; i++)
  {
    bag.add(i * i - 24 * i + 100);
  }
  start = clock();
  bag.clear4();
  end = clock();
  REQUIRE(bag.isEmpty());
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  std::cout << "clear4() time used: " << seconds << " seconds" << std::endl;
}