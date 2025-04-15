#include <functional>
#include <unordered_set>

#include "puzzle_solver.hpp"
#include "puzzle.hpp"
#include "state.hpp"
#include "frontier_queue.hpp"

// specialize the std::hash function for Puzzles
// reference here: https://en.cppreference.com/w/cpp/language/extending_std
namespace std
{
  template <>
  struct hash<Puzzle>
  {
    typedef Puzzle argument_type;
    typedef uint64_t result_type;

    result_type operator()(const argument_type &x) const { return x.hash(); }
  };
}

PuzzleSolver::PuzzleSolver(const Puzzle &initialPuzzle, const Puzzle &goalPuzzle) : initial(initialPuzzle), goal(goalPuzzle)
{
} // end constructor

std::pair<bool, std::size_t> PuzzleSolver::search()
{

  std::size_t solution_cost;
  frontier_queue<Puzzle> frontier;
  // TODO: instantiate explored

  frontier.push(initial, 0, initial.heuristic(goal));

  bool found = false;
  while (true)
  {
    if (frontier.empty())
    {
      found = false;
      break;
    }

    State<Puzzle> node = frontier.pop();
    Puzzle value = node.getValue();
    std::size_t cost = node.getPathCost();

    // TODO: add state to explored

    // TODO: visualize the solving process, check DemoVisualize()

    if (value.heuristic(goal) == 0)
    {
      found = true;
      solution_cost = node.getPathCost();
      break;
    }

    for (int a = Puzzle::LEFT; a <= Puzzle::DOWN; ++a)
    {
      bool ok;
      Puzzle result;
      std::tie(ok, result) = value.apply(static_cast<Puzzle::Action>(a));

      if (ok)
      {
        // TODO: define in_explored as whether the result has been explored

        bool in_explored = false;
        bool in_frontier = frontier.contains(result);
        if (!(in_explored || in_frontier))
        {
          frontier.push(result, cost + 1, result.heuristic(goal));
        }
        else if (in_frontier)
        {
          frontier.replaceif(result, cost + 1);
        }
      }
    }
  }
  return std::make_pair(found, solution_cost);
}

void PuzzleSolver::DemoVisualize()
{
  GifWriter gif;
  Image<Pixel> image = initial.toPicture();

  int gif_height = image.width();
  int gif_width = image.height();
  int frame_duration = 100; // Duration of each frame in milliseconds
  GifBegin(&gif, "puzzle_solver_output.gif", gif_width, gif_height, frame_duration, 8, true);

  Puzzle puzzle1;
  puzzle1.fromString("012345678");
  addFrameToGif(gif, puzzle1, frame_duration);

  puzzle1.fromString("102345678"); // demo here from directly constructing another, not solving it
  addFrameToGif(gif, puzzle1, frame_duration);

  puzzle1.fromString("142305678");
  addFrameToGif(gif, puzzle1, frame_duration);

  puzzle1.fromString("142375608");
  addFrameToGif(gif, puzzle1, frame_duration);

  GifEnd(&gif); // Finish writing the GIF
}

// Helper function
void PuzzleSolver::addFrameToGif(GifWriter &gif, Puzzle curr, int frame_duration)
{
  Image<Pixel> image = curr.toPicture();

  int gif_height = image.width();
  int gif_width = image.height();
  // 4 is the number of channels (RGBA)
  std::vector<uint8_t> rgb_data(gif_height * gif_width * 4);

  // Convert the image to RGB format for the GIF
  for (int r = 0; r < image.height(); ++r)
  {
    for (int c = 0; c < image.width(); ++c)
    {
      Pixel color = (image(r, c) == WHITE) ? Pixel{255, 255, 255} : Pixel{238, 142, 139}; // White and Pink
      int index = (r * gif_width + c) * 4;
      rgb_data[index + 0] = color.red;
      rgb_data[index + 1] = color.green;
      rgb_data[index + 2] = color.blue;
      rgb_data[index + 3] = 255; // Alpha channel
    }
  }
  // Write the frame to the GIF
  GifWriteFrame(&gif, rgb_data.data(), gif_width, gif_height, frame_duration, 8, true);
} // end addFrameToGif
