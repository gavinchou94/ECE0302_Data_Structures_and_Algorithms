#ifndef _PRIORITY_QUEUE_HPP_
#define _PRIORITY_QUEUE_HPP_

#include "abstract_priority_queue.hpp"

// Type T must be orderable
// Type L must conform to AbstractSortedList<T>
template <typename T, typename L>
class PriorityQueue : public AbstractPriorityQueue<T>
{
public:
  bool isEmpty() const;

  void add(const T &item);

  void remove();

  T peek();

private:
  L slist; // internal sorted list
};

#include "priority_queue.tpp"

#endif