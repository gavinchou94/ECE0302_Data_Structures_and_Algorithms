#ifndef _PRIORITY_QUEUE_HPP_
#define _PRIORITY_QUEUE_HPP_

#include "abstract_priority_queue.hpp"

// Type T must be orderable
template <typename T>
class PriorityQueue : public AbstractPriorityQueue<T>
{
public:
  bool isEmpty() const;

  void add(const T &item);

  /** Remove the item with the highest priority from the queue
   * @throw std::out_of_range if queue is empty */
  void remove();

  /** @return the item with the highest priority from the queue
   * @throw std::out_of_range if queue is empty */
  T peek();

private:
  // TODO, you need to use composition to implement the priority queue using a sorted list
};

#include "priority_queue.tpp"

#endif