#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "AVLtree.hpp"
#include "BinaryNode.hpp"

// Try this visualization of the AVL tree:
// https://www.cs.usfca.edu/~galles/visualization/AVLtree.html

TEST_CASE("AVLtree: test construct", "[construct]")
{
  AVLTree<int> tree;
  REQUIRE(tree.isEmpty());
  REQUIRE(tree.getHeight() == 0);
}

// AVLtree insert, lecture examples (case 2)
TEST_CASE("AVLtree: test insert, left rotate", "[insert]")
{
  AVLTree<int> tree;
  tree.insert(20);
  tree.insert(10);
  tree.insert(40);
  tree.insert(30);
  tree.insert(50);
  REQUIRE(tree.getRootBalance() == -1);
  REQUIRE(tree.getHeight() == 3);
  REQUIRE(tree.getRoot()->getItem() == 20);

  tree.insert(60);
  // After inserting 60, without balancing, the tree would be (height=4):
  //       20
  //      /  \
  //    10   40
  //         / \
  //       30  50
  //            \
  //            60

  // with balancing (after 60), the tree is (height=3):
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

// AVLtree insert, (case 1)
TEST_CASE("AVLtree: test insert, right rotate", "[insert]")
{
  AVLTree<int> tree;

  // can you finish the following sequence of insertions that will cause a right rotation?
  // Hints: you need to add a node to the left of the left child?

  tree.insert(50);
  tree.insert(40);
  tree.insert(60);
  tree.insert(30);
  tree.insert(45);
  // tree.insert(??);
  // TODO

  // Verify using REQUIRE to show that the tree is balanced again
  // and the root is the expected value, and the height is correct
}

// Also lecture example
TEST_CASE("AVLtree: test more insert", "[insert]")
{
  // adding 20 10 40 5 30 50 25 35 60
  AVLTree<int> tree;
  tree.insert(20);
  tree.insert(10);
  tree.insert(40);
  tree.insert(5);
  tree.insert(30);
  tree.insert(50);
  tree.insert(25);
  tree.insert(35);
  tree.insert(60);

  //       20
  //      /  \
  //    10   40
  //   /  \    \
  //  5   30   50
  //      / \    \
  //    25  35   60

  REQUIRE(tree.getRootBalance() == -1);
  REQUIRE(tree.getHeight() == 4);
  REQUIRE(tree.getRoot()->getItem() == 20);
  REQUIRE(tree.getRoot()->getLeftChildPtr()->getItem() == 10);
  REQUIRE(tree.getRoot()->getRightChildPtr()->getItem() == 40);

  // adding 22
  // TODO: finish the REQUIRE statements to verify the tree is balanced
  // Refer to lecture slides on what tree should look like

  // And which case (1/2/3/4) is this?
}

TEST_CASE("AVLtree: test in-order traversal", "[inorder]")
{
  AVLTree<int> tree;
  tree.insert(20);
  tree.insert(10);
  tree.insert(40);
  tree.insert(30);
  tree.insert(50);

  tree.inOrderTraversal();
}

TEST_CASE("AVLtree: test skewed tree", "[skewed]")
{
  AVLTree<int> tree;
  for (int i = 0; i < 20; i++)
  {
    tree.insert(i);
    bool bal = (tree.getRootBalance() == 0 || tree.getRootBalance() == -1 || tree.getRootBalance() == 1);
    REQUIRE(bal);
  }
}