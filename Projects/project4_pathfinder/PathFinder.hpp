#ifndef _PATHFINDER_HPP
#define _PATHFINDER_HPP

#include <cstdlib>
#include <iostream>
#include "lib/image.h"
#include "lib/gif.h"
#include "list.hpp"
#include "queue.hpp"

// Define the coordinate structure
struct Coord
{
  int row;
  int col;
  Coord() : row(-1), col(-1) {}
  Coord(int r, int c) : row(r), col(c) {}
  bool operator==(const Coord &other) const
  {
    return row == other.row && col == other.col;
  }
  bool operator!=(const Coord &other) const
  {
    return !(*this == other);
  }
};

class PathFinder
{
public:
  // Constructor and destructor

  /** @brief Construct a PathFinder from an Image<Pixel> object
   * @param img: Image<Pixel> object from lib/image.h */
  PathFinder(const Image<Pixel> &img);

  /** @brief Destructor; deallocates all dynamic memory used by the class */
  ~PathFinder();

  PathFinder(const PathFinder &other) = delete;            // Disable copy constructor
  PathFinder &operator=(const PathFinder &other) = delete; // Disable copy assignment operator

  // Public Methods
  /** @brief Load a maze image into the PathFinder, replacing any previous state
   * @param img: Image<Pixel> object from lib/image.h
   * @post  The image is stored and ready for pathfinding
   * @throws std::invalid_argument if the image fails validation (see checkImage) */
  void load(const Image<Pixel> &img);

  /** @brief Reset the PathFinder to an empty state, deallocating all dynamic memory */
  void clear();

  /** @brief Check if the image is valid for pathfinding
   * @param img: Image<Pixel> object from lib/image.h
   * @throws std::invalid_argument if the image is not valid for maze pathfinding
   * Invalid conditions include: no RED pixel, multiple RED pixels, or image containing pixels
   * that are not BLACK, WHITE, or RED */
  void checkImage(const Image<Pixel> &img) const;

  /** @brief Get the start coordinate (the RED pixel)
   * @return Coord object representing the start coordinate, if not exist, return the default Coord */
  Coord getStart() const;

  /** @brief Get the end coordinate (a WHITE pixel on the image boundary, discovered by BFS)
   * @return Coord object representing the end coordinate, if not yet found, return the default Coord */
  Coord getEnd() const;

  /** @brief Find the path from start to end using BFS algorithm and Queue ADT
   * @param strategy: string representing the search strategy, default is "NSWE". When adding new coordinates to the queue,
   * the order of the coordinates is determined by this string. For example, "NSWE" means North, South, West, East.
   * Four allowed strategies are "NSWE", "WENS", "NESW" and "NWSE"
   * @post  The exit (if found) should be marked as GREEN in the image.
   * For full functionality, the path from start to exit should also be marked as YELLOW.
   * If no exit is found, the image stays unchanged.
   * @throws std::runtime_error if no path is found */
  void findPath(const std::string &strategy = "NSWE");

  // BONUS: Same BFS as findPath(), plus GIF visualization
  /** @brief Find the path using BFS (same logic as findPath), recording the search as an animated GIF
   * @param outfile: base name for output files (produces outfile.gif and outfile_final_visual.png)
   * @param frame_duration: duration of each GIF frame in milliseconds
   * @param frame_gap: number of BFS steps between recorded frames (1 = every step)
   * @param strategy: search strategy string, default is "NSWE" (same options as findPath)
   * @post  In addition to GREEN exit and YELLOW path, all visited coordinates are marked BLUE.
   * The search is saved as a GIF and the final image is saved as a PNG.
   * @throws std::runtime_error if no path is found */
  void findPathWithVisualization(const std::string &outfile, int frame_duration, int frame_gap, const std::string &strategy = "NSWE");

  /** @brief Convert the current image state to an RGBA buffer and append it as one GIF frame
   * @param gif: GifWriter object from lib/gif.h
   * @param frame_duration: duration of this frame in milliseconds */
  void addFrameToGif(GifWriter &gif, int frame_duration);

  /** @brief Write the current image (with any path markings) to a PNG file
   * @param filename: name of the output PNG file */
  void writeSolutionToFile(const std::string &filename);

private:
  Image<Pixel> image;
  // TODO: Add more private member variables and methods as needed
};

// Nonmember functions

/** @brief Compare two images, checking only that GREEN pixels appear at the same coordinates.
 * Differences between non-GREEN pixels (e.g., BLUE vs WHITE visited markings) are ignored.
 * @param img1_str: filename of the first image
 * @param img2_str: filename of the second image
 * @return true if GREEN pixels match in both images, false otherwise */
bool compareImagesExit(const std::string &img1_str, const std::string &img2_str);

/** @brief Compare two images for exact pixel-by-pixel equality
 * @param img1_str: filename of the first image
 * @param img2_str: filename of the second image
 * @return true if every pixel is identical, false otherwise */
bool compareImages(const std::string &img1_str, const std::string &img2_str);

#endif // _PATHFINDER_HPP