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

/** Two time-consuming tests are given here for your reference.
  * Uncomment them to try locally
  * The test case of cost 31 should be executed within 1 minute locally to avoid timeout on the autograder.

TEST_CASE("Puzzle: solve puzzle of cost=8 and show procedures", "[PuzzleSolver]")
{

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456780"));
  REQUIRE(puzzle2.fromString("012563478"));
  REQUIRE(puzzle1 != puzzle2);
  REQUIRE(puzzle1.heuristic(puzzle2) == 12); // heuristic also takes into account of the distance of the blank tile

  PuzzleSolver solver(puzzle2, puzzle1);
  bool found;
  std::size_t solution_cost;
  std::tie(found, solution_cost) = solver.search();

  REQUIRE(found);
  REQUIRE(solution_cost == 8);

  std::pair<bool, Puzzle> curr_result = std::make_pair(true, puzzle2);
  std::vector<Puzzle::Action> actions = {Puzzle::RIGHT, Puzzle::RIGHT, Puzzle::DOWN, Puzzle::LEFT, Puzzle::LEFT, Puzzle::DOWN, Puzzle::RIGHT, Puzzle::RIGHT};
  for (int i = 0; i < actions.size(); ++i)
  {
    curr_result = curr_result.second.apply(actions[i]);
    REQUIRE(curr_result.first);

    Puzzle result = curr_result.second;
    bool found;
    std::size_t solution_cost;
    PuzzleSolver solver(result, puzzle1);
    std::tie(found, solution_cost) = solver.search();
    REQUIRE(found);
    REQUIRE(solution_cost == 8 - (i + 1));                   // Check if the cost decreases by 1 for each action
    REQUIRE(result.heuristic(puzzle1) <= solution_cost + 4); // Check if the heuristic is always admissible
  }
  REQUIRE(curr_result.second == puzzle1); // Check if the final state is the goal state
}

TEST_CASE("Puzzle: testing the puzzle solver limit of cost=31", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456780"));
  REQUIRE(puzzle2.fromString("867254301"));

  PuzzleSolver solver(puzzle2, puzzle1);
  bool found;
  std::size_t solution_cost;
  auto start = std::chrono::high_resolution_clock::now();
  std::tie(found, solution_cost) = solver.search();
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;

  REQUIRE(found);
  REQUIRE(solution_cost == 31);

  std::cout << "\n**********************************************************\n"
            << std::endl;
  std::cout << "Time taken to find solutions in the hardest puzzle: " << elapsed.count() << " seconds" << std::endl;
  std::cout << "\n**********************************************************\n"
            << std::endl;
}
*/

/* You still need to write your own unit test*/