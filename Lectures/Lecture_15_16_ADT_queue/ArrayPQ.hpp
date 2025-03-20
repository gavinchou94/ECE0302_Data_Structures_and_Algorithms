#ifndef _ARRAY_PQ_HPP_
#define _ARRAY_PQ_HPP_

#include "abstract_priority_queue.hpp"

template <typename T>
class ArrayPQ : public AbstractPriorityQueue<T>
{
public:
  ArrayPQ();
  ~ArrayPQ();
  bool isEmpty() const;
  void add(const T &item);
  void remove();
  T peek();

private:
  int count;
  T *items;
};

#include "ArrayPQ.tpp"

#endif
