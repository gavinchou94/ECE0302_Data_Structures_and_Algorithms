#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "SpanningTree.hpp"
#include "TreePrinter.hpp"
#include <vector>
#include <iostream>

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
  for (int i = 0; i < Edges.size(); ++i)
    graph.add(Edges[i].start, Edges[i].end, Edges[i].weight);

  SpanningTree<char> dfsTree = graph.dfs_spanning('a');
  TreePrinter::printSpanningTree(dfsTree, 'a', "DFS Spanning Tree");

  REQUIRE(dfsTree.getNumVertices() == graph.getNumVertices());
  REQUIRE(dfsTree.getNumEdges() == graph.getNumVertices() - 1);

  REQUIRE(dfsTree.getEdgeWeight('a', 'b') != -1);
  REQUIRE(dfsTree.getEdgeWeight('a', 'i') != -1);
  REQUIRE(dfsTree.getEdgeWeight('b', 'c') != -1);
  REQUIRE(dfsTree.getEdgeWeight('c', 'd') != -1);
  REQUIRE(dfsTree.getEdgeWeight('d', 'g') != -1);
  REQUIRE(dfsTree.getEdgeWeight('d', 'h') != -1);
  REQUIRE(dfsTree.getEdgeWeight('e', 'g') != -1);
  REQUIRE(dfsTree.getEdgeWeight('f', 'g') != -1);

  REQUIRE(dfsTree.getEdgeWeight('a', 'f') == -1);
  REQUIRE(dfsTree.getEdgeWeight('b', 'e') == -1);
  REQUIRE(dfsTree.getEdgeWeight('c', 'e') == -1);

  int dfsCost = 0;
  for (const auto &edge : Edges)
  {
    if (dfsTree.getEdgeWeight(edge.start, edge.end) != -1)
      dfsCost += edge.weight;
  }
  std::cout << "DFS spanning tree cost: " << dfsCost << std::endl;
}

TEST_CASE("SpanningTree: BFS spanning tree has n-1 edges")
{
  SpanningTree<char> graph;
  for (int i = 0; i < Edges.size(); ++i)
    graph.add(Edges[i].start, Edges[i].end, Edges[i].weight);

  SpanningTree<char> bfsTree = graph.bfs_spanning('a');
  TreePrinter::printSpanningTree(bfsTree, 'a', "BFS Spanning Tree");

  REQUIRE(bfsTree.getNumVertices() == graph.getNumVertices());
  REQUIRE(bfsTree.getNumEdges() == graph.getNumVertices() - 1);

  REQUIRE(bfsTree.getEdgeWeight('a', 'b') != -1);
  REQUIRE(bfsTree.getEdgeWeight('a', 'i') != -1);
  REQUIRE(bfsTree.getEdgeWeight('a', 'f') != -1);
  REQUIRE(bfsTree.getEdgeWeight('b', 'c') != -1);
  REQUIRE(bfsTree.getEdgeWeight('b', 'e') != -1);
  REQUIRE(bfsTree.getEdgeWeight('c', 'd') != -1);
  REQUIRE(bfsTree.getEdgeWeight('d', 'h') != -1);
  REQUIRE(bfsTree.getEdgeWeight('f', 'g') != -1);

  REQUIRE(bfsTree.getEdgeWeight('c', 'e') == -1);
  REQUIRE(bfsTree.getEdgeWeight('d', 'g') == -1);
  REQUIRE(bfsTree.getEdgeWeight('e', 'g') == -1);

  int bfsCost = 0;
  for (const auto &edge : Edges)
  {
    if (bfsTree.getEdgeWeight(edge.start, edge.end) != -1)
      bfsCost += edge.weight;
  }
  std::cout << "BFS spanning tree cost: " << bfsCost << std::endl;
}

TEST_CASE("SpanningTree: Prim spanning tree has n-1 edges")
{
  SpanningTree<char> graph;
  for (int i = 0; i < Edges.size(); ++i)
    graph.add(Edges[i].start, Edges[i].end, Edges[i].weight);

  SpanningTree<char> primTree = graph.prim_spanning('a');
  TreePrinter::printSpanningTree(primTree, 'a', "Prim Spanning Tree");

  REQUIRE(primTree.getNumVertices() == graph.getNumVertices());
  REQUIRE(primTree.getNumEdges() == graph.getNumVertices() - 1);

  // TODO: Add more specific checks for which edges are in the Prim tree
  // and which are not, but for now just check that the total cost is indeed the minimum possible.
  // That is write your REQUIRE statements here and take screenshots of them

  int primCost = 0;
  for (const auto &edge : Edges)
  {
    if (primTree.getEdgeWeight(edge.start, edge.end) != -1)
      primCost += edge.weight;
  }
  std::cout << "Prim spanning tree cost: " << primCost << std::endl;
}