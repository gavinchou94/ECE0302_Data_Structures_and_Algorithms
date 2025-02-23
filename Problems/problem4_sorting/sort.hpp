#ifndef _SORT_HPP
#define _SORT_HPP

#include "list.hpp"

/** Sorts a list into ascending order. Uses the quick sort method.
 @pre  list[first..last] is a list.
 @post  list[first..last] is sorted.
 @throw std::out_of_range if first < 1 or last > list.getLength()
 @param list  The given list.
 @param first  The start element to consider in list.
 @param last  The end element to consider in list. */

template <typename T>
void quick_sort(List<T> &list, int first, int last)
{
    // TODO, note the 1-index based list

    // must call partition below
}

/** Partitions the entries in a list about a pivot entry for quicksort.
 @pre  list[first..last] is an list; first <= last.
 @throw std::out_of_range if first > last, or if first < 1 or last > list.getLength()
 @post  list[first..last] is partitioned such that:
 S1 = list[first..pivotIndex-1] <= pivot
      list[pivotIndex]          == pivot
 S2 = list[pivotIndex+1..last]  >= pivot
 @param list  The given list.
 @param first  The start entry to consider in list.
 @param last  The end entry to consider in list.
 @return  The index of the pivot.
 */

template <typename T>
int partition(List<T> &list, int first, int last)
{

    // TODO, note the 1-index based list

    // You can choose the pivot yourself, but no matter what you choose
    // list[first..pivotIndex-1] <= pivot, list[pivotIndex] == pivot, list[pivotIndex + 1..last] >= pivot
}
#endif
