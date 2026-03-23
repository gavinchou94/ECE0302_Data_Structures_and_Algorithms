#ifndef _SORTED_LIST_HPP_
#define _SORTED_LIST_HPP_

#include "abstract_sorted_list.hpp"
#include "list.hpp"

template <typename T>
class SortedList : public AbstractSortedList<T>, private List<T> // multiple inheritance
{
public:
  SortedList();

  SortedList(List<T> unsorted_list); // constructor from list (should sort the input list)

  SortedList(const SortedList &x); // copy constructor

  SortedList &operator=(SortedList x); // copy assignment operator

  ~SortedList();

  bool isEmpty() const noexcept;

  int getLength() const noexcept;

  void insert(const T &item);

  // remove first occurrence of item from the list
  // throw std::invalid_argument if not found (but exception handled by the List<T>)
  void remove(const T &item);

  // remove item at position in the list using 1-based indexing
  // throw std::out_of_range if position is invalid (but exception handled by the List<T>)
  void removeAt(int position);

  void clear();
  T getEntry(int position) const;

  // get the position (int type) of the first occurrence of item
  // throw std::invalid_argument if not found, handled by itself
  int getPosition(const T &item);

private:
  // TODO, you might be able reuse code from Problem 6
};

#include "sorted_list.tpp"

#endif