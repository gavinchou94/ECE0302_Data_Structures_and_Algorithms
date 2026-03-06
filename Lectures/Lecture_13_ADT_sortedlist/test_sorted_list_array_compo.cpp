/** @file test_sorted_list.cpp
 * @author G. Zhou */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "sorted_list_array_compo.hpp"
#include "ArrayList.hpp"

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
};

TEST_CASE("SortedList: Testing insert", "[sorted list]")
{
   SortedList<char> lst;

   char c = 'a';
   while (c <= 'g')
   {
      lst.insert(c);
      ++c;
   }
   REQUIRE(lst.getLength() == 7);

   bool getEntryCheck;
   for (int i = 1; i <= 7; ++i)
   {
      getEntryCheck = (lst.getEntry(i) == 'a' + i - 1);
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
   int size = 9;
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

TEST_CASE("SortedList: Comparing Linked and Array-based sorted list", "[sorted list]")
{
   // SortedList<char> lst; assume the list is sorted in ascending order
   // Suppose lst is built from inserting 'z', 'y', 'x', ..., 'a' by order
   // The insertion cost is already incurred and should not be considered

   // Case 1: Remove characters from the sorted list
   // Most removals target characters near the end of the alphabet
   // Like lst.remove('x'), lst.remove('y'), lst.remove('z')
   // Which implementation is better for this removal pattern?
   // A. Linked-based  B. Array-based

   // Case 2: Insert 20 instances of 'b' into the sorted list
   // Which implementation is better for this insertion pattern?
   // A. Linked-based  B. Array-based
}

// Sort by another field, e.g., key:value pair
struct PittStudent
{
   std::string name;
   std::string PeopleSoftID;
   static bool sortByID;

   // must overload some operators for struct PittStudent before it can be used with SortedList
   // TODO: but some of the following overloaded operators are not necessary, which ones are needed?
   bool operator<(const PittStudent &other) const { return sortByID ? (PeopleSoftID < other.PeopleSoftID) : (name < other.name); }
   bool operator>(const PittStudent &other) const { return sortByID ? (PeopleSoftID > other.PeopleSoftID) : (name > other.name); }
   bool operator==(const PittStudent &other) const { return sortByID ? (PeopleSoftID == other.PeopleSoftID) : (name == other.name); }
   bool operator!=(const PittStudent &other) const { return sortByID ? (PeopleSoftID != other.PeopleSoftID) : !(name == other.name); }
};

// Define the static member
bool PittStudent::sortByID = false;

class sortedPittStudent
{
private:
   SortedList<PittStudent> lst;

public:
   sortedPittStudent() : lst() {}
   PittStudent getEntry(int position) const { return lst.getEntry(position); }

   void change_to_ID() { PittStudent::sortByID = true; }
   void insert(PittStudent &item)
   {
      lst.insert(item);
   }
};

TEST_CASE("SortedList: Testing PittStudent", "[sorted list]")
{
   sortedPittStudent studentList;

   PittStudent student1 = {"Alice", "12345"};
   PittStudent student2 = {"Bob", "54321"};
   PittStudent student3 = {"Charlie", "37890"};

   // Test sorting by name
   studentList.insert(student3);
   studentList.insert(student1);
   studentList.insert(student2);

   REQUIRE(studentList.getEntry(1).name == "Alice");
   REQUIRE(studentList.getEntry(2).name == "Bob");
   REQUIRE(studentList.getEntry(3).name == "Charlie");
}

TEST_CASE("SortedList: Testing sort by ID", "[sorted list]")
{
   sortedPittStudent studentList;

   PittStudent student1 = {"Alice", "12345"};
   PittStudent student2 = {"Bob", "54321"};
   PittStudent student3 = {"Charlie", "37890"};

   // Test sorting by ID
   studentList.change_to_ID();
   studentList.insert(student1);
   studentList.insert(student2);
   studentList.insert(student3);

   REQUIRE(studentList.getEntry(1).PeopleSoftID == "12345");
   REQUIRE(studentList.getEntry(2).PeopleSoftID == "37890");
   REQUIRE(studentList.getEntry(3).PeopleSoftID == "54321");
}

TEST_CASE("SortedList: Testing sorting other built-in types or ADTs", "[sorted list]")
{
   REQUIRE(false < true);
   REQUIRE(false != true);

   SortedList<bool> lst;
   lst.insert(true);
   lst.insert(true);
   lst.insert(false);
   lst.insert(true);
   lst.insert(false);
   lst.insert(true);

   REQUIRE(lst.getEntry(1) == false);

   // TODO: First finish the tests to verify lst.getEntry(2) and lst.getEntry(3) and so on,
   // then answer the following question:
   // What does this tell you about the prerequisites for ItemType in SortedList?
   // In other words, under what conditions can you use SortedList<Date> or SortedList<BitArray>?
}