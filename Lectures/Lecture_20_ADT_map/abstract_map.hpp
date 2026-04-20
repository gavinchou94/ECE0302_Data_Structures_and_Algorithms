/** An interface for the ADT map. (Distinct search keys.)
 @file  abstract_map.hpp */

#ifndef ABSTRACT_MAP_
#define ABSTRACT_MAP_

#include <functional>

template <typename KeyType, typename ItemType>
class AbstractMap
{
public:
   /** Sees whether this map is empty.
    @return True if the map is empty;
       otherwise returns false. */
   virtual bool isEmpty() const = 0;

   /** Gets the number of items in this map.
    @return The number of items in the map. */
   virtual int getNumberOfItems() const = 0;

   /** Inserts an item into this map according to the item’s search key.
    @pre  The search key of the new item differs from all search
       keys presently in the map.
    @post  If the insertion is successful, newItem is in its
       proper position within the map.
    @param searchKey  The search key associated with the item to be inserted.
    @param newItem  The item to add to the map.
    @return  True if item was successfully added, or false if not. */
   virtual bool add(const KeyType &searchKey, const ItemType &newItem) = 0;

   /** Removes an item with the given search key from this map.
    @post  If the item whose search key equals searchKey existed in the map,
       the item was removed.
    @param searchKey  The search key of the item to be removed.
    @return  True if the item was successfully removed, or false if not. */
   virtual bool remove(const KeyType &searchKey) = 0;

   /** Removes all entries from this map. */
   virtual void clear() = 0;

   /** Retrieves an item with a given search key from a map.
    @post  If the retrieval is successful, the item is returned.
    @param searchKey  The search key of the item to be retrieved.
    @return  The item associated with the search key.
    @throw  std::invalid_argument if the item does not exist. */
   virtual ItemType getItem(const KeyType &searchKey) const = 0;

   /** Sees whether this map contains an item with a given search key.
    @post  The map is unchanged.
    @param searchKey  The search key of the item to be retrieved.
    @return  True if an item with the given search key exists in the map. */
   virtual bool contains(const KeyType &searchKey) const = 0;

   /** Traverses this map and calls a given client function once for each item.
    * @post The given function’s action occurs once for each item in the
         map and possibly alters the item.
    * @param visit A client function. */
   virtual void traverse(std::function<void(ItemType &)> visit) const = 0;

   /** Deletes this map and frees its allocated memory. */
   virtual ~AbstractMap() {}
}; // end AbstractMap

#endif