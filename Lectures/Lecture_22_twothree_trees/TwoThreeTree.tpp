#include "TwoThreeTree.hpp"

// ============================================================
// Private helpers
// ============================================================

template <typename ItemType>
int TwoThreeTree<ItemType>::getHeightHelper(std::shared_ptr<TriNode<ItemType>> node) const
{
  if (node == nullptr)
    return 0;
  int leftHeight = getHeightHelper(node->getLeftChildPtr());
  int midHeight = getHeightHelper(node->getMidChildPtr());
  int rightHeight = getHeightHelper(node->getRightChildPtr());
  return 1 + std::max({leftHeight, midHeight, rightHeight});
}

template <typename ItemType>
int TwoThreeTree<ItemType>::getLevelHelper(std::shared_ptr<TriNode<ItemType>> node,
                                           const ItemType &anItem) const
{
  if (node == nullptr)
    return -1;

  if (anItem == node->getSmallItem() ||                       // 2-node match
      (!node->isTwoNode() && anItem == node->getLargeItem())) // 3-node match
    return 1;                                                 // found at this node, count it

  int result;
  if (anItem < node->getSmallItem())
    result = getLevelHelper(node->getLeftChildPtr(), anItem);
  else if (node->isTwoNode() || anItem < node->getLargeItem())
    result = getLevelHelper(node->getMidChildPtr(), anItem);
  else
    result = getLevelHelper(node->getRightChildPtr(), anItem);

  return result == -1 ? -1 : result + 1; // propagate not-found, or count this level
}

template <typename ItemType>
int TwoThreeTree<ItemType>::getNumofNodesHelper(std::shared_ptr<TriNode<ItemType>> node) const
{
  if (node == nullptr)
    return 0;
  return 1 + getNumofNodesHelper(node->getLeftChildPtr()) + getNumofNodesHelper(node->getMidChildPtr()) + getNumofNodesHelper(node->getRightChildPtr());
}

template <typename ItemType>
void TwoThreeTree<ItemType>::inOrderTraversalHelper(
    std::shared_ptr<TriNode<ItemType>> node,
    std::function<void(ItemType &)> visit) const
{
  if (node == nullptr)
    return;

  if (node->isTwoNode())
  {
    inOrderTraversalHelper(node->getLeftChildPtr(), visit);
    ItemType small = node->getSmallItem();
    visit(small);
    inOrderTraversalHelper(node->getMidChildPtr(), visit);
    return;
  }

  inOrderTraversalHelper(node->getLeftChildPtr(), visit);
  ItemType small = node->getSmallItem();
  visit(small);
  inOrderTraversalHelper(node->getMidChildPtr(), visit);
  ItemType large = node->getLargeItem();
  visit(large);
  inOrderTraversalHelper(node->getRightChildPtr(), visit);
}

template <typename ItemType>
void TwoThreeTree<ItemType>::printTreeCustomHelper(
    std::shared_ptr<TriNode<ItemType>> node, int depth) const
{
  if (node == nullptr)
    return;

  for (int i = 0; i < depth; ++i)
    std::cout << "\t";

  std::cout << "[" << node->getSmallItem();
  if (!node->isTwoNode())
    std::cout << ", " << node->getLargeItem();
  std::cout << "]" << std::endl;

  printTreeCustomHelper(node->getLeftChildPtr(), depth + 1);
  printTreeCustomHelper(node->getMidChildPtr(), depth + 1);
  printTreeCustomHelper(node->getRightChildPtr(), depth + 1);
}

template <typename ItemType>
std::shared_ptr<TriNode<ItemType>> TwoThreeTree<ItemType>::findNode(
    const ItemType &anItem) const
{
  auto current = root;
  while (current != nullptr)
  {
    if (anItem == current->getSmallItem() ||
        (!current->isTwoNode() && anItem == current->getLargeItem()))
      return current;

    if (anItem < current->getSmallItem())
      current = current->getLeftChildPtr();
    else if (current->isTwoNode() || anItem < current->getLargeItem())
      current = current->getMidChildPtr();
    else
      current = current->getRightChildPtr();
  }
  return nullptr;
}

// Splits node n, which already contains two data items (3 with the new item).
// Note: If n is not a leaf, it has four children.
// split(n: Type23Tree): void {
//   if (n is the root)
//     Create a new node p containing someItem
//   else  // n is internal
//     Let p be the parent of n
//   Replace node n with two nodes, n1 and n2, with p as their parent
//   Give n1 the smallest data item in n
//   Give n2 the largest data item in n
//   if (n is not a leaf) {
//     n1 becomes the parent of n's two leftmost children
//     n2 becomes the parent of n's two rightmost children
//   }
//   Move the middle-valued item in n up to p
//   if (p now has three data items)
//     split(p)
// }
template <typename ItemType>
std::shared_ptr<TriNode<ItemType>> TwoThreeTree<ItemType>::split(
    std::shared_ptr<TriNode<ItemType>> node, const ItemType &newItem)
{
  // Determine small < middle < large across the three values
  ItemType small, middle, large;
  if (newItem < node->getSmallItem())
  {
    small = newItem;
    middle = node->getSmallItem();
    large = node->getLargeItem();
  }
  else if (newItem < node->getLargeItem())
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

  // Give n1 the smallest data item in n
  auto n1 = std::make_shared<TriNode<ItemType>>(small);

  // Give n2 the largest data item in n
  auto n2 = std::make_shared<TriNode<ItemType>>(large);

  // If node n is a leaf, we can simply create parent node and return
  // For example, in the subcall of split(node_2_5, 8) when adding 8 to the tree
  //         [10   15]
  //       /     |     \
  //   [2 5]  [11 14]   [20, 25]
  if (node->isLeaf())
  {
    auto p = std::make_shared<TriNode<ItemType>>(middle, middle, n1, n2, nullptr); // dummy sentinel with smallItem == largeItem signals
    p->setRightChildPtr(std::make_shared<TriNode<ItemType>>(middle));              // to safe-guard isThreeNode() check on this dummy node
    // The temp dummy structure looks like:
    //         [10   15]
    //       /     |     \
    //   [5 5]  [11 14]   [20, 25]
    //   / |  \
    // [2] [8] [5] <- never be read

    // node_5_5 would be returned
    // The caller would clean up the dummy node
    return p;
  }

  // Otherwise, node n is not a leaf (on the way back up from addHelper), it has four children
  // For example, in the subcall of split(node_10_15, 5) when adding 8 to the tree (5 moved up to node_10_15)
  //         [10   15]
  //       /     |     \
  //   [2 5]  [11 14]   [20, 25]
  //   n1 becomes the parent of n's two leftmost children
  //   n2 becomes the parent of n's two rightmost children
  else
  {
    // The temp dummy structure looks like:
    //     n1=5  [10   15]   n2=15
    //
    //   [2] [8]  [11 14]   [20, 25]
    // At this point, we have created n1 with small = 5 and n2 with large = 15, but we haven't set their children yet
    if (newItem < node->getSmallItem())
    {
      // Above given example fires this case, since 5 < 10
      n1->setLeftChildPtr(node->getLeftChildPtr()->getLeftChildPtr());
      n1->setMidChildPtr(node->getLeftChildPtr()->getMidChildPtr());
      n2->setLeftChildPtr(node->getMidChildPtr());
      n2->setMidChildPtr(node->getRightChildPtr());
      // The temp dummy structure looks like:
      //     [5]           [15]
      //    /  \           /  \
      //   [2] [8]  [11 14]   [20, 25]
    }
    else if (newItem > node->getLargeItem())
    {
      n1->setLeftChildPtr(node->getLeftChildPtr());
      n1->setMidChildPtr(node->getMidChildPtr());
      n2->setLeftChildPtr(node->getRightChildPtr()->getLeftChildPtr());
      n2->setMidChildPtr(node->getRightChildPtr()->getMidChildPtr());
    }
    else
    {
      n1->setLeftChildPtr(node->getLeftChildPtr());
      n1->setMidChildPtr(node->getMidChildPtr()->getLeftChildPtr());
      n2->setLeftChildPtr(node->getMidChildPtr()->getMidChildPtr());
      n2->setMidChildPtr(node->getRightChildPtr());
    }

    auto p = std::make_shared<TriNode<ItemType>>(middle, middle, n1, n2, nullptr);
    p->setRightChildPtr(std::make_shared<TriNode<ItemType>>(middle));

    // The temp dummy structure looks like:
    //         [10        10]
    //        /            |       \
    //      [5]           [15]     [10] <- never be read
    //     /  \           /  \
    //   [2] [8]   [11 14]   [20, 25]
    // node_10_10 would be returned, the caller would clean up the dummy node
    return p;
  }
}

// Adds a new data item to a 2-3 tree whose items are distinct and differ from the new item.
// add(some23Tree: Type23Tree, someItem: ItemType): boolean {
//   Locate the leaf, leafNode, in which someItem belongs
//   Add someItem to leafNode
//   if (leafNode has three data items) {
//     split(leafNode)
//     return true
//   } else  // leafNode has two data items
//     return true
// }
template <typename ItemType>
std::shared_ptr<TriNode<ItemType>> TwoThreeTree<ItemType>::addHelper(
    std::shared_ptr<TriNode<ItemType>> node, const ItemType &newItem)
{
  // Base case: insert position found — create a new leaf
  if (node == nullptr)
    return std::make_shared<TriNode<ItemType>>(newItem);

  // --- Locate the leaf, leafNode, in which someItem belongs ---
  if (node->isLeaf())
  {
    if (node->isTwoNode())
    {
      // Add someItem to leafNode — leaf now has two data items → done
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
    // leafNode has three data items → split(leafNode)
    return split(node, newItem);
  }

  // --- Internal node: recurse toward the correct leaf ---
  if (newItem < node->getSmallItem())
    node->setLeftChildPtr(addHelper(node->getLeftChildPtr(), newItem));
  else if (node->isTwoNode() || newItem < node->getLargeItem())
    node->setMidChildPtr(addHelper(node->getMidChildPtr(), newItem));
  else
    node->setRightChildPtr(addHelper(node->getRightChildPtr(), newItem));

  // Would go beyond this point only if a split occurred in the subtree
  // check for it and handle it on the way back up
  // For example, in the subcall of addHelper(node_10_15, 8) or addHelper(node_10_15, 13) or addHelper(node_10_15, 27)
  //         [10   15]
  //       /     |     \
  //   [2 5]  [11 14]   [20, 25]

  std::shared_ptr<TriNode<ItemType>> splitChild = nullptr;
  // A split child signals itself with smallItem == largeItem (dummy sentinel)

  // Example 1: If 8 was added, and node_2_5 was split
  // When we unwind back to node_10_15, we check its children and find node_2_5 was split
  // The temp dummy structure looks like:
  //         [10   15]
  //       /     |     \
  //   [5 5]  [11 14]   [20, 25]
  //   /   \
  // [2]   [8]
  // and splitChild will point to the dummy node [5 5] with smallItem == largeItem == 5
  if (node->getLeftChildPtr() && node->getLeftChildPtr()->isThreeNode() &&
      node->getLeftChildPtr()->getSmallItem() == node->getLeftChildPtr()->getLargeItem())
    splitChild = node->getLeftChildPtr();

  // Example 2: If 13 was added, and node_11_14 was split
  // When we unwind back to node_10_15, we check its children and find node_11_14 was split
  // The temp dummy structure looks like:
  //         [10   15]
  //       /     |     \
  //   [2 5]  [13 13]   [20, 25]
  //           /   \
  //         [11]  [14]
  // and splitChild will point to the dummy node [13 13] with smallItem == largeItem == 13
  else if (node->getMidChildPtr() && node->getMidChildPtr()->isThreeNode() &&
           node->getMidChildPtr()->getSmallItem() == node->getMidChildPtr()->getLargeItem())
    splitChild = node->getMidChildPtr();

  // Example 3: If 27 was added, and node_20_25 was split
  // When we unwind back to node_10_15, we check its children and find node_20_25 was split
  // The temp dummy structure looks like:
  //         [10   15]
  //       /     |     \
  //   [2 5]  [11 14]   [25 25]
  //                      /   \
  //                    [20]  [27]
  // and splitChild will point to the dummy node [25 25] with smallItem == largeItem == 25
  else if (node->getRightChildPtr() && node->getRightChildPtr()->isThreeNode() &&
           node->getRightChildPtr()->getSmallItem() == node->getRightChildPtr()->getLargeItem())
    splitChild = node->getRightChildPtr();

  if (splitChild)
  {
    // Ready to handle the dummy split
    // First store the dummy split's item, left and mid children before we collapse the dummy
    auto middleItem = splitChild->getSmallItem();
    auto n1 = splitChild->getLeftChildPtr();
    auto n2 = splitChild->getMidChildPtr();
    splitChild->setRightChildPtr(nullptr);
    splitChild->setLargeItem(ItemType());

    if (node->isTwoNode())
    {
      // This node absorbs middle — becomes a 3-node, no further split needed
      if (middleItem < node->getSmallItem())
      {
        node->setLargeItem(node->getSmallItem());
        node->setSmallItem(middleItem);
        node->setRightChildPtr(node->getMidChildPtr());
        node->setLeftChildPtr(n1);
        node->setMidChildPtr(n2);
      }
      else
      {
        node->setLargeItem(middleItem);
        node->setMidChildPtr(n1);
        node->setRightChildPtr(n2);
      }
    }
    else
    {
      // This node already has two items → adding middle gives three, further split needed
      return split(node, middleItem);
    }
  }

  return node;
}

// TODO: Which structure of add/addHelper/split suggests the add operation is O(log n)?
// Hints: Think how many branches addHelper takes at each internal node on the way down?
// How many levels addHelper visits total, how much work each split() call does — does it depend on n?
// In the worst case, how many split() calls can there be?

// Removes a given data item from a 2-3 tree.
// Returns true if successful or false if no such item exists.
// remove(some23Tree: Type23Tree, dataItem: ItemType): boolean {
//   Attempt to locate dataItem
//   if (dataItem is found) {
//     if (dataItem is not in a leaf)
//       Swap dataItem with its inorder successor, which will be in a leaf, leafNode
//     // The removal always begins at a leaf
//     Remove dataItem from leaf leafNode
//     if (leafNode now has no data items)
//       fixTree(leafNode)
//     return true
//   } else
//     return false
// }
template <typename ItemType>
std::shared_ptr<TriNode<ItemType>> TwoThreeTree<ItemType>::removeHelper(std::shared_ptr<TriNode<ItemType>> node, const ItemType &anItem)
{
  // TODO: implementation needed
  return node;
}

// Recursively completes the removal when node n is empty by either,
// redistributing values, merging nodes, deleting n, or deleting the root.
// Note: If n is internal, it has one child.
// fixTree(n: Type23Node): void {
//   if (n is the root)
//     Delete the root
//   else {
//     Let p be the parent of n
//     if (some sibling of n has two data items) {
//       Distribute items appropriately among n, the sibling, and p
//       if (n is internal)
//         Move the appropriate child from sibling to n
//     } else // Merge the node {
//       Choose an adjacent sibling s of n
//       Bring the appropriate data item down from p into s
//       if (n is internal)
//         Move n's child to s
//       Delete node n
//       if (p is now empty)
//         fixTree(p)
//     }
//   }
// }
template <typename ItemType>
void TwoThreeTree<ItemType>::fixTree(std::shared_ptr<TriNode<ItemType>> node, std::shared_ptr<TriNode<ItemType>> parent)
{
  // TODO: implementation needed
}

// ============================================================
// Public interface
// ============================================================

template <typename ItemType>
TwoThreeTree<ItemType>::TwoThreeTree() : root(nullptr), numItems(0)
{
}

template <typename ItemType>
TwoThreeTree<ItemType>::~TwoThreeTree()
{
  clear();
}

template <typename ItemType>
bool TwoThreeTree<ItemType>::isEmpty() const
{
  return numItems == 0;
}

template <typename ItemType>
int TwoThreeTree<ItemType>::getNumofDataItems() const
{
  return numItems;
}

template <typename ItemType>
int TwoThreeTree<ItemType>::getHeight() const
{
  return getHeightHelper(root);
}

template <typename ItemType>
int TwoThreeTree<ItemType>::getNumofNodes() const
{
  return getNumofNodesHelper(root);
}

template <typename ItemType>
std::shared_ptr<TriNode<ItemType>> TwoThreeTree<ItemType>::getRoot() const
{
  return root;
}

template <typename ItemType>
int TwoThreeTree<ItemType>::getLevel(const ItemType &anItem) const
{
  return getLevelHelper(root, anItem);
}

template <typename ItemType>
bool TwoThreeTree<ItemType>::contains(const ItemType &anItem) const
{
  return findNode(anItem) != nullptr;
}

template <typename ItemType>
ItemType TwoThreeTree<ItemType>::getEntry(const ItemType &anItem) const
{
  auto node = findNode(anItem);
  if (!node)
    throw std::runtime_error("Item not found in the tree.");
  return anItem == node->getSmallItem() ? node->getSmallItem() : node->getLargeItem();
}

template <typename ItemType>
bool TwoThreeTree<ItemType>::isleaf(const ItemType &anItem) const
{
  auto node = findNode(anItem);
  if (!node)
    throw std::runtime_error("Item not found in the tree.");
  return node->isLeaf();
}

template <typename ItemType>
void TwoThreeTree<ItemType>::inOrderTraversal(std::function<void(ItemType &)> visit) const
{
  inOrderTraversalHelper(root, visit);
}

template <typename ItemType>
void TwoThreeTree<ItemType>::printTreeCustom() const
{
  printTreeCustomHelper(root, 0);
}

template <typename ItemType>
void TwoThreeTree<ItemType>::add(const ItemType &anItem)
{
  if (contains(anItem))
    throw std::runtime_error("Item already exists in the tree.");

  root = addHelper(root, anItem);

  // If root was split, the dummy sentinel appears at root level —
  // collapse it into a clean 2-node root
  if (root->getSmallItem() == root->getLargeItem())
  {
    root->setLargeItem(ItemType());
    root->setRightChildPtr(nullptr);
  }

  numItems++;
}

template <typename ItemType>
void TwoThreeTree<ItemType>::remove(const ItemType &anItem)
{
  if (!contains(anItem))
    throw std::invalid_argument("Item not in the tree.");

  root = removeHelper(root, anItem);
  numItems--;
}

template <typename ItemType>
void TwoThreeTree<ItemType>::clear()
{
  root = nullptr;
  numItems = 0;
}