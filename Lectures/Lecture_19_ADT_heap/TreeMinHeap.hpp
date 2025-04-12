/** BinaryNode-based implementation of the ADT heap.
@file TreeMinHeap.hpp */

#ifndef TREE_MIN_HEAP_
#define TREE_MIN_HEAP_
#include "abstract_heap.hpp"
#include "BinaryNode.hpp"
#include <stdexcept>

template <typename ItemType>
class TreeMinHeap : public AbstractHeap<ItemType>
{
private:
  std::shared_ptr<BinaryNode<ItemType>> rootPtr; // Pointer to root node
  int itemCount;                                 // Current count of heap items

  // Helper for remove, converts a semiheap to a heap
  // subTreeRootPtr is the only node that might violate the heap property
  void heapRebuild(std::shared_ptr<BinaryNode<ItemType>> subTreeRootPtr);

  // Helper for add, bubble up the new node to restore the heap property
  // newNodePtr is the only node that might violate the heap property
  void bubbleUp(std::shared_ptr<BinaryNode<ItemType>> newNodePtr, const std::string &path);

  // Swap the data in two nodes
  void swapData(std::shared_ptr<BinaryNode<ItemType>> node1, std::shared_ptr<BinaryNode<ItemType>> node2);

  // Check if the heap contains an item
  bool contains(const ItemType &anEntry, std::shared_ptr<BinaryNode<ItemType>> subTreeRootPtr) const;

public:
  TreeMinHeap();
  virtual ~TreeMinHeap();

  // AbstractHeap Public Methods:
  bool isEmpty() const noexcept;
  int getNumberOfNodes() const noexcept;
  int getHeight() const noexcept;
  ItemType peekTop() const;          // throw std::out_of_range error if empty
  bool add(const ItemType &newData); // false if newData is a duplicate
  bool remove();                     // false if empty
  void clear() noexcept;

  void sort_a(ItemType *arr, int n); // sort array in ascending order
  void sort_d(ItemType *arr, int n); // sort array in descending order

}; // end TreeMinHeap

#include "TreeMinHeap.tpp"
#endif