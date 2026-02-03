#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include "abstract_list.hpp"

template <typename T>
class ArrayList : public AbstractList<T>
{
public:
  // default constructor
  ArrayList();

  // destructor
  ~ArrayList();

  // copy constructor
  ArrayList(const ArrayList &rhs);

  // copy assignment using copy-and-swap idiom
  ArrayList &operator=(ArrayList rhs);

  // swap
  void swap(ArrayList &rhs);

  // determine if a list is empty
  bool isEmpty() const noexcept;

  // return current length of the list
  int getLength() const noexcept;

  // insert item at position in the list
  bool insert(int position, const T &item);

  // remove item at position in the list
  bool remove(int position);

  // remove all items from the list
  void clear();

  // get a copy of the item at position
  // throw std::out_of_range if position < 1 or position > getLength()
  T getEntry(int position) const;

  // set the value of the item at position
  // throw std::out_of_range if position < 1 or position > getLength()
  void setEntry(int position, const T &newValue);

private:
  // TODO
};

#include "array_list.tpp"

#endif