/** @file ArrayBagInt.cpp */

#include "ArrayBagInt.hpp"
#include <stdexcept>

// alg efficiency O(1) here
ArrayBagInt::ArrayBagInt() : itemCount(0)
{
} // end default constructor

// alg efficiency O(1) here
int ArrayBagInt::getCurrentSize() const
{
   return itemCount;
} // end getCurrentSize

// alg efficiency O(1) here
bool ArrayBagInt::isEmpty() const
{
   return itemCount == 0;
} // end isEmpty

// alg efficiency O(1) here
bool ArrayBagInt::add(const int &newEntry)
{
   bool hasRoomToAdd = (itemCount < DEFAULT_CAPACITY);
   if (hasRoomToAdd)
   {
      items[itemCount] = newEntry;
      itemCount++;
   } // end if

   return hasRoomToAdd;
} // end add

// TODO: explain what is the alg efficiency of this method (Hints: what method does it call?)
bool ArrayBagInt::remove(const int &anEntry)
{
   int index = getIndexOf(anEntry);
   if (index > -1)
   {
      itemCount--;
      items[index] = items[itemCount]; // Replace entry to be removed with last entry
      return true;
   }
   return false;
} // end remove

// TODO: explain what is the alg efficiency of this method (Hints: what method does it call? and any keyword)
bool ArrayBagInt::remove2(const int &anEntry)
{
   int index = getIndexOf(anEntry);
   if (index > -1)
   {
      for (int i = index; i < itemCount - 1; i++)
      {
         items[i] = items[i + 1]; // Shift entries to the left
      }
      itemCount--;
      return true;
   }
   return false;
} // end remove

// What is the alg efficiency of this method?
void ArrayBagInt::clear()
{
   itemCount = 0;
} // end clear

// What is the alg efficiency of clear2?
void ArrayBagInt::clear2()
{
   for (int i = 0; i < itemCount; i++)
   {
      items[i] = 0;
   }
   itemCount = 0;
} // end clear

// what is the alg efficiency of clear3?
void ArrayBagInt::clear3()
{
   while (!isEmpty())
   {
      remove(items[0]);
   }
} // end clear

// what is the alg efficiency of clear4?
void ArrayBagInt::clear4()
{
   while (!isEmpty())
   {
      remove2(items[0]);
   }
} // end clear

// alg efficiency depends on that of both getIndexOf and the while-loop
int ArrayBagInt::getFrequencyOf(const int &anEntry) const
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

// alg efficiency depends on that of getIndexOf
bool ArrayBagInt::contains(const int &anEntry) const
{
   return getIndexOf(anEntry) > -1;
} // end contains

// alg efficiency depends on that of getIndexOf
bool ArrayBagInt::replace(const int &oldEntry, const int &newEntry)
{
   int index = getIndexOf(oldEntry);
   if (index == -1)
   {
      return false;
   }
   items[index] = newEntry;
   return true;
}

// alg efficiency is O(n) here
// remember that the efficiency of accessing items[i] in an array is O(1)
std::vector<int> ArrayBagInt::toVector() const
{
   std::vector<int> bagContents;
   for (int i = 0; i < itemCount; i++)
      bagContents.push_back(items[i]);

   return bagContents;
} // end toVector

// private
// alg efficiency is O(n) here, n is the size of the bag due to the sequential search
int ArrayBagInt::getIndexOf(const int &target) const
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

// If some preprocessing work (that we assume is done at no cost) is done before using getIndexOf(),
// the alg efficiency of getIndexOf() is now reduced to O(log n):

// What is the new alg efficiency of the rest of methods using this new implementation of getIndexOf(),
// e.g., replace(), getFrequencyOf()?