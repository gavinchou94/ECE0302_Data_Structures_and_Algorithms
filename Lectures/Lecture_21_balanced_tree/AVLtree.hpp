#include <iostream>
#include <stdexcept>
#include "BinaryNode.hpp"

#include <iostream>
#include <algorithm>

template <typename ItemType>
class AVLTree
{
private:
  std::shared_ptr<BinaryNode<ItemType>> root;

public:
  AVLTree() : root(nullptr) {}
  ~AVLTree()
  {
    clear();
  }

  // isEmpty
  bool isEmpty() const
  {
    return root == nullptr;
  }

  // Get height
  int getHeight() const
  {
    return height(root);
  }

  // Utility to get height recursively
  int height(std::shared_ptr<BinaryNode<ItemType>> n) const
  {
    if (!n)
      return 0;
    return 1 + std::max(height(n->getLeftChildPtr()), height(n->getRightChildPtr()));
  }

  // Get root balance factor
  int getRootBalance() const
  {
    return getBalance(root);
  }

  // Get balance factor
  int getBalance(std::shared_ptr<BinaryNode<ItemType>> n) const
  {
    return n ? height(n->getLeftChildPtr()) - height(n->getRightChildPtr()) : 0;
  }

  // Right rotate
  std::shared_ptr<BinaryNode<ItemType>> rightRotate(std::shared_ptr<BinaryNode<ItemType>> a)
  { /**
     *   Right rotate at a, before rotation
     *        a
     *       / \
     *      b   Z
     *     / \
     *    X   Y
     *
     *   After rotation
     *       b
     *      / \
     *     X  a
     *       / \
     *      Y  Z
     */
    auto b = a->getLeftChildPtr();
    // auto Z = a->getRightChildPtr(); // not used and not changed during rotation
    auto Y = b->getRightChildPtr();
    // auto X = b->getLeftChildPtr(); // not used and not changed during rotation

    b->setRightChildPtr(a);
    a->setLeftChildPtr(Y);

    return b; // New root
  }

  // Left rotate
  std::shared_ptr<BinaryNode<ItemType>> leftRotate(std::shared_ptr<BinaryNode<ItemType>> a)
  {
    /**
     *   Left rotate at a, before rotation
     *        a
     *       / \
     *      X   b
     *         / \
     *        Y   Z
     *
     *   After rotation
     *       b
     *      / \
     *     a   Z
     *    / \
     *   X  Y
     */
    auto b = a->getRightChildPtr();
    auto Y = b->getLeftChildPtr();

    b->setLeftChildPtr(a);
    a->setRightChildPtr(Y);

    return b; // New root
  }

  // Insert with balancing
  std::shared_ptr<BinaryNode<ItemType>> insert(std::shared_ptr<BinaryNode<ItemType>> node, const ItemType &key)
  {
    if (!node)
      return std::make_shared<BinaryNode<ItemType>>(key);

    if (key < node->getItem())
      node->setLeftChildPtr(insert(node->getLeftChildPtr(), key));
    else if (key > node->getItem())
      node->setRightChildPtr(insert(node->getRightChildPtr(), key));
    else
      throw std::invalid_argument("Duplicate key");

    // Update height and balance
    int balance = getBalance(node);

    // Rotate cases
    // Case 1: Left Left, inserted in left subtree of left child
    if (balance > 1 && key < node->getLeftChildPtr()->getItem())
      return rightRotate(node);
    // Case 2: Right Right, inserted in right subtree of right child
    if (balance < -1 && key > node->getRightChildPtr()->getItem())
      return leftRotate(node);
    // Case 3: Left Right, inserted in right subtree of left child
    if (balance > 1 && key > node->getLeftChildPtr()->getItem())
    {
      node->setLeftChildPtr(leftRotate(node->getLeftChildPtr())); // rotate left child
      return rightRotate(node);                                   // rotate node
    }
    // Case 4: Right Left, inserted in left subtree of right child
    if (balance < -1 && key < node->getRightChildPtr()->getItem())
    {
      node->setRightChildPtr(rightRotate(node->getRightChildPtr())); // rotate right child
      return leftRotate(node);                                       // rotate node
    }
    return node;
  }

  void insert(const ItemType &key)
  {
    root = insert(root, key);
  }

  // getRoot
  std::shared_ptr<BinaryNode<ItemType>> getRoot() const
  {
    return root;
  }

  // In-order traversal
  void inOrder(std::shared_ptr<BinaryNode<ItemType>> root) const
  {
    if (root)
    {
      inOrder(root->getLeftChildPtr());
      std::cout << root->getItem() << " ";
      inOrder(root->getRightChildPtr());
    }
  }

  void inOrderTraversal() const
  {
    inOrder(root);
    std::cout << std::endl;
  }

  // Clear tree
  void clear()
  {
    root = nullptr;
  }

  // remove node
  void remove(const ItemType &key)
  {
    // STUB

    // First do a normal BST delete
    // Then update height and balance

    // Then we rotate cases according to the following cases:
    // Case 1: Left Left, removed from left subtree of left child
    // Case 2: Right Right, removed from right subtree of right child
    // Case 3: Left Right, removed from right subtree of left child
    // Case 4: Right Left, removed from left subtree of right child

    // Do we miss any special cases of removal?
  }
};
