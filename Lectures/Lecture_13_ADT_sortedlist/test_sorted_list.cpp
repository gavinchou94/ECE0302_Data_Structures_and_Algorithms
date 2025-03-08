/** @file test_sorted_list.cpp
 * @author G. Zhou
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "sorted_list.hpp"
#include "ArrayList.hpp"
#include <algorithm>

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
   // SortedList<char> lst; and assuming the list is sorted small to large
   // Supposing lst has been inserted with 'z', 'y', 'x' until 'a'
   // the above cost is already spent, and no need to consider it any more

   // Case 1: We are about to remove some chars from the sorted list
   // Most of the removals are x, y, z, u, v, w (letters near the end of alphabet)

   // Which implementation is better in terms of above removal Case 1?
   // A. Linked-based sorted list B. Array-based sorted list

   // Case 2: We are about to insert 20 chars of 'b' to the sorted list
   // Which implementation is better in terms of above removal Case 2?
   // A. Linked-based sorted list B. Array-based sorted list
}

// Sort by another field, e.g., key:value pair
struct PittStudent
{
   std::string name;
   std::string PeopleSoftID;

   // must overload some operators for struct PittStudent, why?
   // but some of them are not needed, which ones are needed?
   bool operator<(const PittStudent &other) const { return name < other.name; }
   bool operator>(const PittStudent &other) const { return name > other.name; }
   bool operator==(const PittStudent &other) const { return name == other.name; }
   bool operator!=(const PittStudent &other) const { return !(name == other.name); }
};

class sortedPittStudent
{
private:
   SortedList<PittStudent> lst;
   bool sortbyID = false;

public:
   sortedPittStudent() : lst() {}
   PittStudent getEntry(std::size_t position) const { return lst.getEntry(position); }

   void change_to_ID() { sortbyID = true; }
   void insert(PittStudent &item)
   {
      if (sortbyID)
      {
         swap(item.name, item.PeopleSoftID);
      }
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

   REQUIRE(studentList.getEntry(1).name == "12345");
   REQUIRE(studentList.getEntry(2).name == "37890");
   REQUIRE(studentList.getEntry(3).name == "54321");
}

TEST_CASE("SortedList: Testing other sort", "[sorted list]")
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
   // finish getEntry(2) and getEntry(3)

   // what does this tell you about the prerequisite of ItemType of sortedlist?
   // Or in other words, under what condition can you use SortedList<Date> or SortedList<BitArray>?
}
