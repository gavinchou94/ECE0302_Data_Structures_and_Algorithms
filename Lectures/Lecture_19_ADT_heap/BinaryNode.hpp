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
