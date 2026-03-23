#include "list.hpp"

template <typename T>
List<T>::List()
{
  // TODO
}

template <typename T>
List<T>::~List()
{
  // TODO
}

template <typename T>
List<T>::List(const List<T> &x)
{
  // TODO
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  // TODO
  return *this;
}

template <typename T>
void List<T>::swap(List &x)
{
  // TODO
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  // TODO
  return false;
}

template <typename T>
int List<T>::getLength() const noexcept
{
  // TODO
  return 0;
}

template <typename T>
void List<T>::insert(int position, const T &item)
{
  // TODO, implement the insert function using 1-based indexing
  // Note the void return type and throw std::out_of_range if the position is invalid
}

template <typename T>
void List<T>::remove(int position)
{
  // TODO, implement the remove function using 1-based indexing
  // Note the void return type and throw std::out_of_range if the position is invalid
}

template <typename T>
void List<T>::clear()
{
  // TODO
}

template <typename T>
T List<T>::getEntry(int position) const
{
  // TODO
  // Throws std::out_of_range if the position is invalid
  return T();
}

template <typename T>
void List<T>::setEntry(int position, const T &newValue)
{
  // TODO
  // Throws std::out_of_range if the position is invalid
}