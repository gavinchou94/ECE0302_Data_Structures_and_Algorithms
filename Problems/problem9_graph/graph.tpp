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
void Graph<ItemType>::depthFirstTraversal(ItemType start, void visit(ItemType &))
{
  // BONUS TODO, you may need a stack and/or a recursive helper function
}

template <typename ItemType>
void Graph<ItemType>::breadthFirstTraversal(ItemType start, void visit(ItemType &))
{
  // BONUS TODO, you may need a queue and/or a recursive helper function
}