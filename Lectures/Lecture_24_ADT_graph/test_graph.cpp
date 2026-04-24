#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "LinkedGraph.hpp"
#include <vector>
#include <string>
#include <algorithm>

// ─────────────────────────────────────────────────────────────────────────────
// Helpers
// ─────────────────────────────────────────────────────────────────────────────
// Print helpers used in traversal output tests (original style)
void print_int(int &i) { std::cout << i << "\n"; }
void print_string(std::string &s) { std::cout << s << "\n"; }

// Builds the shared 7-vertex graph used in traversal tests:
//
//   5 -- 2 -- 4 -- 3
//   |   /    /
//   10 -- 7
//
// Edges added: 5-2, 2-4, 4-3, 10-5, 10-2, 10-7, 7-4

TEST_CASE("Construction: empty graph has zero vertices and edges")
{
  LinkedGraph<int> g;
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);
}

TEST_CASE("Add: edge between two existing vertices adds no new vertices")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(5, 2));
  REQUIRE(g.add(10, 5));
  REQUIRE(g.add(2, 10));
  REQUIRE(g.getNumVertices() == 3);
  REQUIRE(g.getNumEdges() == 3);
}

TEST_CASE("Add: duplicate edge is rejected")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(5, 2));
  REQUIRE(!g.add(5, 2));
  REQUIRE(g.getNumVertices() == 2);
  REQUIRE(g.getNumEdges() == 1);

  LinkedGraph<int> g2;
  REQUIRE(g2.add(5, 2));
  REQUIRE(!g2.add(2, 5));
  REQUIRE(g2.getNumVertices() == 2);
  REQUIRE(g2.getNumEdges() == 1);
}

TEST_CASE("Self-loop: rejected")
{
  LinkedGraph<int> g;
  REQUIRE(!g.add(5, 5));
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);

  LinkedGraph<int> g2;
  REQUIRE(g2.add(5, 2));
  REQUIRE(!g2.add(5, 5));
  REQUIRE(!g2.add(2, 2));
  REQUIRE(g2.getNumVertices() == 2);
  REQUIRE(g2.getNumEdges() == 1);
}

TEST_CASE("Connectivity: edge where neither endpoint exists is rejected")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(5, 2));
  REQUIRE(!g.add(10, 3)); // Neither 10 nor 3 exist — would create isolated component
  REQUIRE(g.getNumVertices() == 2);
  REQUIRE(g.getNumEdges() == 1);
}

TEST_CASE("Connectivity: first edge on empty graph is always allowed")
{
  LinkedGraph<int> g;
  // The "neither endpoint exists" rule only applies to a non-empty graph
  REQUIRE(g.add(99, 100));
  REQUIRE(g.getNumVertices() == 2);
  REQUIRE(g.getNumEdges() == 1);
}

TEST_CASE("Weighted: edge weight is stored and retrievable in both directions")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(5, 2, 7));
  REQUIRE(g.getEdgeWeight(5, 2) == 7);
  REQUIRE(g.getEdgeWeight(2, 5) == 7); // Symmetric — undirected
}

TEST_CASE("Weighted: getEdgeWeight returns -1 for nonexistent edge or vertex")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(5, 2));
  REQUIRE(g.getEdgeWeight(5, 10) == -1); // 10 does not exist
  REQUIRE(g.getEdgeWeight(99, 1) == -1); // Neither vertex exists
}

TEST_CASE("Weighted: removed edge weight is no longer retrievable")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(1, 2, 42));
  REQUIRE(g.add(2, 3, 1)); // Keep vertex 2 connected so it isn't deleted
  REQUIRE(g.remove(1, 2));
  REQUIRE(g.getEdgeWeight(1, 2) == -1);
}

TEST_CASE("Remove: removing the only edge leaves an empty graph")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(5, 2));
  REQUIRE(g.remove(5, 2));
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);
}

TEST_CASE("Remove: edge between multi-neighbor vertices removes no vertices")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(5, 2));
  REQUIRE(g.add(10, 5));
  REQUIRE(g.add(10, 2));
  REQUIRE(g.remove(10, 2));
  REQUIRE(g.getNumVertices() == 3);
  REQUIRE(g.getNumEdges() == 2);
}

TEST_CASE("Remove: isolating a vertex causes it to be deleted")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(5, 2));
  REQUIRE(g.add(10, 5));
  REQUIRE(g.add(10, 2));
  REQUIRE(g.remove(10, 2));
  REQUIRE(g.remove(10, 5)); // 10 is now isolated -> deleted
  REQUIRE(g.getNumVertices() == 2);
  REQUIRE(g.getNumEdges() == 1);
}

TEST_CASE("Remove: fails on edge that was already removed")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(5, 2));
  REQUIRE(g.add(10, 5));
  REQUIRE(g.add(10, 2));
  REQUIRE(g.remove(5, 2));
  REQUIRE(!g.remove(5, 2));
}

TEST_CASE("Remove then Add: graph empties and accepts a fresh edge")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(5, 2));
  REQUIRE(g.remove(5, 2));
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);
  REQUIRE(g.add(5, 2));
  REQUIRE(g.getNumVertices() == 2);
  REQUIRE(g.getNumEdges() == 1);
}

TEST_CASE("Remove then Add: graph can be fully rebuilt after clearing")
{
  LinkedGraph<int> g;
  REQUIRE(g.add(1, 2));
  REQUIRE(g.add(2, 3));
  REQUIRE(g.remove(2, 3));
  REQUIRE(g.remove(1, 2));
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);

  REQUIRE(g.add(10, 20));
  REQUIRE(g.add(20, 30));
  REQUIRE(g.getNumVertices() == 3);
  REQUIRE(g.getNumEdges() == 2);
}

std::vector<char> items;
void visit(char &item) { items.push_back(item); }

TEST_CASE("String labels: BFS traversal visits all vertices")
{
  LinkedGraph<char> g;
  REQUIRE(g.add('a', 'b'));
  REQUIRE(g.add('a', 'f'));
  REQUIRE(g.add('a', 'i'));
  REQUIRE(g.add('b', 'c'));
  REQUIRE(g.add('b', 'e'));
  REQUIRE(g.add('c', 'd'));
  REQUIRE(g.add('c', 'e'));
  REQUIRE(g.add('d', 'g'));
  REQUIRE(g.add('d', 'h'));
  REQUIRE(g.add('e', 'g'));
  REQUIRE(g.add('f', 'g'));

  g.breadthFirstTraversal('a', visit);

  REQUIRE(items.size() == 9);
  REQUIRE(items == std::vector<char>({'a', 'b', 'f', 'i', 'c', 'e', 'g', 'd', 'h'})); // BFS order
  items.clear();
}

TEST_CASE("String labels: DFS traversal visits all vertices")
{
  LinkedGraph<char> g;
  REQUIRE(g.add('a', 'b'));
  REQUIRE(g.add('a', 'f'));
  REQUIRE(g.add('a', 'i'));
  REQUIRE(g.add('b', 'c'));
  REQUIRE(g.add('b', 'e'));
  REQUIRE(g.add('c', 'd'));
  REQUIRE(g.add('c', 'e'));
  REQUIRE(g.add('d', 'g'));
  REQUIRE(g.add('d', 'h'));
  REQUIRE(g.add('e', 'g'));
  REQUIRE(g.add('f', 'g'));

  g.depthFirstTraversal('a', visit);
  REQUIRE(items.size() == 9);
  REQUIRE(items == std::vector<char>({'a', 'b', 'c', 'd', 'g', 'e', 'f', 'h', 'i'})); // DFS order
  items.clear();
}

TEST_CASE("Large graph: chain of 100 vertices has correct counts")
{
  LinkedGraph<int> g;
  for (int i = 0; i < 99; i++)
    REQUIRE(g.add(i, i + 1));

  REQUIRE(g.getNumVertices() == 100);
  REQUIRE(g.getNumEdges() == 99);
}

TEST_CASE("Large graph: dense graph with cross-edges has correct counts")
{
  // Chain 0-1-2-...-49, then cross-edges every 10 steps (both endpoints already exist)
  LinkedGraph<int> g;
  for (int i = 0; i < 49; i++)
    g.add(i, i + 1);

  int crossEdges = 0;
  for (int i = 0; i + 10 < 50; i += 10)
    if (g.add(i, i + 10))
      crossEdges++;

  REQUIRE(g.getNumVertices() == 50);
  REQUIRE(g.getNumEdges() == 49 + crossEdges);
}

TEST_CASE("Large graph: bulk removal reduces counts correctly")
{
  // Two triangles sharing a vertex: 0-1-2-0, 2-3-4-2
  LinkedGraph<int> g;
  REQUIRE(g.add(0, 1));
  REQUIRE(g.add(1, 2));
  REQUIRE(g.add(2, 0));
  REQUIRE(g.add(2, 3));
  REQUIRE(g.add(3, 4));
  REQUIRE(g.add(4, 2));
  // 0 - 1
  // | /
  // 2 - 3 
  // | /
  // 4
  REQUIRE(g.getNumVertices() == 5);
  REQUIRE(g.getNumEdges() == 6);

  REQUIRE(g.remove(3, 4));
  REQUIRE(g.getNumVertices() == 5);
  REQUIRE(g.getNumEdges() == 5);

  REQUIRE(g.remove(2, 3)); // 3 isolated -> deleted
  REQUIRE(g.getNumVertices() == 4);
  REQUIRE(g.getNumEdges() == 4);

  // Remove triangle 0-1-2
  REQUIRE(g.remove(2, 0));
  REQUIRE(g.remove(1, 2));
  REQUIRE(g.remove(0, 1));
  REQUIRE(g.getNumVertices() == 2);
  REQUIRE(g.getNumEdges() == 1);

  REQUIRE(g.remove(2, 4)); // Remove last edge of 2-4, both isolated -> deleted
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);
}

TEST_CASE("Re-traversal: BFS after removing a vertex excludes it")
{
  LinkedGraph<char> g;
  REQUIRE(g.add('a', 'b'));
  REQUIRE(g.add('b', 'c'));
  REQUIRE(g.add('c', 'd'));
  REQUIRE(g.add('d', 'a'));

  g.breadthFirstTraversal('a', visit);
  REQUIRE(items.size() == 4);
  REQUIRE(items == std::vector<char>({'a', 'b', 'd', 'c'})); // BFS order
  items.clear();

  REQUIRE(g.remove('a', 'd')); // remove edge a-d, but no vertices are isolated so none are deleted
  g.breadthFirstTraversal('a', visit);
  REQUIRE(items.size() == 4);
  REQUIRE(items == std::vector<char>({'a', 'b', 'c', 'd'})); // BFS order unchanged
  items.clear();

  REQUIRE(g.remove('a', 'b')); // remove edge a-b
  g.breadthFirstTraversal('b', visit);
  REQUIRE(items.size() == 3);
  REQUIRE(items == std::vector<char>({'b', 'c', 'd'})); // BFS order after removal
  items.clear();
}