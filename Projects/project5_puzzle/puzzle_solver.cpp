#include "puzzle_solver.hpp"

void addFrameToGif(GifWriter &gif, const Puzzle &curr, int frame_duration)
{
  Image<Pixel> image = curr.toPicture();
  int gif_height = image.height();
  int gif_width = image.width();

  // 4 channels (RGBA)
  std::vector<uint8_t> rgb_data(gif_height * gif_width * 4);

  // convert the image to RGBA format for the GIF
  for (int r = 0; r < image.height(); ++r)
  {
    for (int c = 0; c < image.width(); ++c)
    {
      Pixel color = (image(r, c) == WHITE) ? Pixel{255, 255, 255} : Pixel{238, 142, 139};
      int index = (r * gif_width + c) * 4;
      rgb_data[index + 0] = color.red;
      rgb_data[index + 1] = color.green;
      rgb_data[index + 2] = color.blue;
      rgb_data[index + 3] = 255;
    }
  }

  GifWriteFrame(&gif, rgb_data.data(), gif_width, gif_height, frame_duration, 8, true);
} // end addFrameToGif

void demoVisualize()
{
  Puzzle puzzle_default;
  GifWriter gif;
  Image<Pixel> img = puzzle_default.toPicture();
  int frame_duration = 100; // 100 centiseconds = 1 second
  GifBegin(&gif, "puzzle_solver_output.gif", img.width(), img.height(), frame_duration, 8, true);

  Puzzle puzzle;
  puzzle.fromString("123046758");
  addFrameToGif(gif, puzzle, frame_duration);
  puzzle.fromString("123406758");
  addFrameToGif(gif, puzzle, frame_duration);
  puzzle.fromString("123456708");
  addFrameToGif(gif, puzzle, frame_duration);
  puzzle.fromString("123456780");
  addFrameToGif(gif, puzzle, frame_duration);

  GifEnd(&gif);
} // end demoVisualize

PuzzleSolver::PuzzleSolver(const Puzzle &initialPuzzle, const Puzzle &goalPuzzle)
    : initial(initialPuzzle), goal(goalPuzzle), solution_cost(0)
{
} // end constructor

int PuzzleSolver::getSolutionCost() const
{
  return solution_cost;
}

std::vector<std::string> PuzzleSolver::getSolutionPath() const
{
  std::vector<std::string> result;
  for (const Puzzle &p : solution_path)
    result.push_back(p.toString());
  return result;
}

bool PuzzleSolver::search()
{
  solution_cost = 0;
  solution_path.clear();
  // A* outline:
  // 1) Enqueue the initial Puzzle into frontier with:
  //      g = 0, h = initial.heuristic(goal), f = g + h.
  // 2) Keep a visited structure (hash-based is convenient for Puzzle).
  // 3) Dequeue (pop) the frontier entry with smallest f.
  //      From that node, read puzzle state and its g-cost.
  // 4) If current state is the goal, set solution_cost = current g-cost and return true.
  //      backtrace the solution via parent relationship into solution_path.
  // 5) Otherwise, generate neighbors in action order LEFT, RIGHT, UP, DOWN.
  // 6) For each valid neighbor:
  //      neighbor_g = current_g + 1
  //      neighbor_h = neighbor.heuristic(goal)
  //      use frontier contain method and visited structure to determine:
  //      - if not "seen" before, enqueue neighbor with g, h values, set up the parent relationship
  //      - if already in frontier with higher g, update that entry via replaceif, update the parent relationship if needed
  // 7) If frontier becomes empty, no solution is found: return false.
  return false;
}