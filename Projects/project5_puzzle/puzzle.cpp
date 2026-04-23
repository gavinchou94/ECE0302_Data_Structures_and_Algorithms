#include "puzzle.hpp"
#include <stdexcept>

bool Puzzle::fromString(const std::string &str)
{
  if (str.size() != 9)
  {
    return false;
  }
  bool seen[9] = {false, false, false, false, false, false, false, false, false};
  for (int i = 0; i < 9; ++i)
  {
    if ((str[i] < '0') || (str[i] > '8'))
      return false;
    int val = str[i] - '0';
    if (seen[val])
      return false;
    seen[val] = true;
    board[i] = static_cast<Tile>(val);
    if (board[i] == BLANK)
    {
      blankpos.row = i / 3;
      blankpos.col = i % 3;
    }
  }
  return true;
}

std::string Puzzle::toString() const
{
  std::string result;
  for (int i = 0; i < 9; ++i)
  {
    result.push_back('0' + board[i]);
  }
  return result;
}

Puzzle::Tile Puzzle::getLabel(Position p) const
{
  if ((p.row < 0) || (p.row > 2) || (p.col < 0) || (p.col > 2))
  {
    throw std::range_error("invalid row/column in Puzzle::getLabel");
  }
  return board[3 * p.row + p.col];
}

void Puzzle::setLabel(Position p, Tile tile)
{
  if ((p.row < 0) || (p.row > 2) || (p.col < 0) || (p.col > 2))
  {
    throw std::range_error("invalid row/column in Puzzle::setLabel");
  }
  board[3 * p.row + p.col] = tile;
}

std::pair<bool, Puzzle> Puzzle::apply(Action a) const
{
  Puzzle temp = *this;
  bool valid = false;
  int newRow = blankpos.row;
  int newCol = blankpos.col;
  if ((a == LEFT) && (blankpos.col > 0))
  {
    newCol -= 1;
    valid = true;
  }
  else if ((a == RIGHT) && (blankpos.col < 2))
  {
    newCol += 1;
    valid = true;
  }
  else if ((a == UP) && (blankpos.row > 0))
  {
    newRow -= 1;
    valid = true;
  }
  else if ((a == DOWN) && (blankpos.row < 2))
  {
    newRow += 1;
    valid = true;
  }
  if (valid)
  {
    int oldIndex = 3 * blankpos.row + blankpos.col;
    int newIndex = 3 * newRow + newCol;
    temp.board[oldIndex] = temp.board[newIndex];
    temp.board[newIndex] = BLANK;
    temp.blankpos.row = newRow;
    temp.blankpos.col = newCol;
  }
  return std::make_pair(valid, temp);
}

Image<Pixel> Puzzle::toPicture() const
{
  Image<Pixel> img = readFromFile("../lib/puzzle.png");
  int blockHeight = img.height() / 3;
  int blockWidth = img.width() / 3;
  Image<Pixel> rearrangedImg(img.height(), img.width());
  for (int blockIndex = 0; blockIndex < 9; ++blockIndex)
  {
    int srcBlockRow = board[blockIndex] / 3;
    int srcBlockCol = board[blockIndex] % 3;
    int destBlockRow = blockIndex / 3;
    int destBlockCol = blockIndex % 3;
    for (int r = 0; r < blockHeight; ++r)
    {
      for (int c = 0; c < blockWidth; ++c)
      {
        rearrangedImg(destBlockRow * blockHeight + r, destBlockCol * blockWidth + c) =
            img(srcBlockRow * blockHeight + r, srcBlockCol * blockWidth + c);
      }
    }
  }
  return rearrangedImg;
}

unsigned long long Puzzle::hash() const
{
  // TODO
  // use bitwise << and | to implemnt the concatenation
  // e.g., 2<<4 | 3 is actually hex 23, which is 35 in decimal
  return 0;
}

bool Puzzle::operator==(const Puzzle &rhs) const
{
  // TODO
  // do not compare tile by tile, use other public member functions
  return false;
}

bool Puzzle::operator!=(const Puzzle &rhs) const
{
  // TODO
  return false;
}

int Puzzle::heuristic(const Puzzle &goal) const
{
  // TODO
  // Research Manhattan distance and implement the heuristic function
  return 0;
}