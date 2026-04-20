/** Separate chaining resolves collisions
 @file  HashedMap.hpp */

#ifndef HASHED_MAP_
#define HASHED_MAP_

#include "abstract_map.hpp"
#include "Entry.hpp"
#include <memory>
#include <functional>

/* Entry Visualization (key, item)
   (5.0, "five") or (9.0, "nine") */

/* HashedEntry node structure
   ┌──────────────┬───────────┐
   │ entry        │  nextPtr  │──> next HashedEntry or nullptr
   │ (key, item)  │           │
   └──────────────┴───────────┘

   HashedEntry is a linked chain via nextPtr (shared_ptr):
   (5.0, "five", nextPtr) -> (9.0, "nine", nextPtr) -> (11.0, "eleven", nullptr) */

template <typename KeyType, typename ItemType>
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

template <typename KeyType, typename ItemType>
using hashTableType = std::shared_ptr<HashedEntry<KeyType, ItemType>>[];
// Define a hashTableType as a type alias for an array of HashedEntry

/* unique_ptr --> shared_ptr[] --> HashedEntry chain

hashTableType Visualization
------------------------------------------
| HashIndex |
------------------------------------------
|     0     |  (5.0, "five", nextPtr) -> (9.0, "nine", nextPtr) -> (11.0, "eleven", nullptr)
------------------------------------------
|     1     |  ...
------------------------------------------
|     2     |  (4.0, "four", nullptr)
------------------------------------------
...
...
-------------------------------------------
|   ...     |  ...
-------------------------------------------
*/

template <typename KeyType, typename ItemType>
class HashedMap : public AbstractMap<KeyType, ItemType>
{
private:
   std::unique_ptr<hashTableType<KeyType, ItemType>> hashTable; // A unique pointer to hashTableType
   int itemCount;                                               // Count of map entries
   int hashTableSize;                                           // User-defined, table size (prime number)
   static const int DEFAULT_CAPACITY = 101;

   int getHashIndex(const KeyType &itemKey) const;
   int getNextPrime(int number) const;
   bool isPrime(int number) const;

public:
   HashedMap();
   HashedMap(int hashTableSize);
   HashedMap(const HashedMap<KeyType, ItemType> &rhs);
   HashedMap<KeyType, ItemType> &operator=(HashedMap<KeyType, ItemType> rhs);
   virtual ~HashedMap();

   bool isEmpty() const;
   int getNumberOfItems() const;
   void clear();
   bool add(const KeyType &itemKey, const ItemType &newItem);
   bool remove(const KeyType &itemKey);
   ItemType getItem(const KeyType &itemKey) const;
   bool contains(const KeyType &itemKey) const;
   void traverse(std::function<void(ItemType &)> visit) const;
}; // end HashedMap

#include "HashedMap.tpp"
#endif

/**
Hash Map Visualization (itemCount = 6, hashTableSize = 7)
----------------------------------------------------------------------------
| HashIndex (int) |                    Entry
----------------------------------------------------------------------------
|         0       |       (8.0, "eight", nullptr)
----------------------------------------------------------------------------
|         1       |
----------------------------------------------------------------------------
|         2       |
----------------------------------------------------------------------------
|         3       |       (9.0, "nine", nextPtr) -> (11.0, "eleven", nullptr)
----------------------------------------------------------------------------
|         4       |
----------------------------------------------------------------------------
|         5       |
----------------------------------------------------------------------------
|         6       |       (4.0, "four", nextPtr) -> (18.0, "eighteen", nextPtr) -> (25.0, "twenty-five", nullptr)
----------------------------------------------------------------------------
*/