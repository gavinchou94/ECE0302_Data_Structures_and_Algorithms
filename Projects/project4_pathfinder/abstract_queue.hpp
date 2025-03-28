#ifndef _ABSTRACT_QUEUE_HPP_
#define _ABSTRACT_QUEUE_HPP_

template <typename T>
class AbstractQueue
{
public:
  // virtual destructor to ensure overriding
  virtual ~AbstractQueue() {};

  // return true is the queue is empty
  virtual bool isEmpty() const = 0;

  // enqueue (add) newEntry to the queue back
  virtual void enqueue(const T &item) = 0;

  // dequeue (remove) newEntry from the queue front
  // throw std::out_of_range if queue is empty
  virtual void dequeue() = 0;

  // return a copy of the item at the front of the queue
  // throw std::out_of_range if queue is empty
  virtual T peekFront() = 0;
};

#endif
