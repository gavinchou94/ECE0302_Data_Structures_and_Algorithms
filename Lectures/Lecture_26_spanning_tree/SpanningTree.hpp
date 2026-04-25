/** @file SpanningTree.hpp */

#ifndef SPANNING_TREE_HPP
#define SPANNING_TREE_HPP

#include "LinkedGraph.hpp"

template <typename ItemType>
class SpanningTree : public LinkedGraph<ItemType>
{
public:
  SpanningTree<ItemType> bfs_spanning(const ItemType &start) const;
  SpanningTree<ItemType> dfs_spanning(const ItemType &start) const;
  SpanningTree<ItemType> prim_spanning(const ItemType &start) const;
};

#include "SpanningTree.tpp"
#endif