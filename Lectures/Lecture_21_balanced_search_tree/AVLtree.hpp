/** @file AVLtree.hpp */

#ifndef AVL_TREE_
#define AVL_TREE_

#include <iostream>
#include <functional>
#include <memory>

#include "BinaryNode.hpp"

template <typename ItemType>
class AVLTree
{
private:
  std::shared_ptr<BinaryNode<ItemType>> root;

  int heightHelper(std::shared_ptr<BinaryNode<ItemType>> node) const;
  int getBalance(std::shared_ptr<BinaryNode<ItemType>> node) const;
  int getNumberOfNodesHelper(std::shared_ptr<BinaryNode<ItemType>> node) const;
  void inOrderHelper(std::shared_ptr<BinaryNode<ItemType>> node, std::function<void(ItemType &)> visit) const;

  std::shared_ptr<BinaryNode<ItemType>> rightRotate(std::shared_ptr<BinaryNode<ItemType>> node);
  std::shared_ptr<BinaryNode<ItemType>> leftRotate(std::shared_ptr<BinaryNode<ItemType>> node);
  std::shared_ptr<BinaryNode<ItemType>> addHelper(std::shared_ptr<BinaryNode<ItemType>> node, const ItemType &key);
  std::shared_ptr<BinaryNode<ItemType>> removeHelper(std::shared_ptr<BinaryNode<ItemType>> node, const ItemType &key);

public:
  AVLTree();

  bool isEmpty() const;
  int getHeight() const;
  int getRootBalance() const;
  int getNumberOfNodes() const;
  std::shared_ptr<BinaryNode<ItemType>> getRoot() const;

  ItemType getEntry(const ItemType &anEntry) const;
  bool contains(const ItemType &anEntry) const;
  void inorderTraverse(std::function<void(ItemType &)> visit) const;

  void clear();
  void add(const ItemType &newEntry);
  void remove(const ItemType &anEntry);
};

#include "AVLtree.tpp"

#endif