#ifndef FRONTIER_QUEUE_HPP
#define FRONTIER_QUEUE_HPP

#include "state.hpp"
#include <vector>

template <typename T>
class frontier_queue
{
public:
  /** @brief Represent whether the queue is empty
   * @return true if the queue is empty, false otherwise
   * @note This should be a O(1) operation */
  bool empty();

  /** @brief push a State with value state, cost, and heuristic into the frontier.
   * @attention You will need to create a state from the passed inputs, and then add it to the queue.
   * @param state The value of the state
   * @param cost The path cost (gcost) of the state
   * @param heur The heuristic (heuristic) of the state
   * @note This should be a O(log n) operation on the queue */
  void push(const T &state, int cost, int heur);

  /** @brief pop the state from the frontier with the smallest f-cost
   * @return The state with the smallest f-cost
   * @note This should be a O(log n) operation */
  State<T> pop();

  /** @brief check if the queue contains a state with the given value
   * @return true if the value state is in the frontier
   * @note This may be at most an O(n) operation */
  bool contains(const T &state);

  /** @brief update state in the frontier with a new lower g-cost (which also updates f-cost)
   * @attention The frontier must still be a valid min heap on f-cost after replacement.
   * @attention If the passed state is not in the frontier or the passed cost is not lower, do nothing.
   * @param state The value of the state
   * @param cost The new path cost (gcost) of the state
   * @note This should be at most a O(log n) operation.*/
  void replaceif(const T &state, int cost);

  /** @brief obtain the current path cost of the state in the frontier, if it exists
   * @attention This should not modify the frontier, and if the state is not in the frontier, return -1.
   * @param state The value of the state
   * @return The path cost (gcost) of the state or -1 if the state is not in the frontier
   * @note This may be at most a O(n) operation.*/
  int getCurrentPathCost(const T &state);

private:
  std::vector<State<T>> queue;
};

#include "frontier_queue.tpp"
#endif