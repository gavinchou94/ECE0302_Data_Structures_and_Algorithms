#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>

template <typename NodeType, typename CostType>
class Dijkstra
{
public:
  using Graph = std::unordered_map<NodeType, std::vector<std::pair<NodeType, CostType>>>;

  // Dijkstra's algorithm to find the shortest path
  std::unordered_map<NodeType, CostType> findShortestPaths(
      const Graph &graph,
      const NodeType &start)
  {
    // Priority queue for the open set (min-heap based on distance)
    using PQElement = std::pair<CostType, NodeType>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> openSet;

    // Distance map to store the shortest distance to each node
    std::unordered_map<NodeType, CostType> distances;

    // Initialize distances to infinity
    for (const auto &node : graph)
    {
      distances[node.first] = std::numeric_limits<CostType>::max();
    }
    distances[start] = 0;

    // Add the start node to the open set
    openSet.emplace(0, start);

    while (!openSet.empty())
    {
      // Get the node with the smallest distance
      NodeType current = openSet.top().second;
      CostType currentDistance = openSet.top().first;
      openSet.pop();

      // Explore neighbors
      for (const auto &[neighbor, cost] : graph.at(current))
      {
        CostType newDistance = currentDistance + cost;

        // If a shorter path is found
        if (newDistance < distances[neighbor])
        {
          distances[neighbor] = newDistance;
          openSet.emplace(newDistance, neighbor);
        }
      }
    }

    return distances;
  }

  // Reconstruct the shortest path from start to goal
  std::vector<NodeType> reconstructPath(
      const Graph &graph,
      const NodeType &start,
      const NodeType &goal)
  {
    // Run Dijkstra's algorithm to get distances
    auto distances = findShortestPaths(graph, start);

    // If the goal is unreachable, return an empty path
    if (distances[goal] == std::numeric_limits<CostType>::max())
    {
      return {};
    }

    // Reconstruct the path by backtracking
    std::vector<NodeType> path;
    NodeType current = goal;

    while (current != start)
    {
      path.push_back(current);

      // Find the previous node in the shortest path
      for (const auto &[neighbor, cost] : graph)
      {
        if (distances[current] == distances[neighbor] + cost)
        {
          current = neighbor;
          break;
        }
      }
    }

    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
  }
};