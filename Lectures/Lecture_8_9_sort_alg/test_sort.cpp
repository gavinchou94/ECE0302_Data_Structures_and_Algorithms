/** @file test_sort.cpp
 * @author G. Zhou */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ArrayList.hpp"
#include "sort.hpp"

TEST_CASE("Sort: Integer selection/bubble/insertion sort", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 11);
  lst.insert(4, 25);
  lst.insert(5, 100);

  // Choose one sorting algorithm to test, you can comment the others
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

  // Choose one sorting algorithm to test, you can comment the others
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

  // Choose one sorting algorithm to test, you can comment the others
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

TEST_CASE("Sort: Integer radix sort", "[sorting]")
{
  List<int> lst;

  // Insert 20 numbers
  lst.insert(1, 450);
  lst.insert(2, 7);
  lst.insert(3, 876);
  lst.insert(4, 42);
  lst.insert(5, 234);
  lst.insert(6, 89);
  lst.insert(7, 567);
  lst.insert(8, 15);
  lst.insert(9, 123);
  lst.insert(10, 55);
  lst.insert(11, 789);
  lst.insert(12, 321);
  lst.insert(13, 654);
  lst.insert(14, 111);
  lst.insert(15, 999);
  lst.insert(16, 345);
  lst.insert(17, 502);
  lst.insert(18, 678);
  lst.insert(19, 812);
  lst.insert(20, 456);

  radix_sort(lst);

  // check sorted list
  REQUIRE(lst.getEntry(1) == 7);
  REQUIRE(lst.getEntry(2) == 15);
  REQUIRE(lst.getEntry(3) == 42);
  REQUIRE(lst.getEntry(4) == 55);
  REQUIRE(lst.getEntry(5) == 89);
  REQUIRE(lst.getEntry(6) == 111);
  REQUIRE(lst.getEntry(7) == 123);
  REQUIRE(lst.getEntry(8) == 234);
  REQUIRE(lst.getEntry(9) == 321);
  REQUIRE(lst.getEntry(10) == 345);
  REQUIRE(lst.getEntry(11) == 450);
  REQUIRE(lst.getEntry(12) == 456);
  REQUIRE(lst.getEntry(13) == 502);
  REQUIRE(lst.getEntry(14) == 567);
  REQUIRE(lst.getEntry(15) == 654);
  REQUIRE(lst.getEntry(16) == 678);
  REQUIRE(lst.getEntry(17) == 789);
  REQUIRE(lst.getEntry(18) == 812);
  REQUIRE(lst.getEntry(19) == 876);
  REQUIRE(lst.getEntry(20) == 999);
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

  // Choose one sorting algorithm to test, you can comment the others
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

  // Choose one sorting algorithm to test, you can comment the others
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