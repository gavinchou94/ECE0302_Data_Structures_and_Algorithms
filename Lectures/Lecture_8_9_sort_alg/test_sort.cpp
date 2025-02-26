/** @file test_sort.cpp
 * @author G. Zhou
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "list.hpp"
#include "sort.hpp"

TEST_CASE("Sort: Integer selection/bubble/insertion sort", "[sorting]")
{

  List<int> lst;

  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 11);
  lst.insert(4, 25);
  lst.insert(5, 100);

  // selection_sort(lst);
  // bubble_sort(lst);
  insertion_sort(lst);

  // check sorted list
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 11);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 100);

  lst.clear();

  lst.insert(1, 100);
  lst.insert(2, 25);
  lst.insert(3, 11);
  lst.insert(4, 10);
  lst.insert(5, 4);

  // selection_sort(lst);
  // bubble_sort(lst);
  insertion_sort(lst);

  // check sorted list
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 11);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 100);

  lst.clear();

  lst.insert(1, 100);
  lst.insert(2, 30);
  lst.insert(3, 50);
  lst.insert(4, 4);
  lst.insert(5, 256);
  lst.insert(6, 1);
  lst.insert(7, 0);
  lst.insert(8, 25);
  lst.insert(9, 10);
  lst.insert(10, 512);

  // selection_sort(lst);
  // bubble_sort(lst);
  insertion_sort(lst);

  // check sorted list
  REQUIRE(lst.getEntry(1) == 0);
  REQUIRE(lst.getEntry(2) == 1);
  REQUIRE(lst.getEntry(3) == 4);
  REQUIRE(lst.getEntry(4) == 10);
  REQUIRE(lst.getEntry(5) == 25);
  REQUIRE(lst.getEntry(6) == 30);
  REQUIRE(lst.getEntry(7) == 50);
  REQUIRE(lst.getEntry(8) == 100);
  REQUIRE(lst.getEntry(9) == 256);
  REQUIRE(lst.getEntry(10) == 512);
}

TEST_CASE("Sort: Integer merge/quick sort", "[sorting]")
{

  List<int> lst;

  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 11);
  lst.insert(4, 25);
  lst.insert(5, 100);

  // quick_sort(lst, 1, lst.getLength());
  merge_sort(lst, 1, lst.getLength());

  // check sorted list
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 11);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 100);

  lst.clear();

  lst.insert(1, 100);
  lst.insert(2, 25);
  lst.insert(3, 11);
  lst.insert(4, 10);
  lst.insert(5, 4);

  // quick_sort(lst, 1, lst.getLength());
  merge_sort(lst, 1, lst.getLength());

  // check sorted list
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 11);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 100);

  lst.clear();

  lst.insert(1, 100);
  lst.insert(2, 30);
  lst.insert(3, 50);
  lst.insert(4, 4);
  lst.insert(5, 256);
  lst.insert(6, 1);
  lst.insert(7, 0);
  lst.insert(8, 25);
  lst.insert(9, 10);
  lst.insert(10, 512);

  // quick_sort(lst, 1, lst.getLength());
  merge_sort(lst, 1, lst.getLength());

  // check sorted list
  REQUIRE(lst.getEntry(1) == 0);
  REQUIRE(lst.getEntry(2) == 1);
  REQUIRE(lst.getEntry(3) == 4);
  REQUIRE(lst.getEntry(4) == 10);
  REQUIRE(lst.getEntry(5) == 25);
  REQUIRE(lst.getEntry(6) == 30);
  REQUIRE(lst.getEntry(7) == 50);
  REQUIRE(lst.getEntry(8) == 100);
  REQUIRE(lst.getEntry(9) == 256);
  REQUIRE(lst.getEntry(10) == 512);
}

TEST_CASE("Sort: Character sorting", "[sorting]")
{

  List<char> lst;
  char b[26] = {'Z', 'Y', 'X', 'W', 'V', 'U', 'T', 'S', 'R', 'Q', 'P',
                'O', 'N', 'M', 'L', 'K', 'J', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'};

  for (int i = 0; i < 26; i++)
  {
    lst.insert(i + 1, b[i]);
  }
  selection_sort(lst);
  // bubble_sort(lst);
  // insertion_sort(lst);
  // quick_sort(lst, 1, lst.getLength());
  // merge_sort(lst, 1, lst.getLength());

  // check sorted list
  for (int i = 1; i <= 26; i++)
  {
    REQUIRE(lst.getEntry(i) == b[26 - i]);
  }
}

TEST_CASE("Sort: Double sorting", "[sorting]")
{

  List<double> lst;

  lst.insert(1, 10.4);
  lst.insert(2, 5.2);
  lst.insert(3, 1.5);
  lst.insert(4, 1.0);

  selection_sort(lst);
  // bubble_sort(lst);
  // insertion_sort(lst);
  // quick_sort(lst, 1, lst.getLength());
  // merge_sort(lst, 1, lst.getLength());

  double threshold = 1e-12;

  // check sorted list
  REQUIRE(std::abs(lst.getEntry(1) - 1.0) <= threshold);
  REQUIRE(std::abs(lst.getEntry(2) - 1.5) <= threshold);
  REQUIRE(std::abs(lst.getEntry(3) - 5.2) <= threshold);
  REQUIRE(std::abs(lst.getEntry(4) - 10.4) <= threshold);
}