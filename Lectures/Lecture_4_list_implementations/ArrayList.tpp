/** @file ArrayList.tpp */

#include "ArrayList.hpp" // Header file

template <typename ItemType>
ArrayList<ItemType>::ArrayList() : itemCount(0)
{
} // end default constructor

template <typename ItemType>
bool ArrayList<ItemType>::isEmpty() const
{
   return itemCount == 0;
} // end isEmpty

template <typename ItemType>
int ArrayList<ItemType>::getLength() const
{
   return itemCount;
} // end getLength

template <typename ItemType>
bool ArrayList<ItemType>::insert(int newPosition, const ItemType &newEntry)
{
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1) && (itemCount < DEFAULT_CAPACITY);
   if (ableToInsert)
   {
      // Make room for new entry by shifting all entries at
      // positions >= newPosition toward the end of the array
      // (no shift if newPosition == itemCount + 1)
      for (int entryPosition = itemCount; entryPosition >= newPosition; entryPosition--)
      {
         items[entryPosition + 1] = items[entryPosition]; // copy entry on the left to right
      }
      items[newPosition] = newEntry; // Insert new entry
      itemCount++;                   // Increase count of entries
   } // end if

   return ableToInsert;
} // end insert

template <typename ItemType>
bool ArrayList<ItemType>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove)
   {
      // Remove entry by shifting all entries after the one at
      // position toward the beginning of the array
      // (no shift if position == itemCount)
      for (int entryPosition = position; entryPosition < itemCount; entryPosition++)
      {
         items[entryPosition] = items[entryPosition + 1]; // copy entry on the right to left
      }
      itemCount--; // Decrease count of entries
   } // end if

   return ableToRemove;
} // end remove

template <typename ItemType>
void ArrayList<ItemType>::clear()
{
   itemCount = 0;
} // end clear

template <typename ItemType>
ItemType ArrayList<ItemType>::getEntry(int position) const
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      return items[position]; // given items[0] is not used, position is directly the index
   }
   else
   {
      throw std::out_of_range("Invalid position, must be between 1 and getLength().");
   } // end if
} // end getEntry

template <typename ItemType>
void ArrayList<ItemType>::replace(int position, const ItemType &newEntry)
{
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
   {
      items[position] = newEntry;
   }
   else
   {
      throw std::out_of_range("Invalid position, must be between 1 and getLength().");
   } // end if
} // end replace

//  End of implementation file.