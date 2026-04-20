/** An array-based implementation of the ADT map
    that organizes its data items in sorted search-key order.
   Search keys in the map are unique.
 @file ArrayMap.tpp */

#include "ArrayMap.hpp"
#include <stdexcept>

template <typename KeyType, typename ItemType>
int ArrayMap<KeyType, ItemType>::findEntryIndex(int firstIndex, int lastIndex, const KeyType &itemKey) const
{
   int middleIndex = firstIndex + (lastIndex - firstIndex) / 2;

   if (firstIndex > lastIndex)
      return -1; // Not found

   else if (itemKey == items[middleIndex].getKey())
      return middleIndex;

   else if (itemKey < items[middleIndex].getKey())
      return findEntryIndex(firstIndex, middleIndex - 1, itemKey);

   else
      return findEntryIndex(middleIndex + 1, lastIndex, itemKey);
} // Recursive binary search, private method

template <typename KeyType, typename ItemType>
ArrayMap<KeyType, ItemType>::ArrayMap() : itemCount(0)
{
   items = new Entry<KeyType, ItemType>[DEFAULT_CAPACITY];
} // end constructor

template <typename KeyType, typename ItemType>
ArrayMap<KeyType, ItemType>::ArrayMap(const ArrayMap<KeyType, ItemType> &rhs) : itemCount(rhs.itemCount)
{
   items = new Entry<KeyType, ItemType>[DEFAULT_CAPACITY];
   for (int index = 0; index < rhs.itemCount; index++)
   {
      items[index] = rhs.items[index];
   }
} // end copy constructor

template <typename KeyType, typename ItemType>
ArrayMap<KeyType, ItemType> &ArrayMap<KeyType, ItemType>::operator=(ArrayMap<KeyType, ItemType> rhs)
{
   itemCount = rhs.itemCount;
   std::swap(items, rhs.items);
   return *this;
} // end copy assignment operator

template <typename KeyType, typename ItemType>
ArrayMap<KeyType, ItemType>::~ArrayMap()
{
   delete[] items;
   items = nullptr;
} // end destructor

template <typename KeyType, typename ItemType>
bool ArrayMap<KeyType, ItemType>::isEmpty() const
{
   return (itemCount == 0);
}

template <typename KeyType, typename ItemType>
int ArrayMap<KeyType, ItemType>::getNumberOfItems() const
{
   return itemCount;
}

template <typename KeyType, typename ItemType>
bool ArrayMap<KeyType, ItemType>::add(const KeyType &searchKey, const ItemType &newItem)
{
   bool ableToInsert = (itemCount < DEFAULT_CAPACITY) && (!contains(searchKey));
   if (ableToInsert)
   {
      // Make room for new entry by shifting all entries at
      // positions >= newPosition toward the end of the array
      // (no shift if newPosition == itemCount + 1). Performing
      // a binary search doesn’t help here, because we need to
      // shift the entries while looking for the insertion location.
      int index = itemCount;

      // Short-circuit evaluation is important
      while ((index > 0) && (searchKey < items[index - 1].getKey()))
      {
         items[index] = items[index - 1];
         index--;
      } // end while

      // Insert new entry
      items[index] = Entry<KeyType, ItemType>(searchKey, newItem);
      itemCount++; // Increase count of entries
   } // end if

   return ableToInsert;
} // end add

template <typename KeyType, typename ItemType>
bool ArrayMap<KeyType, ItemType>::remove(const KeyType &itemKey)
{
   int itemIndex = findEntryIndex(0, itemCount - 1, itemKey);
   bool ableToRemove = !isEmpty() && (itemIndex >= 0);

   if (ableToRemove)
   {
      // If found, shift items to left
      while (itemIndex < itemCount - 1)
      {
         items[itemIndex] = items[itemIndex + 1];
         itemIndex++;
      } // end while

      itemCount--; // Decrease count of entries
   } // end if

   return ableToRemove;
} // end remove

template <typename KeyType, typename ItemType>
void ArrayMap<KeyType, ItemType>::clear()
{
   delete[] items;
   items = new Entry<KeyType, ItemType>[DEFAULT_CAPACITY];
   itemCount = 0;
} // end clear

template <typename KeyType, typename ItemType>
ItemType ArrayMap<KeyType, ItemType>::getItem(const KeyType &itemKey) const
{
   int itemIndex = findEntryIndex(0, itemCount - 1, itemKey);
   if (itemIndex < 0)
      throw std::invalid_argument("getItem: item not found");
   return items[itemIndex].getItem();
} // end getItem

template <typename KeyType, typename ItemType>
bool ArrayMap<KeyType, ItemType>::contains(const KeyType &itemKey) const
{
   return (findEntryIndex(0, itemCount - 1, itemKey) >= 0);
} // end contains

template <typename KeyType, typename ItemType>
void ArrayMap<KeyType, ItemType>::traverse(std::function<void(ItemType &)> visit) const
{
   // Simple because the array is sorted.
   for (int index = 0; index < itemCount; index++)
   {
      ItemType currentItem = items[index].getItem();
      visit(currentItem);
   } // end for
} // end traverse

// TODO: The core feature of ADT map is to build the association between key and value,
// why do we bother to sort the keys in ADT map. what operations of ADT map does it benefit the most?