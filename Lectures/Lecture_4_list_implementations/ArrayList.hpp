/** @file ArrayList.hpp */

#ifndef ARRAY_LIST_
#define ARRAY_LIST_

#include "ListInterface.hpp"
#include <stdexcept>

template <typename ItemType>
class ArrayList : public ListInterface<ItemType>
{
private:
   static const int DEFAULT_CAPACITY = 5; // Small capacity to test for a full list
   ItemType items[DEFAULT_CAPACITY + 1];  // Array of list items (not using items[0] in fixed-size array)
   int itemCount;                         // Current count of list items
   // Note: No dynamic memory allocation is needed here
   // but you will implement dynamic array-based ADT List in Programming Problem 3

public:
   ArrayList();
   // Copy constructor and destructor are supplied by compiler

   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType &newEntry);
   bool remove(int position);
   void clear();

   /** @throw std::out_of_range if position < 1 or position > getLength(). */
   ItemType getEntry(int position) const;

   /** @throw std::out_of_range if position < 1 or position > getLength(). */
   void replace(int position, const ItemType &newEntry);
}; // end ArrayList

#include "ArrayList.tpp"
#endif