/** @file BinaryNode.hpp */

#ifndef BINARY_NODE_
#define BINARY_NODE_

#include <memory>

template <typename ItemType>
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

// TODO: The isLeaf() method is currently implemented as a member of the Node class (see line 25 above).
// Should this method remain in the Node class, or would it be better to move it to the BST (tree) class?
// If you think it should be moved to the BST class, design an appropriate function signature and discuss why this is necessary.
// If you think it should remain in the Node class, explain your reasoning.