/** @file test_bst.cpp
 * @author G. Zhou */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "BinarySearchTree.hpp"

TEST_CASE("BST: Adding elements to Binary Search Tree")
{
  BinarySearchTree<int> bst;

  bst.add(10);
  bst.add(5);
  bst.add(15);

  REQUIRE(bst.getRootData() == 10);
  REQUIRE(bst.getEntry(5) == 5);
  REQUIRE(bst.getEntry(15) == 15);
}

TEST_CASE("BST: Removing elements from Binary Search Tree")
{
  BinarySearchTree<int> bst;

  bst.add(10);
  bst.add(5);
  bst.add(15);

  REQUIRE(bst.remove(5) == true);
  REQUIRE_THROWS_AS(bst.getEntry(5), std::out_of_range);
}

TEST_CASE("BST: Removing non-existent element from Binary Search Tree")
{
  BinarySearchTree<int> bst;

  bst.add(10);
  bst.add(5);
  bst.add(15);

  REQUIRE(bst.remove(20) == false);
}

std::vector<int> result;
void visit(int &item)
{
  result.push_back(item);
}

TEST_CASE("BST: Removing and then checking BST properties")
{
  BinarySearchTree<int> bst;

  bst.add(10);
  bst.add(5);
  bst.add(15);
  bst.add(20);
  bst.add(19);
  bst.add(25);
  bst.add(3);
  bst.add(7);

  bst.remove(15);
  bst.remove(5);

  REQUIRE(bst.remove(5) == false);
  REQUIRE(bst.getEntry(3) == 3);
  REQUIRE(bst.getEntry(7) == 7);
  REQUIRE(bst.getRootData() == 10);

  // Inorder traversal should be sorted
  bst.inorderTraverse(visit);
  std::vector<int> expected = {3, 7, 10, 19, 20, 25};
  REQUIRE(result == expected);
  result.clear();

  // Preorder traversal should start with root
  bst.preorderTraverse(visit);
  expected = {10, 7, 3, 20, 19, 25};
  REQUIRE(result == expected);
  result.clear();

  // Postorder traversal should end with root
  bst.postorderTraverse(visit);
  expected = {3, 7, 19, 25, 20, 10};
  REQUIRE(result == expected);
  result.clear();

  bst.clear();
  REQUIRE(bst.isEmpty());
}

TEST_CASE("BST: Adding duplicate elements to Binary Search Tree")
{
  BinarySearchTree<int> bst;

  bst.add(10);
  bst.add(5);
  bst.add(15);

  // Attempt to add duplicates
  REQUIRE(bst.add(10) == false);
  REQUIRE(bst.add(5) == false);
  REQUIRE(bst.add(15) == false);

  // Tree contents should remain unchanged
  REQUIRE(bst.getEntry(10) == 10);
  REQUIRE(bst.getEntry(5) == 5);
  REQUIRE(bst.getEntry(15) == 15);
}

TEST_CASE("BST: Adding more")
{
  BinarySearchTree<int> bst;

  bst.add(20);
  bst.add(10);
  bst.add(30);
  REQUIRE(bst.getHeight() == 2);

  bst.add(5);
  REQUIRE(bst.getHeight() == 3);

  bst.add(15);
  bst.add(40);
  bst.add(12);
  bst.add(17);
  bst.add(35);
  REQUIRE(bst.getHeight() == 4);

  bst.add(11);
  bst.add(3);
  bst.remove(30);

  REQUIRE(bst.getHeight() == 5);
  REQUIRE(bst.getNumberOfNodes() == 10);
  REQUIRE(bst.getRootData() == 20);
}

TEST_CASE("BST: Adding using a sorted order")
{
  BinarySearchTree<int> bst;
  REQUIRE(bst.isEmpty());

  // Adding elements in sorted order
  bst.add(10);
  bst.add(20);
  bst.add(30);
  bst.add(40);
  bst.add(50);
  bst.add(60);
  bst.add(70);
  bst.add(80);
  bst.add(90);
  bst.add(100);

  // In the worst case, adding elements in sorted order creates a skewed tree.
  // Add a breakpoint here to report the capacity of the tree after these insertions?
  // Comparing this array/vector-based implementation to your Problem 8 linked-based implementation,
  // which approach do you think is more negatively affected in terms of performance
  // when elements are added in sorted order? Why?
}

TEST_CASE("BST: Writing and reading tree data")
{
  BinarySearchTree<int> bst;
  REQUIRE(bst.isEmpty());

  // bst.add(50);
  // bst.add(70);
  // bst.add(60);
  // bst.add(80);
  // bst.add(40);
  // bst.add(30);
  // bst.add(20);

  // std::vector<int> treeData = bst.writeTree();
  // BinarySearchTree<int> newBst;
  // newBst.readTree(treeData);

  // REQUIRE(newBst.getHeight() == 3);
  // REQUIRE(newBst.getRootData() == 50);
}