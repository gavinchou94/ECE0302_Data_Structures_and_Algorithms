/** An array-based implementation of the ADT dictionary
    that organizes its data items in sorted search-key order.
    Search keys in the dictionary are unique.
 @file ArrayDictionary.h */

#ifndef ARRAY_DICTIONARY_
#define ARRAY_DICTIONARY_

#include "abstract_dictionary.hpp"
#include "Entry.hpp"

template <class KeyType, class ItemType>
class ArrayDictionary : public AbstractDictionary<KeyType, ItemType>
{
private:
   static const int DEFAULT_CAPACITY = 100;           // Small capacity to test for
                                                      // a full dictionary
   std::unique_ptr<Entry<KeyType, ItemType>[]> items; // Array of dictionary entries
   int itemCount;                                     // Current count of dictionary items
   void destroyDictionary();
   int findEntryIndex(int firstIndex, int lastIndex,
                      const KeyType &searchKey) const;

public:
   ArrayDictionary();
   ArrayDictionary(const ArrayDictionary<KeyType, ItemType> &dict);

   virtual ~ArrayDictionary();

   bool isEmpty() const;
   int getNumberOfItems() const;
   bool add(const KeyType &searchKey, const ItemType &newItem);
   bool remove(const KeyType &searchKey);
   void clear();
   ItemType getItem(const KeyType &searchKey) const;
   bool contains(const KeyType &searchKey) const;

   /** Traverses the items in this dictionary in sorted search-key order
       and calls a given client function once for each item. */
   void traverse(void visit(ItemType &)) const;
}; // end ArrayDictionary

#include "ArrayDictionary.tpp"
#endif
