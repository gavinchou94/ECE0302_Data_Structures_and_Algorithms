#include <unordered_map>
#include <queue>
#include <vector>
#include <limits>
#include <functional>
#include <algorithm>

template <typename NodeType, typename CostType>
class AStar
{
public:
  // Type alias for the graph representation
  using Graph = std::unordered_map<NodeType, std::vector<std::pair<NodeType, CostType>>>;
  // The graph is represented as an adjacency list
  // where each node maps to a vector of pairs (neighbor, cost)

  // A* algorithm to find the shortest path
  std::vector<NodeType> findPath(
      const Graph &graph,
      const NodeType &start,
      const NodeType &goal,
      std::function<CostType(const NodeType &, const NodeType &)> heuristic)
  {
    // Priority queue for open set (min-heap based on f-cost)
    using PQElement = std::pair<CostType, NodeType>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> openSet;

    // Maps to store g-costs and f-costs
    std::unordered_map<NodeType, CostType> gCost;
    std::unordered_map<NodeType, CostType> fCost;

    // Parent map to reconstruct the path
    std::unordered_map<NodeType, NodeType> cameFrom;

    // Initialize costs
    for (const auto &node : graph)
    {
      gCost[node.first] = std::numeric_limits<CostType>::max();
      fCost[node.first] = std::numeric_limits<CostType>::max();
    }
    gCost[start] = 0;
    fCost[start] = heuristic(start, goal);

    // Add the start node to the open set
    openSet.emplace(fCost[start], start);

    while (!openSet.empty())
    {
      // Get the node with the lowest f-cost
      NodeType current = openSet.top().second;
      openSet.pop();

      // If we reached the goal, reconstruct the path
      if (current == goal)
      {
        return reconstructPath(cameFrom, current);
      }

      // Explore neighbors
      for (const auto &[neighbor, cost] : graph.at(current))
      {
        CostType tentativeGCost = gCost[current] + cost;

        if (tentativeGCost < gCost[neighbor])
        {
          // Update costs and parent
          cameFrom[neighbor] = current;
          gCost[neighbor] = tentativeGCost;
          fCost[neighbor] = gCost[neighbor] + heuristic(neighbor, goal);

          // Add neighbor to the open set
          openSet.emplace(fCost[neighbor], neighbor);
        }
      }
    }

    // If we reach here, no path was found
    return {};
  }

private:
  // Reconstruct the path from the cameFrom map
  std::vector<NodeType> reconstructPath(const std::unordered_map<NodeType, NodeType> &cameFrom, NodeType current)
  {
    std::vector<NodeType> path;
    while (cameFrom.find(current) != cameFrom.end())
    {
      path.push_back(current);
      current = cameFrom.at(current);
    }
    path.push_back(current); // Add the start node
    std::reverse(path.begin(), path.end());
    return path;
  }
};