#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <utility> // for std::pair
#include <string>
#include <functional>
#include "lib/image.h"

/** @brief A Puzzle class of a 3x3 array of cells containing a label, indexed by row, and column
 * @note It also defines enum for the labels, and the actions to move the blank tile, and position struct*/
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

  /** @brief Initialize the puzzle board from a string representation
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
  std::string toString() const;

  /** @brief get the label at position p
   * @param p The position to get the label
   * @return The tile at the position
   * @throws std::range_error if p is out of bounds */
  Tile getLabel(Position p) const;

  /** @brief set the label at position p to tile
   * @param p The position to set the label
   * @param tile The tile to set at the position
   * @throws std::range_error if p is out of bounds */
  void setLabel(Position p, Tile tile);

  /** @brief Returns the resulting puzzle board if the action is applied, without modifying this object
   * @param a The action to apply
   * @return true and the resulting puzzle if the action was valid,
   *         false and the original puzzle otherwise */
  std::pair<bool, Puzzle> apply(Action a) const;

  /** @brief convert the puzzle to a picture
   * @return The picture representation of the puzzle
   * @note The picture is a 3x3 array of pixels, with each pixel representing a tile
   *       The blank tile is represented by white, and the other tiles are represented by pink colors */
  Image<Pixel> toPicture() const;

  /** @brief Hash the puzzle board to a unique value for fast equality comparison
   * @return A hash value of the puzzle board
   * @note The hash is computed by packing each tile value into 4 bits and concatenating them
   *       This is not a cryptographic hash, but should be sufficient for our purposes
   *       hash's binary hash_b = "tile[0]'s 4-bit binary" & "tile[1]'s 4-bit binary" & ... (& is concatenation)
   *       e.g., board "012345678"(012 // 345 // 678) is hashed to binary 0000_0001_0010_0011_0100_0101_0110_0111_1000
   *       that is 305419896 in decimal */
  unsigned long long hash() const;

  /** @brief Check if two puzzles are equal
   * @param rhs The puzzle to compare against
   * @return true if the two puzzles are equal, false otherwise */
  bool operator==(const Puzzle &rhs) const;

  /** @brief Check if two puzzles are not equal
   * @param rhs The puzzle to compare against
   * @return true if the two puzzles are not equal, false otherwise */
  bool operator!=(const Puzzle &rhs) const;

  /** @brief a simple heuristic value of current puzzle to the goal puzzle
   * @param goal The goal puzzle to compare against
   * @return The heuristic value of the current puzzle to the goal puzzle
   * @note The heuristic is computed as the sum of the Manhattan distances of each tile (excluding the blank tile) from its goal position
   *       It should be admissible, meaning it never overestimates the true cost to reach the goal*/
  int heuristic(const Puzzle &goal) const;

private:
  Tile board[9] = {A, B, C, D, E, F, G, H, BLANK}; // default board
  /*
   1 2 3
   4 5 6
   7 8 _
  */
  Position blankpos = {2, 2}; // default blank position is at (2,2)
};

// Specialize the std::hash function for Puzzles such that we can use unordered_set and unordered_map with Puzzles as keys
// Reference here: https://en.cppreference.com/w/cpp/language/extending_std
namespace std
{
  template <>
  struct hash<Puzzle>
  {
    unsigned long long operator()(const Puzzle &x) const { return x.hash(); }
  };
}

#endif