#include "state.hpp"

template <typename T>
State<T>::State(const T &p, int cost, int heur) : value(p), gcost(cost), heuristic(heur)
{
  fcost = gcost + heuristic;
}

template <typename T>
T State<T>::getValue() const
{
  return value;
}

template <typename T>
void State<T>::updatePathCost(int cost)
{
  gcost = cost;
  fcost = gcost + heuristic;
}

template <typename T>
int State<T>::getPathCost() const
{
  return gcost;
}

template <typename T>
int State<T>::getFCost() const
{
  return fcost;
}