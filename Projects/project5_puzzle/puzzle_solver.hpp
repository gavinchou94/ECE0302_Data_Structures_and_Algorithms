#ifndef PUZZLE_SOLVER_HPP
#define PUZZLE_SOLVER_HPP

#include <utility>
#include "puzzle.hpp"
#include "lib/gif.h"

class PuzzleSolver
{
public:
  PuzzleSolver(const Puzzle &initialPuzzle, const Puzzle &goalPuzzle);

  std::pair<bool, std::size_t> search();

  void DemoVisualize();

  void addFrameToGif(GifWriter &gif, Puzzle curr, int frame_duration);

private:
  Puzzle initial, goal;
};

#endif
