#ifndef PUZZLE_SOLVER_HPP
#define PUZZLE_SOLVER_HPP

#include <utility> // for std::pair
#include "puzzle.hpp"
#include "lib/gif.h"

class PuzzleSolver
{
public:
  // Constructor, parameters are the initial and goal puzzles
  PuzzleSolver(const Puzzle &initialPuzzle, const Puzzle &goalPuzzle);

  /** @brief This function searches for a solution to the puzzle using the A* algorithm.
   *  @return A pair containing a boolean indicating if a solution was found and the cost of the solution.
   *  If no solution is found, the cost will be 0.
   *  The function shall also visualize the solving process by creating a GIF.*/
  std::pair<bool, std::size_t> search();

  /** @brief This function demonstrate the creation of gif from simple sequences of puzzle states.*/
  void DemoVisualize();

  /** @brief This helper function adds a frame to the GIF.
   *  @param gif The GifWriter object to write the frame to.
   *  @param curr The current puzzle state to be added as a frame.
   *  @param frame_duration The duration of the frame in milliseconds, usually set to be 100 so each frame last for 1s*/
  void addFrameToGif(GifWriter &gif, Puzzle curr, int frame_duration);

private:
  Puzzle initial, goal;
};

#endif
