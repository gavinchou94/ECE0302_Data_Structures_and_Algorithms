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

   // Private index helpers (array-index-based, safe since methods are private)
   int getLeftChildIndex(const int nodeIndex) const;
   int getRightChildIndex(int nodeIndex) const;
   int getParentIndex(int nodeIndex) const;
   bool isLeaf(int nodeIndex) const;
   void heapCreate();

   // Private methods
   void heapRebuild(int subTreeRootIndex);

public:
   ArrayMaxHeap();
   ArrayMaxHeap(const ItemType someArray[], const int arraySize);
   virtual ~ArrayMaxHeap();

   // Completed
   bool isEmpty() const noexcept;
   int getNumberOfNodes() const noexcept;
   int getHeight() const noexcept;
   void clear() noexcept;

   // TODO
   ItemType peekTop() const;          // throws std::out_of_range if empty
   bool add(const ItemType &newData); // false if full or newData is a duplicate
   bool remove();                     // false if empty

   /** Sorts anArray[0..n-1] into descending order using heap sort.
    @throw std::invalid_argument if anArray has duplicates or n > DEFAULT_CAPACITY. */
   void heapSort(ItemType anArray[], int n);
}; // end ArrayMaxHeap

#include "ArrayMaxHeap.tpp"
#endif