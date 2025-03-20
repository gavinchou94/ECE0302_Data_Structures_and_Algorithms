#include "ArrayPQ.hpp"
#include <stdexcept>

template <typename T>
ArrayPQ<T>::ArrayPQ() : count(0), items(nullptr)
{
} // end default constructor

template <typename T>
ArrayPQ<T>::~ArrayPQ()
{
  delete[] items;
} // end destructor

template <typename T>
bool ArrayPQ<T>::isEmpty() const
{
  return count == 0;
} // end isEmpty

template <typename T>
void ArrayPQ<T>::add(const T &item)
{
  T *newItems = new T[count + 1];

  int i = 0;
  while (i < count && items[i] < item)
  {
    newItems[i] = items[i];
    i++;
  }
  // i is the index where the new item should be added to the queue
  newItems[i] = item;
  while (i < count)
  {
    newItems[i + 1] = items[i];
    i++;
  }
  count++;
  delete[] items;
  items = newItems;

} // end add

template <typename T>
void ArrayPQ<T>::remove()
{
  if (isEmpty())
  {
    throw std::out_of_range("remove() called with empty queue");
  }
  T *newItems = new T[count - 1];
  // always remove the last item (highest priority)
  for (int i = 0; i < count - 1; i++)
  {
    newItems[i] = items[i];
  }
  count--;
  delete[] items;
  items = newItems;
} // end remove

template <typename T>
T ArrayPQ<T>::peek()
{
  if (isEmpty())
  {
    throw std::out_of_range("peek() called with empty queue");
  }
  return items[count - 1];
} // end peek
// End of implementation file.

// What is the advantage and disadvantage of directly sorting the queue using the item value
// compared to using an additional priority value (see example below)?

// Give an example when sorting the queue using the item value is more efficient than using an additional priority value.
// Give another example when sorting the queue using an additional priority value is more efficient than using the item value.

// struct PQEntry
//{
//   T item;
//   double priority;
// };