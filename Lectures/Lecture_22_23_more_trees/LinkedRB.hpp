#ifndef LINKEDRB_HPP
#define LINKEDRB_HPP

#include <stdexcept>
#include <memory>
#include "RedBlackNode.hpp"

template <class ItemType>
class LinkedRB
{
private:
  std::shared_ptr<RedBlackNode<ItemType>> root;
  int numItems;
  int getHeightHelper(std::shared_ptr<RedBlackNode<ItemType>> node) const;
  void rotateLeft(std::shared_ptr<RedBlackNode<ItemType>> &node);
  void rotateRight(std::shared_ptr<RedBlackNode<ItemType>> &node);
  void fixViolations(std::shared_ptr<RedBlackNode<ItemType>> &node);
  std::shared_ptr<RedBlackNode<ItemType>> findParent(const std::shared_ptr<RedBlackNode<ItemType>> &root,
                                                     const std::shared_ptr<RedBlackNode<ItemType>> &node);

public:
  LinkedRB();
  ~LinkedRB();
  bool isEmpty() const;
  int getHeight() const;
  std::shared_ptr<RedBlackNode<ItemType>> getRoot() const;
  void add(const ItemType &anItem);
  void remove(const ItemType &anItem);
  void clear();
  int getNumItems() const;
  bool contains(const ItemType &anItem) const;
  int getBlackDistance(const ItemType &anItem) const;
  int getLevel(const ItemType &anItem) const;
  void plotTree(const std::string &filename) const;
};
#include "LinkedRB.tpp"
#endif
