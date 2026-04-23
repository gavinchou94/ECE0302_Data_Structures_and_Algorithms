#include "frontier_queue.hpp"

// Min-heap index helpers:
//   parent of i      : (i - 1) / 2
//   left  child of i : 2 * i + 1
//   right child of i : 2 * i + 2

template <typename T>
State<T> frontier_queue<T>::pop()
{
  // TODO: implement frontier_queue as a min heap. Compare states using getFCost.
  return State<T>(T(), 0, 0);
}

template <typename T>
void frontier_queue<T>::push(const T &state, int cost, int heur)
{
  // TODO
}

template <typename T>
bool frontier_queue<T>::empty()
{
  // TODO
  return true;
}

template <typename T>
bool frontier_queue<T>::contains(const T &state)
{
  // TODO
  return false;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &state, int cost)
{
  // TODO
}

template <typename T>
int frontier_queue<T>::getCurrentPathCost(const T &state)
{
  // TODO
  return 0;
}