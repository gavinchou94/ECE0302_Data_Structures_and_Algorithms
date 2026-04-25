#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "GraphSearch.hpp"

int heuristicToP(const char &current, const char &)
{
  std::unordered_map<char, int> heuristics = {
      {'A', 16}, {'B', 17}, {'C', 13}, {'D', 16}, {'E', 16}, {'F', 20}, {'G', 17}, {'H', 11}, {'I', 10}, {'J', 8}, {'K', 4}, {'L', 7}, {'M', 10}, {'N', 7}, {'O', 5}, {'P', 0}};
  return heuristics.at(current);
}

TEST_CASE("GraphSearch: Test A* Pathfinding")
{
  GraphSearch<char> graph;
  graph.add('A', 'B', 5);
  graph.add('A', 'C', 5);
  graph.add('B', 'C', 4);
  graph.add('B', 'D', 3);
  graph.add('C', 'D', 7);
  graph.add('C', 'E', 7);
  graph.add('C', 'H', 8);
  graph.add('D', 'H', 11);
  graph.add('D', 'M', 14);
  graph.add('D', 'L', 13);
  graph.add('D', 'K', 16);
  graph.add('E', 'F', 4);
  graph.add('E', 'H', 5);
  graph.add('F', 'G', 9);
  graph.add('G', 'N', 12);
  graph.add('H', 'I', 3);
  graph.add('I', 'J', 4);
  graph.add('J', 'P', 8);
  graph.add('J', 'N', 3);
  graph.add('M', 'L', 9);
  graph.add('M', 'O', 5);
  graph.add('L', 'K', 5);
  graph.add('L', 'O', 4);
  graph.add('K', 'P', 4);
  graph.add('K', 'N', 7);
  graph.add('N', 'P', 7);

  std::vector<char> path = graph.AStarSearch('A', 'P', heuristicToP);
  std::vector<char> expectedPath = {'A', 'C', 'H', 'I', 'J', 'P'};
  REQUIRE(path == expectedPath);

  // TODO: Comment here why you don't even need to run the code to extract the
  // shortest path from C to P, then use the REQUIRE statement to check that the path is correct.
  // Take a screenshot of your comment and the REQUIRE statement here.
}

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

  // find shortest distance from vertex 0 to every reachable vertex
  std::unordered_map<char, int> distances = graph.dijkstra('0');

  REQUIRE(distances['0'] == 0);
  REQUIRE(distances['1'] == 6);
  REQUIRE(distances['2'] == 5);
  REQUIRE(distances['3'] == 8);
  REQUIRE(distances['4'] == 4);

  // TODO: Verify the minimum distances from vertex 3 to all other vertices using REQUIRE statements.
  // Take a screenshot of these REQUIRE statements and upload it.
  distances = graph.dijkstra('3');
}

TEST_CASE("Test that Dijkstra_from_AStar and regular Dijkstra")
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
  int distance0to1 = distances['1'];
  int distance0to2 = distances['2'];
  int distance0to3 = distances['3'];
  int distance0to4 = distances['4'];

  std::vector<char> pathDijkstra0to1 = graph.Dijkstra_from_AStar('0', '1');
  int cost0to1 = 0;
  for (int i = 0; i + 1 < pathDijkstra0to1.size(); ++i)
  {
    cost0to1 += graph.getEdgeWeight(pathDijkstra0to1[i], pathDijkstra0to1[i + 1]);
  }
  REQUIRE(cost0to1 == distance0to1);

  std::vector<char> pathDijkstra0to2 = graph.Dijkstra_from_AStar('0', '2');
  int cost0to2 = 0;
  for (int i = 0; i + 1 < pathDijkstra0to2.size(); ++i)
  {
    cost0to2 += graph.getEdgeWeight(pathDijkstra0to2[i], pathDijkstra0to2[i + 1]);
  }
  REQUIRE(cost0to2 == distance0to2);

  std::vector<char> pathDijkstra0to3 = graph.Dijkstra_from_AStar('0', '3');
  int cost0to3 = 0;
  for (int i = 0; i + 1 < pathDijkstra0to3.size(); ++i)
  {
    cost0to3 += graph.getEdgeWeight(pathDijkstra0to3[i], pathDijkstra0to3[i + 1]);
  }
  REQUIRE(cost0to3 == distance0to3);

  std::vector<char> pathDijkstra0to4 = graph.Dijkstra_from_AStar('0', '4');
  int cost0to4 = 0;
  for (int i = 0; i + 1 < pathDijkstra0to4.size(); ++i)
  {
    cost0to4 += graph.getEdgeWeight(pathDijkstra0to4[i], pathDijkstra0to4[i + 1]);
  }
  REQUIRE(cost0to4 == distance0to4);

  // TODO: What exactly are we verifying in this test case?
  // Justify your answer using both your understanding of the algorithms and the implementation in GraphSearch.tpp.

  // Also explain why std::priority_queue and std::map are used so frequently
  // in Lectures 25 and 26 graph search code, and which operations does each of
  // them support our task the most so they become a good fit for graph search algorithms.
}