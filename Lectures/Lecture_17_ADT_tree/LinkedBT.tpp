#include "LinkedBT.hpp"
#include <stdexcept>

// Private helper functions

template <typename ItemType>
int BinaryTree<ItemType>::getHeightHelper(Node<ItemType> *node) const
{
  if (node == nullptr)
    return 0;
  return 1 + std::max(getHeightHelper(node->left), getHeightHelper(node->right));
}

template <typename ItemType>
int BinaryTree<ItemType>::getNumberOfNodesHelper(Node<ItemType> *node) const
{
  if (node == nullptr)
    return 0;
  return 1 + getNumberOfNodesHelper(node->left) + getNumberOfNodesHelper(node->right);
}

template <typename ItemType>
void BinaryTree<ItemType>::clearHelper(Node<ItemType> *&node)
{
  if (node != nullptr)
  {
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
    node = nullptr;
  }
}

template <typename ItemType>
void BinaryTree<ItemType>::preorderHelper(Node<ItemType> *node, std::function<void(ItemType &)> visit) const
{
  if (node != nullptr)
  {
    visit(node->data);
    preorderHelper(node->left, visit);
    preorderHelper(node->right, visit);
  }
}

template <typename ItemType>
void BinaryTree<ItemType>::inorderHelper(Node<ItemType> *node, std::function<void(ItemType &)> visit) const
{
  if (node != nullptr)
  {
    inorderHelper(node->left, visit);
    visit(node->data);
    inorderHelper(node->right, visit);
  }
}

template <typename ItemType>
void BinaryTree<ItemType>::postorderHelper(Node<ItemType> *node, std::function<void(ItemType &)> visit) const
{
  if (node != nullptr)
  {
    postorderHelper(node->left, visit);
    postorderHelper(node->right, visit);
    visit(node->data);
  }
}

// Public member functions

template <typename ItemType>
BinaryTree<ItemType>::BinaryTree() : root(nullptr) {}

template <typename ItemType>
BinaryTree<ItemType>::~BinaryTree()
{
  clear();
}

template <typename ItemType>
bool BinaryTree<ItemType>::isEmpty() const
{
  return root == nullptr;
}

template <typename ItemType>
int BinaryTree<ItemType>::getHeight() const
{
  return getHeightHelper(root);
}

template <typename ItemType>
int BinaryTree<ItemType>::getNumberOfNodes() const
{
  return getNumberOfNodesHelper(root);
}

template <typename ItemType>
ItemType BinaryTree<ItemType>::getRootData() const
{
  if (isEmpty())
    throw std::runtime_error("Tree is empty.");
  return root->data;
}

template <typename ItemType>
void BinaryTree<ItemType>::setRootData(const ItemType &someItem)
{
  if (isEmpty())
  {
    root = new Node<ItemType>(someItem);
  }
  else
  {
    root->data = someItem;
  }
}

template <typename ItemType>
bool BinaryTree<ItemType>::add(const ItemType &someItem)
{
  if (isEmpty())
  {
    root = new Node<ItemType>(someItem);
    return true;
  }

  // BST insertion logic
  Node<ItemType> *current = root;
  while (true)
  {
    if (someItem < current->data)
    {
      if (current->left == nullptr)
      {
        current->left = new Node<ItemType>(someItem);
        return true;
      }
      current = current->left;
    }
    else
    {
      if (current->right == nullptr)
      {
        current->right = new Node<ItemType>(someItem);
        return true;
      }
      current = current->right;
    }
  }
}

template <typename ItemType>
bool BinaryTree<ItemType>::remove(const ItemType &target)
{
  // Stub implementation
  return false;
}

template <typename ItemType>
void BinaryTree<ItemType>::clear()
{
  clearHelper(root);
}

template <typename ItemType>
ItemType BinaryTree<ItemType>::getEntry(const ItemType &target) const
{
  Node<ItemType> *current = root;
  while (current != nullptr)
  {
    if (current->data == target)
      return current->data;
    current = (target < current->data) ? current->left : current->right;
  }
  throw std::logic_error("Target not found in the tree.");
}

template <typename ItemType>
bool BinaryTree<ItemType>::contains(const ItemType &target) const
{
  Node<ItemType> *current = root;
  while (current != nullptr)
  {
    if (current->data == target)
      return true;
    current = (target < current->data) ? current->left : current->right;
  }
  return false;
}

template <typename ItemType>
void BinaryTree<ItemType>::preorderTraverse(std::function<void(ItemType &)> visit) const
{
  preorderHelper(root, visit);
}

template <typename ItemType>
void BinaryTree<ItemType>::inorderTraverse(std::function<void(ItemType &)> visit) const
{
  inorderHelper(root, visit);
}

template <typename ItemType>
void BinaryTree<ItemType>::postorderTraverse(std::function<void(ItemType &)> visit) const
{
  postorderHelper(root, visit);
}
