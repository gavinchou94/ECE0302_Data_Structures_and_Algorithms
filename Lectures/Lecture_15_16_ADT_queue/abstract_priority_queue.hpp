#ifndef _ABSTRACT_PRIORITY_QUEUE_HPP_
#define _ABSTRACT_PRIORITY_QUEUE_HPP_

// type T must be orderable (support operator<)
template <typename T>
class AbstractPriorityQueue
{
public:
  // virtual destructor to ensure overriding
  virtual ~AbstractPriorityQueue() {};

  // return true if the priority queue is empty
  virtual bool isEmpty() const = 0;

  // insert item into the queue
  virtual void add(const T &item) = 0;

  // remove highest priority item from the queue
  virtual void remove() = 0;

  // get the item with the highest priority from the queue
  // throw std::out_of_range if queue is empty
  virtual T peek() = 0;
};

#endif