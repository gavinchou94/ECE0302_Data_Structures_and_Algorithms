/** @file test_.cpp
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

// show an example of deleting a smart pointer on linked node
struct Node
{
  int data;
  std::shared_ptr<Node> next;

  Node(int val) : data(val), next(nullptr) {}
};

TEST_CASE("deleting smart pointer on linked node", "[smart_ptr]")
{
  // Create the head node
  std::shared_ptr<Node> head = std::make_shared<Node>(1);
  head->next = std::make_shared<Node>(2);
  head->next->next = std::make_shared<Node>(3);

  // Print the linked list
  std::shared_ptr<Node> current = head;
  while (current)
  {
    std::cout << current->data << " ";
    current = current->next;
  }
  std::cout << std::endl;

  REQUIRE(head.use_count() == 1);             // 1
  REQUIRE(head->next.use_count() == 1);       // 1
  REQUIRE(head->next->next.use_count() == 1); // 1

  {
    std::shared_ptr<Node> tempHead = head;
    REQUIRE(tempHead.use_count() == 2); // 2
    REQUIRE(head.use_count() == 2);     // 2
  }
  // tempHead is out of scope, use_count should be back to 1
  REQUIRE(head.use_count() == 1);             // 1
  REQUIRE(head->next.use_count() == 1);       // 1
  REQUIRE(head->next->next.use_count() == 1); // 1
}
