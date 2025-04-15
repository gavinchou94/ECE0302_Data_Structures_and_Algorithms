#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "frontier_queue.hpp"
#include "puzzle_solver.hpp"

/* frontier_queue tests start here*/
TEST_CASE("Simple push test", "[frontier_queue]")
{
  frontier_queue<int> fq;
  REQUIRE(fq.empty());

  fq.push(1, 0, 1);

  REQUIRE_FALSE(fq.empty());
  REQUIRE(fq.contains(1));
}

TEST_CASE("Simple contains test", "[frontier_queue]")
{
  frontier_queue<int> fq;

  REQUIRE_FALSE(fq.contains(1));
  REQUIRE_FALSE(fq.contains(2));

  fq.push(1, 1, 1);
  fq.push(2, 2, 2);

  REQUIRE(fq.contains(1));
  REQUIRE(fq.contains(2));
  REQUIRE_FALSE(fq.contains(3));
}

TEST_CASE("Simple pop test", "[frontier_queue]")
{
  frontier_queue<int> fq;

  fq.push(1, 1, 1);

  State<int> state = fq.pop();
  REQUIRE(state.getValue() == 1);
  REQUIRE(state.getPathCost() == 1);
  REQUIRE(state.getFCost() == 2);
  REQUIRE(fq.empty());
}

TEST_CASE("Simple replaceif test", "[frontier_queue]")
{
  frontier_queue<int> fq;

  fq.push(1, 100, 100);

  fq.replaceif(1, 1);
  State<int> state = fq.pop();
  REQUIRE(state.getValue() == 1);
  REQUIRE(state.getPathCost() == 1);
  REQUIRE(state.getFCost() == 101);
}

/* Puzzle solver tests start here*/
TEST_CASE("Test-0", "[PuzzleSolver]")
{

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("012345678"));
  REQUIRE(puzzle2.fromString("012345678"));

  {
    PuzzleSolver solver(puzzle1, puzzle2);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();

    REQUIRE(found);
    REQUIRE(solution_cost == 0);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();

    REQUIRE(found);
    REQUIRE(solution_cost == 0);
  }
}

TEST_CASE("Test-1", "[PuzzleSolver]")
{

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("012345678"));
  REQUIRE(puzzle2.fromString("012345687"));
  Image<Pixel> img = puzzle1.toPicture();
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();

    REQUIRE(found);
    REQUIRE(solution_cost == 1);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();

    REQUIRE(found);
    REQUIRE(solution_cost == 1);
  }

  {
    PuzzleSolver solver(puzzle1, puzzle2);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();

    REQUIRE(found);
    REQUIRE(solution_cost == 1);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();

    REQUIRE(found);
    REQUIRE(solution_cost == 1);
  }
}

TEST_CASE("Test-2", "[PuzzleSolver]")
{

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("012345678"));
  REQUIRE(puzzle2.fromString("012345867"));

  {
    PuzzleSolver solver(puzzle1, puzzle2);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();

    REQUIRE(found);
    REQUIRE(solution_cost == 2);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();

    REQUIRE(found);
    REQUIRE(solution_cost == 2);
  }
}

TEST_CASE("Solver: Test-5", "[PuzzleSolver]")
{

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("012345678"));
  REQUIRE(puzzle2.fromString("182045367"));

  {
    PuzzleSolver solver(puzzle1, puzzle2);
    solver.DemoVisualize();
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();

    REQUIRE(found);
    REQUIRE(solution_cost == 5);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();

    REQUIRE(found);
    REQUIRE(solution_cost == 5);
  }
}

/* Write your own unit test*/