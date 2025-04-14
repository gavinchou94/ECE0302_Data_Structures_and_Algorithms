#ifndef REDBLACKNODE_HPP
#define REDBLACKNODE_HPP
#include "BinaryNode.hpp"
#include <memory>
enum Color
{
   RED,
   BLACK
};

template <class ItemType>
class RedBlackNode : public BinaryNode<ItemType>
{
private:
   Color nodeColor;

public:
   RedBlackNode(const ItemType &anItem, std::shared_ptr<RedBlackNode<ItemType>> leftPtr = nullptr,
                std::shared_ptr<RedBlackNode<ItemType>> rightPtr = nullptr, Color col = RED)
       : BinaryNode<ItemType>(anItem, leftPtr, rightPtr), nodeColor(col)
   {
   }

   // Override parent methods to handle RedBlackNode pointers
   std::shared_ptr<RedBlackNode<ItemType>> getLeftChildPtr() const
   {
      return std::dynamic_pointer_cast<RedBlackNode<ItemType>>(BinaryNode<ItemType>::getLeftChildPtr());
   }

   std::shared_ptr<RedBlackNode<ItemType>> getRightChildPtr() const
   {
      return std::dynamic_pointer_cast<RedBlackNode<ItemType>>(BinaryNode<ItemType>::getRightChildPtr());
   }

   void setLeftChildPtr(std::shared_ptr<RedBlackNode<ItemType>> leftPtr)
   {
      BinaryNode<ItemType>::setLeftChildPtr(leftPtr);
   }

   void setRightChildPtr(std::shared_ptr<RedBlackNode<ItemType>> rightPtr)
   {
      BinaryNode<ItemType>::setRightChildPtr(rightPtr);
   }

   Color getColor() const
   {
      return nodeColor;
   }

   void setColor(Color col)
   {
      nodeColor = col;
   }

   bool hasOneChild() const
   {
      return (this->getLeftChildPtr() != nullptr) ^ (this->getRightChildPtr() != nullptr);
   }
   // All other member functions are inherited from BinaryNode
};

#endif