#ifndef _LIST_HPP_
#define _LIST_HPP_

#include "abstract_list.hpp"

template <typename T>
class List : public AbstractList<T>
{
public:
  List();

  List(const List &x);

  ~List();

  List &operator=(List x);

  void swap(List &x);

  bool isEmpty() const noexcept;

  std::size_t getLength() const noexcept;

  void insert(std::size_t position, const T &item);

  void remove(std::size_t position);

  void clear();

  T getEntry(std::size_t position) const;

  void setEntry(std::size_t position, const T &newValue);

private:
  // TODO, refer to Problem 2 or 4
};

#include "list.tpp"

#endif
