/** @file Stack.tpp */
// Finish this link-based Stack to pass unit tests 1~3

#include <stdexcept>
#include "Stack.hpp"
#include "Node.hpp"

template <typename ItemType>
Stack<ItemType>::Stack()
{
	// TODO
}

template <typename ItemType>
Stack<ItemType>::~Stack()
{
	// TODO
}

template <typename ItemType>
bool Stack<ItemType>::isEmpty() const
{
	// TODO
	return true;
}

template <typename ItemType>
int Stack<ItemType>::size() const
{
	// TODO
	return 0;
}

template <typename ItemType>
bool Stack<ItemType>::push(const ItemType &newItem)
{
	// TODO
	return true;
}

template <typename ItemType>
ItemType Stack<ItemType>::peek() const
{
	// TODO
	return ItemType();
}

template <typename ItemType>
bool Stack<ItemType>::pop()
{
	// TODO
	return false;
}

template <typename ItemType>
void Stack<ItemType>::clear()
{
	// TODO
}