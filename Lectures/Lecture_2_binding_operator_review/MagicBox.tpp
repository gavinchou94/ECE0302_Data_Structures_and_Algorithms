/** @file MagicBox.tpp */

#include "MagicBox.hpp"

template <typename ItemType>
MagicBox<ItemType>::MagicBox()
    : firstItemStored(false) // Box has no magic initially
{
}

template <typename ItemType>
MagicBox<ItemType>::MagicBox(const ItemType &theItem)
    : firstItemStored(false) // Box has no magic initially
{
   setItem(theItem); // Box has magic now
}

template <typename ItemType>
void MagicBox<ItemType>::setItem(const ItemType &theItem)
{
   if (!firstItemStored)
   {
      PlainBox<ItemType>::setItem(theItem);
      firstItemStored = true; // Box now has magic
   } // end if
}