/** @file DoubleLinkNode.hpp*/
#ifndef DOUBLE_LINK_NODE_
#define DOUBLE_LINK_NODE_

#include <memory>

template <typename ItemType>
class DoubleLinkNode
{
private:
   ItemType item;                                  // A data item
   std::shared_ptr<DoubleLinkNode<ItemType>> next; // Pointer to next node
   std::weak_ptr<DoubleLinkNode<ItemType>> prev;   // Pointer to previous node

public:
   DoubleLinkNode();
   DoubleLinkNode(const ItemType &anItem);
   DoubleLinkNode(const ItemType &anItem, const std::shared_ptr<DoubleLinkNode<ItemType>> &nextNodePtr, const std::shared_ptr<DoubleLinkNode<ItemType>> &prevNodePtr);
   void setItem(const ItemType &anItem);
   void setNext(const std::shared_ptr<DoubleLinkNode<ItemType>> &nextNodePtr);
   void setPrev(const std::shared_ptr<DoubleLinkNode<ItemType>> &prevNodePtr);
   ItemType getItem() const;
   std::shared_ptr<DoubleLinkNode<ItemType>> getNext() const;
   std::weak_ptr<DoubleLinkNode<ItemType>> getPrev() const;
}; // end DoubleLinkNode

#include "DoubleLinkNode.tpp"
#endif