#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <cstdint> // for uint64_t hash value
#include <utility> // for std::pair
#include <string>  // for toString()
#include <sstream> // for toString()
#include "lib/image.h"

/** @brief A Puzzle class of a 3x3 array of cells containing a label, indexed by row, and column
 * @note It also defines enum for the labels, and the actions to move the blank tile, and position struct
 * @todo make the class more generic to support larger puzzles IN THE FUTURE, 2*2, 4*4, etc */
class Puzzle
{
public:
  // tiles are labeled BLANK and A-H, they are mapped to 0-8 using enum
  enum Tile
  {
    BLANK,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H
  };

  // a position is a 0 <= row < 3 and 0 <= column < 3
  struct Position
  {
    int row;
    int col;
  };

  // actions are specified as moving the blank tile
  enum Action
  {
    LEFT,
    RIGHT,
    UP,
    DOWN
  };

  // default constructor, no dynamic memory involved
  Puzzle() = default;

  /** @brief set the label at position p to tile
   * @param p The position to set the label
   * @param tile The tile to set at the position
   * @throws std::range_error if p is out of bounds */
  void setLabel(Position p, Tile tile);

  /** @brief get the label at position p
   * @param p The position to get the label
   * @return The tile at the position
   * @throws std::range_error if p is out of bounds */
  Tile getLabel(Position p) const;

  /** @brief apply an action to the puzzle board
   * @param a The action to apply
   * @return A pair of a bool and a new puzzle, the bool is true if the action was valid */
  std::pair<bool, Puzzle> apply(Action a) const;

  // check if two puzzles are equal
  bool operator==(const Puzzle &rhs) const;
  bool operator!=(const Puzzle &rhs) const;

  /** @brief hash the puzzle board to a unique 64-bit value to avoid tile-to-tile comparisons
   * @return A 64-bit hash value of the puzzle board
   * @note The hash is computed as a simple polynomial hash function over the tile values
   *       This is not a cryptographic hash, but should be sufficient for our purposes
   *       The hash is computed as follows (where tile[i] is the value of the tile at position i)
   *       hash's binary hash_b = "tile[8]'s 4-bit binary t8_b" & "tile[7]'s 4-bit binary t7_b" & ...
   *       e.g., board 876 // 543 // 210 is hashed to binary 0000_0001_0010_0011_0100_0101_0110_0111_1000
   *       that is 305419896 in decimal */
  uint64_t hash() const;

  /** @brief a simple heuristic value of current puzzle to the goal puzzle
   * @param goal The goal puzzle to compare against
   * @return The heuristic value of the current puzzle to the goal puzzle
   * @note The heuristic is computed as the sum of the Manhattan distances of each tile from its goal position
   *       The blank tile is now included in the heuristic calculation but should be excluded
   *       It should be admissible, meaning it never overestimates the true cost to reach the goal
   * @todo Update to exclude the Manhattan distances of blank tile IN THE FUTURE */
  int heuristic(const Puzzle &goal) const;

  /** @brief constructor to create a puzzle from a string
   * @param str The string to create the puzzle from
   * @return true if the string is valid, false otherwise
   * @note The string should be 9 characters long, and each character should be a digit from 0-8
   *       The string should represent a valid puzzle board, with no duplicate tiles
   *       The blank tile is represented by 0, and the other tiles are represented by 1-8 */
  bool fromString(const std::string &str);

  /** @brief convert the puzzle to a string
   * @return The string representation of the puzzle
   * @note The string is 9 characters long, and each character is a digit from 0-8
   *       The blank tile is represented by 0, and the other tiles are represented by 1-8 */
  std::string toString();

  /** @brief convert the puzzle to a picture
   * @return The picture representation of the puzzle
   * @note The picture is a 3x3 array of pixels, with each pixel representing a tile
   *       The blank tile is represented by white, and the other tiles are represented by pink colors */
  Image<Pixel> toPicture() const;

private:
  Tile board[9] = {A, B, C, D, E, F, G, H, BLANK}; // default board
  /*
   1 2 3
   4 5 6
   7 8
  */
  Position blankpos = {2, 2}; // default blank position is at (2,2)

  // helper function to swap two tiles in the board
  void swap(Position a, Position b);
};

#endif