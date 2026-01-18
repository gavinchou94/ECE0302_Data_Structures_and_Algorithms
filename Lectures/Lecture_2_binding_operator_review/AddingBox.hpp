/** @file AddingBox.hpp */
#ifndef ADDING_BOX_
#define ADDING_BOX_
#include "PlainBox.hpp"

// AddingBox is a template class derived from PlainBox
template <typename ItemType>
class AddingBox : public PlainBox<ItemType>
{
    using PlainBox<ItemType>::PlainBox;
};

// + can be used to connect two AddingBox objects
template <typename ItemType>
AddingBox<ItemType> operator+(const AddingBox<ItemType> &box1,
                              const AddingBox<ItemType> &box2);

#include "AddingBox.tpp"
#endif