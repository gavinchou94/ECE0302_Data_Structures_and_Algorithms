/** ADT Deque: Doubly linked-based implementation.
 @file LinkedDeque.hpp */
#ifndef LINKED_DEQUE_
#define LINKED_DEQUE_

#include "abstract_deque.hpp"
#include "DoubleLinkNode.hpp"
#include <stdexcept>

template <typename ItemType>
class LinkedDeque : public AbstractDeque<ItemType>
{
private:
   // The deque is implemented as a chain of linked nodes that has two external pointers
   // a head pointer for front of the deque and
   // a tail pointer for the back of the deque.
   std::shared_ptr<DoubleLinkNode<ItemType>> backPtr;
   std::shared_ptr<DoubleLinkNode<ItemType>> frontPtr;

public:
   LinkedDeque();
   LinkedDeque(const LinkedDeque<ItemType> &rhs);
   LinkedDeque<ItemType> &operator=(LinkedDeque<ItemType> rhs); // Copy assignment operator
   ~LinkedDeque();

   bool isEmpty() const;
   void enqueue_front(const ItemType &someItem);
   void enqueue_back(const ItemType &someItem);
   void dequeue_front();
   void dequeue_back();
   ItemType peekFront() const;
   ItemType peekBack() const;
   bool isFull() const;
}; // end LinkedDeque

#include "LinkedDeque.tpp"
#endif // LINKED_DEQUE_