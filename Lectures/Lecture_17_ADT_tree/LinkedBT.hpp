#ifndef LINKED_BT_HPP
#define LINKED_BT_HPP

#include <iostream>
#include <stdexcept>
#include "abstract_binary_tree.hpp"

template <typename ItemType>
struct Node
{
  ItemType data;
  Node<ItemType> *left;
  Node<ItemType> *right;

  Node(const ItemType &item) : data(item), left(nullptr), right(nullptr) {}
};

template <typename ItemType>
class BinaryTree : public BinaryTreeInterface<ItemType>
{
private:
  Node<ItemType> *root;

  // Helper functions(recursive) are often used for tree operations
  int getHeightHelper(Node<ItemType> *node) const;
  int getNumberOfNodesHelper(Node<ItemType> *node) const;
  void clearHelper(Node<ItemType> *&node);
  void preorderHelper(Node<ItemType> *node, std::function<void(ItemType &)> visit) const;
  void inorderHelper(Node<ItemType> *node, std::function<void(ItemType &)> visit) const;
  void postorderHelper(Node<ItemType> *node, std::function<void(ItemType &)> visit) const;

public:
  BinaryTree();
  ~BinaryTree();

  BinaryTree(const BinaryTree<ItemType> &other) = delete;                      // Disable copy constructor
  BinaryTree<ItemType> &operator=(const BinaryTree<ItemType> &other) = delete; // Disable copy assignment operator

  bool isEmpty() const;
  int getHeight() const;
  int getNumberOfNodes() const;
  ItemType getRootData() const;
  Node<ItemType> *getRoot() const;
  void setRootData(const ItemType &someItem);
  bool add(const ItemType &someItem);
  bool remove(const ItemType &target);
  void clear();
  ItemType getEntry(const ItemType &target) const;
  bool contains(const ItemType &target) const;
  void preorderTraverse(std::function<void(ItemType &)> visit) const;
  void inorderTraverse(std::function<void(ItemType &)> visit) const;
  void postorderTraverse(std::function<void(ItemType &)> visit) const;
};

#include "LinkedBT.tpp"

#endif

// TODO:
// Consider a member function that determines whether a binary tree contains exactly one node
// (that is, the tree consists only of a root that is also a leaf), returning `true` if this condition holds and `false` otherwise;
// Specify this member function, and then explain whether a test case could implement the same functionality if it were not provided as a member function.
// Hint: using any public memeber function in this header is allowed