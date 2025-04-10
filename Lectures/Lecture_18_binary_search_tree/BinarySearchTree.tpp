/** @file BinarySearchTree.tpp */
#include <iostream>
#include <functional>
#include <cmath>
#include <stdexcept>

#include "BinarySearchTree.hpp"

//////////////////////////////////////////////////////////////
//
//      Helper Section
//
//////////////////////////////////////////////////////////////

template <class ItemType>
int BinarySearchTree<ItemType>::getLeftChildIndex(int parentIndex) const
{
   return 2 * parentIndex + 1;
}

template <class ItemType>
int BinarySearchTree<ItemType>::getRightChildIndex(int parentIndex) const
{
   return 2 * parentIndex + 2;
}

template <class ItemType>
int BinarySearchTree<ItemType>::getParentIndex(int childIndex) const
{
   return (childIndex - 1) / 2;
}

template <class ItemType>
int BinarySearchTree<ItemType>::getIndexOf(const ItemType &anEntry) const
{
   int currentIndex = 0;

   while (currentIndex < capacity && treeArray[currentIndex] != ItemType())
   {
      if (treeArray[currentIndex] == anEntry)
      {
         return currentIndex; // Entry found, return its index
      }
      else if (anEntry < treeArray[currentIndex])
      {
         currentIndex = getLeftChildIndex(currentIndex); // Move to the left child
      }
      else
      {
         currentIndex = getRightChildIndex(currentIndex); // Move to the right child
      }
   }

   return -1; // Entry not found, return -1
}

template <class ItemType>
int BinarySearchTree<ItemType>::getHeightHelper(int index) const
{
   if (treeArray[index] == ItemType())
   {
      return 0; // Base case: empty node
   }

   int leftHeight = getHeightHelper(getLeftChildIndex(index));
   int rightHeight = getHeightHelper(getRightChildIndex(index));

   return 1 + std::max(leftHeight, rightHeight); // Add 1 for the current node
}

template <class ItemType>
void BinarySearchTree<ItemType>::resizeArray()
{
   capacity = 2 * capacity + 1;
   treeArray.resize(capacity);
   // Why is resizing by twice necessary important here in this implementation of BST?
   // and what disadvantages can you see here?
}

template <class ItemType>
void BinarySearchTree<ItemType>::shiftSubtreeUp(int &currentIndex, int &targetIndex)
{
   if (currentIndex >= capacity || treeArray[currentIndex] == ItemType())
   {
      return; // Base case: index is out of bounds or empty node
   }

   // Shift the current node to the target index
   treeArray[targetIndex] = treeArray[currentIndex];
   treeArray[currentIndex] = ItemType(); // Mark the current index as empty

   // Recursively shift the left and right subtrees
   int currentleft = getLeftChildIndex(currentIndex);
   int targetleft = getLeftChildIndex(targetIndex);
   shiftSubtreeUp(currentleft, targetleft);
   int currentright = getRightChildIndex(currentIndex);
   int targetright = getRightChildIndex(targetIndex);
   shiftSubtreeUp(currentright, targetright);
}

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : size(0), capacity(15), treeArray(15, ItemType())
{
} // end default constructor

template <class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
   return size == 0;
} // end isEmpty

template <class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
   return getHeightHelper(0); // Start from the root (index 0)
} // end getHeight

template <class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
   return size;
} // end getNumberOfNodes

template <class ItemType>
void BinarySearchTree<ItemType>::clear()
{
   treeArray.clear();
   treeArray.resize(capacity, ItemType());
   size = 0;
} // end clear

template <class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const
{
   if (isEmpty())
   {
      throw std::out_of_range("Tree is empty.");
   }
   return treeArray[0];
} // end getRootData

template <class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType &newData)
{
   if (isEmpty())
   {
      treeArray[0] = newData;
      size = 1;
   }
   else
   {
      treeArray[0] = newData;
   }
   // What can you see the problem here if we are trying to set the root data to a new value?
   // What is the possible solution considering this implementation of BST?

} // end setRootData

template <class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType &newData)
{
   // Check if the new data is already in the tree
   if (contains(newData))
   {
      return false; // Duplicate entry, do not add
   }

   // If the tree is empty, insert the new data at the root
   if (isEmpty())
   {
      treeArray[0] = newData;
      size = 1;
      return true; // Successfully added as the root
   }

   // if capacity's allowed height is equal to the current height of the tree, resize the array
   if (std::floor(std::log2(capacity + 1)) < getHeight() + 1)
   {
      resizeArray();
   }

   // Insert the new data into the correct position to maintain the binary search tree property
   int parentIndex = 0;
   while (true)
   {
      if (newData < treeArray[parentIndex])
      // if newData is less than the parent, go to the left child of the parent
      {
         int leftChildIndex = getLeftChildIndex(parentIndex);
         if (treeArray[leftChildIndex] == ItemType())
         {
            treeArray[leftChildIndex] = newData;
            break;
            // and if the left child is empty, insert the new data there.
         }
         parentIndex = leftChildIndex;
         // Move to the left child index for the next iteration
      }
      else
      {
         // If newData is greater than the parent, go to the right child of the parent
         int rightChildIndex = getRightChildIndex(parentIndex);
         if (treeArray[rightChildIndex] == ItemType())
         {
            treeArray[rightChildIndex] = newData;
            break;
            // and if the right child is empty, insert the new data there.
         }
         parentIndex = rightChildIndex;
         // Move to the right child index for the next iteration
      }
   }
   size++;
   return true;

} // end add

template <class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &target)
{
   if (!contains(target))
   {
      return false; // Target not found, nothing to remove
   }

   int targetIndex = getIndexOf(target);

   // Case 1: Node is a leaf
   int leftChildIndex = getLeftChildIndex(targetIndex);
   int rightChildIndex = getRightChildIndex(targetIndex);
   if (leftChildIndex >= capacity || treeArray[leftChildIndex] == ItemType()) // No left child
   {
      if (rightChildIndex >= capacity || treeArray[rightChildIndex] == ItemType()) // No right child
      {
         treeArray[targetIndex] = ItemType(); // Remove the leaf
         size--;
         return true;
      }
   }

   // Case 2: Node has one child
   if (leftChildIndex >= capacity || treeArray[leftChildIndex] == ItemType()) // No left child
   {
      // Shift all descendants of the right child up
      int temp = targetIndex;
      shiftSubtreeUp(rightChildIndex, temp);
      size--;
      return true;
   }
   if (rightChildIndex >= capacity || treeArray[rightChildIndex] == ItemType()) // No right child
   {
      // Shift all descendants of the left child up
      int temp = targetIndex;
      shiftSubtreeUp(leftChildIndex, temp);
      size--;
      return true;
   }

   // Case 3: Node has two children
   // Find the in-order successor (smallest value in the right subtree)
   int successorIndex = rightChildIndex;
   while (getLeftChildIndex(successorIndex) < capacity && treeArray[getLeftChildIndex(successorIndex)] != ItemType())
   {
      successorIndex = getLeftChildIndex(successorIndex);
   }

   // Recursively remove the in-order successor
   ItemType successorValue = treeArray[successorIndex];
   remove(treeArray[successorIndex]);
   treeArray[targetIndex] = successorValue;
   return true;
} // end remove

template <class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType &anEntry) const
{
   int index = getIndexOf(anEntry);
   if (index != -1)
   {
      return treeArray[index];
   }
   else
   {
      throw std::out_of_range("Entry not found in the tree.");
   }
} // end getEntry

template <class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &anEntry) const
{
   return getIndexOf(anEntry) != -1;
} // end contains

template <class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType &)) const
{
   inorderHelper(0, visit); // Start traversal from the root (index 0)
}

template <class ItemType>
void BinarySearchTree<ItemType>::inorderHelper(int index, void visit(ItemType &)) const
{
   if (index >= capacity)
   {
      return; // Base case
   }

   // Traverse the left subtree
   int leftChildIndex = getLeftChildIndex(index);
   if (leftChildIndex < capacity && treeArray[leftChildIndex] != ItemType())
   {
      inorderHelper(leftChildIndex, visit);
   }

   // Visit the current node if it's not empty
   if (treeArray[index] != ItemType())
   {
      visit(const_cast<ItemType &>(treeArray[index]));
   }

   // Traverse the right subtree
   int rightChildIndex = getRightChildIndex(index);
   if (rightChildIndex < capacity && treeArray[rightChildIndex] != ItemType())
   {
      inorderHelper(rightChildIndex, visit);
   }
}

template <class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType &)) const
{
   preorderHelper(0, visit); // Start traversal from the root (index 0)
}

template <class ItemType>
void BinarySearchTree<ItemType>::preorderHelper(int index, void visit(ItemType &)) const
{
   if (index >= capacity)
   {
      return; // Base case
   }

   // Visit the current node if it's not empty
   if (treeArray[index] != ItemType())
   {
      visit(const_cast<ItemType &>(treeArray[index]));
   }

   // Traverse the left subtree
   int leftChildIndex = getLeftChildIndex(index);
   if (leftChildIndex < capacity && treeArray[leftChildIndex] != ItemType())
   {
      preorderHelper(leftChildIndex, visit);
   }

   // Traverse the right subtree
   int rightChildIndex = getRightChildIndex(index);
   if (rightChildIndex < capacity && treeArray[rightChildIndex] != ItemType())
   {
      preorderHelper(rightChildIndex, visit);
   }
}

template <class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType &)) const
{
   postorderHelper(0, visit); // Start traversal from the root (index 0)
}

template <class ItemType>
void BinarySearchTree<ItemType>::postorderHelper(int index, void visit(ItemType &)) const
{
   if (index >= capacity)
   {
      return; // Base case
   }

   // Traverse the left subtree
   int leftChildIndex = getLeftChildIndex(index);
   if (leftChildIndex < capacity && treeArray[leftChildIndex] != ItemType())
   {
      postorderHelper(leftChildIndex, visit);
   }

   // Traverse the right subtree
   int rightChildIndex = getRightChildIndex(index);
   if (rightChildIndex < capacity && treeArray[rightChildIndex] != ItemType())
   {
      postorderHelper(rightChildIndex, visit);
   }

   // Visit the current node if it's not empty
   if (treeArray[index] != ItemType())
   {
      visit(const_cast<ItemType &>(treeArray[index]));
   }
}