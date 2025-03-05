#include "sorted_list.hpp"
#include <stdexcept>

template <typename T>
SortedList<T>::SortedList() : List<T>() // base called, completed
{
}

template <typename T>
SortedList<T>::SortedList(List<T> unsorted_list)
{
  // TODO
}

template <typename T>
SortedList<T>::SortedList(const SortedList<T> &x) : List<T>(x) // base called, completed
{
}

template <typename T>
SortedList<T> &SortedList<T>::operator=(SortedList<T> x)
{
  List<T>::operator=(x);
  return *this;
} // base called, completed

template <typename T>
SortedList<T>::~SortedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedList<T>::isEmpty() const noexcept
{
  return List<T>::isEmpty();
} // base called, completed

template <typename T>
std::size_t SortedList<T>::getLength() const noexcept
{
  return List<T>::getLength();
} // base called, completed

template <typename T>
void SortedList<T>::insert(const T &item)
{
  // TODO, check description in the header file sorted_list.hpp
}

template <typename T>
void SortedList<T>::remove(const T &item)
{
  // TODO, check description in the header file sorted_list.hpp
}

template <typename T>
void SortedList<T>::removeAt(std::size_t position)
{
  // TODO, check description in the header file sorted_list.hpp
}

template <typename T>
void SortedList<T>::clear()
{
  List<T>::clear();
} // base called, completed

template <typename T>
T SortedList<T>::getEntry(std::size_t position) const
{
  return List<T>::getEntry(position);
} // base called, completed

template <typename T>
std::size_t SortedList<T>::getPosition(const T &item)
{
  // TODO, check description in the header file sorted_list.hpp
  return 0;
}