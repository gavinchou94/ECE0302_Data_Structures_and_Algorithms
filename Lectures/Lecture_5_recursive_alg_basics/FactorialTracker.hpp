/** @file FactorialTracker.hpp */

#ifndef FACTORIAL_TRACKER_HPP
#define FACTORIAL_TRACKER_HPP
#include "OperationTracker.hpp"

// Derived class for Factorial calculation
// The only new derived class function is factorial()
class FactorialTracker : public OperationTracker
{
public:
   /**
    * Calculates the factorial of a given number.
    * @param n The number to calculate the factorial of.
    * @return The factorial of the number.
    */
   long long factorial(int n)
   {
      if (getMaxRecursionDepth() == 0)
      {
         startTimer(); // TODO: explain why startTimer() is inside the if-statement?
      }
      enterRecursion();
      // incrementOperations(); // if also counting function call as an operation, uncomment this line

      if (n == 0 || n == 1)
      {
         stopTimer();
         exitRecursion();
         return 1;
      }

      long long result = n * factorial(n - 1);
      stopTimer();
      exitRecursion();
      incrementOperations(); // Count multiplication operation
      return result;
   }
};

#endif