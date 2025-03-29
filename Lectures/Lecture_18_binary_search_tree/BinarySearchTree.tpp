/** @file BinarySearchTree.tpp */
#include <iostream>
#include <functional>

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
void BinarySearchTree<ItemType>::resizeArray()
{
   capacity *= 2;
   treeArray.resize(capacity);

   // Why is resizing by twice necessary important here in this implementation of BST?
   // and what disadvantages can you see here?
}

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : size(0), capacity(10), treeArray(10, ItemType())
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
   return std::ceil(std::log2(size + 1));

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

   // If the tree is full, we need to resize the array
   if (size == capacity)
   {
      resizeArray();
   }

   // Add the new data to the next available position
   int currentIndex = size;
   treeArray[currentIndex] = newData;
   size++;

   // Insert the new data into the correct position to maintain the binary search tree property
   int parentIndex = 0;
   while (true)
   {
      if (newData < treeArray[parentIndex])
      // if newData is less than the parent, go to the left child of the parent
      {
         int leftChildIndex = getLeftChildIndex(parentIndex);
         if (leftChildIndex >= size || treeArray[leftChildIndex] == ItemType())
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
         if (rightChildIndex >= size || treeArray[rightChildIndex] == ItemType())
         {
            treeArray[rightChildIndex] = newData;
            break;
            // and if the right child is empty, insert the new data there.
         }
         parentIndex = rightChildIndex;
         // Move to the right child index for the next iteration
      }
   }

   return true;

} // end add

template <class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &target)
{
   // Tree is not empty because the contains check ensures the target exists

   if (!contains(target))
   {
      return false; // Target not found, nothing to remove
   }

   int targetIndex = -1; // Declare and initialize targetIndex
   for (int i = 0; i < size; i++)
   {
      if (treeArray[i] == target)
      {
         targetIndex = i;
         break;
      }
   }

   // Replace the target with the last element
   treeArray[targetIndex] = treeArray[size - 1];
   size--;

   // Restore binary search tree property
   int currentIndex = targetIndex;
   while (true)
   {
      int leftChildIndex = getLeftChildIndex(currentIndex);
      int rightChildIndex = getRightChildIndex(currentIndex);

      // Determine the correct child to swap with based on BST property
      int swapChildIndex = -1;
      if (leftChildIndex < size && treeArray[currentIndex] < treeArray[leftChildIndex])
      {
         swapChildIndex = leftChildIndex;
         // If the left child is greater than the current node, it becomes the swap candidate
      }
      if (rightChildIndex < size && treeArray[currentIndex] > treeArray[rightChildIndex])
      {
         swapChildIndex = rightChildIndex;
         // If the right child is smaller than the current node, it becomes the swap candidate
      }

      if (swapChildIndex == -1)
      {
         break;
         // If no valid swap candidate is found, the BST property is restored
      }

      std::swap(treeArray[currentIndex], treeArray[swapChildIndex]);
      currentIndex = swapChildIndex;
   }

   return true;

} // end remove

template <class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType &anEntry) const
{
   // Find the index of the target entry
   for (int i = 0; i < size; i++)
   {
      if (treeArray[i] == anEntry)
      {
         return treeArray[i];
      }
   }
   throw std::out_of_range("Entry not found in the tree.");

} // end getEntry

template <class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &anEntry) const
{
   for (int i = 0; i < size; i++)
   {
      if (treeArray[i] == anEntry)
      {
         return true;
      }
   }
   return false;

} // end contains

template <class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType &)) const
{
   inorderHelper(0, visit); // Start traversal from the root (index 0)
}

template <class ItemType>
void BinarySearchTree<ItemType>::inorderHelper(int index, void visit(ItemType &)) const
{
   if (index >= size)
   {
      return; // Base case: index is out of bounds
   }

   // Traverse the left subtree
   int leftChildIndex = getLeftChildIndex(index);
   inorderHelper(leftChildIndex, visit);

   // Visit the current node
   visit(const_cast<ItemType &>(treeArray[index]));

   // Traverse the right subtree
   int rightChildIndex = getRightChildIndex(index);
   inorderHelper(rightChildIndex, visit);
}

template <class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType &)) const
{
   //
}

template <class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType &)) const
{
   //
}
