#ifndef ABSTRACT_HEAP_
#define ABSTRACT_HEAP_

template <typename ItemType>
class AbstractHeap
{
public:
   /** Sees whether this heap is empty.
    @return True if the heap is empty, or false if not. */
   virtual bool isEmpty() const = 0;

   /** Gets the number of nodes in this heap.
    @return The number of nodes in the heap. */
   virtual int getNumberOfNodes() const = 0;

   /** Gets the height of this heap.
    @return The height of the heap. */
   virtual int getHeight() const = 0;

   /** Gets the data that is in the root (top) of this heap.
    For a maxheap, the data is the largest value in the heap;
    for a minheap, the data is the smallest value in the heap.
    @pre The heap is not empty.
    @post The root’s data has been returned, and the heap is unchanged.
    @return The data in the root of the heap. */
   virtual ItemType peekTop() const = 0;

   /** Adds a new node containing the given data to this heap.
    @param someItem The data for the new node.
    @post The heap contains a new node.
    @return True if the addition is successful, or false if not. */
   virtual bool add(const ItemType &someItem) = 0;

   /** Removes the root node from this heap.
    @return True if the removal is successful, or false if not. */
   virtual bool remove() = 0;

   /** Removes all nodes from this heap. */
   virtual void clear() = 0;

   /** Destroys this heap and frees its assigned memory. */
   virtual ~AbstractHeap() {}

}; // end AbstractHeap
#endif
