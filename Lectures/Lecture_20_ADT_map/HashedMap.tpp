/** Separate chaining resolves collisions
 @file  HashedMap.tpp */

#include "HashedMap.hpp"
#include <cmath>

//////////////////////////////////////////////////////////////////////
// Private helper methods
//////////////////////////////////////////////////////////////////////

template <typename KeyType, typename ItemType>
int HashedMap<KeyType, ItemType>::getHashIndex(const KeyType &key) const
{
   // Obtain the hash function for KeyType directly from std::hash
   auto hashFunction = std::hash<KeyType>();

   std::size_t result = hashFunction(key);

   // hashFunction returns a large numerical value for any type of key that can be easily mapped
   // e.g. key=1.14 -> 4607812922747849277
   // 2.35 -> 4612474148362177741
   // 3.98 -> 4616144582058484695

   // another type "hello" -> 235368941344721064
   // "hola" -> 16100555142912586306
   // "hi" -> 17851379961049682469
   // "hey" -> 8758220568996551694

   // Hash value would depends on platform, compiler etc,
   // but it is deterministic for the same key on the same platform and compiler

   return static_cast<int>(result % hashTableSize);
   // static_cast needed since hashFunction returns a std::size_t
   // and hashTableSize is an int, it is a modulo operation
} // end getHashIndex

// hashTableSize must be prime since we divide the hash value by hashTableSize
// if hashTableSize is not prime, we will have a lot of collisions at hashTableType[0]
// Any number that is divisible by hashTableSize will hash to 0
// Linked chain of entries (we define it as HashedEntry) at hashTableType[0] will grow
// and grow and grow, which slow down the search due to linked list traversal

// These two functions are used to find the next prime number
template <typename KeyType, typename ItemType>
int HashedMap<KeyType, ItemType>::getNextPrime(int number) const
{
   if (number <= 2)
      return 2;

   if (number % 2 == 0)
      number++;

   while (!isPrime(number))
   {
      number += 2;
   }

   return number;
} // end getNextPrime

template <typename KeyType, typename ItemType>
bool HashedMap<KeyType, ItemType>::isPrime(int number) const
{
   if (number < 2)
      return false;

   if ((number == 2) || (number == 3))
      return true;

   if (number % 2 == 0)
      return false;

   int root = sqrt(number);
   for (int divisor = 3; divisor <= root; divisor += 2)
   {
      if (number % divisor == 0)
         return false;
   }

   return true;
} // end isPrime

//////////////////////////////////////////////////////////////////////
// Constructors & Destructor
//////////////////////////////////////////////////////////////////////

template <typename KeyType, typename ItemType>
HashedMap<KeyType, ItemType>::HashedMap() : itemCount(0), hashTableSize(DEFAULT_CAPACITY)
{
   // All shared pointers in array initialized to nullptr & reference count zero
   hashTable = std::unique_ptr<std::shared_ptr<HashedEntry<KeyType, ItemType>>[]>(
       new std::shared_ptr<HashedEntry<KeyType, ItemType>>[DEFAULT_CAPACITY]());
   // You may think this as a 2D array like ptr = **hashTable
   // hashTable[0] = nullptr; // hashTable[1] = nullptr; ... hashTable[DEFAULT_CAPACITY-1] = nullptr;
} // end default constructor

template <typename KeyType, typename ItemType>
HashedMap<KeyType, ItemType>::HashedMap(int hashTableSize) : itemCount(0), hashTableSize(getNextPrime(hashTableSize))
{
   // Client specifies a hash table size, but we adjust to next prime if not prime
   hashTable = std::unique_ptr<std::shared_ptr<HashedEntry<KeyType, ItemType>>[]>(
       new std::shared_ptr<HashedEntry<KeyType, ItemType>>[this->hashTableSize]());
} // end constructor

template <typename KeyType, typename ItemType>
HashedMap<KeyType, ItemType>::HashedMap(const HashedMap<KeyType, ItemType> &rhs)
    : itemCount(rhs.itemCount), hashTableSize(rhs.hashTableSize)
{
   hashTable = std::unique_ptr<std::shared_ptr<HashedEntry<KeyType, ItemType>>[]>(
       new std::shared_ptr<HashedEntry<KeyType, ItemType>>[rhs.hashTableSize]());
   for (int index = 0; index < rhs.hashTableSize; index++)
   {
      auto srcPtr = rhs.hashTable[index];
      auto curPtr = hashTable[index];
      while (srcPtr != nullptr)
      {
         auto newNode = std::make_shared<HashedEntry<KeyType, ItemType>>(srcPtr->getKey(), srcPtr->getItem());
         if (hashTable[index] == nullptr)
         {
            hashTable[index] = newNode;
            curPtr = newNode;
         }
         else
         {
            curPtr->setNext(newNode);
            curPtr = newNode;
         }
         srcPtr = srcPtr->getNext();
      }
   } // end for
} // end copy constructor

template <typename KeyType, typename ItemType>
HashedMap<KeyType, ItemType> &HashedMap<KeyType, ItemType>::operator=(HashedMap<KeyType, ItemType> rhs)
{
   std::swap(itemCount, rhs.itemCount);
   std::swap(hashTableSize, rhs.hashTableSize);
   std::swap(hashTable, rhs.hashTable);
   return *this;
}

template <typename KeyType, typename ItemType>
HashedMap<KeyType, ItemType>::~HashedMap()
{
   clear();
} // end destructor

//////////////////////////////////////////////////////////////////////
// Public methods
//////////////////////////////////////////////////////////////////////

template <typename KeyType, typename ItemType>
bool HashedMap<KeyType, ItemType>::isEmpty() const
{
   return (itemCount == 0);
} // end isEmpty

template <typename KeyType, typename ItemType>
int HashedMap<KeyType, ItemType>::getNumberOfItems() const
{
   return itemCount;
} // end getNumberOfItems

template <typename KeyType, typename ItemType>
void HashedMap<KeyType, ItemType>::clear()
{
   for (int i = 0; i < hashTableSize; i++)
   {
      // If there are hashed entries at this location, we need to delete them
      while (hashTable[i] != nullptr)
      {
         hashTable[i] = hashTable[i]->getNext();
         // Move to next entry in chain, previous entry will be automatically deleted when the shared pointer goes out of scope
      }
   }
   itemCount = 0;
} // end clear

template <typename KeyType, typename ItemType>
bool HashedMap<KeyType, ItemType>::add(const KeyType &searchKey, const ItemType &newItem)
{
   // Check if the item already exists
   if (contains(searchKey))
      return false;

   // Create entry to add to map
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
      // TODO: Based on the design, where do we add the new entry at each index of the hash table?
      // Front? Middle? End?
      entryToAddPtr->setNext(hashTable[itemHashIndex]);
      hashTable[itemHashIndex] = entryToAddPtr;
   } // end if
   itemCount++;
   return true;
} // end add

template <typename KeyType, typename ItemType>
bool HashedMap<KeyType, ItemType>::remove(const KeyType &searchKey)
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
         // First node will be automatically deleted when the shared pointer goes out of scope
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
            }
         }
      }
   }
   if (itemFound)
      itemCount--;

   return itemFound;
} // end remove

template <typename KeyType, typename ItemType>
ItemType HashedMap<KeyType, ItemType>::getItem(const KeyType &searchKey) const
{
   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);
   auto chainPtr = hashTable[itemHashIndex];

   // Short circuit evaluation is important here
   while ((chainPtr != nullptr) && (searchKey != chainPtr->getKey()))
   {
      chainPtr = chainPtr->getNext();
   }

   if (chainPtr == nullptr)
      throw std::runtime_error("Key not found");

   return chainPtr->getItem();
} // end getItem

template <typename KeyType, typename ItemType>
bool HashedMap<KeyType, ItemType>::contains(const KeyType &searchKey) const
{
   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);

   auto chainPtr = hashTable[itemHashIndex];

   // Short circuit evaluation is important here
   while ((chainPtr != nullptr) && (searchKey != chainPtr->getKey()))
   {
      chainPtr = chainPtr->getNext();
   }

   return (chainPtr != nullptr);
} // end contains

template <typename KeyType, typename ItemType>
void HashedMap<KeyType, ItemType>::traverse(std::function<void(ItemType &)> visit) const
{
   for (int index = 0; index < hashTableSize; index++)
   {
      std::cout << "Hash index " << index << " has items: "; // for testing
      auto chainPtr = hashTable[index];
      while (chainPtr != nullptr)
      {
         ItemType currentItem = chainPtr->getItem();
         visit(currentItem);
         std::cout << currentItem << " "; // for testing
         chainPtr = chainPtr->getNext();
      }
      std::cout << std::endl; // for testing
   }
} // end traverse