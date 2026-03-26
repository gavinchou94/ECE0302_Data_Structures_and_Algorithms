/** @file ArrayQueue.cpp */
#include "ArrayQueue.hpp"
#include <stdexcept>

template <typename ItemType>
ArrayQueue<ItemType>::ArrayQueue() : back(0), count(0)
{
} // end default constructor
// TODO: Explain why we don't need a private member variable for front? And what index is the front of the queue? Can we further simplify the private member variables?

template <typename ItemType>
bool ArrayQueue<ItemType>::isEmpty() const
{
   return count == 0;
} // end isEmpty

template <typename ItemType>
void ArrayQueue<ItemType>::enqueue(const ItemType &someItem)
{
   if (count < DEFAULT_CAPACITY) // Queue has room for another item
   {
      back++;
      items[back] = someItem;
      count++;
   }
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
      }
      back--;
      count--;
   }
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
   {
      throw std::logic_error("dequeue() called with empty queue");
   }
   return items[1]; // Queue is not empty; return front
} // end peekFront
// End of implementation file