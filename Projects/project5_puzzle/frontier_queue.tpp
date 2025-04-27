#include "frontier_queue.hpp"

template <typename T>
State<T> frontier_queue<T>::pop()
{

  // TODO: implement frontier_queue as a min heap, the same way we implemented pop in the heap lecture.
  // Compare states using getFCost.

  return State<T>(T(), 0, 0);
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur)
{

  // TODO: implement this the same way we implemented push in the heap lecture.
}

template <typename T>
bool frontier_queue<T>::empty()
{

  // TODO

  return true;
}

template <typename T>
bool frontier_queue<T>::contains(const T &p)
{

  // TODO

  return false;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost)
{
  // TODO
}

template <typename T>
std::size_t frontier_queue<T>::getcurrentCost(const T &p)
{
  if (!contains(p))
  {
    return -1; // if the state is not in the queue, return -1
  }
  // find the index of the state in the queue
  int index = -1;
  for (int i = 0; i < queue.size(); ++i)
  {
    if (queue[i].getValue() == p)
    {
      index = i;
      break;
    }
  }
  return queue[index].getPathCost(); // return the cost of the state
}