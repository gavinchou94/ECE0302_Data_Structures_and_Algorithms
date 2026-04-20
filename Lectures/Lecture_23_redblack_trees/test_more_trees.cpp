#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>

#include "catch.hpp"

#include "Convert234toRB.hpp"
#include "RedBlackTree.hpp"
#include "TreePrinter.hpp"
#include "TwoThreeFourTree.hpp"

TEST_CASE("Test 2-3-4 tree add", "[TwoThreeFourTree]") // Chapter 26.1 example
{
  TwoThreeFourTree<int> tree;
  std::vector<int> order = {10, 30, 60, 20, 50, 40, 70, 80, 15, 90, 100};
  for (int i = 0; i < order.size(); i++)
  {
    tree.add(order[i]);
  }
  TreePrinter::printTwoThreeFour(tree.getRoot());
}

TEST_CASE("TwoThreeFourTree: construct", "[construct]")
{
  TwoThreeFourTree<int> tree;
  REQUIRE(tree.isEmpty());
  REQUIRE(tree.getHeight() == 0);
  REQUIRE(tree.getNumofDataItems() == 0);
  REQUIRE(tree.getNumofNodes() == 0);
}

TEST_CASE("TwoThreeFourTree: proactive split", "[split]")
{
  TwoThreeFourTree<int> tree;

  // After 3 inserts: single 4-node root [10|30|60], height = 1
  tree.add(10);
  tree.add(30);
  tree.add(60);
  REQUIRE(tree.getHeight() == 1);
  REQUIRE(tree.getRoot()->isFourNode());

  // 4th insert splits root: 30 rises, new root [30] with children [10], [60], height = 2
  tree.add(20);
  REQUIRE(tree.getHeight() == 2);
  REQUIRE(tree.getRoot()->getSmallItem() == 30);
  REQUIRE(tree.getRoot()->isTwoNode());

  // Add until right child becomes 4-node [40|50|60], then add 70
  tree.add(50);
  tree.add(40);
  // Right child [40|50|60] splits proactively when 70 is added:
  // 50 rises into root → [30|50], 70 placed in [60|70]
  tree.add(70);
  REQUIRE(tree.getRoot()->getSmallItem() == 30);
  REQUIRE(tree.getRoot()->getLargeItem() == 50);
  REQUIRE(tree.getHeight() == 2);
}

TEST_CASE("TwoThreeFourTree: all leaves at same level", "[balance]")
{
  TwoThreeFourTree<int> tree;
  // Sorted insert is worst case for BST — 2-3-4 stays balanced
  for (int i = 1; i <= 50; i++)
  {
    tree.add(i);
  }

  bool test = true;
  int someLevel = tree.getLevel(1);
  for (int i = 1; i <= 50; i++)
  {
    if (tree.isLeaf(i))
    {
      if (someLevel != tree.getLevel(i))
      {
        test = false;
      }
    }
  }
  REQUIRE(test);
}

TEST_CASE("TwoThreeFourTree: height stays within log bounds", "[height]")
{
  TwoThreeFourTree<int> tree;
  for (int i = 1; i <= 1000; i++)
  {
    tree.add(i);
  }
  int n = tree.getNumofDataItems();
  int h = tree.getHeight();
  REQUIRE(h >= 5);  // ceil(log4(n+1))
  REQUIRE(h <= 10); // ceil(log2(n+1))
}

std::vector<int> result;
void visit(int &item) { result.push_back(item); }

TEST_CASE("TwoThreeFourTree: search and sorted traversal", "[search]")
{
  TwoThreeFourTree<int> tree;
  std::vector<int> input = {10, 30, 60, 20, 50, 40, 70, 80, 15, 90, 100};
  for (int v : input)
    tree.add(v);

  // contains and getEntry
  for (int v : input)
  {
    REQUIRE(tree.contains(v));
    REQUIRE(tree.getEntry(v) == v);
  }
  REQUIRE_FALSE(tree.contains(99));
  REQUIRE_THROWS_AS(tree.getEntry(99), std::runtime_error);

  // duplicate insert throws
  REQUIRE_THROWS_AS(tree.add(10), std::runtime_error);

  // in-order traversal must be sorted
  std::vector<int> sorted_values = input;
  std::sort(sorted_values.begin(), sorted_values.end());

  tree.inOrderTraversal(visit);
  REQUIRE(result == sorted_values);
  result.clear();
}

TEST_CASE("TwoThreeFourTree: handles zero as data", "[search]")
{
  TwoThreeFourTree<int> tree;
  std::vector<int> input = {0, -10, 10, -5, 5};
  for (int v : input)
    tree.add(v);

  std::vector<int> sorted_values = input;
  std::sort(sorted_values.begin(), sorted_values.end());

  REQUIRE(tree.contains(0));
  REQUIRE(tree.getEntry(0) == 0);
  tree.inOrderTraversal(visit);
  REQUIRE(result == sorted_values);
  result.clear();
}

TEST_CASE("TwoThreeFourTree: clear resets tree", "[clear]")
{
  TwoThreeFourTree<int> tree;
  for (int v : {10, 30, 60, 20, 50})
    tree.add(v);
  tree.clear();
  REQUIRE(tree.isEmpty());
  REQUIRE(tree.getHeight() == 0);
  REQUIRE_FALSE(tree.contains(10));
  // Can re-add after clear
  tree.add(10);
  REQUIRE(tree.contains(10));
  REQUIRE(tree.getHeight() == 1);
}

TEST_CASE("Test conversion from 2-3-4 to Red-Black Tree", "[RedBlackTree]")
{
  TwoThreeFourTree<int> tree234;
  std::vector<int> input = {100, 50, 40, 20, 70, 60, 30, 90, 39, 37, 10, 38, 35, 80, 34, 36, 33, 32};
  std::vector<int> sorted_values = input;
  std::sort(sorted_values.begin(), sorted_values.end());

  for (int v : input)
    tree234.add(v);
  TreePrinter::printTwoThreeFour(tree234.getRoot(), "2-3-4 Tree before conversion");
  tree234.printTreeCustom("../test_234tree.dot");

  RedBlackTree<int> treeRB = convertToRB(tree234);
  TreePrinter::printRedBlack(treeRB.getRoot(), "Converted Red-Black Tree");
  treeRB.printTreeCustom("../test_RBtree_converted.dot");
  REQUIRE(treeRB.getRoot() != nullptr);
  REQUIRE(treeRB.getRoot()->getColor() == BLACK);
  REQUIRE(treeRB.getNumItems() == input.size());
  treeRB.inOrderTraversal(visit);
  REQUIRE(result == sorted_values);
  result.clear();

  RedBlackTree<int> treeRB2;
  for (int v : input)
  {
    treeRB2.add(v);
  }
  TreePrinter::printRedBlack(treeRB2.getRoot(), "Red-Black Tree from direct insert");
  REQUIRE(treeRB2.getRoot() != nullptr);
  REQUIRE(treeRB2.getRoot()->getColor() == BLACK);
  REQUIRE(treeRB2.getNumItems() == input.size());
  treeRB2.inOrderTraversal(visit);
  REQUIRE(result == sorted_values);
  result.clear();
}

/**
On Wikipedia, it says:

For every 2–3–4 tree, there are corresponding red–black trees with data elements in the same order.
The insertion and deletion operations on 2–3–4 trees are also equivalent to color-flipping and rotations in red–black trees.
This makes 2–3–4 trees an important tool for understanding the logic behind red–black trees,
and this is why many introductory algorithm texts introduce 2–3–4 trees just before red–black trees,
even though 2–3–4 trees are not often used in practice.

This code implementation and test cases do not use the split/rotate/recolor conversion from a 2-3-4 tree to a red-black tree,
because that is more complicated than this course needs. Instead, we directly create a red-black tree and test its properties.

I suggest using the 2-3-4 tree and red-black tree visualizations below to understand the conversion:
https://www.cs.usfca.edu/~galles/visualization/BTree.html (2-3-4 tree, choose Max degree 4)
https://www.cs.usfca.edu/~galles/visualization/RedBlackTree.html (red-black tree)

*/

// Red-Black Tree Properties (for reference in tests below):
// 1. Every node is either red or black.
// 2. All null nodes are considered black.
// 3. A red node does not have a red child.
// 4. Every path from a given node to any of its leaf nodes
//    goes through the same number of black nodes.
// 5. If a node has exactly one child, that child must be red.

// Helper: recursively validate all 5 RB properties for a subtree.
// Returns the black-height of the subtree, or -1 if any property is violated.

TEST_CASE("RedBlackTree: construct", "[construct]")
{
  RedBlackTree<int> tree;
  REQUIRE(tree.isEmpty());
  REQUIRE(tree.getHeight() == 0);
  REQUIRE(tree.getNumItems() == 0);
  REQUIRE(tree.getRoot() == nullptr);
}

TEST_CASE("RedBlackTree: single insert, root black", "[add]")
{
  RedBlackTree<int> tree;
  tree.add(10);
  REQUIRE(tree.getRoot()->getColor() == BLACK);
  REQUIRE(tree.getRoot()->getItem() == 10);
  REQUIRE(tree.getNumItems() == 1);
}

TEST_CASE("RedBlackTree: lecture example add", "[add]")
{
  RedBlackTree<int> tree;
  REQUIRE(tree.isEmpty());

  std::vector<int> order = {55, 23, 108, 15, 40, 88, 123, 8, 17, 69, 111, 21};
  for (int v : order)
    tree.add(v);

  TreePrinter::printRedBlack(tree.getRoot());

  // Root must be black
  REQUIRE(tree.getRoot()->getColor() == BLACK);
  REQUIRE(tree.contains(123));

  // Height of a red-black tree is at most 2*log2(n+1)
  REQUIRE(tree.getHeight() <= 2 * (log2(order.size() + 1)));

  REQUIRE(tree.getNumItems() == order.size());
  REQUIRE(tree.getBlackDistance(55) == 1);
  REQUIRE(tree.getBlackDistance(123) == 3);
  REQUIRE(tree.getLevel(123) < 6);

  // Feel free to print to verify visually against lecture slides
  // tree.printTreeCustom("../test_RBtree_small.dot");

  // Duplicate insert must throw
  REQUIRE_THROWS_AS(tree.add(55), std::runtime_error);
  REQUIRE_NOTHROW(tree.add(56));

  // remove is still a stub — test throw conditions only
  REQUIRE_THROWS(tree.remove(29));  // item not in tree
  REQUIRE_NOTHROW(tree.remove(55)); // item in tree, stub just checks contains

  tree.clear();
  REQUIRE(tree.isEmpty());
  REQUIRE(tree.getNumItems() == 0);
  REQUIRE(tree.getHeight() == 0);
  REQUIRE(tree.getRoot() == nullptr);
  REQUIRE_FALSE(tree.contains(55));
  REQUIRE_THROWS(tree.remove(55)); // empty tree after clear
}

TEST_CASE("RedBlackTree: random order add", "[add]")
{
  RedBlackTree<int> tree;
  std::vector<int> order = {30, 20, 39, 40, 10, 38, 37, 42, 41, 35, 45, 60, 128, 100, 90, 80, 70, 50};
  for (int v : order)
    tree.add(v);

  // All items must be findable
  for (int v : order)
    REQUIRE(tree.contains(v));

  // Height bound must hold
  REQUIRE(tree.getHeight() <= 2 * (log2(order.size() + 1)));

  // In-order traversal must be sorted
  std::vector<int> sorted_values = order;
  std::sort(sorted_values.begin(), sorted_values.end());
  tree.inOrderTraversal(visit);
  REQUIRE(result == sorted_values);
  result.clear();
}

TEST_CASE("RedBlackTree: other functions", "[search]")
{
  RedBlackTree<int> tree;
  for (int v : {20, 10, 30, 5, 15, 25, 35})
    tree.add(v);

  // getEntry
  REQUIRE(tree.getEntry(20) == 20);
  REQUIRE(tree.getEntry(5) == 5);
  REQUIRE_THROWS_AS(tree.getEntry(99), std::runtime_error);

  // contains
  REQUIRE(tree.contains(15));
  REQUIRE_FALSE(tree.contains(99));

  // Root is never a leaf (tree has more than 1 node)
  REQUIRE_FALSE(tree.isLeaf(tree.getRoot()->getItem()));

  // getLevel — root is level 0
  REQUIRE(tree.getLevel(tree.getRoot()->getItem()) == 0);

  // getBlackDistance — root counts itself as 1
  REQUIRE(tree.getBlackDistance(tree.getRoot()->getItem()) == 1);

  // Black distance of any leaf must be >= 1 and <= height
  for (int v : {20, 10, 30, 5, 15, 25, 35})
  {
    int bd = tree.getBlackDistance(v);
    REQUIRE(bd >= 1);
    REQUIRE(bd <= tree.getHeight());
  }

  tree.clear();
  REQUIRE(tree.isEmpty());
  REQUIRE(tree.getHeight() == 0);
  REQUIRE(tree.getNumItems() == 0);
  REQUIRE(tree.getRoot() == nullptr);
  REQUIRE_FALSE(tree.contains(10));

  // Can re-add after clear
  tree.add(10);
  REQUIRE(tree.contains(10));
  REQUIRE(tree.getRoot()->getColor() == BLACK);
}

/**
Red-Black Trees are defined by the following properties:
1. Every node is either red or black.
2. All null nodes are considered black.
3. A red node does not have a red child.
4. Every path from a given node to any of its leaf nodes goes through the same number of black nodes.
5. If a node N has exactly one child, the child must be red.
*/

TEST_CASE("Test red-black tree large trees with its definition", "[RedBlackTree]")
{
  RedBlackTree<int> tree;

  // Generate 100 unique random numbers from 1 to 500
  std::vector<int> random_unique = []
  {
    std::vector<int> v(500);
    std::iota(v.begin(), v.end(), 1);
    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});
    return std::vector<int>(v.begin(), v.begin() + 100);
  }();

  // Add them to the red-black tree
  for (int i = 0; i < random_unique.size(); i++)
  {
    tree.add(random_unique[i]);
  }

  // Use max to test black distance because max must be a leaf
  int max = *std::max_element(random_unique.begin(), random_unique.end());
  int expected = tree.getBlackDistance(max);

  // Feel free to print to verify visually
  // tree.printTreeCustom("../test_RBtree_large.dot");

  bool valid1 = true;
  bool valid2 = true;
  bool valid3 = true;
  bool valid4 = true;

  std::shared_ptr<RBNode<int>> current = nullptr;
  for (int i = 0; i < random_unique.size(); i++)
  {
    // Find the pointer to each inserted item
    current = tree.getRoot();
    while (current != nullptr && current->getItem() != random_unique[i])
    {
      if (random_unique[i] < current->getItem())
      {
        current = current->getLeftChildPtr();
      }
      else
      {
        current = current->getRightChildPtr();
      }
    }

    REQUIRE(current != nullptr);

    if (current->getColor() == RED)
    {
      if (current->getLeftChildPtr() != nullptr && current->getLeftChildPtr()->getColor() == RED)
      {
        valid1 = false;
      }
      if (current->getRightChildPtr() != nullptr && current->getRightChildPtr()->getColor() == RED)
      {
        valid1 = false;
      }
    }

    if (current->hasOneChild())
    {
      if (!(current->getLeftChildPtr() == nullptr && current->getRightChildPtr()->getColor() == RED ||
            current->getRightChildPtr() == nullptr && current->getLeftChildPtr()->getColor() == RED))
      {
        valid2 = false;
      }
    }

    if (current->isLeaf())
    {
      if (tree.getBlackDistance(current->getItem()) != expected)
      {
        valid3 = false;
      }

      int distance_x = tree.getBlackDistance(current->getItem()); // Distance from root to a leaf in black nodes
      int distance_y = tree.getLevel(current->getItem()) + 1;     // Distance from root to a leaf in all nodes

      // if (distance_x ??? distance_y)
      // {
      //   valid3 = false;
      // }
    }
  }
  REQUIRE(valid1);
  REQUIRE(valid2);
  REQUIRE(valid3);
  // What important feature is tested here using these REQUIRE statements?

  // REQUIRE(valid4); // and based on your understanding of red-black trees, finish the if-block above to test valid4
}