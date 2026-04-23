#ifndef STATE_HPP
#define STATE_HPP

template <typename T> // generic state holding a label value of type T
class State
{
public:
  // Constructs a state with a value, path cost (gcost), and heuristic
  State(const T &p, int cost, int heur);

  // Returns the state's label value
  T getValue() const;

  /** @brief Update the path cost (gcost) and recalculate fcost (fcost = gcost + heuristic) of the state
   *  @param cost The new path cost (gcost) to the state point */
  void updatePathCost(int cost);

  // Returns the path cost g(n) to reach this state
  int getPathCost() const;

  // Returns the total estimated cost f(n) = g(n) + h(n)
  int getFCost() const;

private:
  // A state in A* search is defined by its label value, path cost (gcost), heuristic (heuristic) and fcost = gcost + heuristic
  T value;
  int gcost{0};
  int heuristic{0};
  int fcost{0};
};

#include "state.tpp"
#endif