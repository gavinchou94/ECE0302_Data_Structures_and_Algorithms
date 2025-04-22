#include "Linked23.hpp"

template <typename ItemType>
Linked23<ItemType>::Linked23() : root(nullptr), numItems(0)
{
}

template <typename ItemType>
Linked23<ItemType>::~Linked23()
{
  clear();
}

template <class ItemType>
bool Linked23<ItemType>::isEmpty() const
{
  return numItems == 0;
}

template <typename ItemType>
bool Linked23<ItemType>::contains(const ItemType &anItem) const
{
  auto current = root;
  while (current != nullptr)
  {
    if (anItem == current->getSmallItem() || (!current->isTwoNode() && anItem == current->getLargeItem()))
      return true;

    if (anItem < current->getSmallItem())
      current = current->getLeftChildPtr();
    else if (current->isTwoNode() || anItem < current->getLargeItem())
      current = current->getMidChildPtr();
    else
      current = current->getRightChildPtr();
  }
  return false;
}

template <typename ItemType>
int Linked23<ItemType>::getHeight() const
{
  return getHeightHelper(root);
}

template <class ItemType>
void Linked23<ItemType>::add(const ItemType &anItem)
{
  if (contains(anItem))
  {
    throw std::runtime_error("Item already exists in the tree.");
  }
  root = insert(root, anItem);
  if (root->getSmallItem() == root->getLargeItem())
  {
    root->setLargeItem(ItemType());
    root->setRightChildPtr(nullptr);
  }
  numItems++;
  std::cout << "Added: " << anItem << std::endl;
}

template <typename ItemType>
int Linked23<ItemType>::getHeightHelper(std::shared_ptr<TriNode<ItemType>> node) const
{
  if (node == nullptr)
    return 0;
  int leftHeight = node->getLeftChildPtr() ? getHeightHelper(node->getLeftChildPtr()) : 0;
  int midHeight = node->getMidChildPtr() ? getHeightHelper(node->getMidChildPtr()) : 0;
  int rightHeight = node->getRightChildPtr() ? getHeightHelper(node->getRightChildPtr()) : 0;
  return 1 + std::max({leftHeight, midHeight, rightHeight});
}

template <typename ItemType>
std::shared_ptr<TriNode<ItemType>> Linked23<ItemType>::insert(
    std::shared_ptr<TriNode<ItemType>> node, const ItemType &newItem)
{
  if (node == nullptr)
  {
    return std::make_shared<TriNode<ItemType>>(newItem);
  }

  if (node->isLeaf())
  {
    if (node->isTwoNode())
    {
      if (newItem < node->getSmallItem())
      {
        node->setLargeItem(node->getSmallItem());
        node->setSmallItem(newItem);
      }
      else
      {
        node->setLargeItem(newItem);
      }
      return node;
    }

    // Split a 3-node
    return splitNode(node, newItem);
  }

  // Recursive case: Traverse to the appropriate child
  if (newItem < node->getSmallItem())
  {
    auto leftChild = insert(node->getLeftChildPtr(), newItem);
    node->setLeftChildPtr(leftChild);
  }
  else if (node->isTwoNode() || newItem < node->getLargeItem())
  {
    auto midChild = insert(node->getMidChildPtr(), newItem);
    node->setMidChildPtr(midChild);
  }
  else
  {
    auto rightChild = insert(node->getRightChildPtr(), newItem);
    node->setRightChildPtr(rightChild);
  }

  // Handle splits from children
  if (node->getLeftChildPtr() && node->getLeftChildPtr()->isThreeNode())
  {
    if (node->getLeftChildPtr()->getSmallItem() == node->getLeftChildPtr()->getLargeItem())
    {
      return handleChildSplit(node, node->getLeftChildPtr());
    }
  }

  if (node->getMidChildPtr() && node->getMidChildPtr()->isThreeNode())
  {
    if (node->getMidChildPtr()->getSmallItem() == node->getMidChildPtr()->getLargeItem())
    {
      return handleChildSplit(node, node->getMidChildPtr());
    }
  }
  if (node->getRightChildPtr() && node->getRightChildPtr()->isThreeNode())
  {
    if (node->getRightChildPtr()->getSmallItem() == node->getRightChildPtr()->getLargeItem())
    {
      return handleChildSplit(node, node->getRightChildPtr());
    }
  }

  return node;
}

template <typename ItemType>
void Linked23<ItemType>::remove(const ItemType &anItem)
{
  // Implementation needed, too complicated so far!
  if (!contains(anItem))
  {
    throw std::invalid_argument("Item not in the tree");
  }
}

template <typename ItemType>
void Linked23<ItemType>::clear()
{
  root = nullptr;
  numItems = 0;
}

template <typename ItemType>
void Linked23<ItemType>::inOrderTraversal() const
{
  inOrderTraversalHelper(root);
}

template <typename ItemType>
void Linked23<ItemType>::inOrderTraversalHelper(std::shared_ptr<TriNode<ItemType>> node) const
{
  if (node == nullptr)
    return;
  inOrderTraversalHelper(node->getLeftChildPtr());
  std::cout << node->getSmallItem() << " ";
  if (!node->isTwoNode())
    std::cout << node->getLargeItem() << " ";
  inOrderTraversalHelper(node->getMidChildPtr());
  inOrderTraversalHelper(node->getRightChildPtr());
}

template <typename ItemType>
std::shared_ptr<TriNode<ItemType>> Linked23<ItemType>::getRoot() const
{
  return root;
}

template <typename ItemType>
int Linked23<ItemType>::getNumItems() const
{
  return numItems;
}

template <typename ItemType>
void Linked23<ItemType>::printTreeStructure() const
{
  printTreeStructureHelper(root, 0);
}

template <typename ItemType>
void Linked23<ItemType>::printTreeStructureHelper(std::shared_ptr<TriNode<ItemType>> node, int depth) const
{
  if (node == nullptr)
    return;

  // Indent based on depth
  for (int i = 0; i < depth; ++i)
    std::cout << "\t";

  // Print the current node's items
  std::cout << "[";
  std::cout << node->getSmallItem();
  if (!node->isTwoNode())
    std::cout << ", " << node->getLargeItem();
  std::cout << "]" << std::endl;

  // Recursively print children
  printTreeStructureHelper(node->getLeftChildPtr(), depth + 1);
  printTreeStructureHelper(node->getMidChildPtr(), depth + 1);
  printTreeStructureHelper(node->getRightChildPtr(), depth + 1);
}

template <typename ItemType>
int Linked23<ItemType>::getNodeCount() const
{
  int result = nodeCountBelow(root);
  return result;
}

template <typename ItemType>
int Linked23<ItemType>::nodeCountBelow(std::shared_ptr<TriNode<ItemType>> node) const
{
  if (node == nullptr)
    return 0;

  // Count the current node
  int count = 1;

  // Recursively count nodes in left, middle, and right subtrees
  count += nodeCountBelow(node->getLeftChildPtr());
  count += nodeCountBelow(node->getMidChildPtr());
  count += nodeCountBelow(node->getRightChildPtr());

  return count;
}

template <typename ItemType>
int Linked23<ItemType>::getLevel(const ItemType &anItem) const
{
  return getLevelHelper(root, anItem, 1);
}

template <class ItemType>
bool Linked23<ItemType>::isleaf(const ItemType &anItem) const
{
  auto current = root;
  while (current != nullptr)
  {
    // Check if current node contains the item
    if (anItem == current->getSmallItem() || (!current->isTwoNode() && anItem == current->getLargeItem()))
    {
      // If node contains the item, check if it's a leaf
      return current->isLeaf();
    }

    // Continue searching for the item
    if (anItem < current->getSmallItem())
      current = current->getLeftChildPtr();
    else if (current->isTwoNode() || anItem < current->getLargeItem())
      current = current->getMidChildPtr();
    else
      current = current->getRightChildPtr();
  }

  // Item not found in the tree
  throw std::runtime_error("Item not found in the tree.");
}

template <typename ItemType>
int Linked23<ItemType>::getLevelHelper(std::shared_ptr<TriNode<ItemType>> node, const ItemType &anItem, int level) const
{
  if (node == nullptr)
    return -1; // Item not found

  if (anItem == node->getSmallItem() || (!node->isTwoNode() && anItem == node->getLargeItem()))
    return level;

  if (anItem < node->getSmallItem())
    return getLevelHelper(node->getLeftChildPtr(), anItem, level + 1);
  else if (node->isTwoNode() || anItem < node->getLargeItem())
    return getLevelHelper(node->getMidChildPtr(), anItem, level + 1);
  else
    return getLevelHelper(node->getRightChildPtr(), anItem, level + 1);
}

// Helper function
// Precondition: node is a 3-node
// newItem is a value bubbled up from one of its child
template <typename ItemType>
std::shared_ptr<TriNode<ItemType>> Linked23<ItemType>::splitNode(
    std::shared_ptr<TriNode<ItemType>> node, const ItemType &newItem)
{
  // Determine the order of items
  ItemType small, middle, large;
  if (newItem < node->getSmallItem())
  {
    small = newItem;
    middle = node->getSmallItem();
    large = node->getLargeItem();
  }
  else if (node->isTwoNode() || newItem < node->getLargeItem())
  {
    small = node->getSmallItem();
    middle = newItem;
    large = node->getLargeItem();
  }
  else
  {
    small = node->getSmallItem();
    middle = node->getLargeItem();
    large = newItem;
  }

  // Create two new child nodes
  auto leftChild = std::make_shared<TriNode<ItemType>>(small);
  if (node->getLeftChildPtr())
  {
    if (newItem < node->getSmallItem())
    {
      leftChild->setLeftChildPtr(node->getLeftChildPtr()->getLeftChildPtr());
    }
    else
    {
      leftChild->setLeftChildPtr(node->getLeftChildPtr());
    }
  }
  if (node->getMidChildPtr() || node->getLeftChildPtr())
  {
    if (newItem < node->getSmallItem())
    {
      leftChild->setMidChildPtr(node->getLeftChildPtr()->getMidChildPtr());
    }
    else if (newItem > node->getLargeItem())
    {
      leftChild->setMidChildPtr(node->getMidChildPtr());
    }
    else if (newItem > node->getSmallItem() && newItem < node->getLargeItem())
    {
      leftChild->setMidChildPtr(node->getMidChildPtr()->getLeftChildPtr());
    }
    //
  }
  auto rightChild = std::make_shared<TriNode<ItemType>>(large);

  if (node->getRightChildPtr() || node->getMidChildPtr())
  {
    if (newItem < node->getSmallItem())
    {
      rightChild->setLeftChildPtr(node->getMidChildPtr());
    }
    else if (newItem > node->getLargeItem())
    {
      rightChild->setLeftChildPtr(node->getRightChildPtr()->getLeftChildPtr());
    }
    else if (newItem > node->getSmallItem() && newItem < node->getLargeItem())
    {
      rightChild->setLeftChildPtr(node->getMidChildPtr()->getMidChildPtr());
    }
  }

  if (node->getRightChildPtr())
  {
    if (newItem > node->getLargeItem())
    {
      rightChild->setMidChildPtr(node->getRightChildPtr()->getMidChildPtr());
    }
    else
    {
      rightChild->setMidChildPtr(node->getRightChildPtr());
    }
  }

  // Return a new node with the middle item
  auto newParent = std::make_shared<TriNode<ItemType>>(middle);

  newParent->setLeftChildPtr(leftChild);
  newParent->setMidChildPtr(rightChild);

  newParent->setLargeItem(middle); // make it looks like a 3-node
  auto dummy = std::make_shared<TriNode<ItemType>>(middle);
  newParent->setRightChildPtr(dummy);

  return newParent;
}

/* Visualize the split:
  *
  * (1) Parent is 2-node, child is 3-node
  * newItem should belong to the 3-node child
  *
  * Before split: (assume xs=9 is added to child and xs<s<l)
  *            parent[sp=20]
  *           /             \
  *      child[s=10, l=15]   X=30
  *       /    \
  *    L-null  R-null          // order: Ln<s<l<Rn<sp<X
  *
  * After split:
  *       parent[s=10, sp=20]
  *        /      \        \
  *     L-null=9 R-null=15   X=30    // order: LC<s<RC<sp<X

* Visualize the split:
  *
  * (2) Parent is 2-node, child is 3-node
  * newItem should belong to the 3-node child
  *
  * Before split: (assume xs=22 is added to child and xs<s<l)
  *            parent[sp=20]
  *           /             \
  *        X=15     child[s=26, l=30]
  *                       /    \
  *                    L-null  R-null
  *
  * After split:
  *       parent[sp=20, s=26]
  *        /      \        \
  *      X   L-null=22   R-null=30    // order: LC<s<RC<sp<X
  *


* Visualize the split:
 *
 * (3) Parent is already 3-node, child is 3-node
 * newItem should belong to the 3-node child
 *
 * Before split: (assume xs=22 is added to child and xs<s<l)
 *             parent[sp=20, lp=30]
 *            /          \        \
 *        X=15     child[s=26, l=28] Y=45
 *
 * or before split: (assume xs=12 is added to child and xs<s<l)
 *             parent[sp=20, lp=30]
 *            /          \        \
 *     child[s=16, l=18] X=25      Y=45
 *
 * or before split: (assume xs=32 is added to child and xs<s<l)
 *             parent[sp=20, lp=30]
 *            /          \        \
 *          X=15       Y=25   child[s=36, l=38]
 *
*/

template <typename ItemType>
std::shared_ptr<TriNode<ItemType>> Linked23<ItemType>::handleChildSplit(
    std::shared_ptr<TriNode<ItemType>> parent,
    std::shared_ptr<TriNode<ItemType>> child)
{
  // Extract the middle item and the left/right children
  auto middleItem = child->getSmallItem();
  auto leftChild = child->getLeftChildPtr();
  auto rightChild = child->getMidChildPtr();
  child->setRightChildPtr(nullptr);
  child->setLargeItem(ItemType());

  // Insert the middle item into the parent
  if (parent->isTwoNode())
  {
    if (middleItem < parent->getSmallItem())
    {
      parent->setLargeItem(parent->getSmallItem());
      parent->setSmallItem(middleItem);
      parent->setRightChildPtr(parent->getMidChildPtr());
      parent->setMidChildPtr(rightChild);
      parent->setLeftChildPtr(leftChild);
    }
    else
    {
      parent->setLargeItem(middleItem);
      parent->setMidChildPtr(leftChild);
      parent->setRightChildPtr(rightChild);
    }
  }
  else
  {
    // If the parent is a 3-node, split the parent, check case (3)
    return splitNode(parent, middleItem);
  }

  return parent;
}