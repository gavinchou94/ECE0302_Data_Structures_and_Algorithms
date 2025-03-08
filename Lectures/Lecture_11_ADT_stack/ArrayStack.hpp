/** @file ArrayStack.hpp */

#ifndef ARRAY_STACK
#define ARRAY_STACK

#include "StackInterface.hpp"

const int MAX_STACK = 10;

template <typename ItemType>
class ArrayStack : public StackInterface<ItemType>
{
private:
	ItemType items[MAX_STACK]; // Array of stack items
	int top;									 // Index to top of stack

public:
	ArrayStack();
	bool isEmpty() const;
	bool push(const ItemType &newEntry);
	bool pop();
	ItemType peek() const;
}; // end ArrayStack

#include "ArrayStack.tpp"
#endif
