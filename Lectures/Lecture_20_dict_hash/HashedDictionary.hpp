/** @file  HashedDictionary.hpp */

#ifndef HASHED_DICTIONARY_
#define HASHED_DICTIONARY_

#include "abstract_dictionary.hpp"
#include "Entry.hpp"
#include <memory>

template <class KeyType, class ItemType>
struct HashedEntry
{
   Entry<KeyType, ItemType> entry;
   std::shared_ptr<HashedEntry<KeyType, ItemType>> nextPtr;
   HashedEntry(Entry<KeyType, ItemType> entry, std::shared_ptr<HashedEntry<KeyType, ItemType>> nextPtr) : entry(entry), nextPtr(nextPtr) {}
   HashedEntry(Entry<KeyType, ItemType> entry) : entry(entry), nextPtr(nullptr) {}
   HashedEntry(KeyType key, ItemType item) : entry(key, item), nextPtr(nullptr) {}
   std::shared_ptr<HashedEntry<KeyType, ItemType>> getNext() const { return nextPtr; }
   void setNext(std::shared_ptr<HashedEntry<KeyType, ItemType>> next) { nextPtr = next; }
   KeyType getKey() const { return entry.getKey(); }
   ItemType getItem() const { return entry.getItem(); }
};
// A HashedEntry is a linked list of regular dict entries (Entry) using shared_ptr

template <class KeyType, class ItemType>
using hashTableType = std::shared_ptr<HashedEntry<KeyType, ItemType>>[];
// Define a hashTableType as an array of shared_ptr to HashedEntry

template <class KeyType, class ItemType>
class HashedDictionary : public AbstractDictionary<KeyType, ItemType>
{
private:
   // creates a unique pointer to an array of shared HashedEntry pointers
   std::unique_ptr<hashTableType<KeyType, ItemType>> hashTable; // Array of pointers to entries
   int itemCount;                                               // Count of dictionary entries
   int hashTableSize;                                           // User-defined, table size must be prime
   static const int DEFAULT_CAPACITY = 101;

   void destroyDictionary();
   int getHashIndex(const KeyType &itemKey) const;
   int getNextPrime(int number) const;
   bool isPrime(int number) const;

public:
   HashedDictionary();
   HashedDictionary(int hashTableSize);
   HashedDictionary(const HashedDictionary<KeyType, ItemType> &dict);

   virtual ~HashedDictionary();

   bool isEmpty() const;
   int getNumberOfItems() const;
   void clear();
   bool add(const KeyType &itemKey, const ItemType &newItem);
   bool remove(const KeyType &itemKey);
   ItemType getItem(const KeyType &itemKey) const;
   bool contains(const KeyType &itemKey) const;
   void traverse(void visit(ItemType &)) const;
}; // end HashedDictionary

#include "HashedDictionary.tpp"
#endif

/*
Hash Dictionary Visualization (itemCount = 7, hashTableSize = 7)
----------------------------------------------------------------------------
| HashIndex (int) |  Key(double)  |  Item(string)  |  nextPtr (*HashedEntry)
----------------------------------------------------------------------------
|         0       |       6.0     |      "six"     |       nullptr
----------------------------------------------------------------------------
|         1       |       8.0     |    "eight"     |       nullptr
----------------------------------------------------------------------------
|         2       |
----------------------------------------------------------------------------
|         3       |       9.0     |    "nine"      |  &(5.0, "five", nullptr)  |   5.0  |  "five"  |  nullptr
----------------------------------------------------------------------------
|         4       |       7.0     |    "seven"     |       nullptr
----------------------------------------------------------------------------
|         5       |       10.0    |    "ten"       |       nullptr
----------------------------------------------------------------------------
|         6       |       4.0     |    "four"      |       nullptr
----------------------------------------------------------------------------

HashedEntry Visualization
(5, five, nullptr)

hashTableType
------------------------------------------
| HashIndex |
------------------------------------------
|     0     |  ...
------------------------------------------
|     1     |  ...
------------------------------------------
|     2     |  ...
------------------------------------------
...
...
-------------------------------------------
|   n-1     |  ...
-------------------------------------------

*/
