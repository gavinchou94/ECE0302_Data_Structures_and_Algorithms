/** @file test_bst.cpp
 * @author G. Zhou
 */

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

  REQUIRE(bst.remove(20) == false); // 20 does not exist in the tree
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

  REQUIRE(bst.remove(5) == false); // Remove a node with children
  REQUIRE(bst.getEntry(3) == 3);   // Ensure remaining nodes are intact
  REQUIRE(bst.getEntry(7) == 7);
  REQUIRE(bst.getRootData() == 10); // Root should remain unchanged

  bst.inorderTraverse(visit);
  std::vector<int> expected = {3, 7, 10, 19, 20, 25}; // Inorder traversal should be sorted
  REQUIRE(result == expected);
  result.clear(); // Clear the result for next test

  bst.preorderTraverse(visit);
  expected = {10, 7, 3, 20, 19, 25}; // Preorder traversal should start with root
  REQUIRE(result == expected);
  result.clear();

  bst.postorderTraverse(visit);
  expected = {3, 7, 19, 25, 20, 10}; // Postorder traversal should end with root
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
  REQUIRE(bst.add(10) == false); // 10 already exists
  REQUIRE(bst.add(5) == false);  // 5 already exists
  REQUIRE(bst.add(15) == false); // 15 already exists

  // Check the size of the tree remains unchanged
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
  // Check if the size of the tree is correct
  REQUIRE(bst.getHeight() == 5);         // Height should be 5 for this tree
  REQUIRE(bst.getNumberOfNodes() == 10); // Total nodes should be 10
  // Check if the root is correct
  REQUIRE(bst.getRootData() == 20); // Root should be 20
}

TEST_CASE("BST: Adding using a sorted order")
{
  BinarySearchTree<int> bst;
  REQUIRE(bst.isEmpty()); // Start with an empty tree
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

  // In worst case, we add elements in sorted order, which creates a skewed tree.
  // Report the capacity of the here!!

  // Based on the implementation details and your Programming Problem 7 implementation,
  // which method do you think gets its performance affected more if we add elements in sorted order?
  // Explain why.
}