#include <cmath>
#include <stdexcept>
#include "ArrayMaxHeap.hpp"

// -----------------------------------------------------------------------
// Private helpers
// -----------------------------------------------------------------------

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 2;
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(const int nodeIndex) const
{
   return (nodeIndex - 1) / 2;
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(const int nodeIndex) const
{
   return (getLeftChildIndex(nodeIndex) >= itemCount);
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
   // Start at the last parent and rebuild up to the root
   for (int index = itemCount / 2 - 1; index >= 0; index--)
      heapRebuild(index);
}

// -----------------------------------------------------------------------
// Public methods
// -----------------------------------------------------------------------

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0)
{
}

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const ItemType someArray[], const int arraySize)
    : itemCount(arraySize)
{
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];
   heapCreate();
}

template <typename ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
   clear();
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const noexcept
{
   return itemCount == 0;
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const noexcept
{
   return ceil(log2(itemCount + 1));
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const noexcept
{
   return itemCount;
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::clear() noexcept
{
   itemCount = 0;
}

// -----------------------------------------------------------------------
// TODO (private and public methods)
// -----------------------------------------------------------------------

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(const int subTreeNodeIndex)
{
   if (!isLeaf(subTreeNodeIndex))
   {
      // TODO
      // 1. Find the larger child
      // 2. If the node < larger child, swap them
      // 3. Recurse on the swapped child's index
   }
}

template <typename ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const
{
   // TODO
   // Throw std::out_of_range if heap is empty
   return ItemType(); // placeholder
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType &newData)
{
   // TODO
   // 1. Return false if full or newData is a duplicate
   // 2. Place newData at the end
   // 3. Bubble up: swap with parent until heap property is restored
   return false; // placeholder
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
   // TODO
   // 1. Return false if empty
   // 2. Remove the root by replacing it with the last item
   // 3. Bubble down by calling heapRebuild to restore heap property
   return false; // placeholder
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapSort(ItemType anArray[], int n)
{
   // TODO
   // 1. Start with entire array as heap region, sorted region empty
   // 2. Build max heap (bottom-up)
   // 3. Repeat until heap is empty:
   //    Swap root (max) with last element in heap
   //    Move that element to sorted region (end of array)
   //    Shrink heap region by 1
   //    Heapify root to restore heap
   // 4. End state: Heap region empty, Sorted region = entire array (ascending order)
   // 5. Reverse array to get descending order
}