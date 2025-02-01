/** @file BinarySearchTracker.hpp */

#ifndef BINARY_SEARCH_TRACKER_HPP
#define BINARY_SEARCH_TRACKER_HPP
#include "OperationTracker.hpp"

// Derived class for Binary Search
class BinarySearchTracker : public OperationTracker
{
public:
  bool binary_search(const int arr[], int val, int start, int end)
  {
    if (getMaxRecursionDepth() == 0)
    {
      startTimer();
    }
    enterRecursion();
    // incrementOperations(); // Optional: Count function call as an operation

    int middle = (start + end) / 2;

    incrementOperations(); // Count comparison operation
    if (arr[middle] == val)
    {
      stopTimer();
      exitRecursion();
      return true;
    }

    if (end == start + 1)
    {
      stopTimer();
      exitRecursion();
      return false;
    }

    incrementOperations(); // Count comparison operation
    if (arr[middle] > val)
    {
      return binary_search(arr, val, start, middle);
    }

    incrementOperations(); // Count comparison operation
    if (arr[middle] < val)
    {
      return binary_search(arr, val, middle, end);
    }

    return false;
  }
};
#endif