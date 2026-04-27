#define CATCH_CONFIG_MAIN

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include "catch.hpp"
#include "Final.hpp"

// If not running on Codespace or not having the same file structure,
// you may need to just comment out the following line

// Lecture 15 - Queue & Deque
#include "ArrayQueue.hpp"
#include "RingDeque.hpp"
#include "LinkedDeque.hpp"
#include "evaluate_postfix.hpp"

// Lecture 16 - Priority Queue
#include "ArrayPQ.hpp"

// Lecture 17 - Binary Tree
#include "LinkedBT.hpp"
#include "TreePrinter.hpp"

// Lecture 18 - BST
#include "BinarySearchTree.hpp"

// Lecture 19 - Heap
#include "TreeMinHeap.hpp"

// Lecture 20 - Map
#include "ArrayMap.hpp"
#include "TreeMap.hpp"
#include "HashedMap.hpp"

// Lecture 21 - AVL Tree
#include "AVLtree.hpp"
#include "BinaryNode.hpp"

// Lecture 22 - 2-3 Tree
#include "TwoThreeTree.hpp"

// Lecture 23 - Red-Black Tree & 2-3-4 Tree
#include "TwoThreeFourTree.hpp"
#include "Convert234toRB.hpp"
#include "RedBlackTree.hpp"

// Lecture 24 - Graph
#include "LinkedGraph.hpp"

// Lecture 25 - Graph Search
#include "GraphSearch.hpp"

// Lecture 26 - Spanning Tree
#include "SpanningTree.hpp"

// ── Lecture 15 ──────────────────────────────────────────────────────────────
TEST_CASE("Test isEmpty() for ArrayQueue", "[ArrayQueue]")
{
    ArrayQueue<int> queue;
    REQUIRE(queue.isEmpty() == true);
}

// ── Lecture 16 ──────────────────────────────────────────────────────────────
TEST_CASE("Test isEmpty() for ArrayPQ", "[ArrayPQ]")
{
    ArrayPQ<int> pq;
    REQUIRE(pq.isEmpty() == true);
}

// ── Lecture 17 ──────────────────────────────────────────────────────────────
TEST_CASE("Test isEmpty() for LinkedBT", "[LinkedBT]")
{
    BinaryTree<int> tree;
    REQUIRE(tree.isEmpty() == true);
}

// ── Lecture 18 ──────────────────────────────────────────────────────────────
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

// ── Lecture 19 ──────────────────────────────────────────────────────────────
TEST_CASE("Heap: test construct", "[construct]")
{
    TreeMinHeap<int> heap;
    REQUIRE(heap.getNumberOfNodes() == 0);
    REQUIRE(heap.isEmpty() == true);
}

// ── Lecture 20 ──────────────────────────────────────────────────────────────
TEST_CASE("ArrayMap -- basic Map contract", "[ArrayMap]")
{
    ArrayMap<int, std::string> map;
    REQUIRE(map.isEmpty());
    REQUIRE(map.getNumberOfItems() == 0);

    REQUIRE(map.add(1, "one"));
    REQUIRE(map.add(2, "two"));
    REQUIRE(map.add(3, "three"));
    REQUIRE(!map.isEmpty());
    REQUIRE(map.getNumberOfItems() == 3);

    REQUIRE_FALSE(map.add(1, "uno"));
    REQUIRE(map.getNumberOfItems() == 3);

    REQUIRE(map.contains(1));
    REQUIRE_FALSE(map.contains(4));

    REQUIRE(map.getItem(1) == "one");
    REQUIRE_THROWS_AS(map.getItem(4), std::invalid_argument);

    REQUIRE(map.remove(2));
    REQUIRE_FALSE(map.contains(2));
    REQUIRE(map.getNumberOfItems() == 2);

    map.clear();
    REQUIRE(map.isEmpty());
}

// ── Lecture 21 ──────────────────────────────────────────────────────────────
TEST_CASE("AVLtree: test construct", "[construct]")
{
    AVLTree<int> tree;
    REQUIRE(tree.isEmpty());
    REQUIRE(tree.getHeight() == 0);
}

// ── Lecture 22 ──────────────────────────────────────────────────────────────
TEST_CASE("Empty tree behavior", "[TwoThreeTree]")
{
    TwoThreeTree<int> tree;
    REQUIRE(tree.isEmpty() == true);
    REQUIRE(tree.getNumofDataItems() == 0);
    REQUIRE(tree.getHeight() == 0);
    REQUIRE(tree.getNumofNodes() == 0);
    REQUIRE(tree.getRoot() == nullptr);
    REQUIRE(tree.contains(42) == false);
    REQUIRE(tree.getLevel(99) == -1);
}

// ── Lecture 23 ──────────────────────────────────────────────────────────────
TEST_CASE("RedBlackTree: construct", "[construct]")
{
    RedBlackTree<int> tree;
    REQUIRE(tree.isEmpty());
    REQUIRE(tree.getHeight() == 0);
    REQUIRE(tree.getNumItems() == 0);
    REQUIRE(tree.getRoot() == nullptr);
}

// ── Lecture 24 ──────────────────────────────────────────────────────────────
TEST_CASE("Construction: empty graph has zero vertices and edges")
{
    LinkedGraph<int> g;
    REQUIRE(g.getNumVertices() == 0);
    REQUIRE(g.getNumEdges() == 0);
}

// ── Lecture 25 ──────────────────────────────────────────────────────────────
TEST_CASE("GraphSearch: Test Dijkstra Distances")
{
    GraphSearch<char> graph;
    graph.add('0', '1', 8);
    graph.add('0', '3', 9);
    graph.add('0', '4', 4);
    graph.add('1', '2', 1);
    graph.add('2', '3', 3);
    graph.add('3', '4', 7);
    graph.add('4', '2', 1);

    std::unordered_map<char, int> distances = graph.dijkstra('0');
    REQUIRE(distances['0'] == 0);
    REQUIRE(distances['1'] == 6);
    REQUIRE(distances['2'] == 5);
    REQUIRE(distances['3'] == 8);
    REQUIRE(distances['4'] == 4);
}

// ── Lecture 26 ──────────────────────────────────────────────────────────────
struct WeightedEdge
{
    char start;
    char end;
    int weight;
};

std::vector<WeightedEdge> Edges = {
    {'a', 'b', 6},
    {'a', 'i', 2},
    {'a', 'f', 4},
    {'b', 'c', 7},
    {'b', 'e', 9},
    {'c', 'e', 3},
    {'c', 'd', 4},
    {'d', 'g', 5},
    {'d', 'h', 1},
    {'e', 'g', 8},
    {'g', 'f', 2},
};

TEST_CASE("SpanningTree: DFS spanning tree has n-1 edges")
{
    SpanningTree<char> graph;
    for (int i = 0; i < (int)Edges.size(); ++i)
        graph.add(Edges[i].start, Edges[i].end, Edges[i].weight);

    SpanningTree<char> dfsTree = graph.dfs_spanning('a');
    TreePrinter::printSpanningTree(dfsTree, 'a', "DFS Spanning Tree");

    REQUIRE(dfsTree.getNumVertices() == graph.getNumVertices());
    REQUIRE(dfsTree.getNumEdges() == graph.getNumVertices() - 1);
}