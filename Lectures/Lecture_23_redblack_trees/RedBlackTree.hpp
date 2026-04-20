#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP
#include <stdexcept>
#include <memory>
#include <functional>
#include <fstream>
#include "RBNode.hpp"

template <typename ItemType>
class RedBlackTree
{
private:
  std::shared_ptr<RBNode<ItemType>> root;
  int numItems;

  // ============================================================
  // Private helpers
  // ============================================================

  bool isRed(std::shared_ptr<RBNode<ItemType>> node) const;
  int getHeightHelper(std::shared_ptr<RBNode<ItemType>> node) const;
  int getNodesHelper(std::shared_ptr<RBNode<ItemType>> node) const;
  void inOrderTraversalHelper(std::shared_ptr<RBNode<ItemType>> node, std::function<void(ItemType &)> visit) const;

  // Note: colors are NOT swapped here — color fixup is handled in addHelper
  std::shared_ptr<RBNode<ItemType>> rotateLeft(std::shared_ptr<RBNode<ItemType>> node);
  std::shared_ptr<RBNode<ItemType>> rotateRight(std::shared_ptr<RBNode<ItemType>> node);

  // Recursive BST insert with proactive 4-node splitting on descent.
  // On the way back up, only two local normalization rules remain:
  // fix a right-leaning red link, and fix two consecutive left red links.
  std::shared_ptr<RBNode<ItemType>> addHelper(
      std::shared_ptr<RBNode<ItemType>> node, const ItemType &newItem);

public:
  // ============================================================
  // Public interface
  // ============================================================

  RedBlackTree();
  ~RedBlackTree();

  bool isEmpty() const;
  int getHeight() const;
  int getNumItems() const;
  std::shared_ptr<RBNode<ItemType>> getRoot() const;

  bool contains(const ItemType &anItem) const;
  int getBlackDistance(const ItemType &anItem) const;
  int getLevel(const ItemType &anItem) const;
  void printTreeCustom(const std::string &filename) const;
  ItemType getEntry(const ItemType &anItem) const;
  bool isLeaf(const ItemType &anItem) const;
  void inOrderTraversal(std::function<void(ItemType &)> visit) const;

  // Build from scratch — BST insert + fix violations bottom-up
  void add(const ItemType &anItem);

  // Conversion from 2-3-4 — inject a pre-built RB subtree directly,
  // bypassing insertion and fixup entirely
  void setRoot(std::shared_ptr<RBNode<ItemType>> node);

  void remove(const ItemType &anItem);
  void clear();
};

#include "RedBlackTree.tpp"
#endif