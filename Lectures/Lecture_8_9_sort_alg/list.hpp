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

  bool insert(std::size_t position, const T &item);

  bool remove(std::size_t position);

  void clear();

  T getEntry(std::size_t position) const;

  void setEntry(std::size_t position, const T &newValue);

  void moveEntry(std::size_t from, std::size_t to);

private:
  T *items;
  std::size_t itemCount;
};

#include "list.tpp"

#endif
