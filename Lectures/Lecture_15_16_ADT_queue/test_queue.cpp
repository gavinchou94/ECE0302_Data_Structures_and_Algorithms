/** @file test_queue.cpp
 * @author G. Zhou
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ArrayQueue.hpp"
#include "RingDeque.hpp"
#include "ArrayPQ.hpp"
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

   // Add a breakpoint here to check the contents of the deque object
   // What is the value of front, back, and count?
   // What is the content stored in the array now? items[0] to items[19]
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

TEST_CASE("Test isEmpty() for ArrayPQ", "[ArrayPQ]")
{
   ArrayPQ<int> pq;
   REQUIRE(pq.isEmpty() == true);
}

TEST_CASE("Test add, remove and peek for ArrayPQ", "[ArrayPQ]")
{
   ArrayPQ<int> pq;
   pq.add(3);
   pq.add(1);
   pq.add(2);
   REQUIRE(pq.peek() == 3);
   pq.add(10);
   pq.add(9);
   pq.add(8);

   REQUIRE(pq.peek() == 10);
   pq.remove();
   REQUIRE(pq.peek() == 9);
}

TEST_CASE("Test exception for empty priority queue for ArrayPQ", "[ArrayPQ]")
{
   ArrayPQ<int> pq;
   REQUIRE_THROWS_AS(pq.peek(), std::out_of_range);
   REQUIRE_THROWS_AS(pq.remove(), std::out_of_range);
}

struct OfficeHoursSequence
{
   std::string name;
   int arrivalTime;
   int urgency;

   bool operator<(const OfficeHoursSequence &rhs) const
   {
      if (arrivalTime != rhs.arrivalTime)
         return arrivalTime > rhs.arrivalTime;
      else
         return urgency < rhs.urgency;
   }
};

TEST_CASE("Test add, remove and peek for ArrayPQ with custom type", "[ArrayPQ]")
{
   ArrayPQ<OfficeHoursSequence> pq;
   OfficeHoursSequence s1 = {"Alice", 300, 1};
   OfficeHoursSequence s2 = {"Bob", 300, 2};
   OfficeHoursSequence s3 = {"Charlie", 315, 3};
   OfficeHoursSequence s4 = {"David", 316, 6};
   pq.add(s1);
   pq.add(s2);
   pq.add(s3);
   pq.add(s4);

   // REQUIRE(pq.peek().name == ???);
   pq.remove();
   // REQUIRE(pq.peek().name == ???);
   pq.remove();
   // REQUIRE(pq.peek().name == ???);
   pq.remove();
   // REQUIRE(pq.peek().name == ???);
   pq.remove();
   REQUIRE_THROWS_AS(pq.peek(), std::out_of_range);
}
