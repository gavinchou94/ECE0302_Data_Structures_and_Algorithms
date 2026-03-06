#include "sorted_list_array_compo.hpp"
#include <stdexcept>

template <typename T>
SortedList<T>::SortedList() : lst()
{
}

template <typename T>
SortedList<T>::SortedList(ArrayList<T> unsorted_list)
{
  for (int i = 0; i < unsorted_list.getLength(); i++)
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
int SortedList<T>::getLength() const noexcept
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

  int position = 1;
  while (position <= lst.getLength() && lst.getEntry(position) < item)
    position++;

  lst.insert(position, item);
}

template <typename T>
void SortedList<T>::remove(const T &item) // TODO: This is of O(n+log n) and the log(n) comes from the getPosition
                                          // but which few lines of getPosition() do you need to change to reduce it to log n
                                          // and why is possible to do so?
{
  int position = getPosition(item);

  if (position < lst.getLength() && lst.getEntry(position) == item)
    removeAt(position);
  else
    throw std::out_of_range("Item not found");
}

template <typename T>
void SortedList<T>::removeAt(int position) // TODO: explain why this is of O(n)? where does it come from?
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
T SortedList<T>::getEntry(int position) const
{
  return lst.getEntry(position);
}

template <typename T>
int SortedList<T>::getPosition(const T &item)
{
  if (isEmpty())
    throw std::out_of_range("List is empty");

  int position = 1;
  while (position <= lst.getLength() && lst.getEntry(position) < item)
    position++;

  if (position == lst.getLength() + 1 || lst.getEntry(position) != item)
    throw std::out_of_range("Item not found");

  return position;
}