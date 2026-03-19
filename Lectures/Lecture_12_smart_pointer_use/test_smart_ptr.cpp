/** @file test_smart_ptr.cpp
 * @author G. Zhou */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "LinkedListSmart.hpp"

#include <iostream>
#include <memory>
#include <chrono>

TEST_CASE("Raw pointer usage", "[smart_ptr]")
{
  // ptr1 is a raw pointer that points to a memory location storing 10,
  int *ptr1 = new int(10);
  REQUIRE(*ptr1 == 10);

  *ptr1 = 20;
  REQUIRE(*ptr1 == 20);

  int *ptr2 = ptr1; // ptr1 is assigned to ptr2, shallow copy
  REQUIRE(*ptr2 == 20);

  delete ptr1; // delete ptr1 to avoid memory leak
  // no need to delete ptr2

  int *ptr3 = new int[5]{1, 2, 3, 4, 5};
  REQUIRE(ptr3[0] == 1);
  REQUIRE(ptr3[4] == 5);

  ptr3++;
  REQUIRE(*ptr3 == 2);
  ptr3--;
  delete[] ptr3; // delete the array to avoid memory leak
}

template <typename T>
class PlainBox
{
public:
  T item;
  PlainBox(const T &anItem) : item(anItem) {}
  T getItem() const { return item; }
  void setItem(const T &newItem) { item = newItem; }
};

void showBoxItem(std::unique_ptr<PlainBox<std::string>> &theBox)
{
  std::cout << theBox->getItem() << std::endl;
}
void changeBoxItem(std::unique_ptr<PlainBox<std::string>> theBox, std::string theItem)
{
  theBox->setItem(theItem);
  std::cout << theBox->getItem() << std::endl;
}
// Generally, passing by value calls copy constructor
// (but unique_ptr doesn't have copy constructor, so you need to call std::move first to transfer ownership.
// which means theBox in this function is a copy of the original unique_ptr that is passed in
// and it owns the PlainBox object. Object in the main function will lose ownership and become nullptr.

TEST_CASE("unique_ptr usage", "[smart_ptr]")
{
  // ptr1 is a unique_ptr that owns an int
  // ptr1 is assigned to store 10
  std::unique_ptr<int> ptr1(new int(10));
  // std::unique_ptr<int> ptr1 = std::make_unique<int>(10); // alternative syntax using make_unique
  // std::unique_ptr<int> ptr1; ptr1.reset(new int(10));    // alternative syntax using reset
  REQUIRE(*ptr1 == 10);

  *ptr1 = 20;
  REQUIRE(*ptr1 == 20);

  // std::unique_ptr<int> ptr2 = ptr1;
  // The above line attempts to make ptr2 also own ptr1's content (shallow copy),
  // but it will not compile due to unique_ptr's design.
  // TODO: Recall Grid class in 301's last programming assignment and Project 1's BitArray class
  // What kind of copy constructor and assignment operator do you believe are defined for unique_ptr? Why?

  std::unique_ptr<int> ptr2 = std::move(ptr1);
  REQUIRE(ptr2 != nullptr);
  REQUIRE(ptr1 == nullptr);
  REQUIRE(*ptr2 == 20);

  // delete ptr2; // wrong to delete ptr2, it will automatically delete the memory when it goes out of scope
  ptr2.reset(); // reset ptr2 to delete the memory, ptr2 will be set to nullptr

  std::unique_ptr<int[]> ptr3(new int[5]{1, 2, 3, 4, 5});
  REQUIRE(ptr3[0] == 1);
  REQUIRE(ptr3[4] == 5);

  // ++, -- and * operators are not supported for unique_ptr
  // ptr3++;
  // std::cout << *ptr3 << std::endl;
  // ptr3--;
  // delete[] ptr3;

  REQUIRE(ptr3 != nullptr);
  ptr3.reset();
  REQUIRE(ptr3 == nullptr);

  std::unique_ptr<PlainBox<std::string>> myboxPtr(new PlainBox<std::string>("my"));
  showBoxItem(myboxPtr);
  if (myboxPtr != nullptr)
  {
    std::cout << "myboxPtr is still valid after being passed to showBoxItem"
              << "(pass by reference).\n\n ";
  }
  // changeBoxItem(myboxPtr, "new item"); // cannot pass by value directly
  changeBoxItem(std::move(myboxPtr), "new item");
  if (myboxPtr == nullptr)
  {
    std::cout << "myboxPtr is now nullptr after being moved "
              << "to changeBoxItem function.\n\n";
  }
}

TEST_CASE("shared_ptr usage", "[smart_ptr]")
{
  // ptr1 is a shared_ptr that owns an int
  // ptr1 is assigned to store 10
  std::shared_ptr<int> ptr1(new int(10));
  // std::shared_ptr<int> ptr1 = std::make_shared<int>(10); // alternative syntax using make_unique
  // std::shared_ptr<int> ptr1; ptr1.reset(new int(10));    // alternative syntax using reset
  REQUIRE(*ptr1 == 10);

  *ptr1 = 20;
  REQUIRE(*ptr1 == 20);

  // ptr1 is assigned to ptr2, which means ptr2 also shares ownership of the same int
  std::shared_ptr<int> ptr2 = ptr1;
  REQUIRE(*ptr2 == 20);

  REQUIRE(ptr1.use_count() == 2);
  REQUIRE(ptr2.use_count() == 2);

  {
    std::shared_ptr<int> ptr3 = ptr1;
    std::shared_ptr<int> ptr4 = ptr2;
    REQUIRE(ptr1.use_count() == 4);
    REQUIRE(ptr2.use_count() == 4);
  } // ptr3, ptr4 goes out of scope

  // TODO: What do you think the use_count of ptr1 and ptr2 will be after the above block? Why?
  // Use REQUIRE to check your answer.
  *ptr2 = 30;
  REQUIRE(*ptr1 == 30);
  REQUIRE(*ptr2 == 30);

  ptr2.reset();
  REQUIRE(ptr2 == nullptr);
  REQUIRE(ptr1.use_count() == 1);
  ptr1.reset();
  REQUIRE(ptr1 == nullptr);
  REQUIRE(ptr1.use_count() == 0);
}

TEST_CASE("weak_ptr usage", "[smart_ptr]")
{
  std::shared_ptr<int> ptr1 = std::make_shared<int>(30);
  std::shared_ptr<int> ptr2 = ptr1;
  REQUIRE(ptr2.use_count() == 2);

  std::weak_ptr<int> ptr3 = ptr1;
  REQUIRE(ptr3.use_count() == 2);
  // TODO: Explain why the above count is not updated to 3? and why the following line is not compiling?
  // *ptr3 = 40;
  REQUIRE(ptr3.expired() == false);
  ptr1.reset();
  REQUIRE(ptr3.expired() == false);
  ptr2.reset();
  REQUIRE(ptr3.expired() == true);
}

struct HotelRoom
{
  int roomNumber;
  std::string guestName;
};

std::ostream &operator<<(std::ostream &os, const HotelRoom &room)
{
  os << "Room occupied by " << room.guestName;
  return os;
}

TEST_CASE("shared_ptr with linked list", "[smart_ptr]")
{
  LinkedListSmart<HotelRoom> RoomList;
  REQUIRE(RoomList.isEmpty());

  HotelRoom room1{412, "Alice"};
  HotelRoom room2{999, "Bob"};
  HotelRoom room3{875, "Charlie"};
  HotelRoom room4{123, "David"};
  HotelRoom room5{555, "Eve"};
  HotelRoom room6{387, "Frank"};
  HotelRoom room7{246, "Gavin"};

  REQUIRE(RoomList.insert(1, room1));
  REQUIRE(RoomList.insert(2, room2));
  REQUIRE(RoomList.insert(3, room3));
  REQUIRE(RoomList.insert(4, room4));
  REQUIRE(RoomList.insert(5, room5));
  REQUIRE(RoomList.insert(6, room6));
  REQUIRE(RoomList.insert(7, room7));

  // After inserting 7 rooms, each node's use_count should be 1 since they are only owned by the linked list
  // That being said, no other program outside of the linked list knows the nodes, which is the main idea of encapsulation
  // E.g., the only way to know room7's information is to find room6 first
  REQUIRE(RoomList.headPtr.use_count() == 1);
  REQUIRE(RoomList.headPtr->next.use_count() == 1);
  REQUIRE(RoomList.headPtr->next->next.use_count() == 1);
  REQUIRE(RoomList.headPtr->next->next->next.use_count() == 1);
  REQUIRE(RoomList.headPtr->next->next->next->next.use_count() == 1);
  REQUIRE(RoomList.headPtr->next->next->next->next->next.use_count() == 1);
  REQUIRE(RoomList.headPtr->next->next->next->next->next->next.use_count() == 1);
}

/*
TEST_CASE("shared_ptr with linked list destructor", "[smart_ptr]")
{
  auto start = std::chrono::high_resolution_clock::now();
  {
    LinkedListSmart<int> IntList;
    for (int i = 0; i < 1000; ++i)
    {
      IntList.insert(i + 1, i);
    }
    start = std::chrono::high_resolution_clock::now(); // start the timer right before IntList goes out of scope
  } // IntList goes out of scope here
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken to destroy the linked list: " << duration.count() << " microseconds" << std::endl;
}
*/