/** @file ArrayQueue.cpp */
#include "ArrayQueue.hpp" // Header file

template <typename ItemType>
ArrayQueue<ItemType>::ArrayQueue() : back(0), count(0)
{
} // end default constructor
// why don't we need a private member variable for front?

template <typename ItemType>
bool ArrayQueue<ItemType>::isEmpty() const
{
   return count == 0;
} // end isEmpty

template <typename ItemType>
void ArrayQueue<ItemType>::enqueue(const ItemType &someItem)
{
   if (count < DEFAULT_CAPACITY)
   {
      // Queue has room for another item
      back++;
      items[back] = someItem;
      count++;
   } // end if
   else
   {
      throw std::logic_error("enqueue() called with full queue");
   }
} // end enqueue

template <typename ItemType>
void ArrayQueue<ItemType>::dequeue()
{
   if (!isEmpty())
   {
      for (int i = 1; i < count; i++)
      {
         items[i] = items[i + 1];
      } // end for
      back--;
      count--;
   } // end if
   else
   {
      throw std::logic_error("dequeue() called with empty queue");
   }
} // end dequeue

template <typename ItemType>
ItemType ArrayQueue<ItemType>::peekFront() const
{
   // Enforce precondition
   if (isEmpty())
      throw std::logic_error("dequeue() called with empty queue");

   // Queue is not empty; return front
   return items[1];
} // end peekFront
// End of implementation file.

// Which statement signifies the time complexity of the dequeue operation to be O(n)?
