/** @file test_binary_tree.cpp
 * @author G. Zhou*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "LinkedBT.hpp"
#include "TreePrinter.hpp"
#include <stdexcept>

TEST_CASE("Test isEmpty() for LinkedBT", "[LinkedBT]")
{
   BinaryTree<int> tree;
   REQUIRE(tree.isEmpty() == true);
}

TEST_CASE("Test add() and getRootData() for LinkedBT", "[LinkedBT]")
{
   BinaryTree<int> tree;
   tree.add(1);
   tree.add(2);
   tree.add(3);
   REQUIRE(tree.getRootData() == 1);
   tree.add(4);
   tree.add(5);
   tree.add(6);
   tree.add(7);
   REQUIRE(tree.getRootData() == 1);
}

TEST_CASE("Test getHeight() and getNumberOfNodes() for LinkedBT", "[LinkedBT]")
{
   BinaryTree<int> tree;
   tree.add(1);
   tree.add(2);
   tree.add(3);
   REQUIRE(tree.getHeight() == 3);
   REQUIRE(tree.getNumberOfNodes() == 3);
   tree.add(4);
   tree.add(5);
   tree.add(6);
   tree.add(7);
   REQUIRE(tree.getHeight() == 7);
   REQUIRE(tree.getNumberOfNodes() == 7);

   // Review getHeightHelper(), getNumberOfNodesHelper(), and clearHelper() in LinkedBT.tpp
   // Also review inorderHelper() and preorderHelper()

   // Why are recursive implementations a natural fit for tree traversal?
   // What is the base case for each of these recursive helpers?
   // What is the best-case and worst-case recursion depth, and how do they relate to tree shape?

   TreePrinter::printBST(tree.getRoot(), "General Binary Tree");
}

TEST_CASE("Test contains() for LinkedBT", "[LinkedBT]")
{
   BinaryTree<int> tree;
   tree.add(1);
   tree.add(2);
   tree.add(3);
   REQUIRE(tree.contains(1) == true);
   REQUIRE(tree.contains(2) == true);
   REQUIRE(tree.contains(3) == true);
   REQUIRE(tree.contains(4) == false);
}

TEST_CASE("Test clear() for LinkedBT", "[LinkedBT]")
{
   BinaryTree<int> tree;
   tree.add(1);
   tree.add(2);
   tree.add(3);
   REQUIRE(tree.getNumberOfNodes() == 3);
   tree.clear();
   REQUIRE(tree.isEmpty() == true);
}

// A client-defined function called visit
std::vector<char> result;
void visit(char &item)
{
   result.push_back(item);
}

TEST_CASE("Test traverse for LinkedBT", "[LinkedBT]")
{
   BinaryTree<char> tree;
   tree.add('D');
   tree.add('B');
   tree.add('C');
   tree.add('A');
   tree.add('E');
   tree.add('F');
   /*
    *         D
    *        / \
    *       B   E
    *      / \   \
    *     A   C   F
    */
   tree.preorderTraverse(visit);
   REQUIRE(result == (std::vector<char>{'D', 'B', 'A', 'C', 'E', 'F'}));
   result.clear();
   tree.inorderTraverse(visit);
   REQUIRE(result == (std::vector<char>{'A', 'B', 'C', 'D', 'E', 'F'}));
   result.clear();
   tree.postorderTraverse(visit);
   // TODO: Finish the REQUIRE statement for postorder traversal.
   // REQUIRE(result == (std::vector<char>{???}));
   TreePrinter::printBST(tree.getRoot(), "General Binary Tree");
}

TEST_CASE("Test add() handling duplicates", "[LinkedBT]")
{
   BinaryTree<int> tree;
   tree.add(1);
   tree.add(2);
   tree.add(2);
   tree.add(3);
   tree.add(2); // Adding duplicates

   // TODO: Read the codes of add() to determine the expected values
   // How does add() handle duplicates? And what is the resulting statistics of the tree?
   // REQUIRE(tree.getNumberOfNodes() == ???);
   // REQUIRE(tree.getHeight() == ???);
   REQUIRE(tree.contains(2));
   TreePrinter::printBST(tree.getRoot(), "General Binary Tree");
}