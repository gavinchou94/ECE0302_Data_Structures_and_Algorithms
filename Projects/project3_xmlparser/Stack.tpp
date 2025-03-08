/** @file Stack.tpp */
// Finish this .tpp first to pass the first 3 unit tests

#include <stdexcept>
#include "Stack.hpp"
#include "Node.hpp"

template <typename ItemType>
Stack<ItemType>::Stack()
{
	// TODO
} // end default constructor

template <typename ItemType>
Stack<ItemType>::~Stack()
{
	// TODO
} // end destructor

template <typename ItemType>
bool Stack<ItemType>::isEmpty() const
{
	// TODO
	return true;
} // end isEmpty

template <typename ItemType>
int Stack<ItemType>::size() const
{
	// TODO
	return 0;
} // end size

template <typename ItemType>
bool Stack<ItemType>::push(const ItemType &newItem)
{
	// TODO
	return true;
} // end push

template <typename ItemType>
ItemType Stack<ItemType>::peek() const
{
	// TODO
	return ItemType();
} // end peek

template <typename ItemType>
bool Stack<ItemType>::pop()
{
	// TODO
	return false;
} // end pop

template <typename ItemType>
void Stack<ItemType>::clear()
{
	// TODO
} // end clear