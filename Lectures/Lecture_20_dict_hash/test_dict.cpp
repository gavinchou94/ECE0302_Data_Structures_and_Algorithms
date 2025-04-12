#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "ArrayDictionary.hpp"
#include "HashedDictionary.hpp"

TEST_CASE("ArrayDictionary Basic", "[ArrayDictionary]")
{
  ArrayDictionary<int, std::string> dict;
  REQUIRE(dict.isEmpty());
  REQUIRE(dict.getNumberOfItems() == 0);

  dict.add(1, "one");
  dict.add(2, "two");
  dict.add(3, "three");

  REQUIRE(!dict.isEmpty());
  REQUIRE(dict.getNumberOfItems() == 3);
  REQUIRE(dict.contains(1));
  REQUIRE(dict.contains(2));
  REQUIRE(dict.contains(3));
  REQUIRE(!dict.contains(4));

  REQUIRE(dict.getItem(1) == "one");
  REQUIRE(dict.getItem(2) == "two");
  REQUIRE(dict.getItem(3) == "three");

  dict.remove(2);
  REQUIRE(!dict.contains(2));
  REQUIRE(dict.getNumberOfItems() == 2);

  dict.clear();
  REQUIRE(dict.isEmpty());
}

TEST_CASE("ArrayDictionary test add and remove", "[ArrayDictionary]")
{
  ArrayDictionary<int, std::string> dict;
  REQUIRE(dict.isEmpty());
  REQUIRE(dict.getNumberOfItems() == 0);

  dict.add(1, "one");
  dict.add(2, "two");
  dict.add(3, "three");

  REQUIRE(!dict.isEmpty());
  REQUIRE(dict.getNumberOfItems() == 3);
  REQUIRE(dict.contains(1));
  REQUIRE(dict.contains(2));
  REQUIRE(dict.contains(3));
  REQUIRE(!dict.contains(4));

  REQUIRE(dict.getItem(1) == "one");
  REQUIRE(dict.getItem(2) == "two");
  REQUIRE(dict.getItem(3) == "three");

  dict.remove(2);
  REQUIRE(!dict.contains(2));
  REQUIRE(dict.getNumberOfItems() == 2);

  dict.clear();
  REQUIRE(dict.isEmpty());

  dict.add(1, "one");
  dict.add(2, "two");
  dict.add(3, "three");
  REQUIRE_FALSE(dict.add(1, "uno"));
  REQUIRE_FALSE(dict.add(2, "dos"));
  REQUIRE_FALSE(dict.add(3, "tres"));
  REQUIRE(dict.getNumberOfItems() == 3);

  REQUIRE_FALSE(dict.remove(4));
}

TEST_CASE("ArrayDictionary test copy constructor", "[ArrayDictionary]")
{
  ArrayDictionary<int, std::string> dict;
  dict.add(1, "one");
  dict.add(2, "two");
  dict.add(3, "three");

  ArrayDictionary<int, std::string> dict2(dict);
  REQUIRE(dict2.getNumberOfItems() == 3);
  REQUIRE(dict2.getItem(1) == "one");
  REQUIRE(dict2.getItem(2) == "two");
  REQUIRE(dict2.getItem(3) == "three");

  dict2.remove(2);
  REQUIRE(dict2.getNumberOfItems() == 2);
  REQUIRE(dict.getNumberOfItems() == 3);
}

// test traverse
void printItem(std::string &item)
{
  std::cout << item << " ";
}

TEST_CASE("ArrayDictionary test traverse", "[ArrayDictionary]")
{
  ArrayDictionary<double, std::string> dict;
  dict.add(1.0, "1.0");
  dict.add(2.2, "2.2");
  dict.add(9.0, "9.0");
  dict.add(3.3, "3.3");
  dict.add(9.9, "9.9");
  dict.add(9.11, "9.11");
  dict.add(9.12, "9.12");

  std::cout << "Traverse: ";
  dict.traverse(printItem);
  std::cout << std::endl;
}

TEST_CASE("HashedDictionary Basic", "[HashedDictionary]")
{
  HashedDictionary<double, std::string> dict;
  REQUIRE(dict.isEmpty());
  REQUIRE(dict.getNumberOfItems() == 0);

  dict.add(1.14, "one");
  dict.add(2.35, "two");
  dict.add(3.98, "three");

  REQUIRE(!dict.isEmpty());
  REQUIRE(dict.getNumberOfItems() == 3);
  REQUIRE(dict.contains(1.14));
  REQUIRE(dict.contains(2.35));
  REQUIRE(dict.contains(3.98));
  REQUIRE(!dict.contains(4));
  REQUIRE(dict.add(2.35, "2.35") == false);

  REQUIRE(dict.getItem(1.14) == "one");
  REQUIRE(dict.getItem(2.35) == "two");
  REQUIRE(dict.getItem(3.98) == "three");

  dict.remove(2.35);
  REQUIRE(!dict.contains(2.35));
  REQUIRE(dict.getNumberOfItems() == 2);

  dict.clear();
  REQUIRE(dict.isEmpty());
}

TEST_CASE("HashedDictionary small size", "[HashedDictionary]")
{
  HashedDictionary<double, std::string> dict(7);
  REQUIRE(dict.isEmpty());
  REQUIRE(dict.getNumberOfItems() == 0);

  dict.add(1.0, "one");
  dict.add(2.0, "two");
  dict.add(3.0, "three");
  dict.add(4.0, "four");
  dict.add(5.0, "five");
  dict.add(6.0, "six");
  dict.add(7.0, "seven");
  dict.add(8.0, "eight");
  dict.add(9.0, "nine");
  dict.add(10.0, "ten");

  REQUIRE(!dict.isEmpty());
  REQUIRE(dict.getNumberOfItems() == 10);

  REQUIRE(dict.contains(1.0));
  REQUIRE(dict.contains(2.0));
  dict.contains(3.0);
  REQUIRE(dict.contains(3.0));
  REQUIRE(dict.contains(4.0));
  REQUIRE(dict.contains(5.0));

  REQUIRE(dict.getItem(1.0) == "one");
  REQUIRE(dict.getItem(2.0) == "two");
  REQUIRE(dict.getItem(3.0) == "three");

  REQUIRE(dict.remove(1.0));
  REQUIRE(!dict.contains(1.0));
  REQUIRE_FALSE(dict.remove(1.0));
  REQUIRE_THROWS(dict.getItem(1.0));
  REQUIRE(dict.getNumberOfItems() == 9);

  REQUIRE(dict.remove(2.0));
  REQUIRE(dict.remove(3.0));

  REQUIRE_FALSE(dict.remove(2.0));
  REQUIRE_THROWS(dict.getItem(2.0));
  REQUIRE_FALSE(dict.remove(3.0));
  REQUIRE_THROWS(dict.getItem(3.0));
  REQUIRE(dict.getNumberOfItems() == 7);

  // Visualize the hash table at this point can be seen in HashedDictionary.hpp
  // Briefly describe the workflow if at this point, we remove (5.0, "five") from the dictionary
  // what sub-functions are called in the background? Which sub-function call is most likely to increase time complexity?
  // Also find out the hash-value of double 5.0 by adding a breakpoint somewhere in the tpp file
  //  A. 4617315517961601023
  //  B. 4617315517961601024
  //  C. 4617315517961601025
  //  D. 4617315517961601026
  //  E. 4617315517961601027

  std::cout << "Traverse in HashedDict: ";
  dict.traverse(printItem);
  std::cout << std::endl;

  dict.clear();
  REQUIRE(dict.isEmpty());
  REQUIRE(dict.getNumberOfItems() == 0);
}

// test HashedDictionary copy constructor
TEST_CASE("HashedDictionary test copy constructor", "[HashedDictionary]")
{
  HashedDictionary<std::string, bool> dict;
  dict.add("hello", true);
  dict.add("hola", false);
  dict.add("hi", true);
  dict.add("hey", true);

  HashedDictionary<std::string, bool> dict2(dict);
  REQUIRE(dict2.getNumberOfItems() == 4);
  REQUIRE(dict2.getItem("hello") == true);
  REQUIRE(dict2.getItem("hola") == false);
  REQUIRE(dict2.getItem("hi") == true);
  REQUIRE(dict2.getItem("hey") == true);

  dict2.remove("hi");
  REQUIRE(dict2.getNumberOfItems() == 3);
  REQUIRE(dict.getNumberOfItems() == 4);
}