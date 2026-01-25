/** @file BinarySearchTracker.hpp */

#ifndef BINARY_SEARCH_TRACKER_HPP
#define BINARY_SEARCH_TRACKER_HPP
#include "OperationTracker.hpp"

// Derived class for Binary Search
// The only new derived class function is binary_search()
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
    // incrementOperations(); // if also counting function call as an operation, uncomment this line

    int middle = (start + end) / 2;

    incrementOperations(); // Count == comparison operation between arr[middle] and val
    if (arr[middle] == val)
    {
      stopTimer();
      exitRecursion(); // base case of true, exit recursion
      return true;
    }

    if (end == start + 1)
    {
      stopTimer();
      exitRecursion(); // base case of false, exit recursion
      return false;
    }

    incrementOperations(); // Count > comparison operation between arr[middle] and val
    if (arr[middle] > val)
    {
      return binary_search(arr, val, start, middle);
    }

    incrementOperations(); // Count < comparison operation between arr[middle] and val
    if (arr[middle] < val)
    {
      return binary_search(arr, val, middle, end);
    }

    return false;
  }
};

#endif