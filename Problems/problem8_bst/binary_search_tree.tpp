#include "binary_search_tree.hpp"
#include <algorithm>
#include <stack>
#include <stdexcept>

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = nullptr;
} // end default constructor

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(const BinarySearchTree &rhs)
{
    root = copyTree(rhs.root);
} // end copy constructor

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType> &BinarySearchTree<KeyType, ItemType>::operator=(BinarySearchTree rhs)
{
    std::swap(root, rhs.root);
    return *this;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy(); // delegate to destroy function to deallocate
} // end destructor

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == nullptr);
} // end isEmpty

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(const KeyType &key, ItemType &item)
{
    Node<KeyType, ItemType> *curr = nullptr;
    Node<KeyType, ItemType> *curr_parent = nullptr;
    bool found = search(key, curr, curr_parent);
    item = found ? curr->data : ItemType(); // if key is found, curr points to the node with the key
    return found;
} // end retrieve

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    // TODO: Iteratively delete all nodes in the tree using a stack.
    // Hint: Use a stack to traverse the tree. For each node, push its children onto the stack, delete the node,
    // and repeat until the stack is empty. Set root to nullptr at the end to avoid dangling pointers.
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(const KeyType &key, const ItemType &item)
{
    // TODO: Insert a new node into the BST if the key does not already exist.
    // Hint: If the tree is empty, create it as root node.
    // Otherwise, use the search function to check for duplicates and find the correct parent
    // If the key is unique, allocate a new node, and link it as the left or right child of the parent.
    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    // TODO: Remove a node with the given key from the BST, handling all cases.
    // Hint: If the tree is empty, return false.
    // Use the search function to find the node and its parent. If not found, return false.
    // For deletion, handle these cases:  (1) node is a leaf, (2) node has only a right child,
    // (3) node has only a left child, (4) node has two children (replace with inorder successor).
    // Update parent pointers and free memory as needed. Return true if deleted, false otherwise.
    return false;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(KeyType arr[], int arr_size)
{
    // TODO: Implement tree sort using the BST.
    // Hint: Insert all array elements into the BST, throwing an exception if a duplicate is found.
    // Then perform an in-order traversal to collect sorted values and overwrite the input array with them.
    // In-order traversal can be conducted starting from the leftmost node and repeatedly finding the inorder successor.
    // Alternatively, you can find the leftmost node, remove it from the tree, and repeatly find the new leftmost node.
}

// ==================== Private Helper Functions ====================
template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder_successor(Node<KeyType, ItemType> *root,
                                                            Node<KeyType, ItemType> *curr,
                                                            Node<KeyType, ItemType> *&inorder,
                                                            Node<KeyType, ItemType> *&inorder_parent)
{
    if (!curr)
    {
        inorder = nullptr;
        inorder_parent = nullptr;
        return;
    }

    // Case 1: Node has right subtree
    // The inorder successor is the leftmost node in the right subtree
    // inorder_parent is tracked in this case
    if (curr->right != nullptr)
    {
        inorder_parent = curr;
        inorder = curr->right;                                 // start with right child
        while (inorder != nullptr && inorder->left != nullptr) // go left until you can't
        {
            inorder_parent = inorder;
            inorder = inorder->left;
        }
        return;
    }

    // Case 2: No right subtree
    // Find the lowest ancestor where curr lies in its left subtree
    // Note: inorder_parent is NOT set in this case
    inorder = nullptr;
    inorder_parent = nullptr;
    Node<KeyType, ItemType> *ancestor = root;
    while (ancestor && ancestor != curr)
    {
        if (curr->key < ancestor->key)
        {
            inorder = ancestor; // potential successor, keep going left to find a closer one
            ancestor = ancestor->left;
        }
        else
        {
            ancestor = ancestor->right;
        }
    }
    // inorder now points to the inorder successor (or nullptr if curr is already the largest node)
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::search(KeyType key,
                                                 Node<KeyType, ItemType> *&curr,
                                                 Node<KeyType, ItemType> *&curr_parent)
{
    curr = root;
    curr_parent = nullptr;
    while (curr != nullptr)
    {
        if (key == curr->key) // key is found
            return true;
        curr_parent = curr;
        if (key < curr->key)
            curr = curr->left; // search left subtree
        else
            curr = curr->right; // search right subtree
    }
    return false;
}

template <typename KeyType, typename ItemType>
typename BinarySearchTree<KeyType, ItemType>::template Node<KeyType, ItemType> *
BinarySearchTree<KeyType, ItemType>::copyTree(Node<KeyType, ItemType> *source)
{
    if (!source)
        return nullptr;
    Node<KeyType, ItemType> *newNode = new Node<KeyType, ItemType>;
    newNode->key = source->key;
    newNode->data = source->data;
    newNode->left = copyTree(source->left);
    newNode->right = copyTree(source->right);
    return newNode;
}