/** Array-based implementation of the ADT heap.
@file ArrayMaxHeap.hpp */

#ifndef ARRAY_MAX_HEAP_
#define ARRAY_MAX_HEAP_

#include "abstract_heap.hpp"

template <typename ItemType>
class ArrayMaxHeap : public AbstractHeap<ItemType>
{
private:
   static const int DEFAULT_CAPACITY = 63; // Small capacity to test for a full heap
   ItemType items[DEFAULT_CAPACITY];       // Array of heap items
   int itemCount;                          // Current count of heap items

   // ---------------------------------------------------------------------
   // Most of the private utility methods use an array index as a parameter
   // and in calculations. This should be safe, even though the array is an
   // implementation detail, since the methods are private.
   // ---------------------------------------------------------------------

   // Returns the array index of the left child (if it exists).
   int getLeftChildIndex(const int nodeIndex) const;

   // Returns the array index of the right child (if it exists).
   int getRightChildIndex(int nodeIndex) const;

   // Returns the array index of the parent node.
   int getParentIndex(int nodeIndex) const;

   // Tests whether this node is a leaf.
   bool isLeaf(int nodeIndex) const;

   // Converts a semiheap to a heap
   void heapRebuild(int subTreeRootIndex);

   // Creates a heap from an unordered array.
   void heapCreate();

public:
   ArrayMaxHeap();
   ArrayMaxHeap(const ItemType someArray[], const int arraySize);
   virtual ~ArrayMaxHeap();

   // AbstractHeap Public Methods:
   bool isEmpty() const noexcept;
   int getNumberOfNodes() const noexcept;
   int getHeight() const noexcept;
   ItemType peekTop() const;          // throw std::out_of_range error if empty
   bool add(const ItemType &newData); // false if array is full or newData is a duplicate
   bool remove();                     // false if empty
   void clear() noexcept;

   /** Sorts the items in an array into descending order.
   @pre  None.
   @post  anArray is sorted into descending order; n is unchanged.
   @param anArray  The given array.
   @param n  The size of theArray.
   @throw std::invalid_argument if anArray contains duplicate or exceeds the DEFAULT_CAPACITY */
   void heapSort(ItemType anArray[], int n);
}; // end ArrayMaxHeap
#include "ArrayMaxHeap.tpp"
#endif