#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "binary_search_tree.hpp"

typedef BinarySearchTree<int, int> TreeType;

/* Provided test cases */

TEST_CASE("BST: Test Insert", "[insert]")
{
    TreeType bst1;

    REQUIRE(bst1.isEmpty());

    bst1.insert(10, 10);
    REQUIRE_FALSE(bst1.isEmpty());
}

TEST_CASE("BST: Test Duplicate Insert", "[duplicate insert]")
{
    TreeType bst1;

    REQUIRE(bst1.insert(12, 12));
    REQUIRE(!bst1.insert(12, 12));
}

TEST_CASE("BST: Test Remove With No Children", "[remove]")
{
    TreeType bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);

    int item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));

    bst1.remove(5);
    REQUIRE_FALSE(bst1.retrieve(5, item));

    bst1.remove(15);
    REQUIRE_FALSE(bst1.retrieve(15, item));

    bst1.remove(10);
    REQUIRE_FALSE(bst1.retrieve(10, item));

    REQUIRE(bst1.isEmpty());
}

TEST_CASE("BST: Test Copy Assign", "[copy assign]")
{
    TreeType bst1;

    bst1.insert(50, 50);
    bst1.insert(0, 0);
    bst1.insert(100, 100);
    bst1.insert(25, 25);
    bst1.insert(75, 75);

    TreeType bst2;

    bst2 = bst1;

    bst1.destroy();

    REQUIRE(bst1.isEmpty());

    REQUIRE_FALSE(bst2.isEmpty());

    int item;
    REQUIRE(bst2.retrieve(100, item));
    REQUIRE(bst2.retrieve(75, item));
    REQUIRE(bst2.retrieve(50, item));
    REQUIRE(bst2.retrieve(25, item));
    REQUIRE_FALSE(bst2.retrieve(51, item));
}

/* Your test cases here */