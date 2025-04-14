#ifndef LINKED23_HPP
#define LINKED23_HPP

#include <stdexcept>
#include <memory>
#include "TriNode.hpp"

template <class ItemType>
class Linked23
{
private:
  // Pointer to the root node of the 2-3 tree.
  std::shared_ptr<TriNode<ItemType>> root;
  // Tracks the total number of items in the 2-3 tree.
  int numItems;
  int getHeightHelper(std::shared_ptr<TriNode<ItemType>> node) const;
  std::shared_ptr<TriNode<ItemType>> handleChildSplit(std::shared_ptr<TriNode<ItemType>> parent, std::shared_ptr<TriNode<ItemType>> child);
  std::shared_ptr<TriNode<ItemType>> splitNode(std::shared_ptr<TriNode<ItemType>> node, const ItemType &newItem);
  int nodeCountBelow(std::shared_ptr<TriNode<ItemType>> node) const;
  int getLevelHelper(std::shared_ptr<TriNode<ItemType>> node, const ItemType &anItem, int level) const;
  std::shared_ptr<TriNode<ItemType>> insert(std::shared_ptr<TriNode<ItemType>> node, const ItemType &newItem);
  void printTreeStructureHelper(std::shared_ptr<TriNode<ItemType>> node, int depth) const;

public:
  Linked23();
  ~Linked23();
  bool isEmpty() const;
  int getHeight() const;
  void add(const ItemType &anItem);
  void remove(const ItemType &anItem);
  void clear();
  void inOrderTraversal() const;
  void inOrderTraversalHelper(std::shared_ptr<TriNode<ItemType>> root) const;
  std::shared_ptr<TriNode<ItemType>> getRoot() const;
  int getNumItems() const;
  bool contains(const ItemType &anItem) const;
  // Prints the structure of the 2-3 tree in a readable format for debugging or visualization.
  void printTreeStructure() const;
  int getNodeCount() const;
  int getLevel(const ItemType &anItem) const;
  bool isleaf(const ItemType &anItem) const;
};
#include "Linked23.tpp"
#endif