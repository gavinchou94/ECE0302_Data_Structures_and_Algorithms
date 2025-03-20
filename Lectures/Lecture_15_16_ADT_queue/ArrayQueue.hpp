/** ADT Queue: array-based implementation.
 @file ArrayQueue.h */
#ifndef ARRAY_QUEUE_
#define ARRAY_QUEUE_
#include "abstract_queue.hpp"
#include <stdexcept>

template <typename ItemType>
class ArrayQueue : public AbstractQueue<ItemType>
{
private:
   static const int DEFAULT_CAPACITY = 10;
   ItemType items[DEFAULT_CAPACITY + 1]; // Array of queue items
   int back;                             // Index to back of queue
   int count;                            // Number of items currently in the queue

public:
   ArrayQueue();
   // Copy constructor supplied by compiler; destructor is inherited
   bool isEmpty() const;
   void enqueue(const ItemType &someItem);
   void dequeue();
   ItemType peekFront() const;
}; // end ArrayQueue
#include "ArrayQueue.tpp"
#endif
