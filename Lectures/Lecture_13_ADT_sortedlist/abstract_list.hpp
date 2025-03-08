#ifndef _ABSTRACT_LIST_HPP_
#define _ABSTRACT_LIST_HPP_

#include <cstdlib>

template <typename T>
class AbstractList
{
public:
  // virtual destructor to ensure overriding
  virtual ~AbstractList() {};

  // determine if a list is empty
  virtual bool isEmpty() const = 0;

  // return current length of the list
  virtual int getLength() const = 0;

  // insert item at position in the list using 1-based indexing
  virtual bool insert(int position, const T &item) = 0;

  // remove item at position in the list using 1-based indexing
  virtual bool remove(int position) = 0;

  // remove all items from the list
  virtual void clear() = 0;

  // get a copy of the item at position using 1-based indexing
  virtual T getEntry(int position) const = 0;

  // set the value of the item at position using 1-based indexing
  virtual void setEntry(int position, const T &newValue) = 0;
};

#endif