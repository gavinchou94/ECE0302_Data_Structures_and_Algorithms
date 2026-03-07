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
      // TODO: explain why we need to use % DEFAULT_CAPACITY?
      // In other words, can we just increment back (e.g., back++) and throw an exception if it exceeds DEFAULT_CAPACITY?
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
   {
      throw std::logic_error("peekFront() called with empty queue");
   }
   return items[front]; // Queue is not empty; return front
} // end peekFront

template <typename ItemType>
ItemType RingDeque<ItemType>::peekBack() const
{
   // Enforce precondition
   if (isEmpty())
   {
      throw std::logic_error("peekBack() called with empty queue");
   }
   return items[back]; // Queue is not empty; return back
} // end peekBack

template <typename ItemType>
bool RingDeque<ItemType>::isFull() const
{
   return count == DEFAULT_CAPACITY;
   // TODO: Is there any other way to implement isFull() using comparisons between front and back?
} // end isFull
// End of implementation file.

// TODO: We discussed in class that the time complexity of each operation (enqueue_front, enqueue_back, dequeue_front, dequeue_back, peekFront, peekBack) in this implementation
// is O(1). Justify this claim by explaining and searching for keywords in the code. 