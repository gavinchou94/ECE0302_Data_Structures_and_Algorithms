#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "AStar.hpp"
#include "Dijkstra.hpp"
#include "Prim.hpp"

// Test the A* algorithm
TEST_CASE("AStar: Test Pathfinding")
{
  AStar<char, int> astar;
  AStar<char, int>::Graph graph = {
      {'A', {{'B', 5}, {'C', 5}}},
      {'B', {{'A', 5}, {'C', 4}, {'D', 3}}},
      {'C', {{'A', 5}, {'B', 4}, {'D', 7}, {'E', 7}, {'H', 8}}},
      {'D', {{'B', 3}, {'C', 7}, {'H', 11}, {'M', 14}, {'L', 13}, {'K', 16}}},
      {'E', {{'C', 7}, {'F', 4}, {'H', 5}}},
      {'F', {{'E', 4}, {'G', 9}}},
      {'G', {{'F', 9}, {'N', 12}}},
      {'H', {{'C', 8}, {'D', 11}, {'E', 5}, {'I', 3}}},
      {'I', {{'H', 3}, {'J', 4}}},
      {'J', {{'I', 4}, {'P', 8}, {'N', 3}}},
      {'M', {{'D', 14}, {'L', 9}, {'O', 5}}},
      {'L', {{'D', 13}, {'K', 5}, {'M', 9}, {'O', 4}}},
      {'K', {{'D', 16}, {'L', 5}, {'P', 4}, {'N', 7}}},
      {'N', {{'J', 3}, {'K', 7}, {'P', 7}}},
      {'P', {{'K', 4}, {'J', 8}, {'N', 7}}},
      {'O', {{'M', 5}, {'L', 4}}}};

  auto heuristic = [](const char &any, const char &p)
  {
    std::unordered_map<char, int> heuristics = {
        {'A', 16}, {'B', 17}, {'C', 13}, {'D', 16}, {'E', 16}, {'F', 20}, {'G', 17}, {'H', 11}, {'I', 10}, {'J', 8}, {'K', 4}, {'L', 7}, {'M', 10}, {'N', 7}, {'O', 5}, {'P', 0}};
    return heuristics.at(any);
  };

  std::vector<char> path = astar.findPath(graph, 'A', 'P', heuristic);
  REQUIRE(path[0] == 'A');
  // verify the rest of path of the class example, see lecture 25
}

// Test the Dijkstra algorithm
TEST_CASE("Dijkstra: Test Pathfinding")
{
  Dijkstra<int, int> dijkstra;
  Dijkstra<int, int>::Graph graph = {
      {0, {{1, 8}, {3, 9}, {4, 4}}},
      {1, {{2, 1}}},
      {2, {{1, 2}, {3, 3}}},
      {3, {{2, 2}, {4, 7}}},
      {4, {{2, 1}}}};

  std::unordered_map<int, int> distances = dijkstra.findShortestPaths(graph, 0);
  REQUIRE(distances[0] == 0);
  REQUIRE(distances[1] == 7);
  REQUIRE(distances[2] == 5);
  REQUIRE(distances[3] == 8);
  REQUIRE(distances[4] == 4);

  // call and verify the minimum distances from node 3 to all other nodes
  // see lecture 25
}

// Test the Prim algorithm
TEST_CASE("Prim: Test MST")
{
  Prim<char, int> prim;
  Prim<char, int>::Graph graph = {
      {'a', {{'b', 6}, {'i', 2}, {'f', 4}}},
      {'b', {{'a', 6}, {'c', 7}, {'e', 9}}},
      {'i', {{'a', 2}}},
      {'d', {{'c', 4}, {'g', 5}, {'h', 1}}},
      {'c', {{'b', 7}, {'e', 3}, {'d', 4}}},
      {'e', {{'b', 9}, {'c', 3}, {'g', 8}}},
      {'g', {{'e', 8}, {'f', 2}, {'d', 5}, {'a', 4}}},
      {'h', {{'d', 1}}},
      {'f', {{'g', 2}, {'a', 4}}}};

  std::vector<std::pair<char, char>> mst = prim.findMST(graph, 'a');

  // Add a breakpoint here to verify the MST via debugger viewer to match the class example
  // see lecture 26

  REQUIRE(mst.size() == graph.size() - 1);
}