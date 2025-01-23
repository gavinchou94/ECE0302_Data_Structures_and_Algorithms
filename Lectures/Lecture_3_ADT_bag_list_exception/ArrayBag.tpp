/** @file ArrayBag.tpp */

#include "ArrayBag.hpp"
#include <cstddef>

template <typename ItemType>
ArrayBag<ItemType>::ArrayBag() : itemCount(0)
{
} // end default constructor

template <typename ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
   return itemCount;
} // end getCurrentSize

template <typename ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
   return itemCount == 0;
} // end isEmpty

template <typename ItemType>
bool ArrayBag<ItemType>::add(const ItemType &newEntry)
{
   bool hasRoomToAdd = (itemCount < DEFAULT_CAPACITY);
   if (hasRoomToAdd)
   {
      items[itemCount] = newEntry;
      itemCount++;
   } // end if

   return hasRoomToAdd;
} // end add

// STUB
template <typename ItemType>
bool ArrayBag<ItemType>::remove(const ItemType &anEntry)
{
   return false; // STUB
} // end remove

// STUB
template <typename ItemType>
void ArrayBag<ItemType>::clear()
{
   // STUB
} // end clear

template <typename ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType &anEntry) const
{
   if (!contains(anEntry))
   {
      throw std::invalid_argument("Item not found in bag");
   }

   int frequency = 0;
   int curIndex = 0; // Current array index
   while (curIndex < itemCount)
   {
      if (items[curIndex] == anEntry)
      {
         frequency++;
      } // end if

      curIndex++; // Increment to next entry
   } // end while

   return frequency;
} // end getFrequencyOf

template <typename ItemType>
bool ArrayBag<ItemType>::contains(const ItemType &anEntry) const
{
   return getIndexOf(anEntry) > -1;
} // end contains

template <typename ItemType>
std::vector<ItemType> ArrayBag<ItemType>::toVector() const
{
   std::vector<ItemType> bagContents;
   for (int i = 0; i < itemCount; i++)
      bagContents.push_back(items[i]);

   return bagContents;
} // end toVector

// private
template <typename ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType &target) const
{
   bool found = false;
   int result = -1;
   int searchIndex = 0;

   // If the bag is empty, itemCount is zero, so loop is skipped
   while (!found && (searchIndex < itemCount))
   {
      if (items[searchIndex] == target)
      {
         found = true;
         result = searchIndex;
      }
      else
      {
         searchIndex++;
      } // end if
   } // end while

   return result;
} // end getIndexOf
