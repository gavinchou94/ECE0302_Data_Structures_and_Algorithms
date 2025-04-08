#include <cmath> // for log2
#include "ArrayMaxHeap.hpp"
#include <stdexcept>

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
} // end getLeftChildIndex, private method

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 2;
} // end getRightChildIndex, private method

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(const int nodeIndex) const
{
   return (nodeIndex - 1) / 2;
} // end getParentIndex, private method

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(const int nodeIndex) const
{
   return (getLeftChildIndex(nodeIndex) >= itemCount);
} // end isLeaf, private method

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(const int subTreeNodeIndex)
{
   if (!isLeaf(subTreeNodeIndex))
   {
      // TODO

      // Find larger child
      // Swap with larger child if node value is smaller
      // Continue with the recursion at that child

   } // end if
} // end heapRebuild, private method

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
   // Start with the last parent node and rebuild the heap to the root
   for (int index = itemCount / 2 - 1; index >= 0; index--)
   {
      heapRebuild(index);
   } // end for
} // end heapCreate, private method

//******************************************************************
//
// Public methods start here
//
//******************************************************************

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0)
{
} // end default constructor

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const ItemType someArray[], const int arraySize) : itemCount(arraySize)
{
   // Copy given values into the array
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];

   // Reorganize the array into a heap
   heapCreate();
} // end constructor

template <typename ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
   clear();
} // end destructor

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const noexcept
{
   return itemCount == 0;
} // end isEmpty

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const noexcept
{
   return ceil(log2(itemCount + 1));
} // end getHeight

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const noexcept
{
   return itemCount;
} // end getNumberOfNodes

template <typename ItemType>
void ArrayMaxHeap<ItemType>::clear() noexcept
{
   itemCount = 0;
} // end clear

template <typename ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const
{
   // TODO
   return ItemType(); // Placeholder
} // end peekTop

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType &newData)
{
   // TODO

   // Place newData in the last position
   // Swap it with its parent until the heap property is restored
   // Make sure to update itemCount

   return false; // Placeholder
} // end add

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
   // TODO

   // remove the last item
   // swap it with the root
   // rebuild the heap
   // make sure to update itemCount

   return false; // Placeholder
} // end remove

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapSort(ItemType anArray[], int n)
{
   // TODO

   // Build initial heap
   // Remove root, swap, and rebuild the heap

} // end heapSort
