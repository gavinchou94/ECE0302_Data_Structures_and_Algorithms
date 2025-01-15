/** @file PlainBox.hpp */

#ifndef PLAIN_BOX_
#define PLAIN_BOX_

#include "BoxInterface.hpp"

// Indicates this is a template definition
template <typename ItemType>
class PlainBox
{
private:
   // Data field
   ItemType item;

public:
   // Default constructor
   PlainBox();

   // Parameterized constructor
   PlainBox(const ItemType &theItem);

   // Mutator method that can change the value of the data field
   virtual void setItem(const ItemType &theItem);

   // Accessor method to get the value of the data field
   ItemType getItem() const;
};

#include "PlainBox.tpp" // Include the template implementation file
#endif