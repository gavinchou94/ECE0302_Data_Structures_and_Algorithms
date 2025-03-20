#ifndef ABSTRACT_QUEUE_
#define ABSTRACT_QUEUE_

template <typename ItemType>
class AbstractQueue
{
public:
   /** Sees whether this queue is empty.
    @return True if the queue is empty, or false if not. */
   virtual bool isEmpty() const = 0;

   /** Adds a new entry to the back of this queue.
    @post If the operation was successful, someItem is at the back of the queue.
    @param someItem  The object to be added as a new entry.
    @return True if the addition is successful or false if not. */
   virtual void enqueue(const ItemType &someItem) = 0;

   /** Removes the front of this queue.
    @post If the operation was successful, the front of the queue has been removed.
    @return True if the removal is successful or false if not. */
   virtual void dequeue() = 0;

   /** Returns the front of this queue.
    @pre The queue is not empty.
    @post The front of the queue has been returned, and the queue is unchanged.
    @return The front of the queue. */
   virtual ItemType peekFront() const = 0;

   /** Destroys object and frees memory allocated by object. */
   virtual ~AbstractQueue() {}
}; // end AbstractQueue
#endif