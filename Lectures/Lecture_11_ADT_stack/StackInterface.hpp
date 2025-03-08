/** @file StackInterface.hpp */
#ifndef STACK_INTERFACE_
#define STACK_INTERFACE_

template <typename ItemType>
class StackInterface
{
public:
   /** Sees whether this stack is empty.
    @return  True if the stack is empty, or false if not. */
   virtual bool isEmpty() const = 0;

   /** Adds a new entry to the top of this stack.
    @post  If the operation was successful, someItem is at the top of the stack.
    @param someItem  The object to be added as a new entry.
    @return  True if the addition is successful or false if not. */
   virtual bool push(const ItemType &anEntry) = 0;

   /** Removes the top of this stack.
    @post  If the operation was successful, the top of the stack
    has been removed.
    @return  True if the removal is successful or false if not. */
   virtual bool pop() = 0;

   /** Returns a copy of the top of this stack.
    @pre  The stack is not empty.
    @throw std::out_of_range if the stack is empty.
    @post  A copy of the top of the stack has been returned, and
    the stack is unchanged.
    @return  A copy of the top of the stack. */
   virtual ItemType peek() const = 0;

   /** Destroys this stack and frees its assigned memory. */
   virtual ~StackInterface() {}
}; // end StackInterface
#endif
