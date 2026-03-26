/** @file DoubleLinkNode.tpp */
#include "DoubleLinkNode.hpp"

template <class ItemType>
DoubleLinkNode<ItemType>::DoubleLinkNode() : next(nullptr), prev(nullptr)
{
} // end default constructor

template <class ItemType>
DoubleLinkNode<ItemType>::DoubleLinkNode(const ItemType &anItem) : item(anItem), next(nullptr), prev(nullptr)
{
} // end constructor

template <class ItemType>
DoubleLinkNode<ItemType>::DoubleLinkNode(const ItemType &anItem, const std::shared_ptr<DoubleLinkNode<ItemType>> &nextNodePtr, const std::shared_ptr<DoubleLinkNode<ItemType>> &prevNodePtr) : item(anItem), next(nextNodePtr), prev(prevNodePtr)
{
} // end constructor

template <class ItemType>
void DoubleLinkNode<ItemType>::setItem(const ItemType &anItem)
{
   item = anItem;
} // end setItem

template <class ItemType>
void DoubleLinkNode<ItemType>::setNext(const std::shared_ptr<DoubleLinkNode<ItemType>> &nextNodePtr)
{
   next = nextNodePtr;
} // end setNext

template <class ItemType>
void DoubleLinkNode<ItemType>::setPrev(const std::shared_ptr<DoubleLinkNode<ItemType>> &prevNodePtr)
{
   prev = prevNodePtr;
} // end setPrev

template <class ItemType>
ItemType DoubleLinkNode<ItemType>::getItem() const
{
   return item;
} // end getItem

template <class ItemType>
std::shared_ptr<DoubleLinkNode<ItemType>> DoubleLinkNode<ItemType>::getNext() const
{
   return next;
} // end getNext

template <typename ItemType>
std::weak_ptr<DoubleLinkNode<ItemType>> DoubleLinkNode<ItemType>::getPrev() const
{
   return prev;
} // end getPrev