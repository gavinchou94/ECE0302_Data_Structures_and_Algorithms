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
std::size_t ArrayList<T>::getLength() const noexcept
{
  // TODO
  return 0;
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T &item)
{
  // TODO
  return false;
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position)
{
  // TODO
  return false;
}

template <typename T>
void ArrayList<T>::clear()
{
  // TODO
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const
{
  // TODO
  return T();
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T &newValue)
{
  // TODO
}
