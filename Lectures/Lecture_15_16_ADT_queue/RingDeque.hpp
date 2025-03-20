/** ADT Deque: ring buffer-based implementation.
 @file RingDeque.hpp */
#ifndef RING_DEQUE_
#define RING_DEQUE_
#include "abstract_deque.hpp"
#include <stdexcept>

template <typename ItemType>
class RingDeque : public AbstractDeque<ItemType>
{
private:
   static const int DEFAULT_CAPACITY = 20;
   ItemType items[DEFAULT_CAPACITY]; // Array of queue items
   int front;                        // Index to front of queue
   int back;                         // Index to back of queue
   int count;                        // Number of items currently in the queue

public:
   RingDeque();
   // Copy constructor supplied by compiler; destructor is inherited
   bool isEmpty() const;
   void enqueue_front(const ItemType &someItem);
   void enqueue_back(const ItemType &someItem);
   void dequeue_front();
   void dequeue_back();
   ItemType peekFront() const;
   ItemType peekBack() const;
   bool isFull() const;
}; // end ArrayQueue
#include "RingDeque.tpp"
#endif
