#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  // TODO, default constructor
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  // TODO, destructor
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &x)
{
  // TODO, copy constructor
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> x)
{
  // TODO, copy assignment
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList &x)
{
  // TODO, swap helper function for copy assignment
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  // TODO
  return true;
}

template <typename T>
int LinkedList<T>::getLength() const noexcept
{
  // TODO
  return 0;
}

template <typename T>
bool LinkedList<T>::insert(int position, const T &item)
{
  // TODO
  return true;
}

template <typename T>
bool LinkedList<T>::remove(int position)
{
  // TODO
  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  // TODO
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
T LinkedList<T>::getEntry(int position) const
{
  // TODO
  return T();
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
void LinkedList<T>::setEntry(int position, const T &newValue)
{
  // TODO
}
