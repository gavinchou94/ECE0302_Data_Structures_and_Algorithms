#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "list.hpp"
#include "sort.hpp"

/* Provided test cases */
TEST_CASE("Sort: Test move entry", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  // move forward
  lst.moveEntry(1, 3);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 100);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 11);

  // move backward
  lst.moveEntry(5, 1);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 11);
  REQUIRE(lst.getEntry(2) == 4);
  REQUIRE(lst.getEntry(3) == 10);
  REQUIRE(lst.getEntry(4) == 100);
  REQUIRE(lst.getEntry(5) == 25);
}

TEST_CASE("Sort: Integer sorting", "[sorting]")
{

  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  quick_sort(lst, 0, lst.getLength() - 1);

  // check sorted list
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 11);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 100);
}

/* Your test cases here */
