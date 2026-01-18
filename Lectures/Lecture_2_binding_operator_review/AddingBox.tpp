/** @file AddingBox.tpp */

#include "AddingBox.hpp"

// non-member function
// Returns a box whose item is the sum of the items in box1 and box2.
// "sum" is defined as result of + operator
template <typename ItemType>
AddingBox<ItemType> operator+(const AddingBox<ItemType> &box1,
                              const AddingBox<ItemType> &box2)
{
    AddingBox<ItemType> sum;
    ItemType item1 = box1.getItem();
    ItemType item2 = box2.getItem();
    sum.setItem(item1 + item2);
    return sum;
}