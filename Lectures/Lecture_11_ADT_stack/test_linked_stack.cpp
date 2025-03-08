/** @file test_linked_stack.cpp
 * @author G. Zhou
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "LinkedStack.hpp"
#include "StackInterface.hpp"
#include <vector>
#include <stack>

TEST_CASE("Testing the Linked-Based Stack with push", "[linked stack]")
{
   StackInterface<std::string> *stackPtr1 = new LinkedStack<std::string>();
   REQUIRE(stackPtr1->isEmpty() == true);

   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

   for (int i = 0; i < 10; i++)
   {
      REQUIRE(stackPtr1->push(items1[i]));
   }

   REQUIRE(stackPtr1->isEmpty() == false);
   // REQUIRE(stackPtr1->push(items1[10]) == false); // stack is never full

   delete stackPtr1;
}

TEST_CASE("Testing the Linked-Based Stack with pop", "[array stack]")
{
   StackInterface<std::string> *stackPtr1 = new LinkedStack<std::string>();
   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

   for (int i = 0; i < 10; i++)
   {
      stackPtr1->push(items1[i]);
   }

   for (int i = 9; i >= 0; i--)
   {
      REQUIRE(stackPtr1->pop()); // Test pop after pushing
   }
   REQUIRE(stackPtr1->isEmpty() == true);
   REQUIRE(stackPtr1->pop() == false); // nothing to pop!
   delete stackPtr1;
}

TEST_CASE("Testing the Linked-Based Stack with peek", "[array stack]")
{
   StackInterface<std::string> *stackPtr1 = new LinkedStack<std::string>();
   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

   for (int i = 0; i < 10; i++)
   {
      stackPtr1->push(items1[i]);
      REQUIRE(stackPtr1->peek() == items1[i]); // Test peek after pushing
   }

   for (int i = 9; i >= 0; i--)
   {
      REQUIRE(stackPtr1->peek() == items1[i]); // Test peek after popping
      stackPtr1->pop();
   }
   REQUIRE(stackPtr1->isEmpty() == true);
   REQUIRE_THROWS_AS(stackPtr1->peek(), std::out_of_range); // nothing to peek!
   delete stackPtr1;
}

TEST_CASE("Testing the Linked-Based Stack with exceptions", "[array stack]")
{
   StackInterface<std::string> *stackPtr1 = new LinkedStack<std::string>();
   REQUIRE_THROWS_AS(stackPtr1->peek(), std::out_of_range); // nothing to peek!
   REQUIRE_FALSE(stackPtr1->pop());                         // nothing to pop!
   delete stackPtr1;
}

// What test cases should be added to comprenhensively test the linked stack?

// There are other ways to implement a stack. For example, using a vector or a list.
// 1. dynamically-sized array to hold stack data
// 2. linked list with smart ptr to hold stack data
// 3. std::vector with push_back and pop_back, and back
// 4. simply std::stack with push, pop, and top

TEST_CASE("Testing other stack implementation 3 and 4", "[stack]")
{
   // Method 3
   std::vector<std::string> stack3;
   stack3.push_back("zero");
   stack3.push_back("one");
   REQUIRE(stack3.back() == "one");
   stack3.pop_back();
   REQUIRE(stack3.back() == "zero");
   stack3.pop_back();
   REQUIRE(stack3.empty() == true);

   // Method 4
   std::stack<std::string> stack4;
   stack4.push("zero");
   stack4.push("one");
   REQUIRE(stack4.top() == "one");
   stack4.pop();
   REQUIRE(stack4.top() == "zero");
   stack4.pop();
   REQUIRE(stack4.empty() == true);
}

// define new class DyArrayStack
class DyArrayStack : public StackInterface<std::string>
{
private:
   std::string *items;
   int numItems;

public:
   DyArrayStack() : items(nullptr), numItems(0) {};
   ~DyArrayStack() { delete[] items; }
   bool isEmpty() const { return numItems == 0; }
   bool push(const std::string &newEntry)
   {
      std::string *newItems = new std::string[numItems + 1];
      for (int i = 0; i < numItems; i++)
         newItems[i] = items[i];
      newItems[numItems] = newEntry;
      delete[] items;
      items = newItems;
      numItems++;
      return true;
   }
   bool pop()
   {
      if (isEmpty())
         return false; // nothing to pop
      if (numItems == 1)
      {
         numItems = 0;
         delete[] items;
         items = nullptr;
         return true;
      }
      std::string *newItems = new std::string[numItems - 1];
      for (int i = 0; i < numItems - 1; i++)
         newItems[i] = items[i];
      delete[] items;
      items = newItems;
      numItems--;
      return true;
   }
   std::string peek() const
   {
      if (isEmpty())
         throw std::out_of_range("Stack is empty");
      return items[numItems - 1];
   }
};

class SmartNode
{
private:
   std::string item;
   std::shared_ptr<SmartNode> next;

public:
   SmartNode() : item(""), next(nullptr) {}
   // more node methods, incomplete
};

// define new class SmartLinkedStack
// use smart pointer to hold stack data
class SmartLinkedStack
{
private:
   std::shared_ptr<SmartNode> topPtr;

public:
   SmartLinkedStack() : topPtr(nullptr) {}
   ~SmartLinkedStack() { topPtr = nullptr; }
   // more stack operations
};

TEST_CASE("Testing other stack implementation 1 and 2", "[stack]")
{
   // Method 1
   DyArrayStack stack1;
   REQUIRE(stack1.isEmpty() == true);
   stack1.push("zero");
   stack1.push("one");
   REQUIRE(stack1.peek() == "one");
   stack1.pop();
   REQUIRE(stack1.peek() == "zero");
   stack1.pop();
   REQUIRE(stack1.isEmpty() == true);
   REQUIRE_THROWS_AS(stack1.peek(), std::out_of_range); // nothing to peek!

   // Method 2
   SmartLinkedStack stack2;
   // should be able to run without compile error
}