/** @file AVLtree.tpp */

#include "AVLtree.hpp"

#include <algorithm>
#include <stdexcept>

template <typename ItemType>
int AVLTree<ItemType>::heightHelper(std::shared_ptr<BinaryNode<ItemType>> node) const
{
  return node ? 1 + std::max(heightHelper(node->getLeftChildPtr()), heightHelper(node->getRightChildPtr())) : 0;
}

template <typename ItemType>
int AVLTree<ItemType>::getBalance(std::shared_ptr<BinaryNode<ItemType>> node) const
{
  return node ? heightHelper(node->getLeftChildPtr()) - heightHelper(node->getRightChildPtr()) : 0;
}

template <typename ItemType>
int AVLTree<ItemType>::getNumberOfNodesHelper(std::shared_ptr<BinaryNode<ItemType>> node) const
{
  return node ? 1 + getNumberOfNodesHelper(node->getLeftChildPtr()) + getNumberOfNodesHelper(node->getRightChildPtr()) : 0;
}

template <typename ItemType>
AVLTree<ItemType>::AVLTree() : root(nullptr)
{
}

template <typename ItemType>
bool AVLTree<ItemType>::isEmpty() const
{
  return root == nullptr;
}

template <typename ItemType>
int AVLTree<ItemType>::getHeight() const
{
  return heightHelper(root);
}

template <typename ItemType>
int AVLTree<ItemType>::getRootBalance() const
{
  return getBalance(root);
}

template <typename ItemType>
int AVLTree<ItemType>::getNumberOfNodes() const
{
  return getNumberOfNodesHelper(root);
}

template <typename ItemType>
std::shared_ptr<BinaryNode<ItemType>> AVLTree<ItemType>::getRoot() const
{
  return root;
}

template <typename ItemType>
ItemType AVLTree<ItemType>::getEntry(const ItemType &anEntry) const
{
  auto current = root;
  while (current)
  {
    if (anEntry < current->getItem())
      current = current->getLeftChildPtr();
    else if (anEntry > current->getItem())
      current = current->getRightChildPtr();
    else
      return current->getItem();
  }

  throw std::invalid_argument("Entry not found");
}

template <typename ItemType>
bool AVLTree<ItemType>::contains(const ItemType &anEntry) const
{
  auto current = root;
  while (current)
  {
    if (anEntry < current->getItem())
      current = current->getLeftChildPtr();
    else if (anEntry > current->getItem())
      current = current->getRightChildPtr();
    else
      return true;
  }

  return false;
}

template <typename ItemType>
void AVLTree<ItemType>::inorderTraverse(std::function<void(ItemType &)> visit) const
{
  inOrderHelper(root, visit);
}

template <typename ItemType>
void AVLTree<ItemType>::clear()
{
  root = nullptr;
}

template <typename ItemType>
void AVLTree<ItemType>::add(const ItemType &newEntry)
{
  root = addHelper(root, newEntry);
}

template <typename ItemType>
void AVLTree<ItemType>::remove(const ItemType &anEntry)
{
  root = removeHelper(root, anEntry);
}

template <typename ItemType>
void AVLTree<ItemType>::inOrderHelper(std::shared_ptr<BinaryNode<ItemType>> node, std::function<void(ItemType &)> visit) const
{
  if (!node)
    return;

  inOrderHelper(node->getLeftChildPtr(), visit);
  ItemType currentItem = node->getItem();
  visit(currentItem);
  inOrderHelper(node->getRightChildPtr(), visit);
}

template <typename ItemType>
std::shared_ptr<BinaryNode<ItemType>> AVLTree<ItemType>::rightRotate(std::shared_ptr<BinaryNode<ItemType>> a)
{
  /**
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

  return b; // New root after rotation
}

template <typename ItemType>
std::shared_ptr<BinaryNode<ItemType>> AVLTree<ItemType>::leftRotate(std::shared_ptr<BinaryNode<ItemType>> a)
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

  return b; // New root after rotation
}

template <typename ItemType>
std::shared_ptr<BinaryNode<ItemType>> AVLTree<ItemType>::addHelper(std::shared_ptr<BinaryNode<ItemType>> node, const ItemType &key)
{
  if (!node)
    return std::make_shared<BinaryNode<ItemType>>(key);

  if (key < node->getItem())
    node->setLeftChildPtr(addHelper(node->getLeftChildPtr(), key));
  else if (key > node->getItem())
    node->setRightChildPtr(addHelper(node->getRightChildPtr(), key));
  else
    throw std::invalid_argument("Duplicate key");

  // Find balance factor to check whether this node became unbalanced
  int balance = getBalance(node);

  // Rotate cases
  // Case 1: Left Left, added to the left subtree of the left child of this ancestor node
  if (balance > 1 && key < node->getLeftChildPtr()->getItem())
    return rightRotate(node);

  // Case 2: Right Right, added to the right subtree of the right child of this ancestor node
  if (balance < -1 && key > node->getRightChildPtr()->getItem())
    return leftRotate(node);

  // Case 3: Left Right, added to the right subtree of the left child of this ancestor node
  if (balance > 1 && key > node->getLeftChildPtr()->getItem())
  {
    node->setLeftChildPtr(leftRotate(node->getLeftChildPtr()));
    return rightRotate(node);
  }

  // Case 4: Right Left, added to the left subtree of the right child of this ancestor node
  if (balance < -1 && key < node->getRightChildPtr()->getItem())
  {
    node->setRightChildPtr(rightRotate(node->getRightChildPtr()));
    return leftRotate(node);
  }

  return node;
}

/*
AVL Add Workflow

1. BST-style add — recurse down the tree normally and create the new node at the correct null position

2. Unwind back up — as the recursion returns, each ancestor node on the add path gets checked for balance:
  At each ancestor:
  (1) Call getBalance(node) to get its BF
  (2) Check if BF hit ±2
      2.1 If not, return the node unchanged and keep unwinding
      2.2 If yes, at the first ancestor where BF = ±2 — determine rotation type
              2.2.1 BF > 1 → left heavy → check which side of the left child the new key went into
                              LL or LR (added to the left subtree of the left child or the right subtree of the left child)
                              LL: Perform single right rotation at this first unbalanced ancestor
                              LR: Perform double rotation (left rotation at left child of this first unbalanced ancestor,
                                                          then right rotation at this first unbalanced ancestor)

              2.2.2 BF < -1 → right heavy → check which side of the right child the new key went into
                              RR or RL (added to the right subtree of the right child or the left subtree of the right child)
                              RR: Perform single left rotation at this first unbalanced ancestor
                              RL: Perform double rotation (right rotation at right child of this first unbalanced ancestor,
                                                          then left rotation at this first unbalanced ancestor)

  (3) Rotation restores the subtree height — so all ancestors above see no BF change and unwind cleanly without further rotations

Deep Add Example and Trace Through the Code:

              20
            /    \
          10      30
         /  \    /  \
        5   15  25   35
       /   / \
      3   12  17
     /
    2(new key)

addHelper(20)
  addHelper(10)
    addHelper(5)
      addHelper(3)
        addHelper(null) → returns new node(2)   ← the new node is created here
      3's left is set, then checks BF of 3  → fine, returns 3
    5's left is set, then checks BF of 5   → BF = +2, ROTATES HERE, LL case
    returns 3 (new subtree root)
  10's left is set, then checks BF of 10  → fine, returns 10
20's left is set, then checks BF of 20   → fine, returns 20

After rotation, the tree becomes:
              20
            /    \
          10      30
         /  \    /  \
        3   15  25   35
       / \  / \
      2   5 12  17

*/

template <typename ItemType>
std::shared_ptr<BinaryNode<ItemType>> AVLTree<ItemType>::removeHelper(std::shared_ptr<BinaryNode<ItemType>> node, const ItemType &key)
{
  // Bonus Project TODO
  return node; // Placeholder
}

// TODO: Why should addHelper and removeHelper return a node instead of void?
// How does returning the updated subtree root allow recursive rotations to propagate upward and reconnect each ancestor correctly?
// Since AVL needs to retrace, would adding a parent pointer to BinaryNode actually help, or would it mostly add extra maintenance?

/*
AVL Delete Workflow

1. BST deletion — recurse down the tree normally to find the node, remove it using standard BST logic:
   - No children → delete from there, and return nullptr
   - One child → return that child
   - Two children → find in-order successor (smallest in right subtree), copy its value up,
                    then delete from that successor

2. Unwind back up — as the recursion returns, each ancestor node on the deletion path gets checked for balance:
   At each ancestor:
   (1) Call getBalance(node) to get its BF
   (2) Check if BF hit ±2
       2.1 If not, return the node unchanged and keep unwinding
       2.2 If yes, determine rotation type using getBalance on the heavy child
           (unlike add, we cannot use key comparison since no single key traveled the path):
           2.2.1 BF > 1 → left heavy → call getBalance(leftChild)
                   >= 0 → LL: Perform single right rotation at this unbalanced ancestor
                   <  0 → LR: Perform double rotation (left rotation at left child,
                               then right rotation at this unbalanced ancestor)

           2.2.2 BF < -1 → right heavy → call getBalance(rightChild)
                   <= 0 → RR: Perform single left rotation at this unbalanced ancestor
                   >  0 → RL: Perform double rotation (right rotation at right child,
                               then left rotation at this unbalanced ancestor)
   (3) Unlike add, do NOT stop after the first rotation — the rotation after deletion
       may leave the subtree shorter than before, causing the parent above to also hit ±2.
       Every ancestor on the path must be checked all the way up to the root,
       potentially firing O(log n) rotations total.

Example:
              10
            /    \
           5      20
          / \    /   \
         3   7  15    25
        /         \   / \
       2           17 22  28
                           \
                            30
Delete 5:
(In-order swap)
              10
            /    \
           7      20
          / \    /   \
         3   5  15    25
        /         \   / \
       2           17 22  28
                           \
                            30

(Then delete 5 from its new position)
              10
            /    \
           7      20
          /      /   \
         3      15    25
        /         \   / \
       2           17 22  28
                           \
                            30

(Trace back from this deletion point, we find 7 is unbalanced, right rotate at 7)
              10
            /    \
           3      20
          / \    /   \
         2   7  15    25
                  \   / \
                   17 22  28
                           \
                            30

(Continue tracing back from this deletion point, we find 10 is also unbalanced, left rotate at 10)
              20
            /    \
           10      25
          /  \    / \
         3   15  22  28
        / \    \       \
       2   7   17      30
*/