/** @file GCDTracker.hpp */

#ifndef GCD_TRACKER_HPP
#define GCD_TRACKER_HPP

#include "OperationTracker.hpp"

// Derived class for GCD calculation
// The only new derived class function is gcd()
class GCDTracker : public OperationTracker
{
public:
   /**
    * @brief Computes the greatest common divisor (GCD) of two integers using the Euclidean algorithm.
    *
    * The Euclidean algorithm is based on the principle that the GCD of two numbers does not change
    * if the larger number is replaced by its difference with the smaller number.
    *
    * @param n First integer, assumed larger than or equal to m (n >= m)
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
      // incrementOperations(); // if also counting function call as an operation, uncomment this line

      if (m == 0)
      {
         stopTimer();
         exitRecursion();
         return n;
      }
      int result = gcd(m, n % m);
      stopTimer();
      exitRecursion();
      incrementOperations(); // TODO: in recursive calls, we need to count operations that matter the most to the algorithm's efficiency;
                             // instead of counting all operations, so what operation does this count?
                             // (1) calling gcd()
                             // or (2) the remainder operation?
                             // or (3) returning the function value and assign to result?
      return result;
   }
};

#endif