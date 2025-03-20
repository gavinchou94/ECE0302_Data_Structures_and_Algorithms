#ifndef ABSTRACT_DEQUE_
#define ABSTRACT_DEQUE_

template <typename ItemType>
class AbstractDeque
{
public:
   // return True if the queue is empty, or false if not. */
   virtual bool isEmpty() const = 0;

   // Adds a new entry to the back of this queue.
   virtual void enqueue_back(const ItemType &someItem) = 0;

   // Adds a new entry to the front of this queue.
   virtual void enqueue_front(const ItemType &someItem) = 0;

   // Removes the front of this queue.
   virtual void dequeue_front() = 0;

   // Removes the back of this queue.
   virtual void dequeue_back() = 0;

   // Returns a copy of the front of this queue.
   virtual ItemType peekFront() const = 0;

   // Returns a copy of the back of this queue.
   virtual ItemType peekBack() const = 0;

   /** Destroys object and frees memory allocated by object. */
   virtual ~AbstractDeque() {}
}; // end AbstractDeque
#endif