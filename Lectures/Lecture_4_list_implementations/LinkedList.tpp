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
   // stub implementation; Refer to copy constructor of LinkedBag for idea below
} // end copy constructor

template <typename ItemType>
LinkedList<ItemType> &LinkedList<ItemType>::operator=(LinkedList<ItemType> aList)
{
   // Once the above copy constructor implementation is complete
   // use copy swap idiom to implement assignment operator
   std::swap(itemCount, aList.itemCount);
   std::swap(headPtr, aList.headPtr);
   return *this;
} // end copy assignment operator

template <typename ItemType>
LinkedList<ItemType>::~LinkedList()
{
   // clear(); // Once all stub methods of copy constructor/insert/remove are complete, using clear() to free memory is enough.
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
   // stub implementation, stay tuned for Problem 3 requirements
   return false;
} // end insert

template <typename ItemType>
bool LinkedList<ItemType>::remove(int position)
{
   // stub implementation, stay tuned for Problem 3 requirements
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
      Node<ItemType> *nodePtr = getNodeAt(position); // call the private helper function
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
      Node<ItemType> *nodePtr = getNodeAt(position); // call the private helper function
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
   // Precondition check
   if (position < 1 || position > itemCount)
   {
      throw std::out_of_range("getNodeAt() called with an invalid position.");
   }

   // Traverse from the beginning of the chain
   Node<ItemType> *curPtr = headPtr;
   for (int skip = 1; skip < position; skip++)
   {
      curPtr = curPtr->getNext();
   }
   return curPtr;
} // end getNodeAt
//  End of implementation file.

/** LinkedBag copy constructor example

template <class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType> &someBag)
{
   itemCount = someBag.itemCount;
   Node<ItemType> *origChainPtr = someBag.headPtr; // Points to nodes in original chain

   if (origChainPtr == nullptr)
      headPtr = nullptr; // Original bag is empty
   else
   {
      // Copy first node
      headPtr = new Node<ItemType>();
      headPtr->setItem(origChainPtr->getItem());

      // Copy remaining nodes
      Node<ItemType> *endChainPtr = headPtr;  // Points to last node in new chain
      origChainPtr = origChainPtr->getNext(); // Advance original-chain pointer

      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();

         // Create a new node containing the next item
         Node<ItemType> *itemNodePtr = new Node<ItemType>(nextItem);

         // Link new node to end of new chain
         endChainPtr->setNext(itemNodePtr);

         // Advance pointer to new last node
         endChainPtr = endChainPtr->getNext();

         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      } // end while

      endChainPtr->setNext(nullptr); // Flag end of chain
   } // end if
} // end copy constructor

*/