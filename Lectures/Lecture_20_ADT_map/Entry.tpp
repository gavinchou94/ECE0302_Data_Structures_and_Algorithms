#include "Entry.hpp"

template <typename KeyType, typename ItemType>
Entry<KeyType, ItemType>::Entry()
{
}

template <typename KeyType, typename ItemType>
Entry<KeyType, ItemType>::Entry(const KeyType &itemKey, const ItemType &newItem) : searchKey(itemKey), item(newItem)
{
}

template <typename KeyType, typename ItemType>
ItemType Entry<KeyType, ItemType>::getItem() const
{
   return item;
}

template <typename KeyType, typename ItemType>
KeyType Entry<KeyType, ItemType>::getKey() const
{
   return searchKey;
}

template <typename KeyType, typename ItemType>
void Entry<KeyType, ItemType>::setItem(const ItemType &newItem)
{
   item = newItem;
}

template <typename KeyType, typename ItemType>
void Entry<KeyType, ItemType>::setKey(const KeyType &itemKey)
{
   searchKey = itemKey;
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator==(const Entry<KeyType, ItemType> &rightHandItem) const
{
   return (searchKey == rightHandItem.getKey());
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator!=(const Entry<KeyType, ItemType> &rightHandItem) const
{
   return !(*this == rightHandItem);
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator>(const Entry<KeyType, ItemType> &rightHandItem) const
{
   return (searchKey > rightHandItem.getKey());
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator<(const Entry<KeyType, ItemType> &rightHandItem) const
{
   return (searchKey < rightHandItem.getKey());
}