/** @file ArrayBagInt.hpp */

#ifndef ARRAY_BAG_INT_
#define ARRAY_BAG_INT_
#include <vector>

class ArrayBagInt
{
private:
	static const int DEFAULT_CAPACITY = 1000000;
	int items[DEFAULT_CAPACITY]; // Array of bag of ints
	int itemCount;							 // Current count of bag items

	// Returns either the index of the element in the array items that
	// contains the given target or -1, if the array does not contain
	// the target.
	int getIndexOf(const int &target) const;

public:
	ArrayBagInt();
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const int &newEntry);
	bool remove(const int &anEntry);
	bool remove2(const int &anEntry);
	void clear();
	void clear2();
	void clear3();
	void clear4();
	bool contains(const int &anEntry) const;
	int getFrequencyOf(const int &anEntry) const;
	bool replace(const int &oldEntry, const int &newEntry);
	std::vector<int> toVector() const;
}; // end ArrayBagInt

#include "ArrayBagInt.cpp"
#endif