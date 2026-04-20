/** An array-based implementation of the ADT map
    that organizes its data items in sorted search-key order.
    Search keys in the map are unique.
 @file ArrayMap.hpp */

#ifndef ARRAY_MAP_
#define ARRAY_MAP_

#include "abstract_map.hpp"
#include "Entry.hpp"
#include <functional>

template <typename KeyType, typename ItemType>
class ArrayMap : public AbstractMap<KeyType, ItemType>
{
private:
   static const int DEFAULT_CAPACITY = 100; // Small capacity to test for a full map
   Entry<KeyType, ItemType> *items;         // Array of map entries
   int itemCount;                           // Current count of map items
   int findEntryIndex(int firstIndex, int lastIndex, const KeyType &searchKey) const;

public:
   ArrayMap();
   ArrayMap(const ArrayMap<KeyType, ItemType> &rhs);
   ArrayMap<KeyType, ItemType> &operator=(ArrayMap<KeyType, ItemType> rhs);
   virtual ~ArrayMap();

   bool isEmpty() const;
   int getNumberOfItems() const;
   bool add(const KeyType &searchKey, const ItemType &newItem);
   bool remove(const KeyType &searchKey);
   void clear();
   ItemType getItem(const KeyType &searchKey) const;
   bool contains(const KeyType &searchKey) const;

   /** Traverses the items in this map in sorted search-key order
       and calls a given client function once for each item. */
   void traverse(std::function<void(ItemType &)> visit) const;
}; // end ArrayMap

#include "ArrayMap.tpp"
#endif