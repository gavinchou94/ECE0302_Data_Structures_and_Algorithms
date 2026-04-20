#include "RedBlackTree.hpp"

// ============================================================
// Private helpers
// ============================================================

template <typename ItemType>
bool RedBlackTree<ItemType>::isRed(std::shared_ptr<RBNode<ItemType>> node) const
{
   return node != nullptr && node->getColor() == RED;
}

template <typename ItemType>
int RedBlackTree<ItemType>::getHeightHelper(std::shared_ptr<RBNode<ItemType>> node) const
{
   if (node == nullptr)
      return 0;
   return 1 + std::max(getHeightHelper(node->getLeftChildPtr()),
                       getHeightHelper(node->getRightChildPtr()));
}

template <typename ItemType>
int RedBlackTree<ItemType>::getNodesHelper(std::shared_ptr<RBNode<ItemType>> node) const
{
   if (node == nullptr)
      return 0;
   return 1 + getNodesHelper(node->getLeftChildPtr()) + getNodesHelper(node->getRightChildPtr());
}

template <typename ItemType>
void RedBlackTree<ItemType>::inOrderTraversalHelper(
    std::shared_ptr<RBNode<ItemType>> node,
    std::function<void(ItemType &)> visit) const
{
   if (node == nullptr)
      return;
   inOrderTraversalHelper(node->getLeftChildPtr(), visit);
   ItemType item = node->getItem();
   visit(item);
   inOrderTraversalHelper(node->getRightChildPtr(), visit);
}

// Rotate left — returns new subtree root
// Note: colors are NOT swapped here — color fixup is handled in addHelper
//        a                  b
//       /  \      →        /  \
//      X     b            a    Z
//           / \         /  \
//          Y   Z       X    Y
template <typename ItemType>
std::shared_ptr<RBNode<ItemType>> RedBlackTree<ItemType>::rotateLeft(std::shared_ptr<RBNode<ItemType>> a)
{
   auto b = a->getRightChildPtr();
   a->setRightChildPtr(b->getLeftChildPtr());
   b->setLeftChildPtr(a);
   return b;
}

// Rotate right — returns new subtree root
// Note: colors are NOT swapped here — color fixup is handled in addHelper
//        a                 b
//       /  \      →       /  \
//      b    Z            X    a
//     / \                    /  \
//    X   Y                  Y    Z
template <typename ItemType>
std::shared_ptr<RBNode<ItemType>> RedBlackTree<ItemType>::rotateRight(std::shared_ptr<RBNode<ItemType>> a)
{
   auto b = a->getLeftChildPtr();
   a->setLeftChildPtr(b->getRightChildPtr());
   b->setRightChildPtr(a);
   return b;
}

// Recursive BST insert + canonical left-leaning RB fixup.
// This lecture uses the left-leaning representation so each 2-3-4 tree maps
// to one consistent red-black tree shape:
//
// 2-node  [B]       ->   B(black)
//
// 3-node  [A|B]     ->   B(black)
//                         /
//                      A(red)
//
// 4-node  [A|B|C]   ->    B(black)
//                         /        \
//                      A(red)    C(red)
//
// To match the lecture's proactive 2-3-4 insertion, temporary 4-nodes are
// split on the way down before recursion. After that, there are only two local
// cleanup rules on the way back up:
// Rule 0. If both children are red, flip colors to split a temporary 4-node.
//         Fires on the way DOWN (proactive), not on the way back up.
//         This differs from Sedgewick's original where all three rules fire on way up.
// Rule 1. Rotate left when a red link leans right.
// Rule 2. Rotate right when two red links lean left in a row.
//
// At each node on the way back up to G, there are 4 possible states:
//
// State A: right child red, left black → Rule 1 fixes it
//
//        G(?)                                 P(?)
//       /    \          Rule 1               /    \
//     U(b)  P(red)      →               G(red)    X
//           /  \                        /    \
//          Y    X                     U(b)    Y
//
// State B: left child red AND left-left red → Rule 2 fixes it
//
//          G(?)                               P(?)
//         /    \         Rule 2              /    \
//      P(red)  U(b)      →              X(red)   G(red)
//      /    \                                    /    \
//   X(red)   Y                                 Y     U(b)
//
// State C: both children red → valid temporary 4-node, left as-is
//
//        G(?)
//       /    \           no rule fires on the way back up —
//     P(red) U(red)      split by Rule 0 on the NEXT descent through G
//
// State D: no violation → done
//
//        G(?)
//       /    \           P is black (or null) — no rule fires
//     P(b)  U(any)
template <typename ItemType>
std::shared_ptr<RBNode<ItemType>> RedBlackTree<ItemType>::addHelper(
    std::shared_ptr<RBNode<ItemType>> node, const ItemType &newItem)
{
   // Base case: insert new red node at correct position
   if (node == nullptr)
   {
      auto newNode = std::make_shared<RBNode<ItemType>>(newItem);
      newNode->setColor(RED);
      return newNode;
   }

   // Proactively split a temporary 4-node before descending, mirroring the
   // 2-3-4 insertion strategy used elsewhere in this lecture.
   // Rule 0: split a temporary 4-node on the way DOWN.
   if (isRed(node->getLeftChildPtr()) && isRed(node->getRightChildPtr()))
   {
      node->setColor(RED);
      node->getLeftChildPtr()->setColor(BLACK);
      node->getRightChildPtr()->setColor(BLACK);
   }

   // BST insert — recurse into correct child
   if (newItem < node->getItem())
      node->setLeftChildPtr(addHelper(node->getLeftChildPtr(), newItem));
   else if (newItem > node->getItem())
      node->setRightChildPtr(addHelper(node->getRightChildPtr(), newItem));
   else
      throw std::runtime_error("Item already exists");

   // Rule 1: rotate a right-leaning red link to the left. (State A)
   //
   //        G(?)                                 P(?)
   //       /    \          Rule 1               /    \
   //     U(b)  P(red)      →               G(red)    X
   //           /  \                        /    \
   //          Y    X                     U(b)    Y
   //
   // 2-3-4 view: [G|P] should be represented with the red child on the left.
   // Preserves node's original color since it may already be RED from Rule 0.
   if (isRed(node->getRightChildPtr()) && !isRed(node->getLeftChildPtr()))
   {
      Color oldColor = node->getColor();
      node = rotateLeft(node);
      node->setColor(oldColor);
      node->getLeftChildPtr()->setColor(RED);
   }

   // Rule 2: collapse two consecutive left-leaning red links. (State B)
   //
   //          G(?)                               P(?)
   //         /    \         Rule 2              /    \
   //      P(red)  U(b)      →              X(red)   G(red)
   //      /    \                                    /    \
   //   X(red)   Y                                 Y     U(b)
   //
   // 2-3-4 view: this straight-line shape must be rotated so the middle item
   // becomes the parent of the local 3-node / temporary 4-node structure.
   // Preserves node's original color since it may already be RED from Rule 0.
   if (isRed(node->getLeftChildPtr()) && isRed(node->getLeftChildPtr()->getLeftChildPtr()))
   {
      Color oldColor = node->getColor();
      node = rotateRight(node);
      node->setColor(oldColor);
      node->getRightChildPtr()->setColor(RED);
   }

   return node;
}

// ============================================================
// Public interface
// ============================================================

template <typename ItemType>
RedBlackTree<ItemType>::RedBlackTree() : root(nullptr), numItems(0) {}

template <typename ItemType>
RedBlackTree<ItemType>::~RedBlackTree() { clear(); }

template <typename ItemType>
bool RedBlackTree<ItemType>::isEmpty() const { return numItems == 0; }
template <typename ItemType>
int RedBlackTree<ItemType>::getHeight() const { return getHeightHelper(root); }
template <typename ItemType>
int RedBlackTree<ItemType>::getNumItems() const { return numItems; }
template <typename ItemType>
std::shared_ptr<RBNode<ItemType>> RedBlackTree<ItemType>::getRoot() const { return root; }

template <typename ItemType>
bool RedBlackTree<ItemType>::contains(const ItemType &anItem) const
{
   auto current = root;
   while (current != nullptr)
   {
      if (anItem == current->getItem())
         return true;
      current = (anItem < current->getItem())
                    ? current->getLeftChildPtr()
                    : current->getRightChildPtr();
   }
   return false;
}

template <typename ItemType>
int RedBlackTree<ItemType>::getBlackDistance(const ItemType &anItem) const
{
   if (isEmpty())
      throw std::runtime_error("Tree is empty");
   if (!contains(anItem))
      throw std::runtime_error("Item not found");

   auto current = root;
   int blackDist = 0;
   while (current != nullptr)
   {
      if (current->getColor() == BLACK)
         blackDist++;
      if (anItem == current->getItem())
         return blackDist;
      current = (anItem < current->getItem())
                    ? current->getLeftChildPtr()
                    : current->getRightChildPtr();
   }
   return -1;
}

template <typename ItemType>
int RedBlackTree<ItemType>::getLevel(const ItemType &anItem) const
{
   if (isEmpty())
      throw std::runtime_error("Tree is empty");
   if (!contains(anItem))
      throw std::runtime_error("Item not found");

   auto current = root;
   int level = 0;
   while (current != nullptr)
   {
      if (anItem == current->getItem())
         return level;
      current = (anItem < current->getItem())
                    ? current->getLeftChildPtr()
                    : current->getRightChildPtr();
      level++;
   }
   return -1;
}

template <typename ItemType>
void RedBlackTree<ItemType>::printTreeCustom(const std::string &filename) const
{
   std::ofstream file(filename);
   const double verticalGap = 1.6;
   const double rootOffset = 4.0;

   file << "graph G {\n";
   file << "    layout=neato;\n";
   file << "    node [shape=circle, style=filled, fontcolor=white, fixedsize=true, width=0.5];\n";
   file << "    edge [dir=none];\n";

   std::function<void(std::shared_ptr<RBNode<ItemType>>, double, double, double)> writeNode;
   writeNode = [&](std::shared_ptr<RBNode<ItemType>> node, double x, double y, double offset)
   {
      if (!node)
         return;
      std::string color = (node->getColor() == RED) ? "red" : "black";
      file << "    \"" << node->getItem() << "\""
           << " [fillcolor=" << color << ", pos=\"" << x << "," << y << "!\"];\n";
      if (node->getLeftChildPtr())
      {
         std::string edgeStyle = (node->getLeftChildPtr()->getColor() == RED)
                                     ? " [color=red, style=dashed]"
                                     : "";
         file << "    \"" << node->getItem() << "\" -- \""
              << node->getLeftChildPtr()->getItem() << "\""
              << edgeStyle << ";\n";
         writeNode(node->getLeftChildPtr(), x - offset, y - verticalGap, offset / 2.0);
      }
      if (node->getRightChildPtr())
      {
         std::string edgeStyle = (node->getRightChildPtr()->getColor() == RED)
                                     ? " [color=red, style=dashed]"
                                     : "";
         file << "    \"" << node->getItem() << "\" -- \""
              << node->getRightChildPtr()->getItem() << "\""
              << edgeStyle << ";\n";
         writeNode(node->getRightChildPtr(), x + offset, y - verticalGap, offset / 2.0);
      }
   };

   writeNode(root, 0, 0, rootOffset);
   file << "}\n";
   file.close();
}
// Paste the generated dot file into Graphviz to visualize the tree
// Online Graphviz: https://dreampuf.github.io/GraphvizOnline/

template <typename ItemType>
ItemType RedBlackTree<ItemType>::getEntry(const ItemType &anItem) const
{
   auto current = root;
   while (current != nullptr)
   {
      if (anItem == current->getItem())
         return current->getItem();
      current = (anItem < current->getItem())
                    ? current->getLeftChildPtr()
                    : current->getRightChildPtr();
   }
   throw std::runtime_error("Item not found");
}

template <typename ItemType>
bool RedBlackTree<ItemType>::isLeaf(const ItemType &anItem) const
{
   auto current = root;
   while (current != nullptr)
   {
      if (anItem == current->getItem())
         return current->getLeftChildPtr() == nullptr &&
                current->getRightChildPtr() == nullptr;
      current = (anItem < current->getItem())
                    ? current->getLeftChildPtr()
                    : current->getRightChildPtr();
   }
   throw std::runtime_error("Item not found");
}

template <typename ItemType>
void RedBlackTree<ItemType>::inOrderTraversal(std::function<void(ItemType &)> visit) const
{
   inOrderTraversalHelper(root, visit);
}

// Build from scratch — BST insert + fix violations bottom-up via addHelper
template <typename ItemType>
void RedBlackTree<ItemType>::add(const ItemType &anItem)
{
   root = addHelper(root, anItem);
   root->setColor(BLACK); // root is always black
   numItems++;
}

// Conversion from 2-3-4 — inject a pre-built RB subtree directly,
// bypassing insertion and fixup entirely
template <typename ItemType>
void RedBlackTree<ItemType>::setRoot(std::shared_ptr<RBNode<ItemType>> node)
{
   root = node;
   if (root)
      root->setColor(BLACK); // root is always black
   numItems = getNodesHelper(root);
}

template <typename ItemType>
void RedBlackTree<ItemType>::remove(const ItemType &anItem)
{
   // BONUS TODO: implementation needed
   if (!contains(anItem))
      throw std::runtime_error("Item not found");
}

template <typename ItemType>
void RedBlackTree<ItemType>::clear()
{
   root = nullptr;
   numItems = 0;
}