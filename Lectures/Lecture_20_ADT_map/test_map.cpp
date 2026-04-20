#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "ArrayMap.hpp"
#include "TreeMap.hpp"
#include "HashedMap.hpp"

//   Implementation | Good at                          | Bad at
//   ---------------|----------------------------------|---------------------------
//   ArrayMap       | sorted traversal, binary search  | insert / remove (O(n) shift)
//   TreeMap        | sorted traversal, avg O(log n)   | worst-case O(n) (skewed tree)
//   HashedMap      | O(1) avg insert/remove/lookup    | sorted order, collision chains

// Shared visit helper for traverse tests
std::vector<std::string> items;
void visit(std::string &item) { items.push_back(item); }

TEST_CASE("ArrayMap -- basic Map contract", "[ArrayMap]")
{
  ArrayMap<int, std::string> map;
  REQUIRE(map.isEmpty());
  REQUIRE(map.getNumberOfItems() == 0);

  REQUIRE(map.add(1, "one"));
  REQUIRE(map.add(2, "two"));
  REQUIRE(map.add(3, "three"));
  REQUIRE(!map.isEmpty());
  REQUIRE(map.getNumberOfItems() == 3);

  // Duplicate key: add must reject it
  REQUIRE_FALSE(map.add(1, "uno"));
  REQUIRE_FALSE(map.add(2, "dos"));
  REQUIRE(map.getNumberOfItems() == 3);

  REQUIRE(map.contains(1));
  REQUIRE(map.contains(2));
  REQUIRE(map.contains(3));
  REQUIRE_FALSE(map.contains(4));

  REQUIRE(map.getItem(1) == "one");
  REQUIRE(map.getItem(2) == "two");
  REQUIRE(map.getItem(3) == "three");
  REQUIRE_THROWS_AS(map.getItem(4), std::invalid_argument); // missing key throws

  REQUIRE(map.remove(2));
  REQUIRE_FALSE(map.contains(2));
  REQUIRE(map.getNumberOfItems() == 2);
  REQUIRE_FALSE(map.remove(2));  // already removed
  REQUIRE_FALSE(map.remove(99)); // never existed

  map.clear();
  REQUIRE(map.isEmpty());
  REQUIRE(map.getNumberOfItems() == 0);
  REQUIRE_FALSE(map.remove(1));
  REQUIRE_THROWS_AS(map.getItem(1), std::invalid_argument);
}

TEST_CASE("TreeMap -- basic Map contract", "[TreeMap]")
{
  TreeMap<int, std::string> map;
  REQUIRE(map.isEmpty());
  REQUIRE(map.getNumberOfItems() == 0);

  REQUIRE(map.add(5, "five"));
  REQUIRE(map.add(2, "two"));
  REQUIRE(map.add(8, "eight"));
  REQUIRE_FALSE(map.add(5, "FIVE")); // duplicate key rejected

  REQUIRE(map.getNumberOfItems() == 3);
  REQUIRE(map.contains(2));
  REQUIRE(map.getItem(8) == "eight");
  REQUIRE_THROWS_AS(map.getItem(4), std::invalid_argument);

  REQUIRE(map.remove(2));
  REQUIRE_FALSE(map.contains(2));
  REQUIRE_FALSE(map.remove(2));

  map.clear();
  REQUIRE(map.isEmpty());
}

TEST_CASE("HashedMap -- basic Map contract", "[HashedMap]")
{
  HashedMap<double, std::string> map;
  REQUIRE(map.isEmpty());
  REQUIRE(map.getNumberOfItems() == 0);

  REQUIRE(map.add(1.14, "one"));
  REQUIRE(map.add(2.35, "two"));
  REQUIRE(map.add(3.98, "three"));
  REQUIRE(!map.isEmpty());
  REQUIRE(map.getNumberOfItems() == 3);

  REQUIRE_FALSE(map.add(2.35, "2.35")); // duplicate key rejected
  REQUIRE(map.getNumberOfItems() == 3);

  REQUIRE(map.contains(1.14));
  REQUIRE(map.contains(2.35));
  REQUIRE(map.contains(3.98));
  REQUIRE_FALSE(map.contains(4.0));

  REQUIRE(map.getItem(1.14) == "one");
  REQUIRE(map.getItem(2.35) == "two");
  REQUIRE(map.getItem(3.98) == "three");
  REQUIRE_THROWS_AS(map.getItem(4.0), std::runtime_error);

  REQUIRE(map.remove(2.35));
  REQUIRE_FALSE(map.contains(2.35));
  REQUIRE(map.getNumberOfItems() == 2);
  REQUIRE_FALSE(map.remove(2.35));
  REQUIRE_FALSE(map.remove(99.0));

  map.clear();
  REQUIRE(map.isEmpty());
  REQUIRE(map.getNumberOfItems() == 0);
  REQUIRE_FALSE(map.remove(1.14));
  REQUIRE_THROWS_AS(map.getItem(1.14), std::runtime_error);
}

TEST_CASE("ArrayMap -- traverse always yields sorted-key order", "[ArrayMap]")
{
  ArrayMap<double, std::string> map;
  map.add(9.0, "9.0");
  map.add(1.0, "1.0");
  map.add(3.3, "3.3");
  map.add(2.2, "2.2");
  map.add(9.9, "9.9");

  map.traverse(visit);
  // ArrayMap maintains a sorted internal array, so this is O(n) with no extra work.

  REQUIRE(items.size() == 5);
  REQUIRE(items[0] == "1.0"); // smallest key visited first
  REQUIRE(items[1] == "2.2");
  REQUIRE(items[2] == "3.3");
  REQUIRE(items[3] == "9.0");
  REQUIRE(items[4] == "9.9"); // largest key visited last
  items.clear();
}

TEST_CASE("TreeMap -- in-order traversal always yields sorted-key order", "[TreeMap]")
{
  TreeMap<int, std::string> map;
  map.add(9, "nine");
  map.add(1, "one");
  map.add(4, "four");
  map.add(2, "two");

  map.traverse(visit);
  // BST in-order walk visits nodes left-root-right, guaranteeing ascending order.

  REQUIRE(items.size() == 4);
  REQUIRE(items[0] == "one");  // key 1
  REQUIRE(items[1] == "two");  // key 2
  REQUIRE(items[2] == "four"); // key 4
  REQUIRE(items[3] == "nine"); // key 9
  items.clear();
}

// Try this visualization of the hashed table:
// https://www.cs.usfca.edu/~galles/visualization/OpenHash.html
// Our given implementation is a hash table with separate chaining

TEST_CASE("HashedMap -- traverse order is NOT sorted and NOT predictable", "[HashedMap]")
{
  HashedMap<double, std::string> map(7);
  REQUIRE(map.isEmpty());
  REQUIRE(map.getNumberOfItems() == 0);

  map.add(1.0, "one");
  map.add(2.0, "two");
  map.add(3.0, "three");
  map.add(4.0, "four");
  map.add(5.0, "five");
  map.add(6.0, "six");
  map.add(7.0, "seven");
  map.add(8.0, "eight");
  map.add(9.0, "nine");
  map.add(10.0, "ten");

  REQUIRE(map.getNumberOfItems() == 10);
  REQUIRE(map.contains(1.0));
  REQUIRE(map.contains(5.0));
  REQUIRE(map.contains(10.0));
  REQUIRE(map.getItem(1.0) == "one");
  REQUIRE(map.getItem(5.0) == "five");
  REQUIRE(map.getItem(10.0) == "ten");

  // Remove from chain (tests prevPtr/curPtr traversal in remove)
  REQUIRE(map.remove(1.0));
  REQUIRE_FALSE(map.contains(1.0));
  REQUIRE_FALSE(map.remove(1.0));
  REQUIRE_THROWS_AS(map.getItem(1.0), std::runtime_error);

  REQUIRE(map.remove(2.0));
  REQUIRE(map.remove(3.0));
  REQUIRE_FALSE(map.remove(2.0));
  REQUIRE_FALSE(map.remove(3.0));
  REQUIRE(map.getNumberOfItems() == 7);

  map.traverse(visit);
  REQUIRE(items.size() == 7);
  std::cout << "Items traversed in hash table in the order: ";
  for (const auto &item : items)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl
            << std::endl;
  items.clear();

  // TODO: Find the visualization in the hpp file to understand Entry, HashEntry, hashTableType and hashedMap structure
  // Run this test case and print out the hash index and the items at each index in the hash table
  // Briefly describe the logic flow if at this point, we remove (5.0, "five") from the map
  // what sub-functions are called under the hood? Which sub-function call is most likely to increase time complexity?

  // Clear then re-add
  map.clear();
  REQUIRE(map.isEmpty());
  REQUIRE(map.getNumberOfItems() == 0);
  REQUIRE(map.add(1.0, "one"));
  REQUIRE(map.getItem(1.0) == "one");
}

TEST_CASE("ArrayMap -- insert shifts elements to maintain sorted order (O(n))", "[ArrayMap]")
{
  // Insert keys in descending order so every insert goes to index 0,
  // forcing the entire existing array to shift right each time.
  ArrayMap<int, std::string> map;
  map.add(8, "eight");
  map.add(7, "seven");
  map.add(6, "six");
  map.add(5, "five");
  map.add(4, "four");
  map.add(3, "three");
  map.add(2, "two");
  map.add(1, "one"); // worst case: shifts all 7 existing items

  // Correctness is preserved — but at growing cost
  REQUIRE(map.getNumberOfItems() == 8);

  map.traverse(visit);
  REQUIRE(items[0] == "one");
  REQUIRE(items[7] == "eight");
  items.clear();
}

TEST_CASE("TreeMap -- insert is O(log n) for a balanced tree", "[TreeMap]")
{
  // Inserting in a non-pathological order gives a reasonably balanced BST.
  // Each insert only traverses the tree height, which is O(log n) on average.
  TreeMap<int, std::string> map;
  map.add(5, "five");  // root
  map.add(2, "two");   // left subtree
  map.add(8, "eight"); // right subtree
  map.add(1, "one");
  map.add(3, "three");
  map.add(7, "seven");
  map.add(9, "nine");

  REQUIRE(map.getNumberOfItems() == 7);
  REQUIRE(map.contains(1));
  REQUIRE(map.contains(9));
}

TEST_CASE("TreeMap -- inserting sorted keys degrades to O(n) skewed tree", "[TreeMap]")
{
  TreeMap<int, std::string> map;
  map.add(1, "one");
  map.add(2, "two");
  map.add(3, "three");
  map.add(4, "four");
  map.add(5, "five");
  map.add(6, "six");
  map.add(7, "seven"); // Under standard BST-based implementation, the tree is now a right-linked list of depth 7
  // But our implementation uses std::set, which is a self-balancing BST

  // Correctness is preserved — but the tree has maximum possible height
  REQUIRE(map.getNumberOfItems() == 7);
  REQUIRE(map.contains(7));
  REQUIRE(map.contains(1));

  // Traversal still visits in sorted order (BST in-order property holds)
  map.traverse(visit);
  REQUIRE(items[0] == "one");
  REQUIRE(items[6] == "seven");
  items.clear();
}

TEST_CASE("HashedMap -- insert is O(1) average, no element shifting", "[HashedMap]")
{
  // Each key hashes to a bucket in O(1); the new entry is prepended to that
  // bucket's chain. No existing entries are moved regardless of table state.
  HashedMap<double, std::string> map; // default table size
  map.add(1.0, "one");
  map.add(2.0, "two");
  map.add(3.0, "three");
  map.add(100.0, "hundred");
  map.add(999.0, "nine-ninety-nine");

  REQUIRE(map.getNumberOfItems() == 5);
  REQUIRE(map.getItem(999.0) == "nine-ninety-nine");
}

TEST_CASE("HashedMap -- correct behavior with collisions (separate chaining)", "[HashedMap]")
{
  // Separate chaining handles this without any data loss.
  HashedMap<double, std::string> map(7);

  for (int i = 0; i <= 10; ++i)
    map.add(static_cast<double>(i), std::to_string(i));

  REQUIRE(map.getNumberOfItems() == 11);
  REQUIRE(map.contains(1.0));
  REQUIRE(map.contains(5.0));
  REQUIRE(map.contains(10.0));
  REQUIRE(map.getItem(1.0) == "1");
  REQUIRE(map.getItem(5.0) == "5");
  REQUIRE(map.getItem(10.0) == "10");

  map.traverse(visit);
  REQUIRE_FALSE((items[0] == "0" && items[1] == "1" && items[2] == "2" && items[3] == "3" && items[4] == "4" &&
                 items[5] == "5" && items[6] == "6" && items[7] == "7" && items[8] == "8" &&
                 items[9] == "9" && items[10] == "10")); // traverse order is not sorted and not predictable
  items.clear();
}

TEST_CASE("ArrayMap -- copy constructor/assignment produces independent copy", "[ArrayMap]")
{
  ArrayMap<int, std::string> map;
  map.add(1, "one");
  map.add(2, "two");
  map.add(3, "three");

  ArrayMap<int, std::string> map2(map);
  REQUIRE(map2.getNumberOfItems() == 3);
  REQUIRE(map2.getItem(1) == "one");
  REQUIRE(map2.getItem(2) == "two");
  REQUIRE(map2.getItem(3) == "three");

  map2.remove(2);
  REQUIRE(map2.getNumberOfItems() == 2);
  REQUIRE(map.getNumberOfItems() == 3); // original unaffected
  REQUIRE(map.contains(2));

  ArrayMap<int, std::string> map3;
  map3.add(1, "one");
  map3.add(2, "two");

  ArrayMap<int, std::string> map4;
  map4.add(9, "nine");
  map4 = map3; // operator=: map4's old contents are discarded

  REQUIRE(map4.getNumberOfItems() == 2);
  REQUIRE(map4.getItem(1) == "one");
  REQUIRE(map4.getItem(2) == "two");
  REQUIRE_FALSE(map4.contains(9)); // old entry gone

  map4.remove(1);
  REQUIRE(map4.getNumberOfItems() == 1);
  REQUIRE(map3.getNumberOfItems() == 2); // original unaffected
}

TEST_CASE("HashedMap -- copy constructor/assignment produces independent copy", "[HashedMap]")
{
  // Because each bucket is a linked chain, deep copy must allocate new nodes
  // for every entry — not just copy the array of head pointers.
  HashedMap<std::string, bool> map;
  map.add("hello", true);
  map.add("hola", false);
  map.add("hi", true);
  map.add("hey", true);

  HashedMap<std::string, bool> map2(map);
  REQUIRE(map2.getNumberOfItems() == 4);
  REQUIRE(map2.getItem("hello") == true);
  REQUIRE(map2.getItem("hola") == false);

  // Mutating the copy must not affect the original
  map2.remove("hi");
  REQUIRE(map2.getNumberOfItems() == 3);
  REQUIRE_FALSE(map2.contains("hi"));
  REQUIRE(map.getNumberOfItems() == 4);
  REQUIRE(map.contains("hi"));

  // Mutating the original must not affect the copy
  map.remove("hello");
  REQUIRE_FALSE(map.contains("hello"));
  REQUIRE(map2.contains("hello"));

  HashedMap<std::string, bool> map3;
  map3.add("yes", true);
  map3.add("no", false);
  map3.add("maybe", true);

  HashedMap<std::string, bool> map4;
  map4.add("old", false);
  map4 = map3; // operator=: map4's old contents are discarded
  REQUIRE(map4.getNumberOfItems() == 3);
  REQUIRE(map4.getItem("yes") == true);
  REQUIRE_FALSE(map4.contains("old")); // old entry gone

  map4.remove("maybe");
  REQUIRE(map4.getNumberOfItems() == 2);
  REQUIRE_FALSE(map4.contains("maybe"));
  REQUIRE(map3.getNumberOfItems() == 3); // original unaffected
}