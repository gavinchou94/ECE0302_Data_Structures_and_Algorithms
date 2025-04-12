#include "TreeMinHeap.hpp"
#include <stdexcept>

template <typename ItemType>
void TreeMinHeap<ItemType>::heapRebuild(std::shared_ptr<BinaryNode<ItemType>> subTreeRootPtr)
{
  if (subTreeRootPtr->isLeaf() || subTreeRootPtr == nullptr)
    return;

  if (subTreeRootPtr->getRightChildPtr() == nullptr)
  {
    if (subTreeRootPtr->getItem() > subTreeRootPtr->getLeftChildPtr()->getItem())
    {
      // swap the data
      swapData(subTreeRootPtr, subTreeRootPtr->getLeftChildPtr());
      // the left child must be a leaf, so we are done
      return;
    }
  }
  else // both children are present
  {
    // find the smaller child
    std::shared_ptr<BinaryNode<ItemType>> smallerChildPtr = subTreeRootPtr->getLeftChildPtr();
    if (subTreeRootPtr->getRightChildPtr()->getItem() < smallerChildPtr->getItem())
      smallerChildPtr = subTreeRootPtr->getRightChildPtr();
    // swap the data if necessary
    if (subTreeRootPtr->getItem() > smallerChildPtr->getItem())
    {
      swapData(subTreeRootPtr, smallerChildPtr);
      // recursively rebuild the heap
      heapRebuild(smallerChildPtr);
    }
  }
}

// For heapRebuild, what are the directions of moving the node?
// For bubbleUp, what are the directions of moving the node?
// Based on the given implementation, compare their code simplicity
// and determine which one is easier to implement and why is that?

template <typename ItemType>
void TreeMinHeap<ItemType>::bubbleUp(std::shared_ptr<BinaryNode<ItemType>> newNodePtr, const std::string &path)
{
  auto current = newNodePtr;
  auto parent = rootPtr;

  // Traverse the path to find the parent node
  for (int i = 0; i < path.length() - 1; i++)
  {
    parent = (path[i] == 'L') ? parent->getLeftChildPtr() : parent->getRightChildPtr();
  }

  // Bubble up the new node
  for (int i = path.length() - 1; i >= 0; --i)
  {
    if (parent->getItem() > current->getItem())
    {
      swapData(parent, current); // Swap the data
      current = parent;          // Move up the tree
      if (i > 0)                 // Update the parent
      {
        parent = rootPtr;
        for (int j = 0; j < i - 1; ++j)
        {
          parent = (path[j] == 'L') ? parent->getLeftChildPtr() : parent->getRightChildPtr();
        }
      }
    }
    else
    {
      break; // Heap property is restored
    }
  }
}

template <typename ItemType>
void TreeMinHeap<ItemType>::swapData(std::shared_ptr<BinaryNode<ItemType>> node1, std::shared_ptr<BinaryNode<ItemType>> node2)
{
  ItemType temp = node1->getItem();
  node1->setItem(node2->getItem());
  node2->setItem(temp);
}

template <typename ItemType>
bool TreeMinHeap<ItemType>::contains(const ItemType &anEntry, std::shared_ptr<BinaryNode<ItemType>> subTreeRootPtr) const
{
  if (subTreeRootPtr == nullptr)
    return false; // Base case: reached a null node
  if (subTreeRootPtr->getItem() == anEntry)
    return true; // Found the entry

  // Base on min heap property, what other base case can we have to cut the search?

  // Recursively search in left and right subtrees
  // But why cannot we use binary search to just search in one side?
  // And does the contains method have time complexity of O(log n)?
  return contains(anEntry, subTreeRootPtr->getLeftChildPtr()) || contains(anEntry, subTreeRootPtr->getRightChildPtr());
}

// Public Methods:

template <typename ItemType>
TreeMinHeap<ItemType>::TreeMinHeap()
{
  itemCount = 0;
  rootPtr = nullptr;
}

template <typename ItemType>
TreeMinHeap<ItemType>::~TreeMinHeap()
{
  clear();
}

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
  return ceil(log2(itemCount + 1));
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
  if (contains(newData, rootPtr)) // Duplicate entry
    return false;

  // Create a new node
  auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newData);

  if (rootPtr == nullptr)
  { // Empty heap
    rootPtr = newNodePtr;
    itemCount++;
    return true;
  }

  // Find the empty spot using the path to the new node
  std::shared_ptr<BinaryNode<ItemType>> current = rootPtr;
  std::string path = "";
  int i = itemCount + 1; // The position of the new node in a complete binary tree
  while (i > 1)
  {
    if (i % 2 == 0)
      path = "L" + path; // Left child
    else
      path = "R" + path; // Right child
    i /= 2;
  }
  // Refresh your memory of project 1 on fixed-width integer
  // and research the usage of << and >> operators
  // What can you do to make the path generation more efficient?

  for (char direction : path)
  {
    if (direction == 'L')
    {
      if (current->getLeftChildPtr() == nullptr)
        break;
      current = current->getLeftChildPtr();
    }
    else
    { // direction == 'R'
      if (current->getRightChildPtr() == nullptr)
        break;
      current = current->getRightChildPtr();
    }
  }

  if (current->getLeftChildPtr() == nullptr)
    current->setLeftChildPtr(newNodePtr);
  else
    current->setRightChildPtr(newNodePtr);

  itemCount++;

  // Bubble up the new node to restore the heap property
  bubbleUp(newNodePtr, path);
  return true;
}

template <typename ItemType>
bool TreeMinHeap<ItemType>::remove()
{
  if (isEmpty())
    return false;
  auto lastNode = rootPtr;
  if (itemCount == 1)
  {
    rootPtr = nullptr;
    itemCount--;
    return true;
  }
  std::string path = "";
  int i = itemCount;
  while (i > 1)
  {
    if (i % 2 == 0)
      path = "L" + path; // Left child
    else
      path = "R" + path; // Right child
    i /= 2;
  }
  for (char direction : path)
  {
    lastNode = (direction == 'L') ? lastNode->getLeftChildPtr() : lastNode->getRightChildPtr();
  }
  // swap the data
  swapData(rootPtr, lastNode);

  // remove the last node
  auto parent = rootPtr;
  for (int i = 0; i < path.length() - 1; ++i)
  {
    parent = (path[i] == 'L') ? parent->getLeftChildPtr() : parent->getRightChildPtr();
  }
  if (path[path.length() - 1] == 'L')
    parent->setLeftChildPtr(nullptr);
  else
    parent->setRightChildPtr(nullptr);

  itemCount--;

  // rebuild the heap
  heapRebuild(rootPtr);
  return true;
}

template <typename ItemType>
void TreeMinHeap<ItemType>::clear() noexcept
{
  rootPtr = nullptr; // due to shared_ptr, this will delete all nodes
  itemCount = 0;
}

template <typename ItemType>
void TreeMinHeap<ItemType>::sort_a(ItemType *arr, int n)
{
  TreeMinHeap<ItemType> heap;
  bool duplicate = true;
  for (int i = 0; i < n; i++)
  {
    duplicate = heap.add(arr[i]);
    if (!duplicate)
    {
      throw std::invalid_argument("Duplicate entry found");
    }
  }
  for (int i = 0; i < n; i++)
  {
    arr[i] = heap.peekTop();
    heap.remove();
  }
}

template <typename ItemType>
void TreeMinHeap<ItemType>::sort_d(ItemType *arr, int n)
{
  TreeMinHeap<ItemType> heap;
  bool duplicate = true;
  for (int i = 0; i < n; i++)
  {
    duplicate = heap.add(arr[i]);
    if (!duplicate)
    {
      throw std::invalid_argument("Duplicate entry found");
    }
  }
  for (int i = n - 1; i >= 0; i--)
  {
    arr[i] = heap.peekTop();
    heap.remove();
  }
}
// In tree-based heap, there are many scenarios that we need to find the last node or the empty spot
// to insert a new node. The current implementation is not quite efficient.

// Can you think of a better way to find the last node or the empty spot using an ADT we learned in this course?
// What type of ADT can be used to quickly find the last node or the empty spot?