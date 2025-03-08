/** @file ArrayStack.cpp */

#include "ArrayStack.hpp" // Stack class specification file

template <typename ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1)
{
} // end default constructor

// Copy constructor and destructor are supplied by the compiler

template <typename ItemType>
bool ArrayStack<ItemType>::isEmpty() const
{
	return top < 0;
} // end isEmpty

template <typename ItemType>
bool ArrayStack<ItemType>::push(const ItemType &newEntry)
{
	bool result = false;
	if (top < MAX_STACK - 1)
	{
		// Stack has room for another item
		top++;
		items[top] = newEntry;
		result = true;
	} // end if

	return result;
} // end push

template <typename ItemType>
bool ArrayStack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		result = true;
		top--;
	} // end if

	return result;
} // end pop

template <typename ItemType>
ItemType ArrayStack<ItemType>::peek() const
{
	// Enforce precondition
	if (isEmpty())
		throw std::out_of_range("peek() called with empty stack");

	// Stack is not empty; return top
	return items[top];
} // end peek

// int getTopPosition() const
// {
//    return top;
// } // end getTopPosition

// Reason yourself whether we need the above function; if we need, should we set it as public or private?

// End of implementation file.