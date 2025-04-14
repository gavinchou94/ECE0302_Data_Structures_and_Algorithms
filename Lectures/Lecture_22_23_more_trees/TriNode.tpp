#include "TriNode.hpp"

template <class ItemType>
TriNode<ItemType>::TriNode()
{
  leftChildPtr = nullptr;
  midChildPtr = nullptr;
  rightChildPtr = nullptr;
}

template <class ItemType>
TriNode<ItemType>::TriNode(const ItemType &anItem)
{
  smallItem = anItem;
  leftChildPtr = nullptr;
  midChildPtr = nullptr;
  rightChildPtr = nullptr;
}

template <class ItemType>
TriNode<ItemType>::TriNode(const ItemType &anItem,
                           const ItemType &anotherItem,
                           std::shared_ptr<TriNode<ItemType>> leftPtr,
                           std::shared_ptr<TriNode<ItemType>> midPtr,
                           std::shared_ptr<TriNode<ItemType>> rightPtr)
{
  smallItem = anItem;
  largeItem = anotherItem;
  leftChildPtr = leftPtr;
  midChildPtr = midPtr;
  rightChildPtr = rightPtr;
}

template <class ItemType>
bool TriNode<ItemType>::isLeaf() const
{
  return (leftChildPtr == nullptr && midChildPtr == nullptr && rightChildPtr == nullptr);
}

template <class ItemType>
bool TriNode<ItemType>::isTwoNode() const
{
  return (largeItem == ItemType() && rightChildPtr == nullptr);
}

template <class ItemType>
bool TriNode<ItemType>::isThreeNode() const
{
  return (largeItem != ItemType() && rightChildPtr != nullptr);
}

template <class ItemType>
ItemType TriNode<ItemType>::getSmallItem() const
{
  return smallItem;
}

template <class ItemType>
ItemType TriNode<ItemType>::getLargeItem() const
{
  return largeItem;
}

template <class ItemType>
void TriNode<ItemType>::setSmallItem(const ItemType &anItem)
{
  smallItem = anItem;
}

template <class ItemType>
void TriNode<ItemType>::setLargeItem(const ItemType &anItem)
{
  largeItem = anItem;
}

template <class ItemType>
std::shared_ptr<TriNode<ItemType>> TriNode<ItemType>::getLeftChildPtr() const
{
  return leftChildPtr;
}

template <class ItemType>
std::shared_ptr<TriNode<ItemType>> TriNode<ItemType>::getMidChildPtr() const
{
  return midChildPtr;
}

template <class ItemType>
std::shared_ptr<TriNode<ItemType>> TriNode<ItemType>::getRightChildPtr() const
{
  return rightChildPtr;
}

template <class ItemType>
void TriNode<ItemType>::setLeftChildPtr(std::shared_ptr<TriNode<ItemType>> leftPtr)
{
  leftChildPtr = leftPtr;
}

template <class ItemType>
void TriNode<ItemType>::setMidChildPtr(std::shared_ptr<TriNode<ItemType>> midPtr)
{
  midChildPtr = midPtr;
}

template <class ItemType>
void TriNode<ItemType>::setRightChildPtr(std::shared_ptr<TriNode<ItemType>> rightPtr)
{
  rightChildPtr = rightPtr;
}