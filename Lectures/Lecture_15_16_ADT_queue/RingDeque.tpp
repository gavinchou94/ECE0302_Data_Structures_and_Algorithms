/** @file RingDeque.tpp */
#include "RingDeque.hpp" // Header file

template <typename ItemType>
RingDeque<ItemType>::RingDeque() : front(0), back(DEFAULT_CAPACITY - 1), count(0)
{
} // end default constructor

template <typename ItemType>
bool RingDeque<ItemType>::isEmpty() const
{
   return count == 0;
} // end isEmpty

template <typename ItemType>
void RingDeque<ItemType>::enqueue_back(const ItemType &someItem)
{
   if (count < DEFAULT_CAPACITY) // Queue has room for another item
   {
      back = (back + 1) % DEFAULT_CAPACITY;
      // why do we need to use % DEFAULT_CAPACITY?
      // in other words, can we just use back++? and if back>DEFAULT_CAPACITY, we throw an exception?
      items[back] = someItem;
      count++;
   }
   else
   {
      throw std::logic_error("enqueue() called with full queue");
   }
} // end enqueue

template <typename ItemType>
void RingDeque<ItemType>::enqueue_front(const ItemType &someItem)
{
   if (count < DEFAULT_CAPACITY) // Queue has room for another item
   {
      front = (front - 1 + DEFAULT_CAPACITY) % DEFAULT_CAPACITY;
      items[front] = someItem;
      count++;
   }
   else
   {
      throw std::logic_error("enqueue() called with full queue");
   }
}

template <typename ItemType>
void RingDeque<ItemType>::dequeue_front()
{
   if (!isEmpty())
   {
      front = (front + 1) % DEFAULT_CAPACITY;
      count--;
   }
   else
   {
      throw std::logic_error("dequeue() called with empty queue");
   }
} // end dequeue

template <typename ItemType>
void RingDeque<ItemType>::dequeue_back()
{
   if (!isEmpty())
   {
      back = (back - 1 + DEFAULT_CAPACITY) % DEFAULT_CAPACITY;
      count--;
   }
   else
   {
      throw std::logic_error("dequeue() called with empty queue");
   }
} // end dequeue

template <typename ItemType>
ItemType RingDeque<ItemType>::peekFront() const
{
   // Enforce precondition
   if (isEmpty())
      throw std::logic_error("peekFront() called with empty queue");
   // Queue is not empty; return front
   return items[front];
} // end peekFront

template <typename ItemType>
ItemType RingDeque<ItemType>::peekBack() const
{
   // Enforce precondition
   if (isEmpty())
      throw std::logic_error("peekBack() called with empty queue");
   // Queue is not empty; return back
   return items[back];
} // end peekBack

template <typename ItemType>
bool RingDeque<ItemType>::isFull() const
{
   // any other way to implement isFull() using comparisons between front and back?
   return count == DEFAULT_CAPACITY;
} // end isFull
// End of implementation file.