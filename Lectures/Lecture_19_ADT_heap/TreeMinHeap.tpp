#include "TreeMinHeap.hpp"
#include <cmath>
#include <stdexcept>

// ─── Private Helpers ────────────────────────────────────────────────────────

template <typename ItemType>
void TreeMinHeap<ItemType>::swapData(std::shared_ptr<BinaryNode<ItemType>> node1,
                                     std::shared_ptr<BinaryNode<ItemType>> node2)
{
  ItemType temp = node1->getItem();
  node1->setItem(node2->getItem());
  node2->setItem(temp);
}

// TODO: In heapRebuild, in which direction does the node move to restore the heap property?
// In bubbleShift, in which direction does the node move to restore the heap property?
// Compare the code simplicity of heapRebuild and bubbleShift based on their implementations.
// Which method is easier to implement with current BinaryNode implementation and why?

template <typename ItemType>
void TreeMinHeap<ItemType>::heapRebuild(std::shared_ptr<BinaryNode<ItemType>> subTreeRootPtr)
{
  if (subTreeRootPtr == nullptr || subTreeRootPtr->isLeaf())
    return;

  std::shared_ptr<BinaryNode<ItemType>> smallerChildPtr;

  if (subTreeRootPtr->getRightChildPtr() == nullptr)
  { // Only a left child exists; it must be a leaf, so one swap suffices.
    smallerChildPtr = subTreeRootPtr->getLeftChildPtr();
    if (subTreeRootPtr->getItem() > smallerChildPtr->getItem())
      swapData(subTreeRootPtr, smallerChildPtr);
    return;
  }

  // Both children exist — swap with the smaller one, then recurse.
  bool rightIsSmaller = subTreeRootPtr->getRightChildPtr()->getItem() <
                        subTreeRootPtr->getLeftChildPtr()->getItem();
  smallerChildPtr = rightIsSmaller ? subTreeRootPtr->getRightChildPtr()
                                   : subTreeRootPtr->getLeftChildPtr();

  if (subTreeRootPtr->getItem() > smallerChildPtr->getItem())
  {
    swapData(subTreeRootPtr, smallerChildPtr);
    heapRebuild(smallerChildPtr);
  }
}

template <typename ItemType>
void TreeMinHeap<ItemType>::bubbleShift(std::shared_ptr<BinaryNode<ItemType>> newNodePtr,
                                        const std::string &path)
{
  // Walk the path from root toward newNodePtr, storing each ancestor.
  // Then compare upward from newNodePtr to restore the heap property.
  int depth = path.length();
  if (depth == 0)
    return;

  auto current = newNodePtr;

  for (int i = depth - 1; i >= 0; --i)
  {
    // Find the parent of current by re-walking from root to path[0..i-1].
    auto parent = rootPtr;
    for (int j = 0; j < i; ++j)
      parent = (path[j] == 'L') ? parent->getLeftChildPtr()
                                : parent->getRightChildPtr();

    if (parent->getItem() > current->getItem())
    {
      swapData(parent, current);
      current = parent;
    }
    else
    {
      break; // Heap property restored.
    }
  }
}

template <typename ItemType>
bool TreeMinHeap<ItemType>::contains(const ItemType &anEntry,
                                     std::shared_ptr<BinaryNode<ItemType>> subTreeRootPtr) const
{
  if (subTreeRootPtr == nullptr)
    return false;

  if (subTreeRootPtr->getItem() == anEntry)
    return true;

  // TODO: Using the min-heap property, what additional base case can we use to terminate the search early?
  // For example: if (??) { return false; }
  // We recursively search both left and right subtrees. Why can't we use binary search to only search one subtree in a heap?
  // Does the contains() method have O(log n) time complexity? Explain why or why not.

  return contains(anEntry, subTreeRootPtr->getLeftChildPtr()) ||
         contains(anEntry, subTreeRootPtr->getRightChildPtr());
}

// ─── Constructor / Destructor ────────────────────────────────────────────────

template <typename ItemType>
TreeMinHeap<ItemType>::TreeMinHeap() : rootPtr(nullptr), itemCount(0)
{
}

template <typename ItemType>
TreeMinHeap<ItemType>::~TreeMinHeap()
{
  clear();
}

// ─── Public Methods ──────────────────────────────────────────────────────────

template <typename ItemType>
bool TreeMinHeap<ItemType>::isEmpty() const noexcept
{
  return itemCount == 0;
}

template <typename ItemType>
int TreeMinHeap<ItemType>::getNumberOfNodes() const noexcept
{
  return itemCount;
}

template <typename ItemType>
int TreeMinHeap<ItemType>::getHeight() const noexcept
{
  return static_cast<int>(std::ceil(std::log2(itemCount + 1)));
}

template <typename ItemType>
ItemType TreeMinHeap<ItemType>::peekTop() const
{
  if (isEmpty())
    throw std::out_of_range("Heap is empty");
  return rootPtr->getItem();
}

template <typename ItemType>
bool TreeMinHeap<ItemType>::add(const ItemType &newData)
{
  if (contains(newData, rootPtr))
    return false; // No duplicates.

  auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newData);

  if (rootPtr == nullptr)
  {
    rootPtr = newNodePtr;
    itemCount++;
    return true;
  }

  // Build the path to the next insertion point in level-order.
  // Position (itemCount + 1) in a 1-indexed complete binary tree:
  // repeatedly check if the index is even (left) or odd (right), then halve.
  std::string path;
  for (int i = itemCount + 1; i > 1; i /= 2)
    path = (i % 2 == 0 ? "L" : "R") + path;
  // Refresh your memory of project 1 on fixed-width integers and the use of << and >> bitwise operators.
  // For efficiency, we could represent the path as a fixed-width integer and use bitwise operations to determine each direction (left or right) when traversing the tree.
  // For example, pathBits could be an unsigned int, and we can extract each bit to decide the direction at each level.

  // Walk to the parent of the new node.
  auto parent = rootPtr;
  for (int i = 0; i < path.length() - 1; ++i)
    parent = (path[i] == 'L') ? parent->getLeftChildPtr()
                              : parent->getRightChildPtr();

  // Attach the new node.
  if (parent->getLeftChildPtr() == nullptr)
    parent->setLeftChildPtr(newNodePtr);
  else
    parent->setRightChildPtr(newNodePtr);

  itemCount++;
  bubbleShift(newNodePtr, path);
  return true;
}

template <typename ItemType>
bool TreeMinHeap<ItemType>::remove()
{
  if (isEmpty())
    return false;

  if (itemCount == 1)
  {
    rootPtr = nullptr;
    itemCount--;
    return true;
  }

  // Build the path to the last node in level-order.
  std::string path;
  for (int i = itemCount; i > 1; i /= 2)
    path = (i % 2 == 0 ? "L" : "R") + path;

  // Locate the last node.
  auto lastNode = rootPtr;
  for (char direction : path)
    lastNode = (direction == 'L') ? lastNode->getLeftChildPtr()
                                  : lastNode->getRightChildPtr();

  // Copy the last node's data to the root, then remove the last node.
  swapData(rootPtr, lastNode);

  auto parent = rootPtr;
  for (int i = 0; i < path.length() - 1; ++i)
    parent = (path[i] == 'L') ? parent->getLeftChildPtr()
                              : parent->getRightChildPtr();

  if (path.back() == 'L')
    parent->setLeftChildPtr(nullptr);
  else
    parent->setRightChildPtr(nullptr);

  itemCount--;
  heapRebuild(rootPtr);
  return true;
}

template <typename ItemType>
void TreeMinHeap<ItemType>::clear() noexcept
{
  rootPtr = nullptr; // shared_ptr reference counting destroys all nodes.
  itemCount = 0;
}

template <typename ItemType>
void TreeMinHeap<ItemType>::heapSort(ItemType *arr, int n, bool descending)
{
  // Build the heap from the array via repeated add().
  clear();
  for (int i = 0; i < n; ++i)
    add(arr[i]);

  // Repeatedly extract the minimum into the output positions.
  // descending = true  → fill arr from the back, producing ascending order in
  //                       memory but reading it reversed gives descending.
  // descending = false → fill arr from the front.

  if (descending)
  {
    for (int i = n - 1; i >= 0; --i)
    {
      arr[i] = peekTop();
      remove();
    }
  }
  else
  {
    for (int i = 0; i < n; ++i)
    {
      arr[i] = peekTop();
      remove();
    }
  }

  // Alternatively, we can implement heap sort in-place if we were using the array to store the heap.
  // ── Step 1: Build a min-heap from the array bottom-up. ──
  // Start at the last internal node (index n/2 - 1) and call heapRebuild
  // downward to index 0 (the root).
  // for (int idx = n / 2 - 1; idx >= 0; --idx)
  //    heapRebuild(arr, size, idx);

  // ── Step 2: Sort via heap region / sorted region. ──
  // Heap region:   arr[0 .. heapSize - 1]
  // Sorted region: arr[heapSize .. n - 1]
  //
  // Repeat until heap region is empty:
  //    swap arr[0] (current min) with arr[heapSize - 1] (last in heap region)
  //    shrink heap region by one (heapSize--)
  //    call heapRebuild from index 0 to restore heap property
  //
  // Result of this process with a min-heap:
  //    sorted region fills right to left with increasing values → descending order
  //    for ascending order, reverse the array afterward
  // for (int heapSize = n; heapSize > 1; --heapSize)
  // {
  //    swap(arr[0], arr[heapSize - 1]);
  //    heapRebuild(arr, heapSize - 1, 0);
  // }
  // if (!descending) reverse(arr, arr + n);
}

// TODO: In a tree-based heap, finding the last node, the next empty spot for insertion, and tracking each node's parent can be quite tedious and inefficient compared to the array-based approach.
// This is one of the main reasons why textbook-style array-based heap implementations are generally preferred—they allow constant-time access to parent and child nodes using simple index arithmetic.

// Given the inefficiency of finding the last node, the next empty spot for insertion, and tracking parent nodes in a node-based heap,
// can you propose any general strategies or data structure enhancements to address these challenges while keeping the tree-based heap implementation?
// For example, could we maintain additional pointers or data structures to facilitate these operations more efficiently?