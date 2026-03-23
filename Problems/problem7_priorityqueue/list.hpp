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

  int getLength() const noexcept;

  void insert(int position, const T &item);

  void remove(int position);

  void clear();

  T getEntry(int position) const;

  void setEntry(int position, const T &newValue);

private:
  // TODO, you might be able reuse code from Problem 3/5/6
};

#include "list.tpp"

#endif