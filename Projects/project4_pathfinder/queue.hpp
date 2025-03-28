#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include "abstract_queue.hpp"

template <typename T, typename L>
class Queue : public AbstractQueue<T>
{
public:
  bool isEmpty() const;

  void enqueue(const T &item);

  void dequeue();

  T peekFront();

private:
  // L must conform to AbstractList interface
  L internal_list;
};

#include "queue.tpp"

#endif
