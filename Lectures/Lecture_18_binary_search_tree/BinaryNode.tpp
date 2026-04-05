/** @file BinaryNode.tpp */

#include "BinaryNode.hpp"

template <typename ItemType>
BinaryNode<ItemType>::BinaryNode()
    : item(nullptr), leftChildPtr(nullptr), rightChildPtr(nullptr)
{
} // end default constructor

template <typename ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &anItem)
    : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr)
{
} // end constructor

template <typename ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &anItem,
                                 std::shared_ptr<BinaryNode<ItemType>> leftPtr,
                                 std::shared_ptr<BinaryNode<ItemType>> rightPtr)
    : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr)
{
} // end constructor

template <typename ItemType>
void BinaryNode<ItemType>::setItem(const ItemType &anItem)
{
   item = anItem;
} // end setItem

template <typename ItemType>
ItemType BinaryNode<ItemType>::getItem() const
{
   return item;
} // end getItem

template <typename ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
   return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));
} // end isLeaf

template <typename ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr)
{
   leftChildPtr = leftPtr;
} // end setLeftChildPtr

template <typename ItemType>
void BinaryNode<ItemType>::setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr)
{
   rightChildPtr = rightPtr;
} // end setRightChildPtr

template <typename ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNode<ItemType>::getLeftChildPtr() const
{
   return leftChildPtr;
} // end getLeftChildPtr

template <typename ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNode<ItemType>::getRightChildPtr() const
{
   return rightChildPtr;
} // end getRightChildPtr