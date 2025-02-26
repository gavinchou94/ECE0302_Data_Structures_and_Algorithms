#ifndef _SORT_HPP
#define _SORT_HPP

#include "list.hpp"

/** Sorts an array into ascending order. Uses the selection sort method.
 @pre  list[1..list.getLength()] is an array.
 @post  list[1..list.getLength()] is sorted.
 @param list  The given array. */

template <typename T>
void selection_sort(List<T> &list)
{
    for (int last = list.getLength(); last >= 1; last--)
    {
        // starting with index 1
        int max = 1;
        // find largest item in list[1..last]
        // first comparing with index 2
        for (int i = 2; i <= last; i++)
        {
            if (list.getEntry(i) > list.getEntry(max))
            {
                max = i;
            }
        }
        // swap largest item with list[last]
        if (max != last)
        {
            T temp = list.getEntry(max);
            list.setEntry(max, list.getEntry(last));
            list.setEntry(last, temp);
        }
    }
}

/** Sorts an array into ascending order. Uses the bubble sort method.
 @pre  list[1..list.getLength()] is an array.
 @post  list[1..list.getLength()] is sorted.
 @param list  The given array. */

template <typename T>
void bubble_sort(List<T> &list)
{
    int swaps = 0;
    int last = list.getLength();
    do
    {
        swaps = 0;
        for (int j = 1; j < last; j++)
        {
            if (list.getEntry(j) > list.getEntry(j + 1))
            {
                // swap j and j+1
                T temp = list.getEntry(j + 1);
                list.setEntry(j + 1, list.getEntry(j));
                list.setEntry(j, temp);
                swaps++;
            }
        }
        last--;
        // finish one full pass, can add a round counter here
    } while (swaps > 0);
}
// TODO: review above, think what makes the bubble sort stop, why is it O(n) in best case
// whereas there are clearly two loops nested?

/** Sorts an array into ascending order. Uses the insertion sort method.
 @pre  list[1..list.getLength()] is an array.
 @post  list[1..list.getLength()] is sorted.
 @param list  The given array. */

template <typename T>
void insertion_sort(List<T> &list)
{
    // starting with index 2
    for (int i = 2; i <= list.getLength(); i++)
    {
        // find the right position for val = list[i]
        T val = list.getEntry(i);
        int index = 1;
        // list before i is considered sorted
        for (int j = i - 1; j >= 1; j--)
        {
            if (val > list.getEntry(j))
            {
                index = j + 1;
                break;
            }
        }
        if (index != i)
        {
            list.insert(index, val);
            list.remove(i + 1);
        }
    }
}
// TODO: review above, think what keyword makes the insertion sort to finish early,
// why is it O(n) in best case whereas there are clearly two loops nested?

/** Merges two sorted array segments list[first..mid] and
    list[mid+1..last] into one sorted array.
 @pre  first <= mid <= last. The subarrays list[first..mid] and
    list[mid+1..last] are each sorted in increasing order.
 @post  list[first..last] is sorted.
 @param list  The given array.
 @param first  The index of the beginning of the first segment in list.
 @param mid  The index of the end of the first segment in list;
    mid + 1 marks the beginning of the second segment.
 @param last  The index of the last element in the second segment in list.*/
template <typename T>
void merge(List<T> &list, int first, int mid, int last)
{
    if (first > mid || mid >= last || first < 1 || last > list.getLength())
    {
        throw std::out_of_range("Invalid range for merge");
    }
    // create a temporary array
    List<T> temp = list;

    // merge two sorted segments
    int i = first;
    int j = mid + 1;
    for (int k = first; k <= last; k++)
    {
        // if all elements in one segment are merged
        // directly copy the other segment
        if (i > mid)
        {
            list.setEntry(k, temp.getEntry(j));
            j++;
        }
        else if (j > last)
        {
            list.setEntry(k, temp.getEntry(i));
            i++;
        }
        // otherwise, compare two segments' first element
        // and copy the smaller one
        else if (temp.getEntry(i) <= temp.getEntry(j))
        {
            list.setEntry(k, temp.getEntry(i));
            i++;
        }
        else
        {
            list.setEntry(k, temp.getEntry(j));
            j++;
        }
    }
}
// TODO: review above, what is the time complexity of this utility function merge()?

/** Sorts the items in an array into ascending order. Uses the merge sort method.
 @pre  list[first..last] is an array.
 @post  list[first..last] is sorted in ascending order.
 @param list  The given array.
 @param first  The index of the first element to consider in list.
 @param last  The index of the last element to consider in list.
 @throw std::out_of_range if first < 1 or last > list.getLength()
 */

template <typename T>
void merge_sort(List<T> &list, int first, int last)
{
    if (first < 1 || last > list.getLength())
    {
        throw std::out_of_range("Invalid range for merge_sort");
    }
    if (first >= last)
    {
        return;
    }
    if (first < last)
    {
        // Sort each half
        int mid = first + (last - first) / 2; // Index of midpoint

        // Sort left half list[first..mid]
        merge_sort(list, first, mid);

        // Sort right half list[mid+1..last]
        merge_sort(list, mid + 1, last);

        // Merge the two halves
        merge(list, first, mid, last);
    } // end if
}
// TODO: if list is of size=302
// how many recursive calls to mergeSort()(i.e., how deep) are made?

/** Sorts an array into ascending order. Uses the quick sort method.
 @pre  list[first..last] is an array.
 @post  list[first..last] is sorted.
 @throw std::out_of_range if first < 1 or last > list.getLength()
 @param list  The given array.
 @param first  The start element to consider in list.
 @param last  The end element to consider in list. */

template <typename T>
void quick_sort(List<T> &list, int first, int last)
{
    // TODO, note the 1-index based list
    // See partition() below
    // Implement in Programming Problem 4
}
// TODO: which of the list initial condition is considered
// closer to best-case quick sort condition? (small to large)
// A. 9 10 13 16 18 19 20 24 25 26 27 30 35
// B. 98 67 63 30 27 26 25 24 23 22 8 7 4
// C. 25 22 7 23 8 4 24 63 27 26 98 67 30
// D. 13 13 13 13 12 12 12 12 14 14 14 14

/** Partitions the entries in an array about a pivot entry for quicksort.
 @pre  list[first..last] is an array; first <= last.
 @throw std::out_of_range if first > last, or if first < 1 or last > list.getLength()
 @post  list[first..last] is partitioned such that:
 S1 = list[first..pivotIndex-1] <= pivot
 list[pivotIndex]          == pivot
 S2 = list[pivotIndex+1..last]  >= pivot
 @param list  The given array.
 @param first  The start entry to consider in list.
 @param last  The end entry to consider in list.
 @return  The index of the pivot.
 */

template <typename T>
int partition(List<T> &list, int first, int last)
{
    // TODO, note the 1-index based list
    // Implement in Programming Problem 4
}
// TODO: check your own implementation
// is your utility function partition() of order O(n)?

/** Sorts an array into ascending order. Uses the radix sort method.
 * Due to the feature of radix sort, the array must be of type int.
 @pre  list[1..list.getLength()] is an array.
 @post  list[1..list.getLength()] is sorted.
 @param list  The given array. */

void radix_sort(List<int> &list)
{
    // TODO later, better with list swap
}
#endif
