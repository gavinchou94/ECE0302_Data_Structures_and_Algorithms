/** @file GCDTracker.hpp */

#ifndef GCD_TRACKER_HPP
#define GCD_TRACKER_HPP

#include "OperationTracker.hpp"

class GCDTracker : public OperationTracker
{
public:
   /**
    * @brief Computes the greatest common divisor (GCD) of two integers using the Euclidean algorithm.
    *
    * The Euclidean algorithm is based on the principle that the GCD of two numbers does not change
    * if the larger number is replaced by its difference with the smaller number.
    *
    * @param n First integer, assumed larger than or equal to m
    * @param m Second integer
    * @return int The GCD of the two integers
    */

   int gcd(int n, int m)
   {
      if (getMaxRecursionDepth() == 0)
      {
         startTimer();
      }
      enterRecursion();
      //   incrementOperations(); // Optional: Count function call as an operation

      if (m == 0)
      {
         stopTimer();
         exitRecursion();
         return n;
      }
      int result = gcd(m, n % m);
      stopTimer();
      exitRecursion();
      incrementOperations(); // TODO: what operation does this count?
                             // (1) calling gcd or (2) the remainder operation?
                             // or (3) passing value to result?
      return result;
   }
};
#endif