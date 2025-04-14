#include "LinkedRB.hpp"
#include <fstream>

template <class ItemType>
LinkedRB<ItemType>::LinkedRB() : root(nullptr), numItems(0)
{
}

template <class ItemType>
LinkedRB<ItemType>::~LinkedRB()
{
   clear();
}

template <class ItemType>
bool LinkedRB<ItemType>::isEmpty() const
{
   return numItems == 0;
}

template <class ItemType>
int LinkedRB<ItemType>::getHeight() const
{
   return getHeightHelper(root);
}

template <class ItemType>
int LinkedRB<ItemType>::getHeightHelper(std::shared_ptr<RedBlackNode<ItemType>> node) const
{
   if (node == nullptr)
      return 0;
   else
      return 1 + std::max(getHeightHelper(node->getLeftChildPtr()), getHeightHelper(node->getRightChildPtr()));
}

template <class ItemType>
void LinkedRB<ItemType>::rotateLeft(std::shared_ptr<RedBlackNode<ItemType>> &node)
{
   // rotate left, node becomes the left child of its right child
   // and the right child becomes the new root of the subtree
   //          node
   //         /    \
   //        x      RC
   //               / \
   //              y   z
   // becomes
   //          RC
   //         /  \
   //        node  z
   //       / \
   //      x   y

   // record the parent of the node first
   std::shared_ptr<RedBlackNode<ItemType>> parent = findParent(root, node);
   if (parent == nullptr)
   {
      // node is root, need to rotate the root to the left
      root = node->getRightChildPtr();
      auto newchild = node->getRightChildPtr()->getLeftChildPtr();
      root->setLeftChildPtr(node);
      node->setRightChildPtr(newchild);
      node = root;
      return;
   }

   // if the node is the left child of its parent, otherwise it is the right child
   bool isleftChild = (parent->getLeftChildPtr() == node);

   // rotate left
   std::shared_ptr<RedBlackNode<ItemType>> rightChild = node->getRightChildPtr();
   node->setRightChildPtr(rightChild->getLeftChildPtr());
   rightChild->setLeftChildPtr(node);
   node = rightChild;

   // update the parent pointer
   if (parent != nullptr)
   {
      if (isleftChild)
         parent->setLeftChildPtr(node);
      else
         parent->setRightChildPtr(node);
   }
   else
   {
      root = node;
   }
}

template <class ItemType>
void LinkedRB<ItemType>::rotateRight(std::shared_ptr<RedBlackNode<ItemType>> &node)
{
   // rotate right, node becomes the right child of its left child
   // and the left child becomes the new root of the subtree
   //          node
   //         /    \
   //        LC     z
   //       / \
   //      x   y
   // becomes
   //          LC
   //         /  \
   //        x    node
   //             / \
   //            y   z

   // record the parent of the node first
   std::shared_ptr<RedBlackNode<ItemType>> parent = findParent(root, node);
   if (parent == nullptr)
   {
      // node is root, need to rotate the root to the right
      root = node->getLeftChildPtr();
      auto newchild = node->getLeftChildPtr()->getRightChildPtr();
      root->setRightChildPtr(node);
      node->setLeftChildPtr(newchild);
      node = root;
      return;
   }

   // if the node is the left child of its parent, otherwise it is the right child
   bool isleftChild = (parent->getLeftChildPtr() == node);

   std::shared_ptr<RedBlackNode<ItemType>> leftChild = node->getLeftChildPtr();
   node->setLeftChildPtr(leftChild->getRightChildPtr());
   leftChild->setRightChildPtr(node);
   node = leftChild;

   // update the parent pointer
   if (parent != nullptr)
   {
      if (isleftChild)
         parent->setLeftChildPtr(node);
      else
         parent->setRightChildPtr(node);
   }
   else
   {
      root = node;
   }
}

template <class ItemType>
std::shared_ptr<RedBlackNode<ItemType>> LinkedRB<ItemType>::findParent(const std::shared_ptr<RedBlackNode<ItemType>> &root,
                                                                       const std::shared_ptr<RedBlackNode<ItemType>> &node)
{
   if (root == nullptr || root == node)
      return nullptr; // Root has no parent, or node is root

   if (root->getLeftChildPtr() == node || root->getRightChildPtr() == node)
   {
      return root;
   }

   auto leftParent = findParent(root->getLeftChildPtr(), node);
   if (leftParent)
      return leftParent;

   return findParent(root->getRightChildPtr(), node);
}

template <class ItemType>
void LinkedRB<ItemType>::fixViolations(std::shared_ptr<RedBlackNode<ItemType>> &node)
{
   while (node != nullptr && node != root && node->getColor() == RED)
   {
      // Get the parent and grandparent of the node
      auto parent = findParent(root, node);
      auto grandparent = findParent(root, parent);

      if (parent == nullptr)
         break; // Parent is null, no violations to fix

      // Case 1: Parent (red) is the left child of the grandparent
      if (grandparent != nullptr && grandparent->getLeftChildPtr() == parent && parent->getColor() == RED)
      {
         auto uncle = grandparent->getRightChildPtr();

         // Case 1a: Uncle is red (color flip)
         if (uncle != nullptr && uncle->getColor() == RED)
         {
            parent->setColor(BLACK);
            uncle->setColor(BLACK);
            grandparent->setColor(RED);
            node = grandparent; // Move up the tree
         }
         else
         {
            // Case 1b: Uncle is black or null
            if (parent->getRightChildPtr() == node)
            {
               rotateLeft(parent);
               node = parent;
               parent = findParent(root, node);
            }
            rotateRight(grandparent);
            grandparent->setColor(BLACK);
            grandparent->getRightChildPtr()->setColor(RED);
            break; // Fix is complete
         }
      }
      // Case 2: Parent (red) is the right child of the grandparent
      else if (grandparent != nullptr && grandparent->getRightChildPtr() == parent && parent->getColor() == RED)
      {
         auto uncle = grandparent->getLeftChildPtr();

         // Case 2a: Uncle is red (color flip)
         if (uncle != nullptr && uncle->getColor() == RED)
         {
            parent->setColor(BLACK);
            uncle->setColor(BLACK);
            grandparent->setColor(RED);
            node = grandparent; // Move up the tree
         }
         else // Case 2b: Uncle is black or null
         {
            if (parent->getLeftChildPtr() == node) // this node is the left child
            {
               rotateRight(parent);
               node = parent; // the base after rotation
               parent = findParent(root, node);
            }
            rotateLeft(grandparent);
            grandparent->setColor(BLACK);
            grandparent->getLeftChildPtr()->setColor(RED);
            break; // Fix is complete
         }
      }
      else
      {
         break; // No violations to fix
      }
   }

   // Ensure the root is always black
   root->setColor(BLACK);

   // Verify black-height consistency
   // getBlackHeight(root); // Throws an error if black-height is violated
}

template <class ItemType>
void LinkedRB<ItemType>::add(const ItemType &anItem)
{
   if (contains(anItem))
      throw std::runtime_error("Item already exists");

   // Create a new node
   std::shared_ptr<RedBlackNode<ItemType>> newNode = std::make_shared<RedBlackNode<ItemType>>(anItem);
   newNode->setColor(RED); // New nodes are always red initially

   // Insert the new node into the tree
   if (root == nullptr)
   {
      root = newNode;
      root->setColor(BLACK); // Set root to black
   }
   else
   {
      // Use binary search tree insertion
      std::shared_ptr<RedBlackNode<ItemType>> current = root;
      std::shared_ptr<RedBlackNode<ItemType>> parent = nullptr;

      while (current != nullptr)
      {
         parent = current;
         if (anItem < current->getItem())
            current = current->getLeftChildPtr();
         else
            current = current->getRightChildPtr();
      }

      // Attach the new node to the parent
      if (anItem < parent->getItem())
         parent->setLeftChildPtr(newNode);
      else
         parent->setRightChildPtr(newNode);

      // Fix violations caused by the insertion
      fixViolations(newNode);
   }

   // Ensure the root is always black
   root->setColor(BLACK);

   // Increment the number of items
   numItems++;
}

template <class ItemType>
void LinkedRB<ItemType>::remove(const ItemType &anItem)
{
   if (isEmpty())
      throw std::runtime_error("Tree is empty");
   if (!contains(anItem))
      throw std::runtime_error("Item not found");

   // remove method too complex to implement here
}

template <class ItemType>
void LinkedRB<ItemType>::clear()
{
   root = nullptr;
   numItems = 0;
}

template <class ItemType>
std::shared_ptr<RedBlackNode<ItemType>> LinkedRB<ItemType>::getRoot() const
{
   return root;
}

template <class ItemType>
int LinkedRB<ItemType>::getNumItems() const
{
   return numItems;
}

template <class ItemType>
bool LinkedRB<ItemType>::contains(const ItemType &anItem) const
{
   std::shared_ptr<RedBlackNode<ItemType>> current = root;

   while (current != nullptr)
   {
      if (anItem == current->getItem())
         return true;
      else if (anItem < current->getItem())
         current = current->getLeftChildPtr();
      else
         current = current->getRightChildPtr();
   }

   return false;
}

template <class ItemType>
int LinkedRB<ItemType>::getBlackDistance(const ItemType &anItem) const
{
   if (isEmpty())
      throw std::runtime_error("Tree is empty");
   if (!contains(anItem))
      throw std::runtime_error("Item not found");

   std::shared_ptr<RedBlackNode<ItemType>> current = root;
   int blackDistance = 0;

   while (current != nullptr)
   {
      // Count this node if it's black
      if (current->getColor() == BLACK)
         blackDistance++;

      // If we found the item, return the black distance
      if (anItem == current->getItem())
         return blackDistance;

      // Navigate to the appropriate child
      if (anItem < current->getItem())
         current = current->getLeftChildPtr();
      else
         current = current->getRightChildPtr();
   }

   return -1; // Should never reach here due to contains check
}

template <class ItemType>
int LinkedRB<ItemType>::getLevel(const ItemType &anItem) const
{
   if (isEmpty())
      throw std::runtime_error("Tree is empty");
   if (!contains(anItem))
      throw std::runtime_error("Item not found");

   std::shared_ptr<RedBlackNode<ItemType>> current = root;
   int level = 0;

   while (current != nullptr)
   {
      // If we found the item, return the level
      if (anItem == current->getItem())
         return level;

      // Navigate to the appropriate child and increment level
      if (anItem < current->getItem())
      {
         current = current->getLeftChildPtr();
         level++;
      }
      else
      {
         current = current->getRightChildPtr();
         level++;
      }
   }

   return -1; // Should never reach here due to contains check
}

template <class ItemType>
void LinkedRB<ItemType>::plotTree(const std::string &filename) const
{
   std::ofstream file(filename);
   file << "graph G {\n";
   file << "    layout=neato;\n";
   file << "    node [shape=circle, style=filled, fontcolor=white, fixedsize=true, width=0.5];\n";
   file << "    edge [dir=none];\n"; // undirected look (optional for trees)

   // Helper function: recursively write nodes with pos="x,y!"
   std::function<void(std::shared_ptr<RedBlackNode<ItemType>>, double, double, double)> writeNode;
   writeNode = [&](std::shared_ptr<RedBlackNode<ItemType>> node, double x, double y, double offset)
   {
      if (!node)
         return;

      std::string color = (node->getColor() == RED) ? "red" : "black";

      // Write node with position
      file << "    \"" << node->getItem() << "\""
           << " [fillcolor=" << color << ", pos=\"" << x << "," << y << "!\"];\n";

      // Write left child and edge
      if (node->getLeftChildPtr())
      {
         file << "    \"" << node->getItem() << "\" -- \"" << node->getLeftChildPtr()->getItem() << "\";\n";
         writeNode(node->getLeftChildPtr(), x - offset, y - 1, offset / 2.0);
      }

      // Write right child and edge
      if (node->getRightChildPtr())
      {
         file << "    \"" << node->getItem() << "\" -- \"" << node->getRightChildPtr()->getItem() << "\";\n";
         writeNode(node->getRightChildPtr(), x + offset, y - 1, offset / 2.0);
      }
   };

   // Start from the root with an initial spacing offset
   writeNode(root, 0, 0, 6); // X, Y, initial spacing between child nodes

   file << "}\n";
   file.close();
}
// Paste the generated dot file into Graphviz to visualize the tree
// Online Graphviz: https://dreampuf.github.io/GraphvizOnline/