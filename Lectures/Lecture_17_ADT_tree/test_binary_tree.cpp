/** @file test_queue.cpp
 * @author G. Zhou
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "LinkedBT.hpp"
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

   // Review getHeight() and getNumberOfNodes() and clear() functions
   // Also check the implementation of inorderhelper() and preorderhelper()
   // functions in LinkedBT.hpp

   // What benefit do recursive functions provide here and what are the base cases?
   // What are the worst and best cases recursive-level for these functions?
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
   // Finish the REQUIRE statement below:
   // REQUIRE(result == (std::vector<char>{???}));
}

TEST_CASE("Test add() handling duplicates", "[LinkedBT]")
{
   BinaryTree<int> tree;
   tree.add(1);
   tree.add(2);
   tree.add(2);
   tree.add(3);
   tree.add(2); // Adding duplicates

   // Read the codes of add() to determine the expected values
   // How does add() handle duplicates?

   // REQUIRE(tree.getNumberOfNodes() == ???);
   // REQUIRE(tree.getHeight() == ???);
   REQUIRE(tree.contains(2));
}

// Linked-based binary tree provides a lot of convenience to quickly access to child nodes.
// Therefore, only root node is needed as the private member.
// Name one scenario that linked-based binary tree is not a good choice based on such structure.
