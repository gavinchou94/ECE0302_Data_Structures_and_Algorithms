#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <set>

template <typename NodeType, typename CostType>
class Prim
{
public:
  using Graph = std::unordered_map<NodeType, std::vector<std::pair<NodeType, CostType>>>;

  // Prim's algorithm to find the Minimum Spanning Tree (MST)
  std::vector<std::pair<NodeType, NodeType>> findMST(const Graph &graph, const NodeType &start)
  {
    // Priority queue to store edges (min-heap based on edge weight)
    using Edge = std::pair<CostType, std::pair<NodeType, NodeType>>; // {weight, {from, to}}
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edgeQueue;

    // Set to track visited nodes
    std::set<NodeType> visited;

    // Vector to store the edges of the MST
    std::vector<std::pair<NodeType, NodeType>> mst;

    // Add all edges from the start node to the priority queue
    visited.insert(start);
    for (const auto &[neighbor, weight] : graph.at(start))
    {
      edgeQueue.emplace(weight, std::make_pair(start, neighbor));
    }

    // Process edges until the MST is complete or the queue is empty
    while (!edgeQueue.empty() && mst.size() < graph.size() - 1)
    {
      // Get the edge with the smallest weight
      auto [weight, edge] = edgeQueue.top();
      edgeQueue.pop();

      auto [from, to] = edge;

      // Skip if the destination node is already visited
      if (visited.count(to))
      {
        continue;
      }

      // Add the edge to the MST
      mst.emplace_back(from, to);
      visited.insert(to);

      // Add all edges from the newly visited node to the priority queue
      for (const auto &[neighbor, neighborWeight] : graph.at(to))
      {
        if (!visited.count(neighbor))
        {
          edgeQueue.emplace(neighborWeight, std::make_pair(to, neighbor));
        }
      }
    }

    return mst;
  }
};