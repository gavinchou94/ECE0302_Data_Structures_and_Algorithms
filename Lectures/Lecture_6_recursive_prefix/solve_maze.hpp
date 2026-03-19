/** Pseudocode
// Used in lecture, also in the book

searchWithRecursion(currentLocation) : boolean
{
  foundExit = false
  if (currentLocation is the exit)
    foundExit = true
  else
    if (currentLocation is a dead end or was visited)
    {
    // Backtrack by returning to caller and signaling no path to exit exists from here
    mark currentLocation as not on path // Red: location not on path to exit
    foundExit = false
    }
    else
    {
    mark currentLocation as visited // Green: first time at location
        if (path to north exists)
            foundExit = searchWithRecursion(square north of currentLocation) // R1
        if (!foundExit and path to south exists)
            foundExit = searchWithRecursion(square south of currentLocation) // R2
        if (!foundExit and path to east exists)
            foundExit = searchWithRecursion(square east of currentLocation) // R3
        if (!foundExit and path to west exists)
            foundExit = searchWithRecursion(square west of currentLocation) // R4
        // If foundExit is false at this point, we are at a dead end or no path to exit
        exists from here
    }
  return foundExit
}

More Context:
wall is denoted as x, open path is denoted as o; the maze is represented as a 2D array of characters
exit is the bottom right corner as (5,5)
*/

#include <iostream>
#include <string>
#include <vector>

using Maze = std::vector<std::vector<char>>; // typedef for readability
using Path = std::vector<std::string>;       // typedef for readability

bool searchWithRecursion(Maze &maze, int row, int col, Path &path, int currentDepth, int &maxDepth)
{
    if (currentDepth > maxDepth)
    {
        maxDepth = currentDepth;
    }

    const int ROWS = maze.size();
    const int COLS = maze[0].size();

    // out of bounds, wall, or already visited.
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS ||
        maze[row][col] == 'x' || maze[row][col] == 'v')
    {
        return false;
    }

    std::cout << "Depth " << currentDepth << ": visiting ("
              << (row + 1) << ',' << (col + 1) << ")\n";

    // path is 1-indexed for better readability, adding current location to path before exploring neighbors
    path.push_back("(" + std::to_string(row + 1) + "," + std::to_string(col + 1) + ")");
    maze[row][col] = 'v'; // mark as visited

    bool atExit = (row == ROWS - 1 && col == COLS - 1);
    if (atExit)
    {
        return true;
    }

    bool foundExit = false;

    if (row - 1 >= 0 && maze[row - 1][col] != 'x' && maze[row - 1][col] != 'v')
    {
        foundExit = searchWithRecursion(maze, row - 1, col, path, currentDepth + 1, maxDepth); // R1: north
    }
    if (!foundExit && row + 1 < ROWS && maze[row + 1][col] != 'x' && maze[row + 1][col] != 'v')
    {
        foundExit = searchWithRecursion(maze, row + 1, col, path, currentDepth + 1, maxDepth); // R2: south
    }
    if (!foundExit && col + 1 < COLS && maze[row][col + 1] != 'x' && maze[row][col + 1] != 'v')
    {
        foundExit = searchWithRecursion(maze, row, col + 1, path, currentDepth + 1, maxDepth); // R3: east
    }
    if (!foundExit && col - 1 >= 0 && maze[row][col - 1] != 'x' && maze[row][col - 1] != 'v')
    {
        foundExit = searchWithRecursion(maze, row, col - 1, path, currentDepth + 1, maxDepth); // R4: west
    }

    // Backtrack by marking this location as not on final path and removing it from route.
    if (!foundExit)
    {
        maze[row][col] = '-'; // mark as backtracked
        path.pop_back();
    }
    return foundExit;
}