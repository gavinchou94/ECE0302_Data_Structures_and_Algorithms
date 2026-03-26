#include "ArrayPQ.hpp"
#include <stdexcept>
#include <algorithm>

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
ArrayPQ<T>::ArrayPQ(const ArrayPQ &rhs) : count(rhs.count), items(nullptr)
{
  if (count > 0)
  {
    items = new T[count];
    for (int i = 0; i < count; i++)
      items[i] = rhs.items[i];
  }
} // end copy constructor

template <typename T>
ArrayPQ<T> &ArrayPQ<T>::operator=(ArrayPQ rhs)
{
  std::swap(count, rhs.count);
  std::swap(items, rhs.items);
  return *this;
} // end operator=

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

// TODO: answer this conceptual question
// In our implementation, priority is determined by T so the items themselves define the ordering.
// An alternative approach uses a wrapper struct (e.g., PQEntry { T item; int priority; }) to attach
// an external priority value to each item.
// What are the advantages and disadvantages of each approach?
// Give an example where letting T define its own ordering is more natural and efficient.
// Give an example where using an external priority value is preferable.

// TODO: answer this conceptual question
// On textbook, it mentions that the actual order of entries in a priority queue is not important as long as we can quickly retrieve the highest priority entry.
// Given this, explain why using an ADT sorted list to implement a priority queue is generally not necessary.