/** @file FactorialTracker.hpp */

#ifndef FACTORIAL_TRACKER_HPP
#define FACTORIAL_TRACKER_HPP
#include "OperationTracker.hpp"

// Derived class for Factorial calculation
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
         startTimer(); // Why is startTimer() here inside the if-statement?
      }
      enterRecursion();
      // incrementOperations(); // Optional: Count function call as an operation

      if (n <= 1)
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