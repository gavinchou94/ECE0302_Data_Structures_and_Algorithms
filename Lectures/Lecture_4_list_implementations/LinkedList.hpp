/** @file LinkedList.hpp */

#ifndef LINKED_LIST_
#define LINKED_LIST_

#include "ListInterface.hpp"
#include "Node.hpp"

template <typename ItemType>
class LinkedList : public ListInterface<ItemType>
{
private:
   Node<ItemType> *headPtr; // Pointer to first node in the chain;
                            // (contains the first entry in the list)
   int itemCount;           // Current count of list items

   // Locates a specified node in this linked list.
   // @pre  position is the number of the desired node;
   //       position >= 1 and position <= itemCount.
   // @post  The node is found and a pointer to it is returned.
   // @param position  The number of the node to locate.
   // @return  A pointer to the node at the given position.
   Node<ItemType> *getNodeAt(int position) const;

public:
   LinkedList();
   LinkedList(const LinkedList<ItemType> &aList);
   LinkedList<ItemType> &operator=(LinkedList<ItemType> aList);
   virtual ~LinkedList();

   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType &newEntry);
   bool remove(int position);
   void clear();

   /** @throw std::out_of_range if position < 1 or position > getLength(). */
   ItemType getEntry(int position) const;

   /** @throw std::out_of_range if position < 1 or position > getLength(). */
   void replace(int position, const ItemType &newEntry);
}; // end LinkedList

#include "LinkedList.tpp"
#endif
