/** @file RBNode.tpp */

#include "RBNode.hpp"

template <typename ItemType>
RBNode<ItemType>::RBNode()
    : item(), leftChildPtr(nullptr), rightChildPtr(nullptr), nodeColor(RED)
{
} // end default constructor

template <typename ItemType>
RBNode<ItemType>::RBNode(const ItemType &anItem)
    : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr), nodeColor(RED)
{
} // end constructor

template <typename ItemType>
RBNode<ItemType>::RBNode(const ItemType &anItem,
                         std::shared_ptr<RBNode<ItemType>> leftPtr,
                         std::shared_ptr<RBNode<ItemType>> rightPtr,
                         Color col)
    : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr), nodeColor(col)
{
} // end constructor

template <typename ItemType>
void RBNode<ItemType>::setItem(const ItemType &anItem)
{
  item = anItem;
} // end setItem

template <typename ItemType>
ItemType RBNode<ItemType>::getItem() const
{
  return item;
} // end getItem

template <typename ItemType>
bool RBNode<ItemType>::isLeaf() const
{
  return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));
} // end isLeaf

template <typename ItemType>
bool RBNode<ItemType>::hasOneChild() const
{
  return (leftChildPtr != nullptr) != (rightChildPtr != nullptr);
} // end hasOneChild

template <typename ItemType>
std::shared_ptr<RBNode<ItemType>> RBNode<ItemType>::getLeftChildPtr() const
{
  return leftChildPtr;
} // end getLeftChildPtr

template <typename ItemType>
std::shared_ptr<RBNode<ItemType>> RBNode<ItemType>::getRightChildPtr() const
{
  return rightChildPtr;
} // end getRightChildPtr

template <typename ItemType>
void RBNode<ItemType>::setLeftChildPtr(std::shared_ptr<RBNode<ItemType>> leftPtr)
{
  leftChildPtr = leftPtr;
} // end setLeftChildPtr

template <typename ItemType>
void RBNode<ItemType>::setRightChildPtr(std::shared_ptr<RBNode<ItemType>> rightPtr)
{
  rightChildPtr = rightPtr;
} // end setRightChildPtr

template <typename ItemType>
Color RBNode<ItemType>::getColor() const
{
  return nodeColor;
} // end getColor

template <typename ItemType>
void RBNode<ItemType>::setColor(Color col)
{
  nodeColor = col;
} // end setColor