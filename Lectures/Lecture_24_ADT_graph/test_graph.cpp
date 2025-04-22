#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "LinkedGraph.hpp"

TEST_CASE("Graph: Test Construction")
{
  LinkedGraph<int> testGraph;
  REQUIRE(testGraph.getNumVertices() == 0);
  REQUIRE(testGraph.getNumEdges() == 0);
}

TEST_CASE("Graph: Test Add")
{
  LinkedGraph<int> testGraph;

  // 5--2
  REQUIRE(testGraph.add(5, 2));
  REQUIRE(testGraph.getNumVertices() == 2);
  REQUIRE(testGraph.getNumEdges() == 1);
}

TEST_CASE("Graph: Test Add More")
{
  LinkedGraph<int> testGraph;

  // create a connected graph
  // 5--2, 10--5, 2--10
  REQUIRE(testGraph.add(5, 2));
  // add an edge and a new vertex
  REQUIRE(testGraph.add(10, 5));
  REQUIRE(testGraph.getNumVertices() == 3);
  REQUIRE(testGraph.getNumEdges() == 2);
  // add a new edge, no new vertices
  REQUIRE(testGraph.add(2, 10));
  REQUIRE(testGraph.getNumVertices() == 3);
  REQUIRE(testGraph.getNumEdges() == 3);
}

TEST_CASE("Graph: Test Add Duplicate")
{
  LinkedGraph<int> testGraph;

  // 5--2, 5--2
  REQUIRE(testGraph.add(5, 2));
  REQUIRE(!testGraph.add(5, 2));
  REQUIRE(testGraph.getNumVertices() == 2);
  REQUIRE(testGraph.getNumEdges() == 1);
}

TEST_CASE("Graph: Test Undirected")
{
  LinkedGraph<int> testGraph;

  // 5--2, 2--5
  REQUIRE(testGraph.add(5, 2));
  REQUIRE(!testGraph.add(2, 5));
  REQUIRE(testGraph.getNumVertices() == 2);
  REQUIRE(testGraph.getNumEdges() == 1);
}

TEST_CASE("Graph: Test Remove")
{
  LinkedGraph<int> testGraph;

  REQUIRE(testGraph.add(5, 2));
  REQUIRE(testGraph.getNumVertices() == 2);
  REQUIRE(testGraph.getNumEdges() == 1);
  REQUIRE(testGraph.remove(5, 2));
  REQUIRE(testGraph.getNumVertices() == 0);
  REQUIRE(testGraph.getNumEdges() == 0);
}

TEST_CASE("Graph: Test Remove 2")
{
  LinkedGraph<int> testGraph;

  // create a connected graph
  //  5--2
  //  | /
  //  10
  // add the first edge
  //  5--2
  REQUIRE(testGraph.add(5, 2));
  // add an edge and a new vertex
  //  5--2
  //  |
  //  10
  REQUIRE(testGraph.add(10, 5));
  REQUIRE(testGraph.getNumVertices() == 3);
  REQUIRE(testGraph.getNumEdges() == 2);

  // add a new edge, no new vertices
  //  5--2
  //  | /
  //  10
  REQUIRE(testGraph.add(10, 2));
  REQUIRE(testGraph.getNumVertices() == 3);
  REQUIRE(testGraph.getNumEdges() == 3);
  // remove the edge but no vertices
  //  5--2
  //  |
  //  10
  REQUIRE(testGraph.remove(10, 2));
  REQUIRE(testGraph.getNumVertices() == 3);
  REQUIRE(testGraph.getNumEdges() == 2);
  // remove an edge and a vertex
  //  5--2
  REQUIRE(testGraph.remove(10, 5));
  REQUIRE(testGraph.getNumVertices() == 2);
  REQUIRE(testGraph.getNumEdges() == 1);
}

TEST_CASE("Graph: Test Remove False")
{
  LinkedGraph<int> testGraph;

  // can't remove if neither vertex exists
  REQUIRE(!testGraph.remove(5, 2));
  REQUIRE(testGraph.add(5, 2));
  // can't remove if one vertex does not exist
  REQUIRE(!testGraph.remove(10, 5));
  REQUIRE(testGraph.add(10, 5));
  REQUIRE(testGraph.add(10, 2));
  REQUIRE(testGraph.remove(5, 2));
  // can't remove an edge that does not exist
  REQUIRE(!testGraph.remove(5, 2));
}

TEST_CASE("Graph: Test Remove then Add")
{
  LinkedGraph<int> testGraph;

  REQUIRE(testGraph.add(5, 2));
  REQUIRE(testGraph.getNumVertices() == 2);
  REQUIRE(testGraph.getNumEdges() == 1);
  REQUIRE(testGraph.remove(5, 2));
  REQUIRE(testGraph.getNumVertices() == 0);
  REQUIRE(testGraph.getNumEdges() == 0);
  REQUIRE(testGraph.add(5, 2));
  REQUIRE(testGraph.getNumVertices() == 2);
  REQUIRE(testGraph.getNumEdges() == 1);
}

TEST_CASE("Graph: Test Add Disconnected")
{
  LinkedGraph<int> testGraph;

  // 5--2, 10--3, should not be allowed
  REQUIRE(testGraph.add(5, 2));
  REQUIRE(!testGraph.add(10, 3)); // would be unconnected
  REQUIRE(testGraph.getNumVertices() == 2);
  REQUIRE(testGraph.getNumEdges() == 1);
}

void print_vertex(int &i) { std::cout << i << std::endl; };

TEST_CASE("Graph: Test Breadth-First Traversal")
{
  LinkedGraph<int> testGraph;

  // create a connected graph
  //  5--2--4--3
  //  | /  /
  //  10--7
  REQUIRE(testGraph.add(5, 2));
  REQUIRE(testGraph.add(2, 4));
  REQUIRE(testGraph.add(4, 3));
  REQUIRE(testGraph.add(10, 5));
  REQUIRE(testGraph.add(10, 2));
  REQUIRE(testGraph.add(10, 7));
  REQUIRE(testGraph.add(7, 4));
  std::cout << "Breadth" << std::endl;
  testGraph.breadthFirstTraversal(5, &print_vertex);
  // what should BFS traversal order be starting at 5?
}

TEST_CASE("Graph: Test Depth-First Traversal")
{
  LinkedGraph<int> testGraph;

  // create a connected graph
  //  5--2--4--3
  //  | /  /
  //  10--7
  REQUIRE(testGraph.add(5, 2));
  REQUIRE(testGraph.add(2, 4));
  REQUIRE(testGraph.add(4, 3));
  REQUIRE(testGraph.add(10, 5));
  REQUIRE(testGraph.add(10, 2));
  REQUIRE(testGraph.add(10, 7));
  REQUIRE(testGraph.add(7, 4));
  std::cout << "Depth" << std::endl;
  testGraph.depthFirstTraversal(5, &print_vertex);
  // what should DFS traversal order be starting at 5?
}

// Describe the composition and inheritance relationship of LinkedGraph
// List all the is-a and has-a relationships.