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

  // Helper functions
  int getHeightHelper(Node<ItemType> *node) const
  {
    if (node == nullptr)
      return 0;
    return 1 + std::max(getHeightHelper(node->left), getHeightHelper(node->right));
  }

  int getNumberOfNodesHelper(Node<ItemType> *node) const
  {
    if (node == nullptr)
      return 0;
    return 1 + getNumberOfNodesHelper(node->left) + getNumberOfNodesHelper(node->right);
  }

  void clearHelper(Node<ItemType> *&node)
  {
    if (node != nullptr)
    {
      clearHelper(node->left);
      clearHelper(node->right);
      delete node;
      node = nullptr;
    }
  }

  void preorderHelper(Node<ItemType> *node, void visit(ItemType &)) const
  {
    if (node != nullptr)
    {
      visit(node->data);
      preorderHelper(node->left, visit);
      preorderHelper(node->right, visit);
    }
  }

  void inorderHelper(Node<ItemType> *node, void visit(ItemType &)) const
  {
    if (node != nullptr)
    {
      inorderHelper(node->left, visit);
      visit(node->data);
      inorderHelper(node->right, visit);
    }
  }

  void postorderHelper(Node<ItemType> *node, void visit(ItemType &)) const
  {
    if (node != nullptr)
    {
      postorderHelper(node->left, visit);
      postorderHelper(node->right, visit);
      visit(node->data);
    }
  }

public:
  BinaryTree() : root(nullptr) {}

  ~BinaryTree()
  {
    clear();
  }

  bool isEmpty() const
  {
    return root == nullptr;
  }

  int getHeight() const
  {
    return getHeightHelper(root);
  }

  int getNumberOfNodes() const
  {
    return getNumberOfNodesHelper(root);
  }

  ItemType getRootData() const
  {
    if (isEmpty())
      throw std::runtime_error("Tree is empty.");
    return root->data;
  }

  void setRootData(const ItemType &someItem)
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

  bool add(const ItemType &someItem)
  {
    if (isEmpty())
    {
      root = new Node<ItemType>(someItem);
      return true;
    }

    // Simple insertion (not a BST)
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

  bool remove(const ItemType &target)
  {
    // Stub implementation
    return false;
  }

  void clear()
  {
    clearHelper(root);
  }

  ItemType getEntry(const ItemType &target) const
  {
    Node<ItemType> *current = root;
    while (current != nullptr)
    {
      if (current->data == target)
        return current->data;
      current = (target < current->data) ? current->left : current->right;
    }
    throw std::runtime_error("Item not found.");
  }

  bool contains(const ItemType &target) const
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

  void preorderTraverse(void visit(ItemType &)) const
  {
    preorderHelper(root, visit);
  }

  void inorderTraverse(void visit(ItemType &)) const
  {
    inorderHelper(root, visit);
  }

  void postorderTraverse(void visit(ItemType &)) const
  {
    postorderHelper(root, visit);
  }
};