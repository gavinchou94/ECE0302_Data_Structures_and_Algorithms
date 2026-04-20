#ifndef TREE_PRINTER_HPP
#define TREE_PRINTER_HPP

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>


// ============================================================
//  TreePrinter — generic horizontal tree printer
//
//  Supported styles (built-in wrappers):
//
//    printBST(root)                      [42]
//    printAVL(root)                      [42 | bf:0]
//    printRedBlack(root, colorFn)        [42, R]
//    printTwoThree(root)                 [10, 20]
//    printTwoThreeFour(root)             [10, 20, 30]
//    printTrie(root)                     [c] / [c*]
//    printHeap(arr, size)                [42]  (array-backed)
//    print(root, labelFn, childrenFn)    bring-your-own lambdas
//
//  Connector style — no dashes, just spaced arms:
//
//           [39]                [20, 39]              [10, 20, 30]
//          /    \              /    |    \            /   |    |   \
//       [20]   [41]         [10]  [30]  [41]       [5] [15] [25] [35]
//
// ============================================================

namespace TreePrinter
{

  // ---- internal layout node ------------------------------------------

  struct LayoutNode
  {
    std::string label;
    std::vector<LayoutNode *> children;
    int width = 0; // computed subtree width (set by computeWidth)
  };

  // ---- low-level helper: write text into a row string ----------------

  inline void writeAt(std::string &row, int col, const std::string &text)
  {
    int end = col + (int)text.size();
    if (end > (int)row.size())
      row.resize(end, ' ');
    for (int i = 0; i < (int)text.size(); i++)
      row[col + i] = text[i];
  }

  // Gap between sibling subtrees (in characters)
  constexpr int SIBLING_GAP = 4;

  // ---- pass 1: compute minimum subtree widths ------------------------

  inline int computeWidth(LayoutNode *node)
  {
    if (!node)
      return 0;

    int labelW = (int)node->label.size();

    if (node->children.empty())
    {
      node->width = labelW;
      return labelW;
    }

    int totalChildW = 0;
    for (int i = 0; i < (int)node->children.size(); i++)
    {
      totalChildW += computeWidth(node->children[i]);
      if (i < (int)node->children.size() - 1)
        totalChildW += SIBLING_GAP;
    }

    node->width = std::max(labelW, totalChildW);
    return node->width;
  }

  // ---- pass 2: place labels and connectors top-down ------------------

  inline void buildLines(LayoutNode *node, int col, int width, int depth,
                         std::vector<std::string> &lines)
  {
    if (!node)
      return;

    // Two rows per depth level: label row then connector row.
    // Non-leaf nodes write to both rows, so allocate them up front.
    while ((int)lines.size() <= depth * 2 + 1)
      lines.push_back("");

    // Center the label within its allocated column band
    int labelCol = col + (width - (int)node->label.size()) / 2;
    int labelCenter = labelCol + (int)node->label.size() / 2;
    writeAt(lines[depth * 2], labelCol, node->label);

    if (node->children.empty())
      return;

    // ---- assign columns to children --------------------------------
    // Left-flush first, then shift the whole block to center it under
    // this node's label.
    std::vector<int> childCols, childWidths;
    int cursor = col;
    for (int i = 0; i < (int)node->children.size(); i++)
    {
      childWidths.push_back(node->children[i]->width);
      childCols.push_back(cursor);
      cursor += node->children[i]->width + SIBLING_GAP;
    }
    int blockW = cursor - col - SIBLING_GAP;
    int shift = (width - blockW) / 2;
    for (int &c : childCols)
      c += shift;

    // ---- center of each child's label (where the arm tip sits) -----
    std::vector<int> centers;
    for (int i = 0; i < (int)node->children.size(); i++)
    {
      int cw = childWidths[i];
      int lw = (int)node->children[i]->label.size();
      int lCol = childCols[i] + (cw - lw) / 2;
      centers.push_back(lCol + lw / 2);
    }

    // ---- draw connector arms: /    |    \ -------------------------
    // No horizontal dashes — each arm is placed at the child center.
    std::string &connRow = lines[depth * 2 + 1];
    int n = (int)node->children.size();

    if (n == 1)
    {
      // Single child: vertical pipe, split the difference
      writeAt(connRow, (labelCenter + centers[0]) / 2, "|");
    }
    else
    {
      for (int i = 0; i < n; i++)
      {
        std::string arm;
        if (i == 0)
          arm = "/";
        else if (i == n - 1)
          arm = "\\";
        else
          arm = "|"; // interior children
        writeAt(connRow, centers[i], arm);
      }
    }

    // ---- recurse ---------------------------------------------------
    for (int i = 0; i < n; i++)
      buildLines(node->children[i], childCols[i], childWidths[i], depth + 1, lines);
  }

  // ---- build LayoutNode tree from user's node type -------------------

  template <typename NodePtr>
  LayoutNode *buildLayout(
      NodePtr node,
      const std::function<std::string(NodePtr)> &labelFn,
      const std::function<std::vector<NodePtr>(NodePtr)> &childrenFn)
  {
    if (!node)
      return nullptr;
    auto *layout = new LayoutNode();
    layout->label = labelFn(node);
    for (NodePtr child : childrenFn(node))
      if (child)
        layout->children.push_back(buildLayout(child, labelFn, childrenFn));
    return layout;
  }

  inline void freeLayout(LayoutNode *node)
  {
    if (!node)
      return;
    for (auto *c : node->children)
      freeLayout(c);
    delete node;
  }

  // ---- public core ---------------------------------------------------

  template <typename NodePtr>
  void print(
      NodePtr root,
      const std::function<std::string(NodePtr)> &labelFn,
      const std::function<std::vector<NodePtr>(NodePtr)> &childrenFn,
      const std::string &title = "")
  {
    if (!root)
    {
      std::cout << "(empty tree)\n";
      return;
    }

    LayoutNode *layout = buildLayout(root, labelFn, childrenFn);
    computeWidth(layout);

    std::vector<std::string> lines;
    buildLines(layout, 2, layout->width + 4, 0, lines);
    freeLayout(layout);

    std::cout << "\n";
    if (!title.empty())
      std::cout << "  " << title << "\n";
    for (const std::string &line : lines)
      std::cout << line << "\n";
    std::cout << "\n";
  }

  // ================================================================
  //  Convenience wrappers
  // ================================================================

  // ----------------------------------------------------------------
  //  BST — [42]
  //
  //  Expects: ->key, ->left, ->right
  // ----------------------------------------------------------------
  template <typename BSTNode>
  void printBST(BSTNode *root, const std::string &title = "BST")
  {
    using Ptr = BSTNode *;
    print<Ptr>(
        root,
        [](Ptr n) -> std::string
        {
          return "[" + std::to_string(n->key) + "]";
        },
        [](Ptr n) -> std::vector<Ptr>
        {
          std::vector<Ptr> kids;
          if (n->left)
            kids.push_back(n->left);
          if (n->right)
            kids.push_back(n->right);
          return kids;
        },
        title);
  }

  // ----------------------------------------------------------------
  //  AVL — [42 | bf:0]
  //
  //  Expects: ->key, ->bf (int balance factor), ->left, ->right
  //  bf = height(right) - height(left):
  //    negative = left-heavy, 0 = balanced, positive = right-heavy
  // ----------------------------------------------------------------
  template <typename AVLNode>
  void printAVL(AVLNode *root, const std::string &title = "AVL Tree")
  {
    using Ptr = AVLNode *;
    print<Ptr>(
        root,
        [](Ptr n) -> std::string
        {
          std::string bf = std::to_string(n->bf);
          if (n->bf > 0)
            bf = "+" + bf;
          return "[" + std::to_string(n->key) + " | bf:" + bf + "]";
        },
        [](Ptr n) -> std::vector<Ptr>
        {
          std::vector<Ptr> kids;
          if (n->left)
            kids.push_back(n->left);
          if (n->right)
            kids.push_back(n->right);
          return kids;
        },
        title);
  }

  template <typename AVLNode>
  int avlHeight(const std::shared_ptr<AVLNode> &node)
  {
    if (!node)
      return 0;

    return 1 + std::max(avlHeight(node->getLeftChildPtr()),
                        avlHeight(node->getRightChildPtr()));
  }

  template <typename AVLNode>
  int avlBalance(const std::shared_ptr<AVLNode> &node)
  {
    if (!node)
      return 0;

    return avlHeight(node->getLeftChildPtr()) -
           avlHeight(node->getRightChildPtr());
  }

  template <typename AVLNode>
  void printAVL(const std::shared_ptr<AVLNode> &root,
                const std::string &title = "AVL Tree")
  {
    using Ptr = std::shared_ptr<AVLNode>;
    print<Ptr>(
        root,
        [](const Ptr &n) -> std::string
        {
          int balance = avlBalance(n);
          std::string bf = std::to_string(balance);
          if (balance > 0)
            bf = "+" + bf;
          return "[" + std::to_string(n->getItem()) + " | bf:" + bf + "]";
        },
        [](const Ptr &n) -> std::vector<Ptr>
        {
          std::vector<Ptr> kids;
          if (n->getLeftChildPtr())
            kids.push_back(n->getLeftChildPtr());
          if (n->getRightChildPtr())
            kids.push_back(n->getRightChildPtr());
          return kids;
        },
        title);
  }

  // ----------------------------------------------------------------
  //  Red-Black — [42, R] / [42, B]
  //
  //  Expects: ->key, ->left, ->right
  //  colorFn: lambda(Ptr) -> std::string  returning "R" or "B"
  //  Nil sentinel nodes (key == -1) are skipped automatically.
  // ----------------------------------------------------------------
  template <typename RBNode>
  void printRedBlack(RBNode *root,
                     const std::function<std::string(RBNode *)> &colorFn,
                     const std::string &title = "Red-Black Tree")
  {
    using Ptr = RBNode *;
    print<Ptr>(
        root,
        [&colorFn](Ptr n) -> std::string
        {
          return "[" + std::to_string(n->key) + ", " + colorFn(n) + "]";
        },
        [](Ptr n) -> std::vector<Ptr>
        {
          std::vector<Ptr> kids;
          if (n->left && n->left->key != -1)
            kids.push_back(n->left);
          if (n->right && n->right->key != -1)
            kids.push_back(n->right);
          return kids;
        },
        title);
  }

  template <typename RBNode>
  void printRedBlack(const std::shared_ptr<RBNode> &root,
                     const std::string &title = "Red-Black Tree")
  {
    using Ptr = std::shared_ptr<RBNode>;
    print<Ptr>(
        root,
        [](const Ptr &n) -> std::string
        {
          std::string color = (n->getColor() == RED) ? "R" : "B";
          return "[" + std::to_string(n->getItem()) + ", " + color + "]";
        },
        [](const Ptr &n) -> std::vector<Ptr>
        {
          std::vector<Ptr> kids;
          if (n->getLeftChildPtr())
            kids.push_back(n->getLeftChildPtr());
          if (n->getRightChildPtr())
            kids.push_back(n->getRightChildPtr());
          return kids;
        },
        title);
  }

  // ----------------------------------------------------------------
  //  2-3 Tree — [10, 20] / [30]
  //
  //  Works with your TriNode<ItemType> shared_ptr interface.
  //  Expects: ->getSmallItem(), ->getLargeItem(), ->isTwoNode(),
  //           ->getLeftChildPtr(), ->getMidChildPtr(), ->getRightChildPtr()
  // ----------------------------------------------------------------
  template <typename TriNodePtr>
  void printTwoThree(TriNodePtr root, const std::string &title = "2-3 Tree")
  {
    using Ptr = TriNodePtr;
    print<Ptr>(
        root,
        [](Ptr n) -> std::string
        {
          std::ostringstream oss;
          oss << "[" << n->getSmallItem();
          if (!n->isTwoNode())
            oss << ", " << n->getLargeItem();
          oss << "]";
          return oss.str();
        },
        [](Ptr n) -> std::vector<Ptr>
        {
          std::vector<Ptr> kids;
          if (n->getLeftChildPtr())
            kids.push_back(n->getLeftChildPtr());
          if (n->getMidChildPtr())
            kids.push_back(n->getMidChildPtr());
          if (n->getRightChildPtr())
            kids.push_back(n->getRightChildPtr());
          return kids;
        },
        title);
  }

  // ----------------------------------------------------------------
  //  2-3-4 Tree — [10, 20, 30] / [10, 20] / [10]
  //
  //  A 2-3-4 node holds 1–3 keys and 0 or (keys.size()+1) children.
  //  Every red-black tree has an equivalent 2-3-4 representation:
  //    Black node alone          → 2-node
  //    Black + one red child     → 3-node
  //    Black + two red children  → 4-node
  //
  //  Expects a node type with:
  //    ->keys     : std::vector<KeyType>    (1–3 items, sorted)
  //    ->children : std::vector<NodePtr>   (empty or keys.size()+1 items)
  // ----------------------------------------------------------------
  template <typename Node234>
  void printTwoThreeFour(Node234 *root, const std::string &title = "2-3-4 Tree")
  {
    using Ptr = Node234 *;
    print<Ptr>(
        root,
        [](Ptr n) -> std::string
        {
          std::ostringstream oss;
          oss << "[";
          for (int i = 0; i < (int)n->keys.size(); i++)
          {
            if (i > 0)
              oss << ", ";
            oss << n->keys[i];
          }
          oss << "]";
          return oss.str();
        },
        [](Ptr n) -> std::vector<Ptr>
        {
          std::vector<Ptr> kids;
          for (Ptr c : n->children)
            if (c)
              kids.push_back(c);
          return kids;
        },
        title);
  }

  template <typename QuadNode>
  void printTwoThreeFour(const std::shared_ptr<QuadNode> &root,
                         const std::string &title = "2-3-4 Tree")
  {
    using Ptr = std::shared_ptr<QuadNode>;
    print<Ptr>(
        root,
        [](const Ptr &n) -> std::string
        {
          std::ostringstream oss;
          oss << "[" << n->getSmallItem();
          if (n->isFourNode())
            oss << ", " << n->getMiddleItem() << ", " << n->getLargeItem();
          else if (n->isThreeNode())
            oss << ", " << n->getLargeItem();
          oss << "]";
          return oss.str();
        },
        [](const Ptr &n) -> std::vector<Ptr>
        {
          std::vector<Ptr> kids;
          if (n->getLeftChildPtr())
            kids.push_back(n->getLeftChildPtr());
          if (n->getLeftMidChildPtr())
            kids.push_back(n->getLeftMidChildPtr());
          if (n->isFourNode())
          {
            if (n->getRightMidChildPtr())
              kids.push_back(n->getRightMidChildPtr());
          }
          if (!n->isTwoNode() && n->getRightChildPtr())
            kids.push_back(n->getRightChildPtr());
          return kids;
        },
        title);
  }

  // ----------------------------------------------------------------
  //  Trie — [c] with end-of-word marker: [c*]
  //
  //  End-of-word nodes are marked with * so you can read which
  //  root-to-leaf paths form complete words.
  //
  //  Expects a node type with:
  //    ->ch       : char
  //    ->isEnd    : bool
  //    ->children : std::map<char, NodePtr>  (or any key-value iterable)
  //
  //  Use ch == '\0' for the root (displays as [root]).
  // ----------------------------------------------------------------
  template <typename TrieNode>
  void printTrie(TrieNode *root, const std::string &title = "Trie")
  {
    using Ptr = TrieNode *;
    print<Ptr>(
        root,
        [](Ptr n) -> std::string
        {
          if (n->ch == '\0')
            return "[root]";
          std::string s = "[";
          s += n->ch;
          if (n->isEnd)
            s += "*";
          s += "]";
          return s;
        },
        [](Ptr n) -> std::vector<Ptr>
        {
          std::vector<Ptr> kids;
          for (auto &kv : n->children)
            if (kv.second)
              kids.push_back(kv.second);
          return kids;
        },
        title);
  }

  // ----------------------------------------------------------------
  //  Binary Heap — [42]  (array-backed, shown as an implicit tree)
  //
  //  Reconstructs the implicit binary tree from the array:
  //    left child of i  = 2i + 1
  //    right child of i = 2i + 2
  //  Works for both min-heaps and max-heaps.
  //
  //  Usage:
  //    std::vector<int> h = {90, 70, 80, 40, 60, 50, 10};
  //    TreePrinter::printHeap(h);
  // ----------------------------------------------------------------
  template <typename T>
  void printHeap(const T *arr, int size, const std::string &title = "Heap")
  {
    if (size <= 0)
    {
      std::cout << "(empty heap)\n";
      return;
    }

    // Build one LayoutNode per array index
    std::vector<LayoutNode *> nodes(size, nullptr);
    for (int i = 0; i < size; i++)
    {
      nodes[i] = new LayoutNode();
      nodes[i]->label = "[" + std::to_string(arr[i]) + "]";
    }
    // Wire children (left-child and right-child of each index)
    for (int i = 0; i < size; i++)
    {
      int l = 2 * i + 1, r = 2 * i + 2;
      if (l < size)
        nodes[i]->children.push_back(nodes[l]);
      if (r < size)
        nodes[i]->children.push_back(nodes[r]);
    }

    computeWidth(nodes[0]);

    std::vector<std::string> lines;
    buildLines(nodes[0], 2, nodes[0]->width + 4, 0, lines);

    // Free structs without double-freeing shared children
    for (auto *nd : nodes)
    {
      nd->children.clear();
      delete nd;
    }

    std::cout << "\n";
    if (!title.empty())
      std::cout << "  " << title << "\n";
    for (const std::string &line : lines)
      std::cout << line << "\n";
    std::cout << "\n";
  }

  template <typename T>
  void printHeap(const std::vector<T> &v, const std::string &title = "Heap")
  {
    printHeap(v.data(), (int)v.size(), title);
  }

} // namespace TreePrinter

#endif // TREE_PRINTER_HPP