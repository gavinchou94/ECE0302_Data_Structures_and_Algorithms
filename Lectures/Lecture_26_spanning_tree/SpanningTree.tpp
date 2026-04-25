/** @file SpanningTree.tpp */

#include "SpanningTree.hpp"

#include <queue>
#include <set>
#include <stack>
#include <utility>

template <typename ItemType>
SpanningTree<ItemType> SpanningTree<ItemType>::bfs_spanning(const ItemType &start) const
{
  SpanningTree<ItemType> tree;
  std::set<ItemType> visited;
  std::queue<ItemType> pending;

  if (this->getNeighbors(start).empty())
    return tree;

  visited.insert(start);
  pending.push(start);

  while (!pending.empty())
  {
    ItemType current = pending.front(); // peek the front
    pending.pop();                      // dequeue it for processing, enqueue its neighbors

    std::map<ItemType, int> neighbors = this->getNeighbors(current);
    auto neighbor = neighbors.begin();
    while (neighbor != neighbors.end())
    {
      if (visited.count(neighbor->first) == 0) // if we haven't visited this neighbor yet
                                               // add it to the visited set, and to the queue for future processing
                                               // and add the edge to the spanning tree
      {
        visited.insert(neighbor->first);
        pending.push(neighbor->first);
        tree.add(current, neighbor->first, neighbor->second);
      }
      ++neighbor;
    }
  }

  return tree;
}

template <typename ItemType>
SpanningTree<ItemType> SpanningTree<ItemType>::dfs_spanning(const ItemType &start) const
{
  SpanningTree<ItemType> tree;
  std::set<ItemType> visited;
  std::stack<ItemType> pending;

  if (this->getNeighbors(start).empty())
    return tree;

  visited.insert(start);
  pending.push(start);

  while (!pending.empty())
  {
    ItemType current = pending.top(); // peek the top
    pending.pop();                    // pop it for processing, enqueue its neighbors

    std::map<ItemType, int> neighbors = this->getNeighbors(current);
    auto neighbor = neighbors.begin();
    while (neighbor != neighbors.end())
    {
      if (visited.count(neighbor->first) == 0) // if we haven't visited this neighbor yet
                                               // add it to the visited set, and to the stack for future processing
                                               // and add the edge to the spanning tree
      {
        visited.insert(neighbor->first);
        // Revisit current later so remaining neighbors are explored after returning.
        pending.push(current);
        pending.push(neighbor->first);
        tree.add(current, neighbor->first, neighbor->second);
        break;
      }
      ++neighbor;
    }
  }

  return tree;
}

template <typename ItemType>
SpanningTree<ItemType> SpanningTree<ItemType>::prim_spanning(const ItemType &start) const
{
  using WeightedEdge = std::pair<int, std::pair<ItemType, ItemType>>;
  // pair an edge's weight with the edge itself (represented as a pair of vertices)

  SpanningTree<ItemType> tree;
  std::set<ItemType> visited;
  std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, std::greater<WeightedEdge>> edges;

  if (this->getNeighbors(start).empty())
    return tree;

  visited.insert(start);

  std::map<ItemType, int> startNeighbors = this->getNeighbors(start);
  auto neighbor = startNeighbors.begin();
  while (neighbor != startNeighbors.end())
  {
    edges.push(WeightedEdge(neighbor->second, std::make_pair(start, neighbor->first)));
    ++neighbor;
  } // add all edges from start to the priority queue

  while (!edges.empty())
  {
    WeightedEdge nextEdge = edges.top(); // always select the edge with the smallest weight
    edges.pop();

    // nextEdge is a pair of (weight, (from, to)),
    // so nextEdge.second is the (from, to) pair, and nextEdge.second.second is the "to" vertex
    ItemType from = nextEdge.second.first;
    ItemType to = nextEdge.second.second;

    if (visited.count(to) != 0)
      continue;

    visited.insert(to);
    tree.add(from, to, nextEdge.first); // add this edge to the tree

    std::map<ItemType, int> neighbors = this->getNeighbors(to);
    auto current = neighbors.begin();
    while (current != neighbors.end())
    {
      if (visited.count(current->first) == 0)
        edges.push(WeightedEdge(current->second, std::make_pair(to, current->first)));
      ++current;
    }
  }

  return tree;
}