#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <random>

#include "Linked23.hpp"
#include "LinkedRB.hpp"

// Try this visualization of the 2-3 tree:
// https://www.cs.usfca.edu/~galles/visualization/BTree.html
// Try this visualization of the red-black tree:
// https://www.cs.usfca.edu/~galles/visualization/RedBlack.html

// Test lecture examples: Lecture 22
TEST_CASE("Add nodes one by one", "[Linked23]")
{
  Linked23<int> tree;
  tree.add(30);
  tree.add(20);
  tree.add(39);
  tree.add(40);
  tree.printTreeStructure();
  tree.add(10);
  tree.printTreeStructure();
  tree.add(38);
  tree.printTreeStructure();
  tree.add(37);
  tree.add(42);
  tree.printTreeStructure();
  tree.add(41);
  tree.printTreeStructure();

  REQUIRE(tree.getNumItems() == 9);
}

TEST_CASE("Add skewed nodes", "[Linked23]")
{
  Linked23<int> tree;
  for (int i = 1; i <= 31; ++i)
  {
    tree.add(i);
  }
  REQUIRE(tree.getNumItems() == 31);
  tree.printTreeStructure();

  // If we add a skewed sequence to 2-3 tree, what can you observe from its ending structure
  // Also refer to https://www.cs.usfca.edu/~galles/visualization/BTree.html to visualization
}

TEST_CASE("Add nodes in random order", "[Linked23]")
{
  Linked23<char> tree;
  std::vector<char> random_order = {'C', 'I', 'L', 'V', 'G', 'F', 'R', 'Y', 'Q', 'H', 'E', 'A', 'D', 'B', 'X', 'Z', 'U', 'J', 'S', 'T', 'W', 'K', 'O', 'M', 'N', 'P'};
  std::vector<char> sorted_values = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  for (int i = 0; i < random_order.size(); i++)
  {
    tree.add(random_order[i]);
  }
  tree.printTreeStructure();

  REQUIRE(tree.getNumItems() == random_order.size());
  // REQUIRE(tree.getHeight() == ??);
  // REQUIRE(tree.getNodeCount() == ??);

  REQUIRE(tree.contains('Z') == true);
  REQUIRE(tree.contains('a') == false);
  REQUIRE_THROWS(tree.add('Z'));

  // REQUIRE(tree.getRoot()->getSmallItem() == ?);
  // REQUIRE(tree.getRoot()->getLargeItem() == ?);

  // Report your findings of the above feature of this 2-3 tree
  // for 3-Height 2-3 tree, what are the maximum number of items? How about 4-level?

  tree.inOrderTraversal(); // you can verify the inorder traversal of the items match the sorted order
  std::cout << std::endl;

  // test getLevel
  REQUIRE(tree.getLevel('A') == 3);
  REQUIRE(tree.getLevel('B') == 3);
  REQUIRE(tree.getLevel('Y') == 3);
  REQUIRE(tree.getLevel('Z') == 3);
  REQUIRE(tree.isleaf('A'));
}

TEST_CASE("Test a very important feature of 2-3 tree", "[Linked23]")
{
  Linked23<int> tree;

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

  bool aligned = true;

  // the minimum item in the tree must be on a leaf
  int alevel = tree.getLevel(*std::min_element(random_unique.begin(), random_unique.end()));

  for (int i = 0; i < random_unique.size(); i++)
  {
    if (tree.isleaf(random_unique[i]))
    {
      if (alevel != tree.getLevel(random_unique[i]))
      {
        aligned = false;
      }
    }
  }
  REQUIRE(aligned);
  // What important feature is tested here using this REQUIRE statement?

  tree.printTreeStructure(); // check terminal outputs
}

TEST_CASE("Test remove", "[Linked23]")
{
  // Remove implementation too hard to finish before posting the codes
  // just test throw conditions

  Linked23<int> tree;
  tree.add(30);
  tree.add(20);
  tree.add(39);
  tree.add(40);
  tree.add(10);
  tree.add(38);
  tree.add(37);
  tree.add(42);
  tree.add(41);

  REQUIRE_THROWS_AS(tree.remove(29), std::invalid_argument);
  REQUIRE_NOTHROW(tree.remove(30));
}

/**
On wikipedia, it says -

For every 2–3–4 tree, there are corresponding red–black trees with data elements in the same order.
The insertion and deletion operations on 2–3–4 trees are also equivalent to color-flipping and rotations in red–black trees.
This makes 2–3–4 trees an important tool for understanding the logic behind red–black trees,
and this is why many introductory algorithm texts introduce 2–3–4 trees just before red–black trees,
even though 2–3–4 trees are not often used in practice.

This code implementation and testing cases didn't take the routes of converting 2-3-4 to red-black trees by splitting/rotating/recolor
which is too complicated for this course. Instead, we directly create a red-black tree and test its properties.

I would suggest you to play with the 2-3-4 tree and red-black tree implementations to understand the conversion:
https://www.cs.usfca.edu/~galles/visualization/BTree.html (2-3-4 tree, choose Max degree 4)
https://www.cs.usfca.edu/~galles/visualization/RedBlackTree.html (red-black tree)

For both 2-3-4 tree and red-black tree, the given codes omits the remove methods!
I would love to have volunteers to help with that :>
 */

TEST_CASE("Test red-black tree add", "[LinkedRB]")
{
  LinkedRB<int> tree;
  std::vector<int> random_order = {30, 20, 39, 40, 10, 38, 37, 42, 41, 35, 45, 60, 128, 100, 90, 80, 70, 50};
  for (int i = 0; i < random_order.size(); i++)
  {
    tree.add(random_order[i]);
  }
  tree.plotTree("../resources/test_RBtree.dot");
  // check if the root is black
  REQUIRE(tree.getRoot()->getColor() == BLACK);
}

// Test lecture examples: Lecture 23
TEST_CASE("Test red-black tree more add", "[LinkedRB]")
{
  LinkedRB<int> tree;
  REQUIRE(tree.isEmpty() == true);
  std::vector<int> random_order = {55, 23, 108, 15, 40, 88, 123, 8, 17, 69, 111, 21};
  for (int i = 0; i < random_order.size(); i++)
  {
    tree.add(random_order[i]);
  }

  // check if root is correct
  REQUIRE(tree.getRoot()->getItem() == 55);
  REQUIRE(tree.getRoot()->getColor() == BLACK);
  REQUIRE(tree.contains(111));

  // check if the height is balanced
  // the height of a red-black tree is at most 2*log2(n+1)
  REQUIRE(tree.getHeight() <= 2 * (log2(random_order.size() + 1)));

  // check if the number of items is correct
  REQUIRE(tree.getNumItems() == random_order.size());

  REQUIRE(tree.getBlackDistance(55) == 1);
  REQUIRE(tree.getBlackDistance(111) == 3);
  REQUIRE(tree.getLevel(111) == 3); // level 3 under root

  // print the tree to match the lecture example
  tree.plotTree("../resources/test_RBtree2.dot");

  REQUIRE_THROWS(tree.add(55));
  REQUIRE_NOTHROW(tree.add(56));

  // remove method is still a STUB, so just test throw conditions
  REQUIRE_THROWS(tree.remove(29));
  REQUIRE_NOTHROW(tree.remove(55));

  tree.clear();
  REQUIRE(tree.isEmpty() == true);
  REQUIRE(tree.getNumItems() == 0);
  REQUIRE(tree.getHeight() == 0);
  REQUIRE(tree.getRoot() == nullptr);
  REQUIRE(tree.contains(55) == false);
  REQUIRE_THROWS(tree.remove(55));
}

/**
Red-Black Trees are defined by the following properties:
1. Every node is either red or black.
2. All null nodes are considered black.
3. A red node does not have a red child.
4. Every path from a given node to any of its leaf nodes goes through the same number of black nodes.
5. If a node N has exactly one child, the child must be red.
*/

TEST_CASE("Test red-black tree large trees with its definition", "[LinkedRB]")
{
  LinkedRB<int> tree;

  // generate random 100 unique numbers from 1-500
  std::vector<int> random_unique = []
  {
    std::vector<int> v(500);
    std::iota(v.begin(), v.end(), 1);
    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});
    return std::vector<int>(v.begin(), v.begin() + 100);
  }();

  // adding to red-black trees
  for (int i = 0; i < random_unique.size(); i++)
  {
    tree.add(random_unique[i]);
  }

  // just use max to test the black distance since max must be a leaf
  int max = *std::max_element(random_unique.begin(), random_unique.end());
  int expected = tree.getBlackDistance(max);

  tree.plotTree("../resources/test_RBtree3.dot");

  bool valid1 = true;
  bool valid2 = true;
  bool valid3 = true;
  bool valid4 = true;

  std::shared_ptr<RedBlackNode<int>> current = nullptr;
  for (int i = 0; i < random_unique.size(); i++)
  {
    // find the ptr to each random_unique_item
    current = tree.getRoot();
    while (current->getItem() != random_unique[i] && current != nullptr)
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

      int distance_x = tree.getBlackDistance(current->getItem()); // distance from root to any leaf in terms of black nodes
      int distance_y = tree.getLevel(current->getItem()) + 1;     // distance from root to any lea terms of all nodes

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

  REQUIRE(valid4); // and based on your understanding of red-black trees, finish the if-block above to test valid4
}
