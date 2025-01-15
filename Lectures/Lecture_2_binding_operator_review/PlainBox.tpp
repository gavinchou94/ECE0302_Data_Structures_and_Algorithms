/** @file PlainBox.tpp */

#include "PlainBox.hpp"

template <typename ItemType>
PlainBox<ItemType>::PlainBox()
{
}

template <typename ItemType>
PlainBox<ItemType>::PlainBox(const ItemType &theItem) : item(theItem)
{
}

template <typename ItemType>
void PlainBox<ItemType>::setItem(const ItemType &theItem)
{
   item = theItem;
}

template <typename ItemType>
ItemType PlainBox<ItemType>::getItem() const
{
   return item;
}