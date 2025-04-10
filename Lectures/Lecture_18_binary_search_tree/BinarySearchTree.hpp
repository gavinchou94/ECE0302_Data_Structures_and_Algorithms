#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "abstract_binary_tree.hpp"

template <class ItemType>
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
   void resizeArray();
   void shiftSubtreeUp(int &index, int &targetIndex);

public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   BinarySearchTree();

   //------------------------------------------------------------
   // Public Methods Section.
   //------------------------------------------------------------
   bool isEmpty() const override;
   int getHeight() const override;
   int getNumberOfNodes() const override;
   ItemType getRootData() const override;
   void setRootData(const ItemType &newData) override;
   bool add(const ItemType &newEntry) override;
   bool remove(const ItemType &anEntry) override;
   void clear() override;
   ItemType getEntry(const ItemType &anEntry) const override;
   bool contains(const ItemType &anEntry) const override;

   //------------------------------------------------------------
   // Public Traversals Section.
   //------------------------------------------------------------
   void preorderTraverse(void visit(ItemType &)) const override;
   void inorderTraverse(void visit(ItemType &)) const override;
   void postorderTraverse(void visit(ItemType &)) const override;

   void inorderHelper(int index, void visit(ItemType &)) const;
   void preorderHelper(int index, void visit(ItemType &)) const;
   void postorderHelper(int index, void visit(ItemType &)) const;
}; // end BinarySearchTree

#include "BinarySearchTree.tpp"

#endif
