/** Pseudocode

// Used in lecture, also in the book

searchWithRecursion(currentLocation) : boolean
{
  foundExit = false if (currentLocation is the exit)
      foundExit = true else if (currentLocation is a dead end or was visited)
  {
    // Backtrack by returning to caller and signaling no path to exit exists from here
    mark currentLocation as not on path // Red: location not on path to exit
        foundExit = false
  }
  else
  {
    mark currentLocation as visited // Green: first time at location
        if (path to east exists)
            foundExit = searchWithRecursion(square east of currentLocation) // R1
        if (!foundExit and path to north exists)
            foundExit = searchWithRecursion(square north of currentLocation) // R2
        if (!foundExit and path to west exists)
            foundExit = searchWithRecursion(square west of currentLocation) // R3
        if (!foundExit and path to south exists)
            foundExit = searchWithRecursion(square south of currentLocation) // R4
        // If foundExit is false at this point, we are at a dead end or no path to exit
        exists from here
  }
  return foundExit
}
*/