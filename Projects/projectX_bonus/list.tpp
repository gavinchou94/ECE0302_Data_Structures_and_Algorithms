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
void List<T>::swap(List<T> &x)
{
  // TODO
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  // TODO
  return true;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  // TODO
  return 0;
}

template <typename T>
void List<T>::insert(std::size_t position, const T &item)
{
  // TODO
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  // TODO
}

template <typename T>
void List<T>::clear()
{
  // TODO
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  // TODO
  return T();
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T &newValue)
{
  // TODO
}
