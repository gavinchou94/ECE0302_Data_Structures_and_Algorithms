/** @file GraphSearch.hpp */
#ifndef GRAPH_SEARCH_HPP
#define GRAPH_SEARCH_HPP

#include <vector>
#include <functional>
#include <unordered_map>
#include "LinkedGraph.hpp"

template <typename ItemType>
class GraphSearch : public LinkedGraph<ItemType>
{
public:
  using Heuristic = std::function<int(const ItemType &, const ItemType &)>;

  // A*: shortest path guided by a heuristic
  std::vector<ItemType> AStarSearch(const ItemType &start, const ItemType &goal, Heuristic heuristic);

  // Dijkstra: shortest path with no heuristic
  std::vector<ItemType> Dijkstra_from_AStar(const ItemType &start, const ItemType &goal);

  // Dijkstra: returns shortest distance from start to every reachable vertex
  std::unordered_map<ItemType, int> dijkstra(const ItemType &start);

private:
  std::vector<ItemType> reconstructPath(const std::unordered_map<ItemType, ItemType> &cameFrom, ItemType current);
};

#include "GraphSearch.tpp"
#endif