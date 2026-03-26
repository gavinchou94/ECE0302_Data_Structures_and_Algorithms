/** @file LinkedDeque.tpp */
#include "LinkedDeque.hpp"

template <typename ItemType>
LinkedDeque<ItemType>::LinkedDeque() : backPtr(nullptr), frontPtr(nullptr)
{
} // end default constructor

template <typename ItemType>
LinkedDeque<ItemType>::LinkedDeque(const LinkedDeque &rhs)
{
   auto origChainPtr = rhs.frontPtr;

   if (origChainPtr != nullptr)
   {
      // Copy first node
      frontPtr = std::make_shared<DoubleLinkNode<ItemType>>(origChainPtr->getItem());

      // Copy remaining nodes
      auto endChainPtr = frontPtr;
      origChainPtr = origChainPtr->getNext();

      while (origChainPtr != nullptr)
      {
         auto newNodePtr = std::make_shared<DoubleLinkNode<ItemType>>(origChainPtr->getItem());
         newNodePtr->setPrev(endChainPtr);
         endChainPtr->setNext(newNodePtr);

         endChainPtr = newNodePtr;
         origChainPtr = origChainPtr->getNext();
      } // end while

      backPtr = endChainPtr;
   } // end if
} // end copy constructor

template <typename ItemType>
LinkedDeque<ItemType> &LinkedDeque<ItemType>::operator=(LinkedDeque<ItemType> rhs)
{
   std::swap(frontPtr, rhs.frontPtr);
   std::swap(backPtr, rhs.backPtr);
   return *this;
} // end operator=

template <typename ItemType>
LinkedDeque<ItemType>::~LinkedDeque()
{
   backPtr = nullptr;
   frontPtr = nullptr;
} // end destructor

template <typename ItemType>
bool LinkedDeque<ItemType>::isEmpty() const
{
   return frontPtr == nullptr;
} // end isEmpty

template <typename ItemType>
void LinkedDeque<ItemType>::enqueue_front(const ItemType &someEntry)
{
   auto itemNodePtr = std::make_shared<DoubleLinkNode<ItemType>>(someEntry, frontPtr, nullptr);

   if (isEmpty())
   {
      backPtr = itemNodePtr;
   }
   else
   {
      frontPtr->setPrev(itemNodePtr);
   }
   frontPtr = itemNodePtr;
} // end enqueue_front

template <typename ItemType>
void LinkedDeque<ItemType>::enqueue_back(const ItemType &someEntry)
{
   auto itemNodePtr = std::make_shared<DoubleLinkNode<ItemType>>(someEntry, nullptr, backPtr);

   if (isEmpty())
   {
      frontPtr = itemNodePtr;
   }
   else
   {
      backPtr->setNext(itemNodePtr);
   }
   backPtr = itemNodePtr;
} // end enqueue_back

template <typename ItemType>
void LinkedDeque<ItemType>::dequeue_front()
{
   if (isEmpty())
      throw std::logic_error("dequeue_front() called on empty deque.");

   if (frontPtr == backPtr)
   {
      frontPtr.reset();
      backPtr.reset();
   }
   else
   {
      frontPtr = frontPtr->getNext();
      frontPtr->setPrev(nullptr);
   }
} // end dequeue_front

template <typename ItemType>
void LinkedDeque<ItemType>::dequeue_back()
{
   if (isEmpty())
      throw std::logic_error("dequeue_back() called on empty deque.");

   if (frontPtr == backPtr)
   {
      frontPtr.reset();
      backPtr.reset();
   }
   else
   {
      backPtr = backPtr->getPrev().lock();
      backPtr->setNext(nullptr);
   }
} // end dequeue_back

template <typename ItemType>
ItemType LinkedDeque<ItemType>::peekFront() const
{
   if (isEmpty())
      throw std::logic_error("peekFront() called on empty deque.");

   return frontPtr->getItem();
} // end peekFront

template <typename ItemType>
ItemType LinkedDeque<ItemType>::peekBack() const
{
   if (isEmpty())
      throw std::logic_error("peekBack() called on empty deque.");

   return backPtr->getItem();
} // end peekBack

template <typename ItemType>
bool LinkedDeque<ItemType>::isFull() const
{
   return false;
} // end isFull