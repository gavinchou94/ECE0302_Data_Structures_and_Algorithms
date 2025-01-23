/** @file ArrayBag.hpp */

#ifndef ARRAY_BAG_
#define ARRAY_BAG_

#include "BagInterface.hpp"

template <typename ItemType>
class ArrayBag : public BagInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 6; // Small size to test for a full bag
	ItemType items[DEFAULT_CAPACITY];			 // Array of bag items
	int itemCount;												 // Current count of bag items

	// Returns either the index of the element in the array items that
	// contains the given target or -1, if the array does not contain
	// the target.
	int getIndexOf(const ItemType &target) const; // used in contains()
																								// what is the rationale of making getIndexOf() private?

public:
	ArrayBag();
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType &newEntry);
	bool remove(const ItemType &anEntry);
	void clear();
	bool contains(const ItemType &anEntry) const;
	int getFrequencyOf(const ItemType &anEntry) const;
	std::vector<ItemType> toVector() const;
}; // end ArrayBag

#include "ArrayBag.tpp"
#endif
