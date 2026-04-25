/** @file BinarySearchTree.hpp */

#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "abstract_binary_tree.hpp"
#include "BinaryNode.hpp"

template <typename ItemType>
class BinarySearchTree : public BinaryTreeInterface<ItemType>
{
private:
   std::vector<ItemType> treeArray; // Array to store tree elements
   int size;                        // Number of elements in the tree
   int capacity;                    // Maximum capacity of the array

   // Helper functions
   int getLeftChildIndex(int parentIndex) const;
   int getRightChildIndex(int parentIndex) const;
   int getParentIndex(int childIndex) const;
   int getIndexOf(const ItemType &anEntry) const;
   int getHeightHelper(int index) const;
   std::shared_ptr<BinaryNode<ItemType>> buildNodeTreeHelper(int index) const;
   void resizeArray();
   void shiftSubtreeUp(int currentIndex, int targetIndex);
   void preorderHelper(int index, std::function<void(ItemType &)> visit) const;
   void inorderHelper(int index, std::function<void(ItemType &)> visit) const;
   void postorderHelper(int index, std::function<void(ItemType &)> visit) const;

public:
   //------------------------------------------------------------
   // Constructor and Destructor Section
   //------------------------------------------------------------
   BinarySearchTree();

   //------------------------------------------------------------
   // Public Methods Section
   //------------------------------------------------------------
   bool isEmpty() const override;
   int getHeight() const override;
   int getNumberOfNodes() const override;

   ItemType getRootData() const override;
   std::shared_ptr<BinaryNode<ItemType>> getRoot() const;
   void setRootData(const ItemType &newData) override;

   bool add(const ItemType &newEntry) override;
   bool remove(const ItemType &anEntry) override;
   void clear() override;

   ItemType getEntry(const ItemType &anEntry) const override;
   bool contains(const ItemType &anEntry) const override;

   std::vector<ItemType> writeTree() const;
   void readTree(const std::vector<ItemType> &input);

   void preorderTraverse(std::function<void(ItemType &)> visit) const override;
   void inorderTraverse(std::function<void(ItemType &)> visit) const override;
   void postorderTraverse(std::function<void(ItemType &)> visit) const override;
}; // end BinarySearchTree

#include "BinarySearchTree.tpp"

#endif