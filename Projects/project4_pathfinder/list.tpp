#include "list.hpp"

template <typename T>
List<T>::List()
{
  // TODO, 1-index based list, feel free to reuse your old code
}

template <typename T>
List<T>::~List()
{
  // TODO, 1-index based list, feel free to reuse your old code
}

template <typename T>
List<T>::List(const List<T> &x)
{
  // TODO, 1-index based list, feel free to reuse your old code
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  // TODO, 1-index based list, feel free to reuse your old code
  return *this;
}

template <typename T>
void List<T>::swap(List &x)
{
  // TODO, 1-index based list, feel free to reuse your old code
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  // TODO, 1-index based list, feel free to reuse your old code
  return true;
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  // TODO, 1-index based list, feel free to reuse your old code
  return 0;
}

template <typename T>
void List<T>::insert(std::size_t position, const T &item)
{
  // TODO, 1-index based list, feel free to reuse your old code
}

template <typename T>
void List<T>::remove(std::size_t position)
{
  // TODO, 1-index based list, feel free to reuse your old code
}

template <typename T>
void List<T>::clear()
{
  // TODO, 1-index based list, feel free to reuse your old code
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  // TODO, 1-index based list, feel free to reuse your old code
  return T();
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T &newValue)
{
  // TODO, 1-index based list, feel free to reuse your old code
}
