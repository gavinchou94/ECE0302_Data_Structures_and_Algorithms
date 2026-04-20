/** A class of a link-based 2-3-4 tree.
 @file TwoThreeFourTree.hpp */
#ifndef TWO_THREE_FOUR_TREE_HPP
#define TWO_THREE_FOUR_TREE_HPP
#include <stdexcept>
#include <cstdint>
#include <memory>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ============================================================
// QuadNode
// ============================================================

template <class ItemType>
class QuadNode
{
private:
  int itemCount;
  ItemType smallItem, middleItem, largeItem;
  std::shared_ptr<QuadNode<ItemType>> leftChildPtr;
  std::shared_ptr<QuadNode<ItemType>> leftMidChildPtr;
  std::shared_ptr<QuadNode<ItemType>> rightMidChildPtr;
  std::shared_ptr<QuadNode<ItemType>> rightChildPtr;

public:
  // ============================================================
  // Constructors
  // ============================================================

  QuadNode()
      : itemCount(0),
        smallItem(ItemType()), middleItem(ItemType()), largeItem(ItemType()),
        leftChildPtr(nullptr), leftMidChildPtr(nullptr),
        rightMidChildPtr(nullptr), rightChildPtr(nullptr) {}

  // 2-node constructor
  QuadNode(const ItemType &small)
      : itemCount(1),
        smallItem(small), middleItem(ItemType()), largeItem(ItemType()),
        leftChildPtr(nullptr), leftMidChildPtr(nullptr),
        rightMidChildPtr(nullptr), rightChildPtr(nullptr) {}

  // 3-node constructor
  QuadNode(const ItemType &small, const ItemType &large)
      : itemCount(2),
        smallItem(small), middleItem(ItemType()), largeItem(large),
        leftChildPtr(nullptr), leftMidChildPtr(nullptr),
        rightMidChildPtr(nullptr), rightChildPtr(nullptr) {}

  // 4-node constructor
  QuadNode(const ItemType &small, const ItemType &middle, const ItemType &large)
      : itemCount(3),
        smallItem(small), middleItem(middle), largeItem(large),
        leftChildPtr(nullptr), leftMidChildPtr(nullptr),
        rightMidChildPtr(nullptr), rightChildPtr(nullptr) {}

  // ============================================================
  // Node type queries
  // ============================================================

  // 2-node: has exactly 1 item
  bool isTwoNode() const
  {
    return itemCount == 1;
  }

  // 3-node: has exactly 2 items
  bool isThreeNode() const
  {
    return itemCount == 2;
  }

  // 4-node: has exactly 3 items
  bool isFourNode() const
  {
    return itemCount == 3;
  }

  // Leaf: has no children
  bool isLeaf() const
  {
    return leftChildPtr == nullptr &&
           leftMidChildPtr == nullptr &&
           rightMidChildPtr == nullptr &&
           rightChildPtr == nullptr;
  }

  // ============================================================
  // Accessors
  // ============================================================

  ItemType getSmallItem() const { return smallItem; }
  ItemType getMiddleItem() const { return middleItem; }
  ItemType getLargeItem() const { return largeItem; }

  std::shared_ptr<QuadNode<ItemType>> getLeftChildPtr() const { return leftChildPtr; }
  std::shared_ptr<QuadNode<ItemType>> getLeftMidChildPtr() const { return leftMidChildPtr; }
  std::shared_ptr<QuadNode<ItemType>> getRightMidChildPtr() const { return rightMidChildPtr; }
  std::shared_ptr<QuadNode<ItemType>> getRightChildPtr() const { return rightChildPtr; }

  // ============================================================
  // Mutators
  // ============================================================

  void setSmallItem(const ItemType &item) { smallItem = item; }
  void setMiddleItem(const ItemType &item)
  {
    middleItem = item;
    itemCount = std::max(itemCount, 3);
  }
  void setLargeItem(const ItemType &item)
  {
    largeItem = item;
    itemCount = std::max(itemCount, 2);
  }

  void setLeftChildPtr(std::shared_ptr<QuadNode<ItemType>> ptr) { leftChildPtr = ptr; }
  void setLeftMidChildPtr(std::shared_ptr<QuadNode<ItemType>> ptr) { leftMidChildPtr = ptr; }
  void setRightMidChildPtr(std::shared_ptr<QuadNode<ItemType>> ptr) { rightMidChildPtr = ptr; }
  void setRightChildPtr(std::shared_ptr<QuadNode<ItemType>> ptr) { rightChildPtr = ptr; }

}; // end QuadNode

// ============================================================
// TwoThreeFourTree
// ============================================================

template <typename ItemType>
class TwoThreeFourTree
{
private:
  std::shared_ptr<QuadNode<ItemType>> root;
  int numItems;

  // ============================================================
  // Private helpers
  // ============================================================

  int getHeightHelper(std::shared_ptr<QuadNode<ItemType>> node) const
  {
    if (node == nullptr)
      return 0;
    int h1 = getHeightHelper(node->getLeftChildPtr());
    int h2 = getHeightHelper(node->getLeftMidChildPtr());
    int h3 = getHeightHelper(node->getRightMidChildPtr());
    int h4 = getHeightHelper(node->getRightChildPtr());
    return 1 + std::max({h1, h2, h3, h4});
  }

  int getLevelHelper(std::shared_ptr<QuadNode<ItemType>> node,
                     const ItemType &anItem) const
  {
    if (node == nullptr)
      return -1;

    if (anItem == node->getSmallItem() ||
        (node->isFourNode() && anItem == node->getMiddleItem()) ||
        (!node->isTwoNode() && anItem == node->getLargeItem()))
      return 1;

    int result;
    if (anItem < node->getSmallItem())
      result = getLevelHelper(node->getLeftChildPtr(), anItem);
    else if (node->isFourNode())
    {
      if (anItem < node->getMiddleItem())
        result = getLevelHelper(node->getLeftMidChildPtr(), anItem);
      else if (anItem < node->getLargeItem())
        result = getLevelHelper(node->getRightMidChildPtr(), anItem);
      else
        result = getLevelHelper(node->getRightChildPtr(), anItem);
    }
    else if (node->isThreeNode())
    {
      if (anItem < node->getLargeItem())
        result = getLevelHelper(node->getLeftMidChildPtr(), anItem);
      else
        result = getLevelHelper(node->getRightChildPtr(), anItem);
    }
    else
    {
      result = getLevelHelper(node->getLeftMidChildPtr(), anItem);
    }

    return result == -1 ? -1 : result + 1;
  }

  int getNumofNodesHelper(std::shared_ptr<QuadNode<ItemType>> node) const
  {
    if (node == nullptr)
      return 0;
    return 1 + getNumofNodesHelper(node->getLeftChildPtr()) + getNumofNodesHelper(node->getLeftMidChildPtr()) + getNumofNodesHelper(node->getRightMidChildPtr()) + getNumofNodesHelper(node->getRightChildPtr());
  }

  void inOrderTraversalHelper(std::shared_ptr<QuadNode<ItemType>> node,
                              std::function<void(ItemType &)> visit) const
  {
    if (node == nullptr)
      return;

    if (node->isTwoNode())
    {
      inOrderTraversalHelper(node->getLeftChildPtr(), visit);
      ItemType s = node->getSmallItem();
      visit(s);
      inOrderTraversalHelper(node->getLeftMidChildPtr(), visit);
      return;
    }

    if (node->isThreeNode())
    {
      inOrderTraversalHelper(node->getLeftChildPtr(), visit);
      ItemType s = node->getSmallItem();
      visit(s);
      inOrderTraversalHelper(node->getLeftMidChildPtr(), visit);
      ItemType l = node->getLargeItem();
      visit(l);
      inOrderTraversalHelper(node->getRightChildPtr(), visit);
      return;
    }

    // 4-node
    inOrderTraversalHelper(node->getLeftChildPtr(), visit);
    ItemType s = node->getSmallItem();
    visit(s);
    inOrderTraversalHelper(node->getLeftMidChildPtr(), visit);
    ItemType m = node->getMiddleItem();
    visit(m);
    inOrderTraversalHelper(node->getRightMidChildPtr(), visit);
    ItemType l = node->getLargeItem();
    visit(l);
    inOrderTraversalHelper(node->getRightChildPtr(), visit);
  }

  void printTreeCustomHelper(std::shared_ptr<QuadNode<ItemType>> node,
                             int depth) const
  {
    if (node == nullptr)
      return;

    for (int i = 0; i < depth; ++i)
      std::cout << "\t";

    std::cout << "[" << node->getSmallItem();
    if (node->isThreeNode())
      std::cout << " | " << node->getLargeItem();
    if (node->isFourNode())
      std::cout << " | " << node->getMiddleItem()
                << " | " << node->getLargeItem();
    std::cout << "]" << std::endl;

    printTreeCustomHelper(node->getLeftChildPtr(), depth + 1);
    printTreeCustomHelper(node->getLeftMidChildPtr(), depth + 1);
    printTreeCustomHelper(node->getRightMidChildPtr(), depth + 1);
    printTreeCustomHelper(node->getRightChildPtr(), depth + 1);
  }

  std::shared_ptr<QuadNode<ItemType>> findNode(const ItemType &anItem) const
  {
    auto current = root;
    while (current != nullptr)
    {
      if (anItem == current->getSmallItem() ||
          (current->isFourNode() && anItem == current->getMiddleItem()) ||
          (!current->isTwoNode() && anItem == current->getLargeItem()))
        return current;

      if (anItem < current->getSmallItem())
        current = current->getLeftChildPtr();
      else if (current->isFourNode())
      {
        if (anItem < current->getMiddleItem())
          current = current->getLeftMidChildPtr();
        else if (anItem < current->getLargeItem())
          current = current->getRightMidChildPtr();
        else
          current = current->getRightChildPtr();
      }
      else if (current->isThreeNode())
      {
        if (anItem < current->getLargeItem())
          current = current->getLeftMidChildPtr();
        else
          current = current->getRightChildPtr();
      }
      else
      {
        current = current->getLeftMidChildPtr();
      }
    }
    return nullptr;
  }

  // Splits a 4-node child and absorbs M directly into parent.
  // parent is guaranteed NOT a 4-node (invariant of top-down splitting).
  // After this call, parent's item set and child pointers are fully updated.
  // Splits a 4-node n encountered on the way down.
  // split(n: Type234Node): void {
  //   Move the middle item M of n up to n's parent p
  //   Replace n with two 2-nodes n1 and n2, both children of p:
  //     Give n1 the smallest item S  — parent of n's two leftmost children
  //     Give n2 the largest item L   — parent of n's two rightmost children
  //   Cases:
  //     (1) n is the root:
  //           create a new 2-node root containing M
  //           n1 and n2 become its left and right children       (handled in add())
  //     (2) n is a child of a 2-node parent p:
  //           p absorbs M → p becomes a 3-node
  //           n1 and n2 replace n as two of p's children
  //     (3) n is a child of a 3-node parent p:
  //           p absorbs M → p becomes a 4-node
  //           n1 and n2 replace n as two of p's children
  //   Note: case (3) never causes a further split because p is at most a 3-node
  //         (guaranteed by the proactive top-down split strategy)
  // }
  void splitChildInParent(std::shared_ptr<QuadNode<ItemType>> parent,
                          std::shared_ptr<QuadNode<ItemType>> child4)
  {
    ItemType S = child4->getSmallItem();
    ItemType M = child4->getMiddleItem();
    ItemType L = child4->getLargeItem();

    // Give n1 the smallest item — parent of child4's two leftmost children
    auto n1 = std::make_shared<QuadNode<ItemType>>(S);
    n1->setLeftChildPtr(child4->getLeftChildPtr());
    n1->setLeftMidChildPtr(child4->getLeftMidChildPtr());

    // Give n2 the largest item — parent of child4's two rightmost children
    auto n2 = std::make_shared<QuadNode<ItemType>>(L);
    n2->setLeftChildPtr(child4->getRightMidChildPtr());
    n2->setLeftMidChildPtr(child4->getRightChildPtr());

    if (parent->isTwoNode())
    {
      if (M < parent->getSmallItem())
      {
        // child4 was leftChild, M < parent's item
        // parent becomes [M, oldSmall] with children n1, n2, old-leftMid
        auto oldLeftMid = parent->getLeftMidChildPtr();
        parent->setLargeItem(parent->getSmallItem());
        parent->setSmallItem(M);
        parent->setLeftChildPtr(n1);
        parent->setLeftMidChildPtr(n2);
        parent->setRightChildPtr(oldLeftMid);
      }
      else
      {
        // child4 was leftMidChild, M > parent's item
        // parent becomes [oldSmall, M] with children old-left, n1, n2
        parent->setLargeItem(M);
        parent->setLeftMidChildPtr(n1);
        parent->setRightChildPtr(n2);
      }
    }
    else // 3-node parent [P, Q]
    {
      if (M < parent->getSmallItem())
      {
        // child4 was leftChild, M < P < Q
        // parent becomes [M, P, Q] with children n1, n2, old-leftMid, old-right
        auto oldSmall = parent->getSmallItem();
        auto oldLeftMid = parent->getLeftMidChildPtr();
        parent->setSmallItem(M);
        parent->setMiddleItem(oldSmall);
        parent->setLeftChildPtr(n1);
        parent->setLeftMidChildPtr(n2);
        parent->setRightMidChildPtr(oldLeftMid);
        // rightChildPtr unchanged
      }
      else if (M < parent->getLargeItem())
      {
        // child4 was leftMidChild, P < M < Q
        // parent becomes [P, M, Q] with children old-left, n1, n2, old-right
        parent->setMiddleItem(M);
        parent->setLeftMidChildPtr(n1);
        parent->setRightMidChildPtr(n2);
        // leftChildPtr and rightChildPtr unchanged
      }
      else
      {
        // child4 was rightChild, M > Q
        // parent becomes [P, Q, M] with children old-left, old-leftMid, n1, n2
        auto oldLarge = parent->getLargeItem();
        parent->setMiddleItem(oldLarge);
        parent->setLargeItem(M);
        parent->setRightMidChildPtr(n1);
        parent->setRightChildPtr(n2);
        // leftChildPtr and leftMidChildPtr unchanged
      }
    }
  }

  // Adds a new data item to a 2-3-4 tree whose items are distinct and differ from the new item.
  // add(some234Tree: Type234Tree, someItem: ItemType): boolean {
  //   Starting at root, search for the leaf where someItem belongs
  //   On the way DOWN, split every 4-node child before recursing into it:
  //     if (target child is a 4-node)
  //       splitChildInParent(current node, target child)   // absorbs M into current node
  //       re-route to correct child after split
  //   Add someItem to the reached leaf   // guaranteed non-4-node by proactive splits
  //   return true
  // }
  std::shared_ptr<QuadNode<ItemType>> addHelper(
      std::shared_ptr<QuadNode<ItemType>> node, const ItemType &newItem)
  {
    // node is guaranteed NOT a 4-node (invariant)
    if (node == nullptr)
      return std::make_shared<QuadNode<ItemType>>(newItem);

    // --- Leaf: insert directly (node is 2-node or 3-node) ---
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
      }
      else // 3-node leaf -> becomes 4-node
      {
        ItemType vals[3] = {node->getSmallItem(), node->getLargeItem(), newItem};
        std::sort(vals, vals + 3);
        node->setSmallItem(vals[0]);
        node->setMiddleItem(vals[1]);
        node->setLargeItem(vals[2]);
      }
      return node;
    }

    // --- Internal node: find target child ---
    std::shared_ptr<QuadNode<ItemType>> targetChild;
    if (newItem < node->getSmallItem())
      targetChild = node->getLeftChildPtr();
    else if (node->isTwoNode() || newItem < node->getLargeItem())
      targetChild = node->getLeftMidChildPtr();
    else
      targetChild = node->getRightChildPtr();

    // --- Proactive split: absorb M into node before recursing ---
    // Parent (node) is guaranteed non-4-node, so it always has room for M
    if (targetChild && targetChild->isFourNode())
      splitChildInParent(node, targetChild);
    // After split, node may have grown from 2-node → 3-node or 3-node → 4-node
    // Re-route using updated node

    // --- Route and recurse using updated node ---
    if (newItem < node->getSmallItem())
    {
      node->setLeftChildPtr(addHelper(node->getLeftChildPtr(), newItem));
    }
    else if (node->isFourNode())
    {
      if (newItem < node->getMiddleItem())
        node->setLeftMidChildPtr(addHelper(node->getLeftMidChildPtr(), newItem));
      else if (newItem < node->getLargeItem())
        node->setRightMidChildPtr(addHelper(node->getRightMidChildPtr(), newItem));
      else
        node->setRightChildPtr(addHelper(node->getRightChildPtr(), newItem));
    }
    else if (node->isThreeNode())
    {
      if (newItem < node->getLargeItem())
        node->setLeftMidChildPtr(addHelper(node->getLeftMidChildPtr(), newItem));
      else
        node->setRightChildPtr(addHelper(node->getRightChildPtr(), newItem));
    }
    else // 2-node
    {
      node->setLeftMidChildPtr(addHelper(node->getLeftMidChildPtr(), newItem));
    }

    return node;
  }

public:
  // ============================================================
  // Public interface
  // ============================================================

  TwoThreeFourTree() : root(nullptr), numItems(0) {}
  ~TwoThreeFourTree() { clear(); }

  bool isEmpty() const { return numItems == 0; }
  int getNumofDataItems() const { return numItems; }
  int getHeight() const { return getHeightHelper(root); }
  int getNumofNodes() const { return getNumofNodesHelper(root); }
  std::shared_ptr<QuadNode<ItemType>> getRoot() const { return root; }
  int getLevel(const ItemType &anItem) const { return getLevelHelper(root, anItem); }
  bool contains(const ItemType &anItem) const { return findNode(anItem) != nullptr; }
  void inOrderTraversal(std::function<void(ItemType &)> visit) const { inOrderTraversalHelper(root, visit); }
  void printTreeCustom() const { printTreeCustomHelper(root, 0); }
  void printTreeCustom(const std::string &filename) const
  {
    std::ofstream file(filename);
    const double verticalGap = 1.6;
    const double rootSpan = 8.0;

    file << "graph G {\n";
    file << "    layout=neato;\n";
    file << "    node [shape=record, style=filled, fillcolor=lightgoldenrod1, fixedsize=false];\n";
    file << "    edge [dir=none];\n";

    std::function<void(std::shared_ptr<QuadNode<ItemType>>, double, double, double)> writeNode;
    writeNode = [&](std::shared_ptr<QuadNode<ItemType>> node, double x, double y, double span)
    {
      if (!node)
        return;

      std::string nodeId = "node_" + std::to_string(reinterpret_cast<std::uintptr_t>(node.get()));
      std::string label = std::to_string(node->getSmallItem());
      if (node->isFourNode())
        label += "|" + std::to_string(node->getMiddleItem()) + "|" + std::to_string(node->getLargeItem());
      else if (node->isThreeNode())
        label += "|" + std::to_string(node->getLargeItem());

      file << "    \"" << nodeId << "\""
           << " [label=\"" << label << "\", pos=\"" << x << "," << y << "!\"];\n";

      std::vector<std::shared_ptr<QuadNode<ItemType>>> childSlots;
      if (node->isFourNode())
      {
        childSlots = {node->getLeftChildPtr(), node->getLeftMidChildPtr(), node->getRightMidChildPtr(), node->getRightChildPtr()};
      }
      else if (node->isThreeNode())
      {
        childSlots = {node->getLeftChildPtr(), node->getLeftMidChildPtr(), node->getRightChildPtr()};
      }
      else
      {
        childSlots = {node->getLeftChildPtr(), node->getLeftMidChildPtr()};
      }

      if (childSlots.empty())
        return;

      double step = (2.0 * span) / childSlots.size();
      double childSpan = step / 2.0;
      for (std::size_t i = 0; i < childSlots.size(); ++i)
      {
        auto child = childSlots[i];
        if (!child)
          continue;

        double childX = x - span + step * (static_cast<double>(i) + 0.5);
        std::string childId = "node_" + std::to_string(reinterpret_cast<std::uintptr_t>(child.get()));
        file << "    \"" << nodeId << "\" -- \"" << childId << "\";\n";
        writeNode(child, childX, y - verticalGap, childSpan);
      }
    };

    writeNode(root, 0, 0, rootSpan);
    file << "}\n";
    file.close();
  }
  // Paste the generated dot file into Graphviz to visualize the tree
  // Online Graphviz: https://dreampuf.github.io/GraphvizOnline/

  void clear()
  {
    root = nullptr;
    numItems = 0;
  }

  ItemType getEntry(const ItemType &anItem) const
  {
    auto node = findNode(anItem);
    if (!node)
      throw std::runtime_error("Item not found in the tree.");
    if (anItem == node->getSmallItem())
      return node->getSmallItem();
    if (anItem == node->getMiddleItem())
      return node->getMiddleItem();
    return node->getLargeItem();
  }

  bool isLeaf(const ItemType &anItem) const
  {
    auto node = findNode(anItem);
    if (!node)
      throw std::runtime_error("Item not found in the tree.");
    return node->isLeaf();
  }

  void add(const ItemType &anItem)
  {
    if (contains(anItem))
      throw std::runtime_error("Item already exists in the tree.");

    // Case (1): root is a 4-node — split it first, creating a new root
    // This is the only place a split happens without a parent to absorb M
    if (root && root->isFourNode())
    {
      ItemType S = root->getSmallItem();
      ItemType M = root->getMiddleItem();
      ItemType L = root->getLargeItem();

      auto n1 = std::make_shared<QuadNode<ItemType>>(S);
      n1->setLeftChildPtr(root->getLeftChildPtr());
      n1->setLeftMidChildPtr(root->getLeftMidChildPtr());

      auto n2 = std::make_shared<QuadNode<ItemType>>(L);
      n2->setLeftChildPtr(root->getRightMidChildPtr());
      n2->setLeftMidChildPtr(root->getRightChildPtr());

      root = std::make_shared<QuadNode<ItemType>>(M);
      root->setLeftChildPtr(n1);
      root->setLeftMidChildPtr(n2);
    }

    root = addHelper(root, anItem);
    numItems++;
  }

  void remove(const ItemType &anItem)
  {
    // BONUS TODO: implementation needed
  }

}; // end TwoThreeFourTree

#endif