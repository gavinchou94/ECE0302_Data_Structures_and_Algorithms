#ifndef STATE_HPP
#define STATE_HPP

template <typename T> // generic state holding a label value of type T
class State
{
public:
  // Constructor
  State(const T &p, std::size_t cost, std::size_t heur);

  // Getters for value
  T getValue() const;

  /** @brief Update the path cost (g) and recalculate f-cost (f = g + h)
   *  @param cost The new path cost (g) to the state point */
  void updatePathCost(std::size_t cost);

  // Getters for g
  std::size_t getPathCost() const;

  // Getters for f
  std::size_t getFCost() const;

private:
  // A state in A* search is defined by its label value, path cost (g), heuristic (h) and f-cost = g + h
  T value;
  std::size_t g{0};
  std::size_t h{0};
  std::size_t f{0};
};

#include "state.tpp"

#endif
