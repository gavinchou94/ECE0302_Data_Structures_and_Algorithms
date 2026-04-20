/** @file RBNode.hpp */

#ifndef RB_NODE_
#define RB_NODE_

#include <memory>

enum Color
{
   RED,
   BLACK
};

template <typename ItemType>
class RBNode
{
private:
   ItemType item;
   std::shared_ptr<RBNode<ItemType>> leftChildPtr;
   std::shared_ptr<RBNode<ItemType>> rightChildPtr;
   Color nodeColor;

public:
   RBNode();
   RBNode(const ItemType &anItem);
   RBNode(const ItemType &anItem,
          std::shared_ptr<RBNode<ItemType>> leftPtr,
          std::shared_ptr<RBNode<ItemType>> rightPtr,
          Color col = RED);

   void setItem(const ItemType &anItem);
   ItemType getItem() const;
   bool isLeaf() const;
   bool hasOneChild() const;

   std::shared_ptr<RBNode<ItemType>> getLeftChildPtr() const;
   std::shared_ptr<RBNode<ItemType>> getRightChildPtr() const;

   void setLeftChildPtr(std::shared_ptr<RBNode<ItemType>> leftPtr);
   void setRightChildPtr(std::shared_ptr<RBNode<ItemType>> rightPtr);

   Color getColor() const;
   void setColor(Color col);
}; // end RBNode

#include "RBNode.tpp"

#endif