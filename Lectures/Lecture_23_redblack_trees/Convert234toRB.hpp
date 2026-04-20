#ifndef CONVERT_234_TO_RB_HPP
#define CONVERT_234_TO_RB_HPP
#include <memory>
#include "RBNode.hpp"
#include "TwoThreeFourTree.hpp"
#include "RedBlackTree.hpp"

// ============================================================
// 2-3-4 to Red-Black Tree Conversion
// ============================================================
// Mapping rules — each 2-3-4 node maps to an RB subtree:
//
// 2-node  [B]       →   B(black)
//
// 3-node  [A|B]     →   B(black)
//                       /
//                     A(red)
//
// 4-node  [A|B|C]   →   B(black)
//                       /      \
//                    A(red)   C(red)
//
// Key insight: the black nodes in the RB tree correspond exactly to the
// 2-3-4 nodes, the red nodes are items packed together in 3-nodes and
// 4-nodes, and the black-height of the RB tree equals the height of the
// 2-3-4 tree.
// ============================================================

// Recursively converts a 2-3-4 subtree rooted at node into an RB subtree.
// Builds the RB structure directly — no BST insertion or fixup is performed.
// Returns the root of the corresponding RB subtree.
template <typename ItemType>
std::shared_ptr<RBNode<ItemType>> convertNode(std::shared_ptr<QuadNode<ItemType>> node)
{
  if (!node)
    return nullptr;

  std::shared_ptr<RBNode<ItemType>> rbNode;

  if (node->isTwoNode())
  {
    // 2-node [B] → single black node, two children mapped recursively
    rbNode = std::make_shared<RBNode<ItemType>>(node->getSmallItem());
    rbNode->setColor(BLACK);
    rbNode->setLeftChildPtr(convertNode<ItemType>(node->getLeftChildPtr()));
    rbNode->setRightChildPtr(convertNode<ItemType>(node->getLeftMidChildPtr()));
  }
  else if (node->isThreeNode())
  {
    // 3-node [A|B] → B black, A red left child
    //     B(black)
    //    /
    //   A(red)
    rbNode = std::make_shared<RBNode<ItemType>>(node->getLargeItem());
    rbNode->setColor(BLACK);

    auto redLeft = std::make_shared<RBNode<ItemType>>(node->getSmallItem());
    redLeft->setColor(RED);
    redLeft->setLeftChildPtr(convertNode<ItemType>(node->getLeftChildPtr()));
    redLeft->setRightChildPtr(convertNode<ItemType>(node->getLeftMidChildPtr()));

    rbNode->setLeftChildPtr(redLeft);
    rbNode->setRightChildPtr(convertNode<ItemType>(node->getRightChildPtr()));
  }
  else // 4-node
  {
    // 4-node [A|B|C] → B black, A red left child, C red right child
    //     B(black)
    //    /        \
    //  A(red)    C(red)
    rbNode = std::make_shared<RBNode<ItemType>>(node->getMiddleItem());
    rbNode->setColor(BLACK);

    auto redLeft = std::make_shared<RBNode<ItemType>>(node->getSmallItem());
    redLeft->setColor(RED);
    redLeft->setLeftChildPtr(convertNode<ItemType>(node->getLeftChildPtr()));
    redLeft->setRightChildPtr(convertNode<ItemType>(node->getLeftMidChildPtr()));

    auto redRight = std::make_shared<RBNode<ItemType>>(node->getLargeItem());
    redRight->setColor(RED);
    redRight->setLeftChildPtr(convertNode<ItemType>(node->getRightMidChildPtr()));
    redRight->setRightChildPtr(convertNode<ItemType>(node->getRightChildPtr()));

    rbNode->setLeftChildPtr(redLeft);
    rbNode->setRightChildPtr(redRight);
  }

  return rbNode;
}

// Converts an entire 2-3-4 tree into a Red-Black tree.
// Uses setRoot() to inject the pre-built RB structure directly,
// bypassing BST insertion and fixup entirely.
template <typename ItemType>
RedBlackTree<ItemType> convertToRB(TwoThreeFourTree<ItemType> &tree234)
{
  RedBlackTree<ItemType> rbTree;
  rbTree.setRoot(convertNode<ItemType>(tree234.getRoot()));
  return rbTree;
}

#endif