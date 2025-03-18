/** @file test_smart_ptr.cpp
 * @author G. Zhou
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <memory>

TEST_CASE("unique_ptr usage", "[smart_ptr]")
{
  // ptr1 is a unique_ptr that owns an int, check the return type on the left
  // ptr1 is assigned to store 10, check the syntax on the right
  std::unique_ptr<int> ptr1(new int(10));
  REQUIRE(*ptr1 == 10);

  // std::unique_ptr<int> ptr2 = ptr1;
  // TODO: why does this line not compile?

  // ptr2 is assigned to ptr1, check the syntax on the right
  std::unique_ptr<int> ptr2 = std::move(ptr1);

  REQUIRE(ptr1 == nullptr);
  REQUIRE(*ptr2 == 10);
}

TEST_CASE("shared_ptr usage", "[smart_ptr]")
{
  // ptr1 is a shared_ptr that owns an int, check the return type on the left
  // ptr1 is assigned to store 20, check the syntax on the right
  std::shared_ptr<int> ptr1 = std::make_shared<int>(20);

  REQUIRE(*ptr1 == 20);

  // ptr2 is assigned to ptr1, check the syntax on the right
  std::shared_ptr<int> ptr2 = ptr1;

  REQUIRE(ptr1.use_count() == 2);
  REQUIRE(ptr2.use_count() == 2);

  {
    std::shared_ptr<int> ptr3 = ptr1;
    std::shared_ptr<int> ptr4 = ptr2;
    REQUIRE(ptr1.use_count() == 4);
    REQUIRE(ptr2.use_count() == 4);
  } // ptr3, ptr4 goes out of scope

  REQUIRE(ptr1.use_count() == 2);
  REQUIRE(ptr2.use_count() == 2);

  REQUIRE(*ptr2 == 20);

  // ptr1 and ptr2 point to the same memory location
  *ptr2 = 30;
  REQUIRE(*ptr1 == 30);
  REQUIRE(*ptr2 == 30);
}

TEST_CASE("weak_ptr usage", "[smart_ptr]")
{
  std::shared_ptr<int> sharedPtr = std::make_shared<int>(30);
  std::shared_ptr<int> ptr2 = sharedPtr;
  REQUIRE(ptr2.use_count() == 2);

  std::weak_ptr<int> weakPtr = sharedPtr;
  REQUIRE(weakPtr.use_count() == 2);
  // Why is above count not updated to 3?

  // why is the following block not compiling?
  // *weakPtr = 40;
  // REQUIRE(*sharedPtr == 40);
  // REQUIRE(*ptr2 == 40);
}

// show an example of working with a linked list using smart pointers
struct Node
{
  int data;
  std::shared_ptr<Node> next;

  Node(int val) : data(val), next(nullptr) {}
};

// A class definition and implementation
class BagInt
{
private:
  std::shared_ptr<Node> head;

public:
  BagInt() : head(nullptr) {}

  void add(int value)
  {
    // create a new node and add it to the end of the linked list

    // Syntax:
    // std::shared_ptr<CLASS> newNode = std::make_shared<CLASS>(DEFAULT_CONSTRUCTOR);

    std::shared_ptr<Node> newNode = std::make_shared<Node>(value);
    if (!head)
    {
      head = newNode;
    }
    else
    {
      std::shared_ptr<Node> current = head;
      while (current->next)
      {
        current = current->next;
      }
      current->next = newNode;
    }
  }

  void print() const
  {
    std::shared_ptr<Node> current = head;
    while (current)
    {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }

  void clear()
  {
    // This will automatically delete all nodes in the linked list
    head = nullptr;
  }
  ~BagInt()
  {
    std::cout << "BagInt destructor called" << std::endl;
    // Destructor is not needed, as shared_ptr will automatically delete the nodes
    // when they are no longer referenced.

    // Option 1:
    // head = nullptr; // This will delete all nodes in the linked list
    // Option 2:
    // clear(); // This will also delete all nodes in the linked list
    // Option 3:
    // Do nothing
    // Option 4:
    // delete head;
  }
};

TEST_CASE("deleting smart pointer on linked node", "[smart_ptr]")
{
  BagInt bag;
  bag.add(1);
  bag.add(2);
  bag.add(3);

  std::cout << "Bag contents: ";
  bag.print();

  bag.clear(); // Clear the bag, which will delete all nodes
  std::cout << "Cleared bag contents: ";
  bag.print();

  // uncomment the above option 1/2/3/4 of destructor to see the effect
}
