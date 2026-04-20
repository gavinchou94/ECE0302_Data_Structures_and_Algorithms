/** A binary search tree implementation of the ADT Map
    that organizes its data items in sorted search-key order.
    Search keys in the map are unique.
 @file TreeMap.hpp */

#ifndef TREE_MAP_
#define TREE_MAP_

#include "abstract_map.hpp"
#include "Entry.hpp"
#include <functional>
#include <set>

template <typename KeyType, typename ItemType>
class TreeMap : public AbstractMap<KeyType, ItemType>
{
private:
  // Could have used BinarySearchTree.hpp from lecture 18,
  // but std::set can help better organize dependency libraries and focus on the ADT map implementation
  // Functionality of std::set is similar to our BST implementation
  using BST = std::set<Entry<KeyType, ItemType>>;

  BST entryTree;

public:
  TreeMap();
  TreeMap(const TreeMap<KeyType, ItemType> &rhs);
  TreeMap<KeyType, ItemType> &operator=(TreeMap<KeyType, ItemType> rhs);
  virtual ~TreeMap();

  bool isEmpty() const;
  int getNumberOfItems() const;
  bool add(const KeyType &searchKey, const ItemType &someItem);
  bool remove(const KeyType &searchKey);
  void clear();
  ItemType getItem(const KeyType &searchKey) const;
  bool contains(const KeyType &searchKey) const;

  /** Traverses the items in this Map in sorted search-key order
      and calls a given client function once for each item. */
  void traverse(std::function<void(ItemType &)> visit) const;
};

#include "TreeMap.tpp"
#endif

/*
A visualization of the tree map (itemCount = 6):

                (5.0, "five")
               /                \
      (3.0, "three")           (8.0, "eight")
      /           \                \
(2.0, "two")   (4.0, "four")     (9.0, "nine")
      \
     (2.5, "two and a half")

*/

// A sorted array-based implementation of the ADT map can retrieve items quickly,
// but adding and removing items is slow because elements must be shifted.
// A sorted linked-list-based implementation of the ADT map can add and remove items more easily,
// but retrieving items is slow because the chain must still be traversed (even the items are sorted).

// TODO: Why can a BST-based implementation of the ADT map be a good choice for balancing the efficiency of all operations?
// What other disadvantages of array-based and linked-list-based implementations does a BST-based implementation avoid?
// What factors can affect the performance of a BST-based implementation of the ADT map?