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
  int row;                                 // row attribute
  int col;                                 // column attribute
  Coord() : row(-1), col(-1) {};           // Default constructor
  Coord(int r, int c) : row(r), col(c) {}; // Constructor with parameters
  bool operator==(const Coord &other) const
  {
    return row == other.row && col == other.col;
  }; // useful for comparison
  bool operator!=(const Coord &other) const
  {
    return !(*this == other);
  }
};

class PathFinder
{
public:
  // Constructor and destructor

  /** @brief Construct the class from a Image<Pixel> object, delegate to load() function
   * @param img: Image<Pixel> object from lib/image.h */
  PathFinder(const Image<Pixel> &img);

  /** @brief Construct the class from a Image<Pixel> object
   * @param img: Image<Pixel> object from lib/image.h
   * @post  The image is loaded into the class
   * @throws std::invalid_argument if the image is not valid, call checkImage() to do so */
  void load(const Image<Pixel> &img);

  PathFinder(const PathFinder &other) = delete;            // Disable copy constructor
  PathFinder &operator=(const PathFinder &other) = delete; // Disable copy assignment

  /** @brief Custom destructor due to likely use of dynamic memory. Delegate to clear() function
   * @post  Deallocates all dynamic memory used by the class */
  ~PathFinder();

  // Public Methods

  /** @brief Check if the image is valid for pathfinding
   * @param img: Image<Pixel> object from lib/image.h
   * @throws std::invalid_argument if the image is not valid for maze pathfinding
   * Invalid conditions include: no red pixel or multiple red pixel or image containing non-B/W/R pixel*/
  void checkImage(const Image<Pixel> &img);

  /** @brief Get the start coordinate
   * @return Coord object representing the start coordinate, if not exist, return the default Coord */
  Coord getStart();

  /** @brief Get the end coordinate
   * @return Coord object representing the end coordinate, if not exist, return the default Coord */
  Coord getEnd();

  /** @brief Find the path from start to end using BFS algorithm and Queue ADT
   * @param strategy: string representing the search strategy, default is "NSWE". When adding new coordinates to the queue,
   * the order of the coordinates is determined by this string. For example, "NSWE" means North, South, West, East.
   * Four Allowed strategies are "NSWE", "WENS", "NESW" and "NWSE"
   * @post  At a minimal viable product, the exit (if found) should marked as GREEN in the image.
   * For full functionality, the path should also be marked as YELLOW
   * If no exit is found, the image stays unchanged and throw an exception.
   * @throw throw a std::runtime_error if no path is found*/
  void findPath(std::string strategy = "NSWE");

  // BONUS: Visualization, should use almost identical codes as above, with some addtions to write to GIF file
  /** @brief Find the path from start to end using BFS algorithm and Queue ADT (all same as above), with visualization
   * @param strategy: string representing the search strategy
   * @param outfile: string representing the name of the output file
   * @param frame_duration: int representing the duration of the frame in milliseconds for displaying
   * @param frame_gap: int representing the gap between two displayed frames in terms of movements
   * if frame_gap = 1, every movement is displayed
   * @post  The path is found and the image is saved to a GIF file. In addition to RED start, GREEN end, YELLOW final path,
   * All visited coordinates can be marked as BLUE in the image
   * @throw same as above, throw a std::runtime_error if no path is found
   */
  void findPathWithVisualization(const std::string &outfile, int frame_duration, int frame_gap, std::string strategy = "NSWE");

  /** @brief Add a frame to a GIF object, an utility function for the BONUS implementation of findPathWithVisualization
   * @param gif: GifWriter object from lib/gif.h
   * @param frame_duration: int representing the duration of the frame in milliseconds for displaying
   * @post  The frame is added to the GIF object */
  void addFrameToGif(GifWriter &gif, int frame_duration);

  /** @brief Write the image solution to a file, delegate to the writeToFile function in lib/image.h
   * @param filename: string representing the name of the file to write to
   * @post  The solution is written to the file in a human-readable format */
  void writeSolutionToFile(const std::string &filename);

  /** @brief Clear the pathfinder object, deallocate all dynamic memory
   * @post  The pathfinder object is cleared, all dynamic memory is deallocated */
  void clear();

private:
  Image<Pixel> image;
  // TODO: Add more private member variables and methods as needed
};

// Nonmember functions

/** @brief Helper function to compare two images for equality, only care about the exit pixel
 * @param img1_str: string representing the name of the first image file
 * @param img2_str: string representing the name of the second image file
 * @return true if the images has green pixels at the same coordinates, false otherwise */
bool compareImagesExit(std::string img1_str, std::string img2_str);

/** @brief Helper function to compare two images for equality
 * @param img1_str: string representing the name of the first image file
 * @param img2_str: string representing the name of the second image file
 * @return true if the images are equal, false otherwise
 * @post  The images are compared pixel by pixel, and the result is returned */
bool compareImages(std::string img1_str, std::string img2_str);

#endif // _PATHFINDER_HPP