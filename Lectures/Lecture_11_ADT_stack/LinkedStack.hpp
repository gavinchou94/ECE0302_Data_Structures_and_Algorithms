/** @file LinkedStack.h */

#ifndef LINKED_STACK_EXCEPTIONS
#define LINKED_STACK_EXCEPTIONS

#include "StackInterface.hpp"
#include "Node.hpp"

/** ADT stack - Linked implementation. */

template <typename ItemType>
class LinkedStack : public StackInterface<ItemType>
{

private:
	Node<ItemType> *topPtr; // Pointer to first node in the chain;
													// this node contains the stack's top

public:
	// Constructors and destructor:
	LinkedStack();																									// Default constructor
	LinkedStack(const LinkedStack<ItemType> &aStack);								// Copy constructor
	LinkedStack<ItemType> &operator=(LinkedStack<ItemType> aStack); // Assignment operator
	virtual ~LinkedStack();																					// Destructor

	// Stack operations:
	bool isEmpty() const;
	bool push(const ItemType &newItem);
	bool pop();
	ItemType peek() const;
}; // end LinkedStack

#include "LinkedStack.tpp"

#endif
