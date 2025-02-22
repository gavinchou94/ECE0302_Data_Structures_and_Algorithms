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
  virtual bool isEmpty() const noexcept = 0;

  // return current length of the list
  virtual std::size_t getLength() const noexcept = 0;

  // insert item at position in the list using 1-based indexing
  virtual bool insert(std::size_t position, const T &item) = 0;

  // remove item at position in the list using 1-based indexing
  virtual bool remove(std::size_t position) = 0;

  // remove all items from the list
  virtual void clear() = 0;

  // get a copy of the item at position using 1-based indexing
  // throw std::out_of_range if position < 1 or position > getLength()
  virtual T getEntry(std::size_t position) const = 0;

  // set the value of the item at position using 1-based indexing
  // throw std::out_of_range if position < 1 or position > getLength()
  virtual void setEntry(std::size_t position, const T &newValue) = 0;

  // move a value from index "from" to index "to"
  // order of other values in the list should be preserved
  // throw std::out_of_range if from/to < 1 or from/to > getLength()
  virtual void moveEntry(std::size_t from, std::size_t to) = 0;
};

#endif
