#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList()
{
  // TODO, default constructor
}

template <typename T>
ArrayList<T>::~ArrayList()
{
  // TODO, destructor
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList &rhs)
{
  // TODO, copy constructor
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList rhs)
{
  // TODO, copy assignment
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList &rhs)
{
  // TODO, swap helper function for copy assignment
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept
{
  // TODO
  return false;
}

template <typename T>
int ArrayList<T>::getLength() const noexcept
{
  // TODO
  return 0;
}

template <typename T>
bool ArrayList<T>::insert(int position, const T &item)
{
  // TODO
  return false;
}

template <typename T>
bool ArrayList<T>::remove(int position)
{
  // TODO
  return false;
}

template <typename T>
void ArrayList<T>::clear()
{
  // TODO
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
T ArrayList<T>::getEntry(int position) const
{
  // TODO
  return T();
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
void ArrayList<T>::setEntry(int position, const T &newValue)
{
  // TODO
}
