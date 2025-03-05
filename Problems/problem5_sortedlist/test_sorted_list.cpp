#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "sorted_list.hpp"
#include "list.hpp"

/* Provided tests */
TEST_CASE("SortedList: Testing size", "[sorted list]")
{
  SortedList<char> lst;

  REQUIRE(lst.isEmpty());
  REQUIRE(lst.getLength() == 0);

  lst.insert('b');
  REQUIRE(!lst.isEmpty());
  REQUIRE(lst.getLength() == 1);

  lst.insert('a');
  REQUIRE(lst.getLength() == 2);

  lst.removeAt(1);
  REQUIRE(lst.getLength() == 1);

  lst.removeAt(1);
  REQUIRE(lst.getLength() == 0);
  REQUIRE(lst.isEmpty());
}

TEST_CASE("SortedList: Testing insert", "[sorted list]")
{
  SortedList<char> lst;

  char c = 'a';
  while (c <= 'z')
  {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  bool getEntryCheck;
  for (int i = 1; i <= 26; ++i)
  {
    getEntryCheck = (lst.getEntry(i) == 'a' + i - 1); // Note the small change!
    if (!getEntryCheck)
    {
      break;
    }
  }
  REQUIRE(getEntryCheck);
}

TEST_CASE("SortedList: Testing remove", "[sorted list]")
{
  SortedList<char> lst;

  char c = 'a';
  int size = 10;
  while (c < 'a' + size)
  {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == size);

  lst.remove('c');
  REQUIRE(lst.getLength() == size - 1);
  REQUIRE(lst.getEntry(3) == 'd');

  lst.remove('e');
  REQUIRE(lst.getLength() == size - 2);
  REQUIRE(lst.getEntry(6) == 'h');

  lst.remove('a');
  REQUIRE(lst.getLength() == size - 3);
  REQUIRE(lst.getEntry(1) == 'b');
}

TEST_CASE("SortedList: Testing getPosition and repeated items", "[sorted list]")
{
  SortedList<char> lst;

  lst.insert('a');
  lst.insert('d');
  lst.insert('e');
  lst.insert('c');
  lst.insert('b');
  lst.insert('e');
  lst.insert('f');
  lst.insert('e');

  REQUIRE(lst.getLength() == 8);
  REQUIRE(lst.getPosition('a') == 1);
  REQUIRE(lst.getPosition('b') == 2);
  REQUIRE(lst.getPosition('c') == 3);
  REQUIRE(lst.getPosition('d') == 4);
  REQUIRE(lst.getPosition('e') == 5);
  REQUIRE(lst.getPosition('f') == 8);

  lst.clear();
  REQUIRE_THROWS(lst.getPosition('a'));
}

TEST_CASE("SortedList: Testing constructor from unsorted list", "[sorted list]")
{
  List<char> unsorted;

  unsorted.insert(1, 'a');
  unsorted.insert(2, 'd');
  unsorted.insert(3, 'e');
  unsorted.insert(4, 'c');
  unsorted.insert(5, 'b');

  SortedList<char> sorted(unsorted);

  REQUIRE(sorted.getPosition('a') == 1);
  REQUIRE(sorted.getPosition('b') == 2);
  REQUIRE(sorted.getPosition('c') == 3);
  REQUIRE(sorted.getPosition('d') == 4);
  REQUIRE(sorted.getPosition('e') == 5);
}

TEST_CASE("SortedList: Testing list and sorted list std::out_of_range exceptions", "[sorted list]")
{
  List<char> lst;

  REQUIRE_THROWS_AS(lst.remove(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(2, 'a'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(1, 'a'), std::out_of_range);

  lst.insert(1, 'a');
  lst.insert(2, 'b');

  REQUIRE_THROWS_AS(lst.remove(3), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(4, 'c'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(3), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(3, 'c'), std::out_of_range);

  SortedList<char> sorted;
  sorted.insert('a');
  sorted.insert('b');
  sorted.insert('c');
  sorted.insert('d');
  sorted.insert('e');

  REQUIRE_THROWS_AS(sorted.removeAt(6), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.getEntry(6), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.removeAt(-1), std::out_of_range);
}

/* Your tests here */