/** A binary search tree implementation of the ADT Map
    that organizes its data items in sorted search-key order.
    Search keys in the map are unique.
 @file TreeMap.tpp */

#include "TreeMap.hpp"
#include <stdexcept>

template <typename KeyType, typename ItemType>
TreeMap<KeyType, ItemType>::TreeMap()
{
}

template <typename KeyType, typename ItemType>
TreeMap<KeyType, ItemType>::TreeMap(const TreeMap<KeyType, ItemType> &rhs) : entryTree(rhs.entryTree)
{
}

template <typename KeyType, typename ItemType>
TreeMap<KeyType, ItemType> &TreeMap<KeyType, ItemType>::operator=(TreeMap<KeyType, ItemType> rhs)
{
  std::swap(entryTree, rhs.entryTree);
  return *this;
}

template <typename KeyType, typename ItemType>
TreeMap<KeyType, ItemType>::~TreeMap()
{
}
// Container classes have their own copy constructor and destructor, so we can rely on them to manage memory for us
// If we use our own BST implementation, we would also just delegate to the copy constructor and destructor of the BST class.

template <typename KeyType, typename ItemType>
bool TreeMap<KeyType, ItemType>::isEmpty() const
{
  return entryTree.empty();
}

template <typename KeyType, typename ItemType>
int TreeMap<KeyType, ItemType>::getNumberOfItems() const
{
  return entryTree.size();
}

template <typename KeyType, typename ItemType>
bool TreeMap<KeyType, ItemType>::add(const KeyType &searchKey, const ItemType &someItem)
{
  if (contains(searchKey))
    return false;

  entryTree.insert(Entry<KeyType, ItemType>(searchKey, someItem));
  return true;
}

template <typename KeyType, typename ItemType>
bool TreeMap<KeyType, ItemType>::remove(const KeyType &searchKey)
{
  if (!contains(searchKey))
    return false;

  entryTree.erase(Entry<KeyType, ItemType>(searchKey, ItemType()));
  return true;
}

template <typename KeyType, typename ItemType>
void TreeMap<KeyType, ItemType>::clear()
{
  entryTree.clear();
}

template <typename KeyType, typename ItemType>
ItemType TreeMap<KeyType, ItemType>::getItem(const KeyType &searchKey) const
{
  if (!contains(searchKey))
    throw std::invalid_argument("getItem: item not found");

  return entryTree.find(Entry<KeyType, ItemType>(searchKey, ItemType()))->getItem();
}

template <typename KeyType, typename ItemType>
bool TreeMap<KeyType, ItemType>::contains(const KeyType &searchKey) const
{
  return entryTree.find(Entry<KeyType, ItemType>(searchKey, ItemType())) != entryTree.end();
}

template <typename KeyType, typename ItemType>
void TreeMap<KeyType, ItemType>::traverse(std::function<void(ItemType &)> visit) const
{
  for (const auto &entry : entryTree)
  {
    ItemType currentItem = entry.getItem();
    visit(currentItem);
  }
}
// If we use std::set, we can just iterate through the set which is already sorted by the search key.
// If we use our own BST implementation, we would need to call the inorder BST traversal to visit the items in sorted order.