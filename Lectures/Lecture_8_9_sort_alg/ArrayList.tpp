#include "ArrayList.hpp"

template <typename T>
List<T>::List() : items(nullptr), itemCount(0)
{
}

template <typename T>
List<T>::~List()
{
  delete[] items;
}

template <typename T>
List<T>::List(const List<T> &x)
{
  itemCount = x.itemCount;
  items = new T[itemCount];
  for (int i = 0; i < itemCount; i++)
  {
    items[i] = x.items[i];
  }
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List &x)
{
  std::swap(items, x.items);
  std::swap(itemCount, x.itemCount);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  return itemCount == 0;
}

template <typename T>
int List<T>::getLength() const noexcept
{
  return itemCount;
}

template <typename T>
bool List<T>::insert(int position, const T &item)
{
  bool ableToInsert = (position >= 1) && (position <= itemCount + 1);
  if (ableToInsert)
  {
    T *newItems = new T[itemCount + 1];
    for (int i = 0; i < position - 1; i++)
    {
      newItems[i] = items[i];
    }
    newItems[position - 1] = item;
    for (int i = position; i < itemCount + 1; i++)
    {
      newItems[i] = items[i - 1];
    }
    delete[] items;
    items = newItems;
    itemCount++;
  }
  return ableToInsert;
}

template <typename T>
bool List<T>::remove(int position)
{
  bool ableToRemove = (position >= 1) && (position <= itemCount);
  if (ableToRemove)
  {
    T *newItems = new T[itemCount - 1];
    for (int i = 0; i < position - 1; i++)
    {
      newItems[i] = items[i];
    }
    for (int i = position; i < itemCount; i++)
    {
      newItems[i - 1] = items[i];
    }
    delete[] items;
    items = newItems;
    itemCount--;
  }
  return ableToRemove;
}

template <typename T>
void List<T>::clear()
{
  delete[] items;
  items = nullptr;
  itemCount = 0;
}

template <typename T>
T List<T>::getEntry(int position) const
{
  if (position >= 1 && position <= itemCount)
  {
    return items[position - 1];
  }
  else
  {
    throw std::out_of_range("Index out of range");
  }
}

template <typename T>
void List<T>::setEntry(int position, const T &newValue)
{
  if (position >= 1 && position <= itemCount)
  {
    items[position - 1] = newValue;
  }
  else
  {
    throw std::out_of_range("Index out of range");
  }
}

template <typename T>
void List<T>::moveEntry(int from, int to)
{
  if (from >= 1 && from <= itemCount && to >= 1 && to <= itemCount)
  {
    T temp = items[from - 1];
    if (from < to)
    {
      for (int i = from; i < to; i++)
      {
        items[i - 1] = items[i];
      }
    }
    else
    {
      for (int i = from; i > to; i--)
      {
        items[i - 1] = items[i - 2];
      }
    }
    items[to - 1] = temp;
  }
  else
  {
    throw std::out_of_range("Index out of range");
  }
}
