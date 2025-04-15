#include "frontier_queue.hpp"

template <typename T>
State<T> frontier_queue<T>::pop()
{

  // TODO: implement this the same way we implemented pop in the heap lecture. Compare states using getFCost.

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
