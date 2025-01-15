/** @file ToyBox.cpp */

#include "ToyBox.hpp"

template <typename ItemType>
ToyBox<ItemType>::ToyBox() : boxColor(BLACK)
{
} 

template <typename ItemType>
ToyBox<ItemType>::ToyBox(const Color& theColor) : boxColor(theColor)
{
}

template <typename ItemType>
ToyBox<ItemType>::ToyBox(const ItemType& theItem, const Color& theColor)
   :PlainBox<ItemType>(theItem), boxColor(theColor) // Initialize item data fields
{
}

template <typename ItemType>
Color ToyBox<ItemType>::getColor() const
{
   return boxColor;
}
