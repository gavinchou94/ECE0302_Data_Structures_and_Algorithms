#include "graph.hpp"

template <typename ItemType>
Graph<ItemType>::Graph()
{
  // TODO
}

template <typename ItemType>
int Graph<ItemType>::getNumVertices() const
{
  // TODO
  return 0; // Placeholder
}

template <typename ItemType>
int Graph<ItemType>::getNumEdges() const
{
  // TODO
  return 0; // Placeholder
}

template <typename ItemType>
bool Graph<ItemType>::add(ItemType start, ItemType end)
{
  // TODO
  return false; // Placeholder
}

template <typename ItemType>
bool Graph<ItemType>::remove(ItemType start, ItemType end)
{
  // TODO
  return false; // Placeholder
}

template <typename ItemType>
void Graph<ItemType>::depthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit)
{
  // TODO, use a stack and similar code structure to breadthFirstTraversal
}

template <typename ItemType>
void Graph<ItemType>::breadthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit)
{
  std::queue<ItemType> q;
  std::set<ItemType> visited; // set is a container that stores unique items in sorted order, and provides fast lookup
  q.push(start);
  visited.insert(start);
  while (!q.empty())
  {
    ItemType current = q.front();
    q.pop();
    visit(current);
    for (ItemType neighbor : std::vector<ItemType>{}) // TODO: get the neighbors of current
    {
      if (!visited.count(neighbor)) // count is a method in std::set that returns 1 if the item is in the set, and 0 otherwise
      {
        visited.insert(neighbor);
        q.push(neighbor);
      }
    }
  }
}