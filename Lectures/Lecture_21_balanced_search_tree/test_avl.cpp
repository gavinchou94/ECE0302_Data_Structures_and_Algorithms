#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "AVLtree.hpp"
#include "BinaryNode.hpp"
#include "TreePrinter.hpp"

// Try this visualization of the AVL tree:
// https://www.cs.usfca.edu/~galles/visualization/AVLtree.html

TEST_CASE("AVLtree: test construct", "[construct]")
{
  AVLTree<int> tree;
  REQUIRE(tree.isEmpty());
  REQUIRE(tree.getHeight() == 0);
}

// AVLtree add, (Case 1: Single left rotation)
TEST_CASE("AVLtree: test add, left rotate", "[add]") // lecture example
{
  AVLTree<int> tree;
  tree.add(20);
  tree.add(10);
  tree.add(40);
  tree.add(30);
  tree.add(50);
  REQUIRE(tree.getRootBalance() == -1);
  REQUIRE(tree.getHeight() == 3);
  REQUIRE(tree.getRoot()->getItem() == 20);
  tree.add(60);
  // After adding 60, without balancing, the tree would be (height=4):
  //       20
  //      /  \
  //    10   40
  //         / \
  //       30  50
  //            \
  //            60
  // With balancing (after 60), the tree is (height=3):
  //       40
  //      /  \
  //    20   50
  //   /  \    \
  //  10   30   60
  REQUIRE(tree.getRootBalance() == 0);
  REQUIRE(tree.getHeight() == 3);
  REQUIRE(tree.getRoot()->getItem() == 40);
  REQUIRE(tree.getRoot()->getLeftChildPtr()->getItem() == 20);
  REQUIRE(tree.getRoot()->getRightChildPtr()->getItem() == 50);
}

// AVLtree add, (Case 2: Single right rotation)
TEST_CASE("AVLtree: test add, right rotate", "[add]")
{
  AVLTree<int> tree;
  // TODO: add a node here to cause a single right rotation (choose from 20, 42, 55, 70)
  // and verify the new root, height, and root balance after rotation
  tree.add(50);
  tree.add(40);
  tree.add(60);
  tree.add(30);
  tree.add(45);

  //       50
  //      /  \
  //    40   60
  //   /  \
  //  30  45
  // tree.add(?);

  // REQUIRE(tree.getRoot()->getItem() == ?);
  // REQUIRE(tree.getHeight() == ?);
  // REQUIRE(tree.getRootBalance() == ?);
  // REQUIRE(tree.getRoot()->getLeftChildPtr()->getItem() == ?);
  // REQUIRE(tree.getRoot()->getRightChildPtr()->getItem() == ?);
}

// AVLtree add, (Case 3: left-right rotation)
TEST_CASE("AVLtree: test add, left-right rotate", "[add]")
{
  AVLTree<int> tree;
  tree.add(50);
  tree.add(30);
  tree.add(60);
  tree.add(20);
  tree.add(40);

  tree.add(35);
  // After adding 35, without balancing, the tree would be (height=4):
  //       50
  //      /  \
  //    30   60
  //   /  \
  //  20  40
  //      /
  //     35

  // With balancing (after 35), the tree is (height=3). Steps are as follows:
  // (1) Right rotation at 30
  //       50
  //      /  \
  //    40   60
  //   /  \
  //  30  35
  // /
  // 20
  // (2) Left rotation at 50
  //       40
  //      /  \
  //    30   50
  //   /  \    \
  //  20  35   60
  REQUIRE(tree.getRoot()->getItem() == 40);
  REQUIRE(tree.getHeight() == 3);
  REQUIRE(tree.getRootBalance() == 0);
  REQUIRE(tree.getRoot()->getLeftChildPtr()->getItem() == 30);
  REQUIRE(tree.getRoot()->getRightChildPtr()->getItem() == 50);
}

// AVLtree add, (Case 4: right-left rotation)
TEST_CASE("AVLtree: test add, right-left rotate", "[add]")
{
  AVLTree<int> tree;
  tree.add(20);
  tree.add(10);
  tree.add(40);
  tree.add(30);
  tree.add(50);

  tree.add(35);
  // After adding 35, without balancing, the tree would be (height=4):
  //       20
  //      /  \
  //    10   40
  //         / \
  //       30  50
  //         \
  //         35
  // With balancing (after 35), the tree is (height=3). Steps are as follows:
  // (1) Left rotation at 40
  //       20
  //      /  \
  //    10   30
  //          \
  //          40
  //          / \
  //         35  50
  // (2) Right rotation at 20
  //       30
  //      /  \
  //    20   40
  //   /     / \
  //  10    35  50
  REQUIRE(tree.getRoot()->getItem() == 30);
  REQUIRE(tree.getHeight() == 3);
  REQUIRE(tree.getRootBalance() == 0);
  REQUIRE(tree.getRoot()->getLeftChildPtr()->getItem() == 20);
  REQUIRE(tree.getRoot()->getRightChildPtr()->getItem() == 40);
}

TEST_CASE("AVLtree: test more add", "[add]") // Also lecture example
{
  // Adding 20 10 40 5 30 50 25 35 60
  AVLTree<int> tree;
  tree.add(20);
  tree.add(10);
  tree.add(40);
  tree.add(5);
  tree.add(30);
  tree.add(50);
  tree.add(25);
  tree.add(35);
  tree.add(60);
  //       20
  //      /  \
  //    10   40
  //   /     / \
  //  5     30  50
  //        / \   \
  //       25  35  60
  REQUIRE(tree.getRootBalance() == -1);
  REQUIRE(tree.getHeight() == 4);
  REQUIRE(tree.getRoot()->getItem() == 20);
  REQUIRE(tree.getRoot()->getLeftChildPtr()->getItem() == 10);
  REQUIRE(tree.getRoot()->getRightChildPtr()->getItem() == 40);

  // Adding 22
  // Which rotation case (Single left rotation, single right rotation, left-right rotation, or right-left rotation) is triggered by adding 22?
  // Refer to lecture slides on what the tree should look like after adding 22
  // TODO: finish the REQUIRE statements to verify the tree is balanced after adding 22,
  //       including the new root, height, and root balance

  tree.add(22);
  // REQUIRE(tree.getRoot()->getItem() == ?);
  // REQUIRE(tree.getHeight() == ?);
  // REQUIRE(tree.getRootBalance() == ?);
  // REQUIRE(tree.getRoot()->getLeftChildPtr()->getItem() == ?);
  // REQUIRE(tree.getRoot()->getRightChildPtr()->getItem() == ?);
}

TEST_CASE("AVLtree: test add duplicate", "[add]")
{
  AVLTree<int> tree;
  tree.add(10);
  tree.add(20);
  REQUIRE_THROWS_AS(tree.add(10), std::invalid_argument);
  REQUIRE_THROWS_AS(tree.add(20), std::invalid_argument);
}

TEST_CASE("AVLtree: test contains and getEntry", "[search]")
{
  AVLTree<int> tree;
  tree.add(20);
  tree.add(10);
  tree.add(40);
  tree.add(30);
  tree.add(50);
  REQUIRE(tree.contains(20));
  REQUIRE(tree.contains(10));
  REQUIRE(tree.contains(50));
  REQUIRE_FALSE(tree.contains(99));
  REQUIRE_FALSE(tree.contains(0));
  REQUIRE(tree.getEntry(30) == 30);
  REQUIRE_THROWS_AS(tree.getEntry(99), std::invalid_argument);
}

std::vector<int> items;
void visit(int &item)
{
  items.push_back(item);
}

TEST_CASE("AVLtree: test in-order traversal", "[inorder]")
{
  AVLTree<int> tree;
  tree.add(20);
  tree.add(10);
  tree.add(40);
  tree.add(30);
  tree.add(50);
  tree.inorderTraverse(visit);
  REQUIRE(items.size() == 5);
  REQUIRE(items[0] == 10);
  REQUIRE(items[1] == 20);
  REQUIRE(items[2] == 30);
  REQUIRE(items[3] == 40);
  REQUIRE(items[4] == 50);
  items.clear();
}

TEST_CASE("AVLtree: test skewed tree", "[skewed]")
{
  AVLTree<int> tree;
  for (int i = 0; i < 20; i++)
  {
    tree.add(i);
    // REQUIRE(??);
    // TODO: add a REQUIRE statement to verify the tree is balanced after each addition.
  }
  TreePrinter::printAVL(tree.getRoot());
}

/* Test only after implementing remove
TEST_CASE("AVLtree: test remove leaf node", "[remove]")
{
  AVLTree<int> tree;
  tree.add(20);
  tree.add(10);
  tree.add(40);
  tree.add(30);
  tree.add(50);
  //       20
  //      /  \
  //    10   40
  //         / \
  //       30  50
  // Removing a leaf node (30) should not trigger any rotation
  tree.remove(30);
  REQUIRE(tree.getHeight() == 3);
  REQUIRE(tree.getRoot()->getItem() == 20);
  REQUIRE(tree.getRootBalance() == -1);
  REQUIRE(tree.getRoot()->getRightChildPtr()->getLeftChildPtr() == nullptr);
}

TEST_CASE("AVLtree: test remove one-child node, with rebalance", "[remove]")
{
  AVLTree<int> tree;
  tree.add(20);
  tree.add(10);
  tree.add(40);
  tree.add(30);
  tree.add(50);
  tree.add(60);
  //       40
  //      /  \
  //    20   50
  //   /  \    \
  //  10   30   60
  // Removing 10 leaves 20 with only a right child (30)
  tree.remove(10);
  //       40
  //      /  \
  //    20   50
  //      \    \
  //      30   60
  // After removing 10, 20 has BF = -1, no rotation needed
  // Can you predict what the tree looks like?
  REQUIRE(tree.getRoot()->getItem() == 40);
  REQUIRE(tree.getHeight() == 3);
  REQUIRE(tree.getRootBalance() == 0);
  REQUIRE(tree.getRoot()->getLeftChildPtr()->getItem() == 20);
  REQUIRE(tree.getRoot()->getLeftChildPtr()->getLeftChildPtr() == nullptr);
  REQUIRE(tree.getRoot()->getLeftChildPtr()->getRightChildPtr()->getItem() == 30);
}

TEST_CASE("AVLtree: test remove two-children node", "[remove]")
{
  AVLTree<int> tree;
  tree.add(20);
  tree.add(10);
  tree.add(40);
  tree.add(30);
  tree.add(50);
  tree.add(60);
  //       40
  //      /  \
  //    20   50
  //   /  \    \
  //  10   30   60
  // Removing 20 (two children: 10 and 30)
  // In-order successor of 20 is 30 (leftmost of right subtree)
  // 30 replaces 20, then 30 is deleted from its original spot
  tree.remove(20);
  //       40
  //      /  \
  //    30   50
  //   /       \
  //  10        60
  // Can you predict what the tree looks like after removing 20?
  REQUIRE(tree.getRoot()->getItem() == 40);
  REQUIRE(tree.getHeight() == 3);
  REQUIRE(tree.getRoot()->getLeftChildPtr()->getItem() == 30);
  REQUIRE(tree.getRoot()->getLeftChildPtr()->getLeftChildPtr()->getItem() == 10);
}

TEST_CASE("AVLtree: test remove, cascading rotations", "[remove]")
{
  AVLTree<int> tree;
  tree.add(10);
  tree.add(5);
  tree.add(20);
  tree.add(3);
  tree.add(7);
  tree.add(15);
  tree.add(25);
  tree.add(2);
  tree.add(22);
  tree.add(28);
  tree.add(30);
  //              10
  //            /    \
  //           5      20
  //          / \    /   \
  //         3   7  15    25
  //        /         \   / \
  //       2           17 22  28
  //                           \
  //                            30
  // Removing 5 (two children: 3 and 7)
  // In-order successor of 5 is 7, copy 7 up, delete 7 from original spot
  tree.remove(5);
  REQUIRE(tree.getRootBalance() >= -1);
  REQUIRE(tree.getRootBalance() <= 1);
  // Verify the full structure after both rotations
  REQUIRE(tree.getHeight() == 4);
}

TEST_CASE("AVLtree: test remove non-existent key", "[remove]")
{
  AVLTree<int> tree;
  tree.add(10);
  tree.add(20);
  REQUIRE_THROWS_AS(tree.remove(99), std::invalid_argument);
}
*/