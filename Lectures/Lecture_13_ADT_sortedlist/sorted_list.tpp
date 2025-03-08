#include "sorted_list.hpp"
#include <stdexcept>

template <typename T>
SortedList<T>::SortedList() : lst()
{
}

template <typename T>
SortedList<T>::SortedList(ArrayList<T> unsorted_list)
{
  for (std::size_t i = 0; i < unsorted_list.getLength(); i++)
    insert(unsorted_list.getEntry(i));
}

template <typename T>
SortedList<T>::SortedList(const SortedList<T> &x) // copy constructor
{
  lst = x.lst;
}

template <typename T>
bool SortedList<T>::isEmpty() const noexcept
{
  return lst.isEmpty();
}

template <typename T>
std::size_t SortedList<T>::getLength() const noexcept
{
  return lst.getLength();
}

template <typename T>
void SortedList<T>::insert(const T &item)
{
  if (isEmpty())
  {
    lst.insert(1, item);
    return;
  }

  std::size_t position = 1;
  while (position <= lst.getLength() && lst.getEntry(position) < item)
    position++;

  lst.insert(position, item);
}

template <typename T>
void SortedList<T>::remove(const T &item) // This is of O(n+log n)
                                          // and the log n comes from the getPosition
                                          // but which lines of getPosition() do you need to change to reduce it to log n
{
  std::size_t position = getPosition(item);

  if (position < lst.getLength() && lst.getEntry(position) == item)
    removeAt(position);
  else
    throw std::out_of_range("Item not found");
}

template <typename T>
void SortedList<T>::removeAt(std::size_t position) // why is this of O(n)?
                                                   // which for-loop and where does it come from?
{
  if (isEmpty())
    throw std::out_of_range("List is empty");

  if (position > lst.getLength())
    throw std::out_of_range("Position out of range");

  lst.remove(position);
}
// if lst.remove(position) is implemented via linked list
// for (int i = 0; i < position; i++)
//      curr = curr->next;
// you need to traverse the list to find the position' node
// then remove it

template <typename T>
void SortedList<T>::clear()
{
  lst.clear();
}

template <typename T>
T SortedList<T>::getEntry(std::size_t position) const
{
  return lst.getEntry(position);
}

template <typename T>
std::size_t SortedList<T>::getPosition(const T &item)
{
  if (isEmpty())
    throw std::out_of_range("List is empty");

  std::size_t position = 1;
  while (position <= lst.getLength() && lst.getEntry(position) < item)
    position++;

  if (position == lst.getLength() + 1 || lst.getEntry(position) != item)
    throw std::out_of_range("Item not found");

  return position;
}