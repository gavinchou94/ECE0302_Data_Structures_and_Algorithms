/** @file MagicBox.hpp */

#ifndef MAGIC_BOX_
#define MAGIC_BOX_
#include "PlainBox.hpp"

template <typename ItemType>
class MagicBox : public PlainBox<ItemType>
{
private:
   bool firstItemStored;

public:
   MagicBox();
   MagicBox(const ItemType &theItem);
   void setItem(const ItemType &theItem);
};

#include "MagicBox.tpp"
#endif