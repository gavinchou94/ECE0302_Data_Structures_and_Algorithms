#ifndef _ABSTRACT_SORTED_LIST_HPP_
#define _ABSTRACT_SORTED_LIST_HPP_

template <typename T>
class AbstractSortedList
{
public:
  // virtual destructor to ensure overriding
  virtual ~AbstractSortedList() {};

  // determine if a list is empty
  virtual bool isEmpty() const noexcept = 0;

  // return current length of the list
  virtual int getLength() const noexcept = 0;

  // insert item at sorted position in the list
  virtual void insert(const T &item) = 0;

  // remove first occurrence of item from the list
  virtual void remove(const T &item) = 0;

  // remove item at position in the list using 1-based indexing
  virtual void removeAt(int position) = 0;

  // remove all items from the list
  virtual void clear() = 0;

  // get the item at position using 1-based indexing
  virtual T getEntry(int position) const = 0;

  // get the position of the first occurrence of item
  virtual int getPosition(const T &newValue) = 0;
};

#endif