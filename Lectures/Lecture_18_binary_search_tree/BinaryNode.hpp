/** @file BinaryNode.hpp */

#ifndef BINARY_NODE_
#define BINARY_NODE_

#include <memory>

template <class ItemType>
class BinaryNode
{
private:
   ItemType item;                                       // Data portion
   std::shared_ptr<BinaryNode<ItemType>> leftChildPtr;  // Pointer to left child
   std::shared_ptr<BinaryNode<ItemType>> rightChildPtr; // Pointer to right child

public:
   BinaryNode();
   BinaryNode(const ItemType &anItem);
   BinaryNode(const ItemType &anItem,
              std::shared_ptr<BinaryNode<ItemType>> leftPtr,
              std::shared_ptr<BinaryNode<ItemType>> rightPtr);

   void setItem(const ItemType &anItem);
   ItemType getItem() const;

   bool isLeaf() const;

   std::shared_ptr<BinaryNode<ItemType>> getLeftChildPtr() const;
   std::shared_ptr<BinaryNode<ItemType>> getRightChildPtr() const;

   void setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr);
   void setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr);
}; // end BinaryNode

#include "BinaryNode.tpp"

#endif

// Just think about this node template class. It is a foundation for building a binary search tree.
// Each node contains an item, and pointers to its left and right children.

// What other functionalities might you want to add to this class?
// Note that this is a Node class, so it should be simple and focused on node-specific operations.
// Explain why it is necessary to have your proposed functionalities in the Node class.
