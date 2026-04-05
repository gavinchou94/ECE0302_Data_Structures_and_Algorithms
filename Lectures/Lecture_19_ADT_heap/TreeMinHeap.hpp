/** BinaryNode-based implementation of the ADT min-heap.
 * @file TreeMinHeap.hpp */
#ifndef TREE_MIN_HEAP_
#define TREE_MIN_HEAP_

#include "abstract_heap.hpp"
#include "BinaryNode.hpp"
#include <memory>
#include <string>
#include <stdexcept>

template <typename ItemType>
class TreeMinHeap : public AbstractHeap<ItemType>
{
private:
  std::shared_ptr<BinaryNode<ItemType>> rootPtr;
  int itemCount;

  /** Restores the heap property downward from subTreeRootPtr.
   *  @pre: subTreeRootPtr is the only node that may violate the heap property. */
  void heapRebuild(std::shared_ptr<BinaryNode<ItemType>> subTreeRootPtr);

  /** Restores the heap property upward from newNodePtr.
   *  @pre: newNodePtr is the only node that may violate the heap property.
   *  @param path  Bit-string path from root to newNodePtr ('L'/'R' characters). */
  void bubbleShift(std::shared_ptr<BinaryNode<ItemType>> newNodePtr, const std::string &path);

  /** Swaps the data items stored in two nodes. */
  void swapData(std::shared_ptr<BinaryNode<ItemType>> node1,
                std::shared_ptr<BinaryNode<ItemType>> node2);

  /** Returns true if the subtree rooted at subTreeRootPtr contains anEntry. */
  bool contains(const ItemType &anEntry,
                std::shared_ptr<BinaryNode<ItemType>> subTreeRootPtr) const;

public:
  TreeMinHeap();
  virtual ~TreeMinHeap();

  bool isEmpty() const noexcept;
  int getNumberOfNodes() const noexcept;
  int getHeight() const noexcept;

  /** @throw std::out_of_range if the heap is empty. */
  ItemType peekTop() const;

  /** @return false if newData is already present (no duplicates allowed). */
  bool add(const ItemType &newData);

  /** @return false if the heap is empty. */
  bool remove();

  void clear() noexcept;

  /** Sorts arr[0..n-1] using this heap.
   *  @param descending  true  → descending order (default),
   *                     false → ascending order. */
  void heapSort(ItemType *arr, int n, bool descending = true);

}; // end TreeMinHeap

#include "TreeMinHeap.tpp"
#endif