#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "graph.hpp"

TEST_CASE("Test Construction", "[construction]")
{
  Graph<int> g;
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);
}