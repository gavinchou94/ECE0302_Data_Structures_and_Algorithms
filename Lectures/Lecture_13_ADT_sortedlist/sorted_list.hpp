#ifndef _SORTED_LIST_HPP_
#define _SORTED_LIST_HPP_

#include "abstract_sorted_list.hpp"
#include "ArrayList.hpp"

template <typename T>
class SortedList : public AbstractSortedList<T>
{
public:
  SortedList();

  // constructor from list (should sort the input list)
  SortedList(ArrayList<T> unsorted_list);

  SortedList(const SortedList &x); // copy constructor

  bool isEmpty() const noexcept;

  std::size_t getLength() const noexcept;

  void insert(const T &item);

  // remove first occurrence of item from the list
  // throw std::invalid_argument if not found (but exception handled by the List<T>)
  void remove(const T &item);

  // remove item at position in the list using 1-based indexing
  // throw std::out_of_range if position is invalid (but exception handled by the List<T>)
  void removeAt(std::size_t position);

  void clear();

  // return the item at position using 1-based indexing
  // throw std::out_of_range if position is invalid (but exception handled by the List<T>)
  T getEntry(std::size_t position) const;

  // get the position (std::size_t type) of the first occurrence of item
  // throw std::invalid_argument if not found, handled by itself
  std::size_t getPosition(const T &item);

private:
  ArrayList<T> lst; // private member variable, composition
};

#include "sorted_list.tpp"

#endif
