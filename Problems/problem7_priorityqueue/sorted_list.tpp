#include "sorted_list.hpp"
#include <stdexcept>

template <typename T>
SortedList<T>::SortedList() : List<T>()
{
} // Constructor, completed

template <typename T>
SortedList<T>::SortedList(List<T> unsorted_list)
{
  // TODO, must comform to the description in the header file sorted_list.hpp
}

template <typename T>
SortedList<T>::SortedList(const SortedList<T> &x) : List<T>(x)
{
} // Copy constructor, completed

template <typename T>
SortedList<T> &SortedList<T>::operator=(SortedList<T> x)
{
  List<T>::operator=(x);
  return *this;
} // Copy assignment operator, completed

template <typename T>
SortedList<T>::~SortedList()
{
} // Destructor, completed

template <typename T>
bool SortedList<T>::isEmpty() const noexcept
{
  return List<T>::isEmpty();
} // Base Class function called, completed

template <typename T>
int SortedList<T>::getLength() const noexcept
{
  return List<T>::getLength();
} // Base Class function called, completed

template <typename T>
void SortedList<T>::insert(const T &item)
{
  // TODO, must comform to the description in the header file sorted_list.hpp
}

template <typename T>
void SortedList<T>::remove(const T &item)
{
  // TODO, must comform to the description in the header file sorted_list.hpp
}

template <typename T>
void SortedList<T>::removeAt(int position)
{
  // TODO, must comform to the description in the header file sorted_list.hpp
}

template <typename T>
void SortedList<T>::clear()
{
  List<T>::clear();
} // Base Class function called, completed

template <typename T>
T SortedList<T>::getEntry(int position) const
{
  return List<T>::getEntry(position);
} // Base Class function called, completed

template <typename T>
int SortedList<T>::getPosition(const T &item)
{
  // TODO, must comform to the description in the header file sorted_list.hpp
  return 0;
}