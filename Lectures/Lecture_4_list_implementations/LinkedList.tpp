/** @file LinkedList.tpp */

#include "LinkedList.hpp" // Header file
#include <algorithm>      // for std::swap
#include <stdexcept>

template <typename ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
} // end default constructor

template <typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType> &aList)
{
   // stub implementation
} // end copy constructor

template <typename ItemType>
LinkedList<ItemType> &LinkedList<ItemType>::operator=(LinkedList<ItemType> aList)
{
   // assuming above copy constructor implementation is complete
   // use copy-and-swap idiom to implement assignment operator
   std::swap(itemCount, aList.itemCount);
   std::swap(headPtr, aList.headPtr);
   return *this;
} // end copy assignment operator

template <typename ItemType>
LinkedList<ItemType>::~LinkedList()
{
   // clear(); // uncomment this after finishing all stub methods of copy constructor/insert/remove
} // end destructor

template <typename ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
   return (itemCount == 0);
} // end isEmpty

template <typename ItemType>
int LinkedList<ItemType>::getLength() const
{
   return itemCount;
} // end getLength

template <typename ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType &newEntry)
{
   // stub implementation
   return false;
} // end insert

template <typename ItemType>
bool LinkedList<ItemType>::remove(int position)
{
   // stub implementation
   return false;
} // end remove

template <typename ItemType>
void LinkedList<ItemType>::clear()
{
   while (!isEmpty())
      remove(1); // This implementation has a disadvantage of being inefficient, why?
                 // Think about number of operations.
} // end clear

template <typename ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      Node<ItemType> *nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else
   {
      throw std::out_of_range("Invalid position, must be between 1 and getLength().");
   } // end if
} // end getEntry

template <typename ItemType>
void LinkedList<ItemType>::replace(int position, const ItemType &newEntry)
{
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
   {
      Node<ItemType> *nodePtr = getNodeAt(position);
      nodePtr->setItem(newEntry);
   }
   else
   {
      throw std::out_of_range("Invalid position, must be between 1 and getLength().");
   } // end if
} // end replace

template <typename ItemType>
Node<ItemType> *LinkedList<ItemType>::getNodeAt(int position) const
{
   // Debugging check of precondition
   if (position < 1 || position > itemCount)
   {
      throw std::out_of_range("getNodeAt() called with an invalid position.");
   };

   // Count from the beginning of the chain
   Node<ItemType> *curPtr = headPtr;
   for (int skip = 1; skip < position; skip++)
      curPtr = curPtr->getNext();

   return curPtr;
} // end getNodeAt
//  End of implementation file.