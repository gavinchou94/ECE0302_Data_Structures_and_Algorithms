/** @file  HashedDictionary.tpp
 Separate chaining resolves collisions
*/

#include "HashedDictionary.hpp"
#include <cmath> // For sqrt

//////////////////////////////////////////////////////////////////////
// Private helper methods
//////////////////////////////////////////////////////////////////////

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::destroyDictionary()
{
   for (int i = 0; i < hashTableSize; i++)
   {
      // If there are hashed entries at this location,
      // we need to delete them
      while (hashTable[i] != nullptr)
      {
         hashTable[i] = hashTable[i]->getNext();
      } // end while
   } // end for

   itemCount = 0;
} // end destroyDictionary

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType &key) const
{
   // Obtain the hash function for KeyType directly from std::hash
   auto hashFunction = std::hash<KeyType>();

   unsigned long result = hashFunction(key);

   // hashFunction returns a large numerical value for any type of key that can be easily mapped
   // e.g. key=1.14 -> 4607812922747849277
   // 2.35 -> 4612474148362177741
   // 3.98 -> 4616144582058484695

   // another type "hello" -> 235368941344721064
   // "hola" -> 16100555142912586306
   // "hi" -> 17851379961049682469
   // "hey" -> 8758220568996551694

   // static_cast needed since hashFunction returns an unsigned long
   // and hashTableSize is an int, it is a modulo operation
   return static_cast<int>(result % hashTableSize);
} // end getHashIndex

// hashTableSize must be prime since we divide the hash value by hashTableSize
// if hashTableSize is not prime, we will have a lot of collisions at hashTableType[0]
// Any number that is divisible by hashTableSize will hash to 0
// Linked list of entries (we design it to be HashedEntry) at hashTableType[0] will grow
// and grow and grow, which slow down the search due to linked list traversal

// These two functions are used to find the next prime number
template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNextPrime(int number) const
{
   bool foundPrime = false;
   if ((number % 2) == 0)
      number++;

   while (!foundPrime)
   {
      if ((number % 5 == 0) || !isPrime(number))
      {
         number = number + 2;
      }
      else
         foundPrime = true;
   } // end

   return number;
} // end getNextPrime

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isPrime(int number) const
{
   bool isPrimeNumber = true; // Assume prime, prove otherwise

   if ((number == 2) || (number == 3)) // Smallest primes
      isPrimeNumber = true;
   else
   {
      if ((number % 2 == 0) || (number < 2)) // Even number or ineligible
         isPrimeNumber = false;
      else
      {
         int root = sqrt(number); // Limit of search
         int i = 3;
         do
         {
            if (number % i == 0) // Not prime
               isPrimeNumber = false;
            else
               i = i + 2;

         } while ((isPrimeNumber == true) && (i <= root));
      } // end if
   } // endif

   return isPrimeNumber;
} // end isPrime

//////////////////////////////////////////////////////////////////////
// Constructors & Destructor
//////////////////////////////////////////////////////////////////////

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
    : itemCount(0), hashTableSize(DEFAULT_CAPACITY)
{
   // All shared pointers in array initialized to nullptr & reference count zero
   hashTable = std::unique_ptr<std::shared_ptr<HashedEntry<KeyType, ItemType>>[]>(
       new std::shared_ptr<HashedEntry<KeyType, ItemType>>[DEFAULT_CAPACITY]());
   // You may think this as a 2D array like ptr = **hashTable
   // hashTable[0] = nullptr; // hashTable[1] = nullptr; ... hashTable[DEFAULT_CAPACITY-1] = nullptr;

} // end

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(int hashTableSize)
    : itemCount(0), hashTableSize(getNextPrime(hashTableSize))
{
   // All shared pointers in array initialized to nullptr & reference count zero
   hashTable = std::unique_ptr<std::shared_ptr<HashedEntry<KeyType, ItemType>>[]>(
       new std::shared_ptr<HashedEntry<KeyType, ItemType>>[hashTableSize]());
} // end constructor

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(const HashedDictionary<KeyType, ItemType> &dict)
    : itemCount(dict.itemCount), hashTableSize(dict.hashTableSize)
{
   hashTable = std::unique_ptr<std::shared_ptr<HashedEntry<KeyType, ItemType>>[]>(
       new std::shared_ptr<HashedEntry<KeyType, ItemType>>[dict.hashTableSize]());
   for (int index = 0; index < dict.hashTableSize; index++)
   {
      hashTable[index] = dict.hashTable[index];
   } // end for
} // end

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::~HashedDictionary()
{
   destroyDictionary();
} // end destructor

////////////////////////////////////////////////////////////////////
// Status and public maintenance (clear) methods
//////////////////////////////////////////////////////////////////////

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty() const
{
   return (itemCount == 0);
} // end isEmpty

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumberOfItems() const
{
   return itemCount;
} // end getNumberOfItems

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear()
{
   destroyDictionary();
} // end clear

///////////////////////////////////////////////////////////////////
// Container methods (add, remove, getItem, contains, traverse)
//////////////////////////////////////////////////////////////////////

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::add(const KeyType &searchKey, const ItemType &newItem)
{
   // Check if the item already exists
   if (contains(searchKey))
      return false;

   // Create entry to add to dictionary
   auto entryToAddPtr = std::make_shared<HashedEntry<KeyType, ItemType>>(searchKey, newItem);

   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);

   // Add the entry to the chain at itemHashIndex
   if (hashTable[itemHashIndex] == nullptr)
   {
      hashTable[itemHashIndex] = entryToAddPtr;
   }
   else
   {
      // Base on the design, where do we add the new entry at each index of the hash table?
      // Front? Middle? End?
      entryToAddPtr->setNext(hashTable[itemHashIndex]);
      hashTable[itemHashIndex] = entryToAddPtr;
   } // end if
   itemCount++;
   return true;
} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType &searchKey)
{
   bool itemFound = false;

   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);
   if (hashTable[itemHashIndex] != nullptr)
   {
      // Special case - first node has target
      if (searchKey == hashTable[itemHashIndex]->getKey())
      {
         hashTable[itemHashIndex] = hashTable[itemHashIndex]->getNext();
         itemFound = true;
      }
      else // Search the rest of the chain
      {
         auto prevPtr = hashTable[itemHashIndex];
         auto curPtr = prevPtr->getNext();
         while ((curPtr != nullptr) && !itemFound)
         {
            // Found item in chain so remove that node
            if (searchKey == curPtr->getKey())
            {
               prevPtr->setNext(curPtr->getNext());
               itemFound = true;
            }
            else // Look at next entry in chain
            {
               prevPtr = curPtr;
               curPtr = curPtr->getNext();
            } // end if
         } // end while
      } // end if
   } // end if
   if (itemFound)
      itemCount--;

   return itemFound;
} // end remove

template <class KeyType, class ItemType>
ItemType HashedDictionary<KeyType, ItemType>::getItem(const KeyType &searchKey) const
{
   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);
   auto chainPtr = hashTable[itemHashIndex];

   // Short circuit evaluation is important here
   while ((chainPtr != nullptr) && (searchKey != chainPtr->getKey()))
   {
      chainPtr = chainPtr->getNext();
   } // end while

   if (chainPtr == nullptr)
      throw std::runtime_error("Key not found");

   return chainPtr->getItem();
} // end getItem

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::contains(const KeyType &searchKey) const
{
   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);

   auto chainPtr = hashTable[itemHashIndex];

   // Short circuit evaluation is important here
   while ((chainPtr != nullptr) && (searchKey != chainPtr->getKey()))
   {
      chainPtr = chainPtr->getNext();
   } // end while

   return (chainPtr != nullptr);
} // end contains

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(void visit(ItemType &)) const
{
   // Simple because the array is sorted.
   for (int index = 0; index < hashTableSize; index++)
   {
      std::cout << "\n Index " << index << "  :"; // for testing
      auto chainPtr = hashTable[index];
      while (chainPtr != nullptr)
      {
         ItemType currentItem = chainPtr->getItem();
         visit(currentItem);
         chainPtr = chainPtr->getNext();
      } // end while
   } // end for
} // end traverse