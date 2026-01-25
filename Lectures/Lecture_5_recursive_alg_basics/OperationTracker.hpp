/** @file OperationTracker.hpp*/

#ifndef OPERATIONTRACKER_HPP
#define OPERATIONTRACKER_HPP

#include <iostream>
#include <stack>
#include <chrono>

// Base class for operation tracking, recursion depth, and execution time
// hpp-only class implementation
class OperationTracker
{
protected:
   std::stack<int> recursionStack;                                    // Tracks recursion depth
   int operationCount;                                                // Counts number of operations performed
   std::chrono::high_resolution_clock::time_point startTime, endTime; // Tracks execution time
   int maxRecursionDepth;                                             // Tracks maximum recursion depth

public:
   OperationTracker() : operationCount(0), maxRecursionDepth(0) {} // Constructor

   // Start and stop execution timer
   void startTimer() { startTime = std::chrono::high_resolution_clock::now(); }
   void stopTimer() { endTime = std::chrono::high_resolution_clock::now(); }

   // Get execution time in nanoseconds
   long long getExecutionTime() const
   {
      return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
   }

   // Track recursion depth
   void enterRecursion()
   {
      recursionStack.push(1);
      if (recursionStack.size() > maxRecursionDepth)
      {
         maxRecursionDepth = recursionStack.size();
      }
   }
   void exitRecursion()
   {
      if (!recursionStack.empty())
         recursionStack.pop();
   }
   int getMaxRecursionDepth() const { return maxRecursionDepth; }

   // Count operations
   void incrementOperations(int count = 1) { operationCount += count; }
   int getOperationCount() const { return operationCount; }

   // Reset tracking
   void reset()
   {
      while (!recursionStack.empty())
         recursionStack.pop();
      operationCount = 0;
      startTime = endTime = std::chrono::high_resolution_clock::now();
      maxRecursionDepth = 0;
   }
};

#endif