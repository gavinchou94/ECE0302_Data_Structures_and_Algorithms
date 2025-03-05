#include "list.hpp"

template <typename T>
List<T>::List()
{
  // TODO, refer to Problem 2 or 4
}

template <typename T>
List<T>::~List()
{
  // TODO, refer to Problem 2 or 4
}

template <typename T>
List<T>::List(const List<T> &x)
{
  // TODO, refer to Problem 2 or 4
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  // TODO, refer to Problem 2 or 4
  return *this;
}

template <typename T>
void List<T>::swap(List &x)
{
  // TODO, refer to Problem 2 or 4
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  // TODO, refer to Problem 2 or 4
  return false;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  // TODO, refer to Problem 2 or 4
  return 0;
}

template <typename T>
void List<T>::insert(std::size_t position, const T &item)
{
  // TODO, implement the insert function using 1-based indexing
  // Note the void return type and throw std::out_of_range if the position is invalid
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  // TODO, implement the remove function using 1-based indexing
  // Note the void return type and throw std::out_of_range if the position is invalid
}

template <typename T>
void List<T>::clear()
{
  // TODO, refer to Problem 2 or 4
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  // TODO, refer to Problem 2 or 4
  // Throws std::out_of_range if the position is invalid
  return T();
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T &newValue)
{
  // TODO, refer to Problem 2 or 4
  // Throws std::out_of_range if the position is invalid
}