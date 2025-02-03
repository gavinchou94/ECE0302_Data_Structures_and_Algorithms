/** @file TowerOfHanoiTracker.hpp */

#ifndef TOWER_OF_HANOI_TRACKER_HPP
#define TOWER_OF_HANOI_TRACKER_HPP

#include <iostream>
#include "OperationTracker.hpp"

// Derived class for Tower of Hanoi
class TowerOfHanoiTracker : public OperationTracker
{
public:
   void hanoi(int n, char source, char target, char spare, bool displayMoves = true)
   {
      if (getMaxRecursionDepth() == 0)
      {
         startTimer();
      }
      enterRecursion();
      // incrementOperations(); // Optional: Count function call as an operation

      if (n == 1)
      {
         if (displayMoves)
         {
            std::cout << "Move top disk from " << source << " to " << target << std::endl;
         }
         stopTimer();
         exitRecursion();
         incrementOperations(); // Count disk move operation
         return;
      }

      hanoi(n - 1, source, spare, target, displayMoves);
      exitRecursion();
      hanoi(1, source, target, spare, displayMoves);
      exitRecursion();
      hanoi(n - 1, spare, target, source, displayMoves);
      exitRecursion();
   }
};
#endif // TOWER_OF_HANOI_TRACKER_HPP