#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <random>
#include "TreePrinter.hpp"

#include "TwoThreeTree.hpp"

// Try this visualization of the 2-3 tree:
// https://www.cs.usfca.edu/~galles/visualization/BTree.html

TEST_CASE("Add nodes one by one", "[TwoThreeTree]") // Lecture 22 Slides examples
{
  TwoThreeTree<int> tree;
  tree.add(30);
  tree.add(20);
  tree.add(39);
  tree.add(40);
  std::cout << "After adding 30, 20, 39, 40:" << std::endl;
  TreePrinter::printTwoThree(tree.getRoot());

  tree.add(10);
  std::cout << "After adding 10:" << std::endl;
  TreePrinter::printTwoThree(tree.getRoot());

  tree.add(38);
  std::cout << "After adding 38:" << std::endl;
  TreePrinter::printTwoThree(tree.getRoot());

  tree.add(37);
  tree.add(42);
  std::cout << "After adding 37 and 42:" << std::endl;
  TreePrinter::printTwoThree(tree.getRoot());

  tree.add(41);
  std::cout << "After adding 41:" << std::endl;
  TreePrinter::printTwoThree(tree.getRoot());

  tree.add(32);
  std::cout << "After adding 32:" << std::endl;
  TreePrinter::printTwoThree(tree.getRoot());
  REQUIRE(tree.getNumofDataItems() == 10);
}

TEST_CASE("Add skewed nodes", "[TwoThreeTree]") // Chapter 25.5 textbook examples
{
  TwoThreeTree<int> tree;
  // Adding 50,30,10,20,40,70,90,60,80,100 in sequence
  tree.add(50);
  tree.add(30);
  tree.add(10);
  tree.add(20);
  tree.add(40);
  tree.add(70);
  tree.add(90);
  tree.add(60);
  tree.add(80);
  tree.add(100);
  std::cout << "After adding 50,30,10,20,40,70,90,60,80,100:" << std::endl;
  TreePrinter::printTwoThree(tree.getRoot());
  REQUIRE(tree.getNumofDataItems() == 10);
  REQUIRE(tree.getHeight() == 3);

  tree.add(39);
  tree.add(38);
  tree.add(37);
  tree.add(36);
  tree.add(35);
  tree.add(34);
  tree.add(33);
  tree.add(32);
  std::cout << "After adding 39,38,37,36,35,34,33,32:" << std::endl;
  TreePrinter::printTwoThree(tree.getRoot());
  REQUIRE(tree.getNumofDataItems() == 18);
  REQUIRE(tree.getHeight() == 4);

  // If we add a skewed sequence (from 39 down to 32) to 2-3 tree.
  // The ending structure will still be balanced

  // Compare with BST: a skewed input into a BST would produce a degenerate linked-list-like chain,
  // but the 2-3 tree stays perfectly balanced. That's the key advantage!
}

std::vector<char> items;
void visit(char &item) { items.push_back(item); }

TEST_CASE("Add nodes in random order", "[TwoThreeTree]")
{
  TwoThreeTree<char> tree;
  std::vector<char> random_order = {'C', 'I', 'L', 'V', 'G', 'F', 'R', 'Y', 'Q', 'H', 'E', 'A', 'D', 'B', 'X', 'Z', 'U', 'J', 'S', 'T', 'W', 'K', 'O', 'M', 'N', 'P'};
  std::vector<char> sorted_values = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  for (int i = 0; i < random_order.size(); i++)
  {
    tree.add(random_order[i]);
  }
  TreePrinter::printTwoThree(tree.getRoot());

  REQUIRE(tree.contains('Z'));
  REQUIRE_FALSE(tree.contains('a'));
  REQUIRE_THROWS(tree.add('Z'));
  REQUIRE(tree.getNumofDataItems() == random_order.size());

  // TODO: print the tree and finish the following REQUIRE statements
  // Also use this example to find general formula of maximum num of data items with height h
  // Justify why node containing 'A' or 'Z' must be a leaf node?
  // REQUIRE(tree.getHeight() == ??);
  // REQUIRE(tree.getNumofNodes() == ??);
  // REQUIRE(tree.getRoot()->getSmallItem() == ?);
  // REQUIRE(tree.getRoot()->getLargeItem() == ?);
  REQUIRE(tree.isleaf('A'));
  REQUIRE(tree.isleaf('Z'));

  tree.inOrderTraversal(visit);
  REQUIRE(items == sorted_values); // verify inorder traversal matches sorted order
  items.clear();                   // reset for next test
}

TEST_CASE("Test a very important feature of 2-3 tree", "[TwoThreeTree]")
{
  TwoThreeTree<int> tree;

  // generate random 100 unique numbers from 1-500
  std::vector<int> random_unique = []
  {
    std::vector<int> v(500);
    std::iota(v.begin(), v.end(), 1);
    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});
    return std::vector<int>(v.begin(), v.begin() + 100);
  }();

  // adding to 2-3 trees
  for (int i = 0; i < random_unique.size(); i++)
  {
    tree.add(random_unique[i]);
  }
  std::cout << "After adding 100 random unique numbers:" << std::endl;
  tree.printTreeCustom(); // check terminal outputs

  bool test = true;

  // the minimum item in the tree must be on a leaf
  int somelevel = tree.getLevel(*std::min_element(random_unique.begin(), random_unique.end()));

  for (int i = 0; i < random_unique.size(); i++)
  {
    if (tree.isleaf(random_unique[i]))
    {
      if (somelevel != tree.getLevel(random_unique[i]))
      {
        test = false;
      }
    }
  }
  REQUIRE(test);
  // TODO: Which important feature is tested here?
  // 1. All additions occur at the leaf level
  // 2. All leaves are at the same level
  // 3. O(log n) worst-case search, insert, and delete.
  // 4. The tree of the same height as a BST can hold more data items than the BST.
}

TEST_CASE("Empty tree behavior", "[TwoThreeTree]")
{
  TwoThreeTree<int> tree;

  // An empty tree should report zero items, height 0, and no nodes
  REQUIRE(tree.isEmpty() == true);
  REQUIRE(tree.getNumofDataItems() == 0);
  REQUIRE(tree.getHeight() == 0);
  REQUIRE(tree.getNumofNodes() == 0);
  REQUIRE(tree.getRoot() == nullptr);

  // contains() on an empty tree must never crash — it should simply return false
  REQUIRE(tree.contains(42) == false);

  // getLevel for a missing item returns -1 (not-found sentinel)
  REQUIRE(tree.getLevel(99) == -1);
}

TEST_CASE("Single item tree", "[TwoThreeTree]")
{
  TwoThreeTree<int> tree;
  tree.add(5);

  // After one insertion the tree should have exactly one node which is also the root and a leaf
  REQUIRE(tree.isEmpty() == false);
  REQUIRE(tree.getNumofDataItems() == 1);
  REQUIRE(tree.getHeight() == 1);
  REQUIRE(tree.getNumofNodes() == 1);

  REQUIRE(tree.contains(5) == true);
  REQUIRE(tree.contains(0) == false);

  // The single item lives at level 1 and is a leaf
  REQUIRE(tree.getLevel(5) == 1);
  REQUIRE(tree.isleaf(5) == true);

  // The root is a 2-node holding only smallItem
  REQUIRE(tree.getRoot()->getSmallItem() == 5);
  REQUIRE(tree.getRoot()->isTwoNode() == true);
  REQUIRE(tree.getRoot()->isLeaf() == true);
}

TEST_CASE("Two items fill a single 3-node", "[TwoThreeTree]")
{
  TwoThreeTree<int> tree;
  tree.add(10);
  tree.add(5); // inserts as largeItem since 5 < 10 → smallItem=5, largeItem=10

  REQUIRE(tree.getNumofDataItems() == 2);
  REQUIRE(tree.getHeight() == 1);
  REQUIRE(tree.getNumofNodes() == 1);

  REQUIRE(tree.getRoot()->getSmallItem() == 5);
  REQUIRE(tree.getRoot()->getLargeItem() == 10);

  // Both items are at level 1 and are leaves
  REQUIRE(tree.getLevel(5) == 1);
  REQUIRE(tree.getLevel(10) == 1);
  REQUIRE(tree.isleaf(5) == true);
  REQUIRE(tree.isleaf(10) == true);
}

TEST_CASE("First split creates a two-level tree", "[TwoThreeTree]")
{
  // Adding a third item to a 3-node root forces the first split,
  // producing a 2-node root with two leaf children.
  TwoThreeTree<int> tree;
  tree.add(10);
  tree.add(20);
  tree.add(30); // triggers split: root becomes [20], children [10] and [30]

  REQUIRE(tree.getNumofDataItems() == 3);
  REQUIRE(tree.getHeight() == 2);
  // Now there is a root node plus two leaf children → 3 nodes total
  REQUIRE(tree.getNumofNodes() == 3);

  // Root is a 2-node whose smallItem is the median (20)
  REQUIRE(tree.getRoot()->getSmallItem() == 20);
  REQUIRE(tree.getRoot()->isTwoNode() == true);

  // 10 and 30 are leaves at level 2; 20 is the internal root at level 1
  REQUIRE(tree.getLevel(20) == 1);
  REQUIRE(tree.getLevel(10) == 2);
  REQUIRE(tree.getLevel(30) == 2);
  REQUIRE(tree.isleaf(10) == true);
  REQUIRE(tree.isleaf(30) == true);
  REQUIRE(tree.isleaf(20) == false);
}

TEST_CASE("Duplicate, or non-existent items", "[TwoThreeTree]")
{
  TwoThreeTree<int> tree;
  tree.add(1);
  tree.add(2);
  tree.add(3);

  // Adding a value already present must throw
  REQUIRE_THROWS(tree.add(1));
  REQUIRE_THROWS(tree.add(2));
  REQUIRE_THROWS(tree.add(3));

  // Item count must remain unchanged after the failed insertions
  REQUIRE(tree.getNumofDataItems() == 3);

  // 99 was never added, so getLevel must return the not-found sentinel (-1)
  REQUIRE(tree.getLevel(99) == -1);
  REQUIRE(tree.getLevel(0) == -1);
  REQUIRE(tree.getLevel(11) == -1);
}

TEST_CASE("Height grows logarithmically", "[TwoThreeTree]")
{
  // In a 2-3 tree the height is bounded by ceil(log3(n+1)) <= h <= ceil(log2(n+1))
  // where n is the number of data items in the tree.
  TwoThreeTree<int> tree;
  for (int i = 1; i <= 1000; ++i)
    tree.add(i);

  int h = tree.getHeight();
  REQUIRE(h >= 7);
  REQUIRE(h <= 10);
}

TEST_CASE("getNumofNodes is consistent with structure", "[TwoThreeTree]")
{
  // Each node holds 1 or 2 items. Therefore: numNodes <= numItems <= 2 * numNodes
  TwoThreeTree<int> tree;
  for (int i = 1; i <= 20; ++i)
    tree.add(i);

  int n = tree.getNumofDataItems();
  int nodes = tree.getNumofNodes();

  REQUIRE(nodes <= n);
  REQUIRE(n <= 2 * nodes);
}

TEST_CASE("contains and getEntry are consistent", "[TwoThreeTree]")
{
  TwoThreeTree<int> tree;
  std::vector<int> vals = {100, 50, 150, 25, 75, 125, 175};

  for (int i = 0; i < vals.size(); i++)
  {
    int v = vals[i];
    tree.add(v);
    REQUIRE(tree.contains(v) == true);
    REQUIRE(tree.getEntry(v) == v);
  }

  // Values not inserted must not be found
  REQUIRE(tree.contains(0) == false);
  REQUIRE(tree.contains(200) == false);
  REQUIRE_THROWS(tree.getEntry(0));
}

TEST_CASE("clear resets the tree completely", "[TwoThreeTree]")
{
  TwoThreeTree<int> tree;
  for (int i = 1; i <= 15; ++i)
    tree.add(i);

  REQUIRE(tree.getNumofDataItems() == 15);

  tree.clear();
  REQUIRE(tree.isEmpty() == true);
  REQUIRE(tree.getNumofDataItems() == 0);
  REQUIRE(tree.getHeight() == 0);
  REQUIRE(tree.getNumofNodes() == 0);
  REQUIRE(tree.getRoot() == nullptr);

  // After clearing, the tree should accept new insertions without issue
  tree.add(42);
  REQUIRE(tree.getNumofDataItems() == 1);
  REQUIRE(tree.contains(42) == true);
}