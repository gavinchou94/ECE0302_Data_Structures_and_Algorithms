/** @file test_list.cpp
 * @author Frank M. Carrano, Tim Henry
 * @copyright 2017 Pearson Education
 * @version 3.0, modified in 2026 by G. Zhou for ECE0302
 */

#define CATCH_CONFIG_MAIN

#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include "catch.hpp"
#include <iostream>
#include <string>

void displayList(ListInterface<std::string> *listPtr)
{
   std::cout << "The list contains " << std::endl;
   for (int pos = 1; pos <= listPtr->getLength(); pos++)
   {
      std::cout << listPtr->getEntry(pos) << " ";
   }
   std::cout << std::endl;
}

void displayList_v2(ListInterface<std::string> &listobj)
{
   std::cout << "The list contains " << std::endl;
   // write your statements here to display the list using listobj
   std::cout << std::endl;
}

/** ------------------------------------------------------------------ */
/** -----------------Test Cases For ArrayList ------------------------ */
/** ------------------------------------------------------------------ */

TEST_CASE("Test initial state of ArrayList and isEmpty()", "[ArrayList]")
{
   ListInterface<std::string> *listPtr = new ArrayList<std::string>();
   REQUIRE(listPtr->isEmpty() == true);
   REQUIRE(listPtr->getLength() == 0);
   delete listPtr;
}

TEST_CASE("Test insert elements into ArrayList", "[ArrayList]")
{
   ListInterface<std::string> *listPtr = new ArrayList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five", "six"};

   for (int i = 0; i < 6; i++)
   {
      if (i < 5) // ArrayList has a capacity of 5
      {
         REQUIRE(listPtr->insert(i + 1, data[i])); // (1, "one"), (2, "two"), ...
         REQUIRE(listPtr->getEntry(i + 1) == data[i]);
      }
      else
      {
         REQUIRE_FALSE(listPtr->insert(i + 1, data[i]));
      }
   }
   displayList(listPtr);
   delete listPtr;
}

TEST_CASE("Test list properties after insertions", "[ArrayList]")
{
   ListInterface<std::string> *listPtr = new ArrayList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five"};

   REQUIRE(listPtr->isEmpty());

   for (int i = 0; i < 5; i++)
   {
      listPtr->insert(i + 1, data[i]);
   }
   REQUIRE(listPtr->insert(6, "six") == false);        // 6 is valid position to insert, given getLength()+1=6 here. Why still false?
   REQUIRE(listPtr->insert(0, "zero") == false);       // 0 is invalid position to insert
   REQUIRE(listPtr->insert(-1, "minus one") == false); // -1 is invalid position to insert
   REQUIRE(listPtr->isEmpty() == false);
   REQUIRE(listPtr->getLength() == 5);
   REQUIRE(listPtr->getEntry(4) == "four");
   delete listPtr;
}

TEST_CASE("Test list properties after removals", "[ArrayList]")
{
   ListInterface<std::string> *listPtr = new ArrayList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five"};

   for (int i = 0; i < 5; i++)
   {
      listPtr->insert(i + 1, data[i]);
   }
   REQUIRE(listPtr->remove(2));
   REQUIRE(listPtr->remove(1));
   REQUIRE(listPtr->getLength() == 3);
   REQUIRE(listPtr->remove(6) == false);  // remove from 3-length list
   REQUIRE(listPtr->remove(5) == false);  // remove from 3-length list
   REQUIRE(listPtr->remove(4) == false);  // remove from 3-length list
   REQUIRE(listPtr->remove(0) == false);  // 0 is invalid position to remove
   REQUIRE(listPtr->remove(-1) == false); // -1 is invalid position to remove
   displayList(listPtr);
   delete listPtr;
}

TEST_CASE("Test list replace (a.k.a setEntry)", "[ArrayList]")
{
   ListInterface<std::string> *listPtr = new ArrayList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five"};

   for (int i = 0; i < 5; i++)
   {
      listPtr->insert(i + 1, data[i]);
   }
   listPtr->replace(3, "THREE");
   REQUIRE(listPtr->getEntry(3) == "THREE");
   delete listPtr;
}

TEST_CASE("Test clear ArrayList", "[ArrayList]")
{
   ListInterface<std::string> *listPtr = new ArrayList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five"};

   for (int i = 0; i < 5; i++)
   {
      listPtr->insert(i + 1, data[i]);
   }
   listPtr->clear();
   REQUIRE(listPtr->isEmpty());
   delete listPtr;
}

TEST_CASE("Test exceptions of operations", "[ArrayList]")
{
   ListInterface<std::string> *listPtr = new ArrayList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five"};

   for (int i = 0; i < 5; i++)
   {
      listPtr->insert(i + 1, data[i]);
   }
   REQUIRE(listPtr->getLength() == 5); // so getEntry(?) and replace(?) are only valid for 1,2,3,4,5
   REQUIRE_THROWS_AS(listPtr->getEntry(6), std::out_of_range);
   REQUIRE_THROWS_AS(listPtr->getEntry(0), std::out_of_range);
   REQUIRE_THROWS_AS(listPtr->getEntry(-1), std::out_of_range);
   REQUIRE_THROWS_AS(listPtr->replace(6, "SIX"), std::out_of_range);
   REQUIRE_THROWS_AS(listPtr->replace(0, "ZERO"), std::out_of_range);
   REQUIRE_THROWS_AS(listPtr->replace(-1, "MINUS ONE"), std::out_of_range);
   delete listPtr;
}

/** ------------------------------------------------------------------ */
/** ----Test Cases For LinkedList, Some Will Fail Due to Stub -------- */
/** ------------------------------------------------------------------ */
TEST_CASE("Test initial state of LinkedList and isEmpty()", "[LinkedList]")
{
   ListInterface<std::string> *listPtr = new LinkedList<std::string>();
   REQUIRE(listPtr->isEmpty() == true);
   REQUIRE(listPtr->getLength() == 0);
   delete listPtr;
}

TEST_CASE("Test insert elements into LinkedList", "[LinkedList]")
{
   ListInterface<std::string> *listPtr = new LinkedList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five", "six"};

   for (int i = 0; i < 6; i++)
   {
      REQUIRE(listPtr->insert(i + 1, data[i]));
      REQUIRE(listPtr->getEntry(i + 1) == data[i]);
   }
   displayList(listPtr);
   delete listPtr;
}

TEST_CASE("Test list properties after LinkedList insertions", "[LinkedList]")
{
   ListInterface<std::string> *listPtr = new LinkedList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five"};

   REQUIRE(listPtr->isEmpty());

   for (int i = 0; i < 5; i++)
   {
      listPtr->insert(i + 1, data[i]);
   }

   // Supposing you have finished the stub implementation (remove/add/copy constructor) of LinkedList.
   // Refer back to Line 76, why is listPtr->insert(6, "six") true for LinkedList but not for ArrayList?
   REQUIRE(listPtr->insert(6, "six") == true);         // 6 is valid position to insert, given getLength()+1=6 here
   REQUIRE(listPtr->insert(7, "seven") == false);      // 7 is invalid position to insert
   REQUIRE(listPtr->insert(0, "zero") == false);       // 0 is invalid position to insert
   REQUIRE(listPtr->insert(-1, "minus one") == false); // -1 is invalid position to insert
   REQUIRE(listPtr->isEmpty() == false);
   REQUIRE(listPtr->getLength() == 5);
   REQUIRE(listPtr->getEntry(4) == "four");
   delete listPtr;
}

TEST_CASE("Test list properties after LinkedList removals", "[LinkedList]")
{
   ListInterface<std::string> *listPtr = new LinkedList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five"};

   for (int i = 0; i < 5; i++)
   {
      listPtr->insert(i + 1, data[i]);
   }
   REQUIRE(listPtr->remove(2));
   REQUIRE(listPtr->remove(1));
   REQUIRE(listPtr->getLength() == 3);
   REQUIRE(listPtr->remove(6) == false);  // remove from 3-length list
   REQUIRE(listPtr->remove(5) == false);  // remove from 3-length list
   REQUIRE(listPtr->remove(4) == false);  // remove from 3-length list
   REQUIRE(listPtr->remove(0) == false);  // 0 is invalid position to remove
   REQUIRE(listPtr->remove(-1) == false); // -1 is invalid position to remove
   displayList(listPtr);
   delete listPtr;
}

TEST_CASE("Test LinkedList replace", "[LinkedList]")
{
   ListInterface<std::string> *listPtr = new LinkedList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five"};

   for (int i = 0; i < 5; i++)
   {
      listPtr->insert(i + 1, data[i]);
   }
   listPtr->replace(3, "THREE");
   REQUIRE(listPtr->getEntry(3) == "THREE");
   delete listPtr;
}

TEST_CASE("Test clear LinkedList", "[LinkedList]")
{
   ListInterface<std::string> *listPtr = new LinkedList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five"};

   for (int i = 0; i < 5; i++)
   {
      listPtr->insert(i + 1, data[i]);
   }
   listPtr->clear();
   REQUIRE(listPtr->isEmpty());
   delete listPtr;
}

TEST_CASE("Test exceptions of LinkedList operations", "[LinkedList]")
{
   ListInterface<std::string> *listPtr = new LinkedList<std::string>();
   std::string data[] = {"one", "two", "three", "four", "five"};

   for (int i = 0; i < 5; i++)
   {
      listPtr->insert(i + 1, data[i]);
   }
   REQUIRE(listPtr->getLength() == 5);
   REQUIRE_THROWS_AS(listPtr->getEntry(6), std::out_of_range);
   REQUIRE_THROWS_AS(listPtr->getEntry(0), std::out_of_range);
   REQUIRE_THROWS_AS(listPtr->getEntry(-1), std::out_of_range);
   REQUIRE_THROWS_AS(listPtr->replace(6, "SIX"), std::out_of_range);
   REQUIRE_THROWS_AS(listPtr->replace(0, "ZERO"), std::out_of_range);
   REQUIRE_THROWS_AS(listPtr->replace(-1, "MINUS ONE"), std::out_of_range);
   delete listPtr;
}

TEST_CASE("Test copy constructor of LinkedList", "[LinkedList]")
{
   LinkedList<std::string> list;
   std::string items[] = {"zero", "one", "two", "three", "four", "five"};
   for (int i = 0; i < 6; i++)
   {
      REQUIRE(list.insert(i + 1, items[i]));
   }

   LinkedList<std::string> copyOfList(list); // construct a copy while declaring it, invoking copy constructor

   REQUIRE(copyOfList.getLength() == list.getLength());
   for (int i = 1; i <= list.getLength(); i++)
   {
      REQUIRE(copyOfList.getEntry(i) == list.getEntry(i));
   }
}

TEST_CASE("Test copy assignment operator of LinkedList", "[LinkedList]")
{
   LinkedList<std::string> list;
   std::string items[] = {"zero", "one", "two", "three", "four", "five"};
   for (int i = 0; i < 6; i++)
   {
      REQUIRE(list.insert(i + 1, items[i]));
   }

   // TODO: Write some statements here, so that we can test copy assignment operator of LinkedList below in Line 299-303

   // REQUIRE(copyOfList.getLength() == list.getLength());
   // for (int i = 1; i <= list.getLength(); i++)
   // {
   //    REQUIRE(copyOfList.getEntry(i) == list.getEntry(i));
   // }
}

TEST_CASE("Test user choice of ArrayList or LinkedList", "[List]")
{

   // TODO: write your statements here to test user choice of ArrayList or LinkedList
   // Based on user input of 'A' or 'L', link a listPtr to different derived classes
   // so that the operations at Line 315-321 can be performed on the listPtr

   // write your statements here

   // listPtr->insert(1, "one");
   // listPtr->getEntry(1);
   // listPtr->isEmpty();
   // listPtr->getLength();
   // listPtr->replace(1, "ONE");
   // listPtr->remove(1);
   // listPtr->clear();
}