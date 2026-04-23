#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "puzzle_solver.hpp"

/* Frontier queue tests start here*/
TEST_CASE("Simple push and pop test", "[frontier_queue]")
{
  frontier_queue<char> fq;
  REQUIRE(fq.empty());
  fq.push('A', 0, 1);
  REQUIRE_FALSE(fq.empty());
  REQUIRE(fq.contains('A'));

  frontier_queue<char> fq2;
  fq2.push('B', 1, 1);
  State<char> state = fq2.pop();
  REQUIRE(state.getValue() == 'B');
  REQUIRE(state.getPathCost() == 1);
  REQUIRE(state.getFCost() == 2);
  REQUIRE(fq2.empty());
}

TEST_CASE("Simple contains and replaceif test", "[frontier_queue]")
{
  frontier_queue<char> fq;
  REQUIRE_FALSE(fq.contains('A'));
  REQUIRE_FALSE(fq.contains('B'));
  fq.push('A', 1, 1);
  fq.push('B', 2, 2);
  REQUIRE(fq.contains('A'));
  REQUIRE(fq.contains('B'));
  REQUIRE_FALSE(fq.contains('C'));

  frontier_queue<char> fq2;
  fq2.push('A', 100, 100);
  fq2.replaceif('A', 1);
  State<char> state = fq2.pop();
  REQUIRE(state.getValue() == 'A');
  REQUIRE(state.getPathCost() == 1);
  REQUIRE(state.getFCost() == 101);

  frontier_queue<char> fq3;
  fq3.push('A', 1, 100);
  fq3.replaceif('A', 50);
  State<char> state2 = fq3.pop();
  REQUIRE(state2.getPathCost() == 1);
}

/* Puzzle tests start here*/
TEST_CASE("Simple hash test", "[puzzle]")
{
  Puzzle p1, p2, p3;
  p1.fromString("876543210");
  p2.fromString("012345678");
  p3.fromString("102345678");
  REQUIRE(p2.hash() == 305419896ULL);
  REQUIRE(p1.hash() != p3.hash());
}

TEST_CASE("Simple operator== and operator!= test", "[puzzle]")
{
  Puzzle p1, p2, p3;
  p1.fromString("012345678");
  p2.fromString("012345678");
  p3.fromString("102345678");
  REQUIRE(p1 == p2);
  REQUIRE_FALSE(p1 == p3);
  REQUIRE(p1 != p3);
  REQUIRE_FALSE(p1 != p2);
}

TEST_CASE("Simple heuristic test", "[puzzle]")
{
  Puzzle goal, p1, p2, p3;
  goal.fromString("012345678");
  p1.fromString("012345678");
  p2.fromString("102345678");
  p3.fromString("120345678");
  REQUIRE(p1.heuristic(goal) == 0);
  REQUIRE(p2.heuristic(goal) == 1);
  REQUIRE(p3.heuristic(goal) == 2);
}

/* Puzzle solver tests start here*/
TEST_CASE("Simple search test cost 0", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456780"));
  REQUIRE(puzzle2.fromString("123456780"));
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 0);
    REQUIRE(solver.getSolutionPath().size() == 1);
  }
  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 0);
    REQUIRE(solver.getSolutionPath().size() == 1);
  }
}

TEST_CASE("Simple search test cost 1", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456708")); // blank at (2,1) — one RIGHT from goal
  REQUIRE(puzzle2.fromString("123456780")); // blank at (2,2) — goal
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 1);
    REQUIRE(solver.getSolutionPath().size() == 2);
    std::vector<std::string> expected_path = {"123456708", "123456780"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }
  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 1);
    REQUIRE(solver.getSolutionPath().size() == 2);
    std::vector<std::string> expected_path = {"123456780", "123456708"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }
}

TEST_CASE("Simple search test cost 2", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456078")); // blank at (2,0) — two RIGHTs from goal
  REQUIRE(puzzle2.fromString("123456780")); // blank at (2,2) — goal
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 2);
    REQUIRE(solver.getSolutionPath().size() == 3);
    std::vector<std::string> expected_path = {"123456078", "123456708", "123456780"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 2);
    REQUIRE(solver.getSolutionPath().size() == 3);
    std::vector<std::string> expected_path = {"123456780", "123456708", "123456078"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }
}

/** Two time-consuming tests are given here for your reference. Uncomment them to try locally.
 * The test case of cost 31 should execute within 1 minute locally to avoid timeout on the autograder.*/

/*
TEST_CASE("Time-consuming search test cost 8", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456780"));
  REQUIRE(puzzle2.fromString("012563478"));
  REQUIRE(puzzle1 != puzzle2);
  REQUIRE(puzzle1.heuristic(puzzle2) == 8);

  PuzzleSolver solver(puzzle2, puzzle1);
  REQUIRE(solver.search());
  REQUIRE(solver.getSolutionCost() == 8);
  Puzzle curr = puzzle2;
  int remaining = 8;
  std::vector<Puzzle::Action> actions = {Puzzle::RIGHT, Puzzle::RIGHT, Puzzle::DOWN, Puzzle::LEFT, Puzzle::LEFT, Puzzle::DOWN, Puzzle::RIGHT, Puzzle::RIGHT};
  for (const auto &a : actions)
  {
    std::pair<bool, Puzzle> result = curr.apply(a);
    REQUIRE(result.first);
    curr = result.second;
    remaining -= 1;
    PuzzleSolver inner(curr, puzzle1);
    REQUIRE(inner.search());
    REQUIRE(inner.getSolutionCost() == remaining);
    REQUIRE(curr.heuristic(puzzle1) <= inner.getSolutionCost());
  }
  REQUIRE(curr == puzzle1);
}

TEST_CASE("Time-consuming search test cost 31", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456780"));
  REQUIRE(puzzle2.fromString("867254301"));
  PuzzleSolver solver(puzzle2, puzzle1);
  auto start = std::chrono::high_resolution_clock::now();
  REQUIRE(solver.search());
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  REQUIRE(solver.getSolutionCost() == 31);
  std::cout << "\n**********************************************************\n"
            << std::endl;
  std::cout << "Time taken to find solutions in the hardest puzzle: " << elapsed.count() << " seconds" << std::endl;
  std::cout << "\n**********************************************************\n"
            << std::endl;
}
*/

// You still need to write your own unit test