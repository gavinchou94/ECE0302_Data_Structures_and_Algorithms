#ifndef _SORTED_LIST_HPP_
#define _SORTED_LIST_HPP_

#include "abstract_sorted_list.hpp"

// T is any orderable type
// L must conform to the AbstractList Interface
template <typename T, typename L>
class SortedList : public AbstractSortedList<T>
{
public:
  SortedList();

  SortedList(const SortedList &x);

  SortedList &operator=(SortedList x);

  ~SortedList();

  bool isEmpty() const noexcept;

  std::size_t getLength() const noexcept;

  void insert(const T &item);

  void remove(const T &item);

  void removeAt(std::size_t position);

  void clear();

  T getEntry(std::size_t position) const;

  std::size_t getPosition(const T &newValue);

private:
  L plist; // private list
};

#include "sorted_list.tpp"

#endif
