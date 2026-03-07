/** @file test_queue.cpp
 * @author G. Zhou */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ArrayQueue.hpp"
#include "RingDeque.hpp"
#include <stdexcept>

TEST_CASE("Test isEmpty() for ArrayQueue", "[ArrayQueue]")
{
   ArrayQueue<int> queue;
   REQUIRE(queue.isEmpty() == true);
}

TEST_CASE("Test enqueue() and peekFront() for ArrayQueue", "[ArrayQueue]")
{
   ArrayQueue<int> queue;
   queue.enqueue(1);
   queue.enqueue(2);
   queue.enqueue(3);
   REQUIRE(queue.peekFront() == 1);
   queue.enqueue(4);
   queue.enqueue(5);
   queue.enqueue(6);
   queue.enqueue(7);
   queue.enqueue(8);
   queue.enqueue(9);
   queue.enqueue(10);
   REQUIRE_THROWS_AS(queue.enqueue(11), std::logic_error);
}

TEST_CASE("Test dequeue() and peekFront() for ArrayQueue", "[ArrayQueue]")
{
   ArrayQueue<int> queue;
   for (int i = 1; i <= 10; ++i)
   {
      queue.enqueue(i);
   }
   REQUIRE(queue.peekFront() == 1);
   REQUIRE_THROWS_AS(queue.enqueue(11), std::logic_error);

   queue.dequeue();
   REQUIRE(queue.peekFront() == 2);
   REQUIRE_NOTHROW(queue.enqueue(11));

   queue.dequeue();
   REQUIRE(queue.peekFront() == 3);
   queue.dequeue();
   REQUIRE(queue.peekFront() == 4);
}

TEST_CASE("Test exception for empty queue for ArrayQueue", "[ArrayQueue]")
{
   ArrayQueue<int> queue;
   REQUIRE_THROWS_AS(queue.dequeue(), std::logic_error);
   REQUIRE_THROWS_AS(queue.peekFront(), std::logic_error);
}

TEST_CASE("Test isEmpty() for RingDeque", "[RingDeque]")
{
   RingDeque<int> deque;
   REQUIRE(deque.isEmpty() == true);
}

TEST_CASE("Test enqueue, deque and peek for RingDeque", "[RingDeque]")
{
   RingDeque<int> deque;
   deque.enqueue_front(1);
   deque.enqueue_front(2);
   deque.enqueue_front(3);
   REQUIRE(deque.peekFront() == 3);
   REQUIRE(deque.peekBack() == 1);

   deque.enqueue_back(4);
   deque.enqueue_back(5);
   deque.enqueue_back(6);
   REQUIRE(deque.peekFront() == 3);
   REQUIRE(deque.peekBack() == 6);

   deque.dequeue_front();
   REQUIRE(deque.peekFront() == 2);

   deque.dequeue_back();
   REQUIRE(deque.peekBack() == 5);
}

TEST_CASE("Test capacity for RingDeque", "[RingDeque]")
{
   RingDeque<int> deque;
   for (int i = 1; i <= 10; ++i)
   {
      deque.enqueue_back(i);
   }
   REQUIRE(deque.peekFront() == 1);
   REQUIRE(deque.peekBack() == 10);

   for (int i = 11; i <= 20; ++i)
   {
      deque.enqueue_front(i);
   }
   REQUIRE(deque.peekFront() == 20);
   REQUIRE(deque.peekBack() == 10);

   // TODO: Add a breakpoint here to check the deque's state.
   // What are the values of front, back, and count?
   // What is stored in the array from items[0] to items[19]?
   REQUIRE_THROWS_AS(deque.enqueue_back(21), std::logic_error);
   REQUIRE_THROWS_AS(deque.enqueue_front(21), std::logic_error);

   REQUIRE(deque.isFull() == true);
}

TEST_CASE("Test exception for empty deque for RingDeque", "[RingDeque]")
{
   RingDeque<int> deque;
   REQUIRE(deque.isEmpty() == true);
   REQUIRE(deque.isFull() == false);
   REQUIRE_THROWS_AS(deque.dequeue_front(), std::logic_error);
   REQUIRE_THROWS_AS(deque.dequeue_back(), std::logic_error);
   REQUIRE_THROWS_AS(deque.peekFront(), std::logic_error);
   REQUIRE_THROWS_AS(deque.peekBack(), std::logic_error);
}