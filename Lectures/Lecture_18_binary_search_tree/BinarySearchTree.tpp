/** @file BinarySearchTree.tpp */

#include <iostream>
#include <functional>
#include <cmath>
#include <stdexcept>

#include "BinarySearchTree.hpp"

//////////////////////////////////////////////////////////////
//      Helper Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
int BinarySearchTree<ItemType>::getLeftChildIndex(int parentIndex) const
{
   return 2 * parentIndex + 1;
}

template <typename ItemType>
int BinarySearchTree<ItemType>::getRightChildIndex(int parentIndex) const
{
   return 2 * parentIndex + 2;
}

template <typename ItemType>
int BinarySearchTree<ItemType>::getParentIndex(int childIndex) const
{
   return (childIndex - 1) / 2;
}

template <typename ItemType>
int BinarySearchTree<ItemType>::getIndexOf(const ItemType &anEntry) const
{
   int currentIndex = 0;

   while (currentIndex < capacity && treeArray[currentIndex] != ItemType())
   {
      if (treeArray[currentIndex] == anEntry)
      {
         return currentIndex;
      }
      else if (anEntry < treeArray[currentIndex])
      {
         currentIndex = getLeftChildIndex(currentIndex);
      }
      else
      {
         currentIndex = getRightChildIndex(currentIndex);
      }
   }

   return -1;
} // end getIndexOf

template <typename ItemType>
int BinarySearchTree<ItemType>::getHeightHelper(int index) const
{
   if (treeArray[index] == ItemType())
   {
      return 0;
   }

   int leftHeight = getHeightHelper(getLeftChildIndex(index));
   int rightHeight = getHeightHelper(getRightChildIndex(index));

   return 1 + std::max(leftHeight, rightHeight);
} // end getHeightHelper

template <typename ItemType>
void BinarySearchTree<ItemType>::resizeArray()
{
   capacity = 2 * capacity + 1;
   treeArray.resize(capacity, ItemType());

   // TODO: In this implementation, the underlying vector is resized using the formula 2*old_size + 1.
   // Why might this particular resizing strategy be chosen for a binary search tree stored in the vector?
   // What are some potential disadvantages of using this approach?

} // end resizeArray

template <typename ItemType>
void BinarySearchTree<ItemType>::shiftSubtreeUp(int currentIndex, int targetIndex)
{
   if (currentIndex >= capacity || treeArray[currentIndex] == ItemType())
   {
      return;
   }

   treeArray[targetIndex] = treeArray[currentIndex];
   treeArray[currentIndex] = ItemType();

   // Recursively shift the left and right subtrees
   shiftSubtreeUp(getLeftChildIndex(currentIndex), getLeftChildIndex(targetIndex));
   shiftSubtreeUp(getRightChildIndex(currentIndex), getRightChildIndex(targetIndex));
} // end shiftSubtreeUp

template <typename ItemType>
void BinarySearchTree<ItemType>::preorderHelper(int index, std::function<void(ItemType &)> visit) const
{
   if (index >= capacity || treeArray[index] == ItemType())
   {
      return;
   }

   visit(const_cast<ItemType &>(treeArray[index]));
   preorderHelper(getLeftChildIndex(index), visit);
   preorderHelper(getRightChildIndex(index), visit);
} // end preorderHelper

template <typename ItemType>
void BinarySearchTree<ItemType>::inorderHelper(int index, std::function<void(ItemType &)> visit) const
{
   if (index >= capacity || treeArray[index] == ItemType())
   {
      return;
   }

   inorderHelper(getLeftChildIndex(index), visit);
   visit(const_cast<ItemType &>(treeArray[index]));
   inorderHelper(getRightChildIndex(index), visit);
} // end inorderHelper

template <typename ItemType>
void BinarySearchTree<ItemType>::postorderHelper(int index, std::function<void(ItemType &)> visit) const
{
   if (index >= capacity || treeArray[index] == ItemType())
   {
      return;
   }

   postorderHelper(getLeftChildIndex(index), visit);
   postorderHelper(getRightChildIndex(index), visit);
   visit(const_cast<ItemType &>(treeArray[index]));
} // end postorderHelper

//////////////////////////////////////////////////////////////
//      Public Methods Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
BinarySearchTree<ItemType>::BinarySearchTree()
    : size(0), capacity(15), treeArray(15, ItemType())
{
} // end default constructor

template <typename ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
   return size == 0;
} // end isEmpty

template <typename ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
   return getHeightHelper(0);
} // end getHeight

template <typename ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
   return size;
} // end getNumberOfNodes

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const
{
   if (isEmpty())
   {
      throw std::out_of_range("Tree is empty.");
   }

   return treeArray[0];
} // end getRootData

template <typename ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType &newData)
{
   if (isEmpty())
   {
      treeArray[0] = newData;
      size = 1;
   }
   else
   {
      // TODO: Propose your solution here to override the BST interface's setRootData function
      // while maintaining the properties of a binary search tree.
      // Given the signature of the setRootData function, design to fail safely upon violation
   }
} // end setRootData

template <typename ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType &newData)
{
   if (contains(newData))
   {
      return false; // Duplicate entry
   }

   if (isEmpty())
   {
      treeArray[0] = newData;
      size = 1;
      return true;
   }

   // Resize if the current height would exceed the array's capacity
   if (std::floor(std::log2(capacity + 1)) < getHeight() + 1)
   {
      resizeArray();
   }

   // Insert into correct position to maintain BST property
   int parentIndex = 0;
   while (true)
   {
      if (newData < treeArray[parentIndex])
      {
         // Go to the left child
         int leftChildIndex = getLeftChildIndex(parentIndex);
         if (treeArray[leftChildIndex] == ItemType())
         {
            treeArray[leftChildIndex] = newData;
            break;
         }
         parentIndex = leftChildIndex;
      }
      else
      {
         // Go to the right child
         int rightChildIndex = getRightChildIndex(parentIndex);
         if (treeArray[rightChildIndex] == ItemType())
         {
            treeArray[rightChildIndex] = newData;
            break;
         }
         parentIndex = rightChildIndex;
      }
   }

   size++;
   return true;
} // end add

template <typename ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &target)
{
   if (!contains(target))
   {
      return false;
   }

   int targetIndex = getIndexOf(target);
   int leftChildIndex = getLeftChildIndex(targetIndex);
   int rightChildIndex = getRightChildIndex(targetIndex);

   bool hasLeft = (leftChildIndex < capacity && treeArray[leftChildIndex] != ItemType());
   bool hasRight = (rightChildIndex < capacity && treeArray[rightChildIndex] != ItemType());

   // Case 1: Leaf node
   if (!hasLeft && !hasRight)
   {
      treeArray[targetIndex] = ItemType();
      size--;
      return true;
   }

   // Case 2: One child only
   if (!hasLeft)
   {
      shiftSubtreeUp(rightChildIndex, targetIndex);
      size--;
      return true;
   }

   if (!hasRight)
   {
      shiftSubtreeUp(leftChildIndex, targetIndex);
      size--;
      return true;
   }

   // Case 3: Two children — replace with in-order successor
   int successorIndex = rightChildIndex;
   while (getLeftChildIndex(successorIndex) < capacity &&
          treeArray[getLeftChildIndex(successorIndex)] != ItemType())
   {
      successorIndex = getLeftChildIndex(successorIndex);
   }

   ItemType successorValue = treeArray[successorIndex];
   remove(treeArray[successorIndex]);
   treeArray[targetIndex] = successorValue;

   return true;
} // end remove

template <typename ItemType>
void BinarySearchTree<ItemType>::clear()
{
   treeArray.clear();
   capacity = 15; // Reset to initial capacity
   treeArray.resize(capacity, ItemType());
   size = 0;
} // end clear

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType &anEntry) const
{
   int index = getIndexOf(anEntry);

   if (index != -1)
   {
      return treeArray[index];
   }

   throw std::out_of_range("Entry not found in the tree.");
} // end getEntry

template <typename ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &anEntry) const
{
   return getIndexOf(anEntry) != -1;
} // end contains

template <typename ItemType>
std::vector<ItemType> BinarySearchTree<ItemType>::writeTree() const
{
   std::vector<ItemType> result;

   // Option A: write the tree using inorder traversal
   // inorderTraverse([&result](ItemType &item)
   //                 { result.push_back(item); });
   // Option B: write the tree using preorder traversal
   // preorderTraverse([&result](ItemType &item)
   //                  { result.push_back(item); });

   return result;
}

template <typename ItemType>
void BinarySearchTree<ItemType>::readTree(const std::vector<ItemType> &input)
{
   if (input.empty())
      return;
   clear();

   // Option C: add one by one sequentially from the input vector
   // for (int i = 0; i < static_cast<int>(input.size()); i++)
   // {
   //    add(input[i]);
   // }

   // Option D: find mid element recursively and add lower and upper halves as left and right subtrees
   // struct RecHelper
   // {
   //    BinarySearchTree<ItemType> *tree;
   //    void build(const std::vector<ItemType> &arr, int start, int end)
   //    {
   //       if (start > end)
   //          return;
   //       int mid = start + (end - start) / 2;
   //       tree->add(arr[mid]);
   //       build(arr, start, mid - 1);
   //       build(arr, mid + 1, end);
   //    }
   // };
   // RecHelper helper{this};
   // helper.build(input, 0, input.size() - 1);
}

template <typename ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(std::function<void(ItemType &)> visit) const
{
   preorderHelper(0, visit);
} // end preorderTraverse

template <typename ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(std::function<void(ItemType &)> visit) const
{
   inorderHelper(0, visit);
} // end inorderTraverse

template <typename ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(std::function<void(ItemType &)> visit) const
{
   postorderHelper(0, visit);
} // end postorderTraverse