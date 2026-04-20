#ifndef TWO_THREE_TREE_HPP
#define TWO_THREE_TREE_HPP

#include <stdexcept>
#include <memory>
#include "TriNode.hpp"
#include "TreePrinter.hpp"

template <typename ItemType>
class TwoThreeTree
{
private:
  std::shared_ptr<TriNode<ItemType>> root;
  int numItems;

  int getHeightHelper(std::shared_ptr<TriNode<ItemType>> node) const;
  int getLevelHelper(std::shared_ptr<TriNode<ItemType>> node, const ItemType &anItem) const;
  int getNumofNodesHelper(std::shared_ptr<TriNode<ItemType>> node) const;
  void inOrderTraversalHelper(std::shared_ptr<TriNode<ItemType>> node, std::function<void(ItemType &)> visit) const;
  void printTreeCustomHelper(std::shared_ptr<TriNode<ItemType>> node, int level) const;

  std::shared_ptr<TriNode<ItemType>> findNode(const ItemType &anItem) const;

  std::shared_ptr<TriNode<ItemType>> split(std::shared_ptr<TriNode<ItemType>> node, const ItemType &newItem);
  std::shared_ptr<TriNode<ItemType>> addHelper(std::shared_ptr<TriNode<ItemType>> node, const ItemType &newItem);
  void fixTree(std::shared_ptr<TriNode<ItemType>> node, std::shared_ptr<TriNode<ItemType>> parent);
  std::shared_ptr<TriNode<ItemType>> removeHelper(std::shared_ptr<TriNode<ItemType>> node, const ItemType &anItem);

public:
  TwoThreeTree();
  ~TwoThreeTree();

  bool isEmpty() const;
  int getNumofDataItems() const;
  int getHeight() const;
  int getNumofNodes() const;

  std::shared_ptr<TriNode<ItemType>> getRoot() const;
  int getLevel(const ItemType &anItem) const;
  bool contains(const ItemType &anItem) const;
  ItemType getEntry(const ItemType &anItem) const;
  bool isleaf(const ItemType &anItem) const;
  void inOrderTraversal(std::function<void(ItemType &)> visit) const;
  void printTreeCustom() const;
  void add(const ItemType &anItem);
  void remove(const ItemType &anItem);
  void clear();
};
#include "TwoThreeTree.tpp"
#endif