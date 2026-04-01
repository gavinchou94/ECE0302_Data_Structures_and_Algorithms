#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

template <typename KeyType, typename ItemType>
class BinarySearchTree
{
public:
    BinarySearchTree();                                // default constructor
    BinarySearchTree(const BinarySearchTree &rhs);     // deep copy constructor
    BinarySearchTree &operator=(BinarySearchTree rhs); // copy assignment operator using copy-and-swap idiom
    ~BinarySearchTree();                               // destructor

    /** Check if the tree is empty
     * @return true if the tree is empty, false otherwise */
    bool isEmpty();

    /** Retrieve the item associated with the specified key
     * @param key: the key to search for the associated item
     * @param item: will be assigned the item (data) associated with the key if the key is found
     * @return true if the key is found, false otherwise */
    bool retrieve(const KeyType &key, ItemType &item);

    /** Clears the tree, deallocates all nodes */
    void destroy();

    /** Insert a new node with the specified key,item pair
     * @param key: sorting key
     * @param item: other data associated with the key
     * @return true if insert was successful, false otherwise (duplicate keys are not allowed)
     * @post tree contains the new node if the insert was successful */
    bool insert(const KeyType &key, const ItemType &item);

    /** Remove the node with the specified key
     * @param key: the key of the node to remove
     * @return true if the key is found and removed, false otherwise
     * @post the node with the specified key is removed from the tree */
    bool remove(KeyType key);

    /** Sort the input data in arr using a tree sort algorithm
     * @param arr: array of data to sort, will be replaced with sorted data
     * @param arr_size: size of the array arr
     * @throw std::invalid_argument if duplicate keys are found during insertion into the BST
     * @post arr contains sorted data
     * @post tree contains the sorted elements as nodes
     * @note destroys any existing tree contents before sorting;
     *       if a duplicate is found during insertion, the partially built tree is destroyed before throwing */
    void treeSort(KeyType arr[], int arr_size);

private:
    // define tree node struct so we can use it in the class
    template <typename K, typename I>
    struct Node
    {
        I data;
        K key;
        Node<K, I> *left;
        Node<K, I> *right;
    };
    // root node, the only private member variable in the class
    Node<KeyType, ItemType> *root;

    /** Find the inorder successor of the input node curr
     * @param root: root of the tree, needed to find the successor when curr has no right subtree
     * @param curr: node to find the inorder successor
     * @param inorder: will be assigned the pointer to the inorder successor if one exists, else nullptr
                       (pass by reference to allow the caller to modify it)
     * @param inorder_parent: will be assigned the pointer to the parent of the inorder successor
                              only when curr has a right subtree (Case 1); not set when the successor
                              is found by walking ancestors (Case 2)
                              (pass by reference to allow the caller to modify it)
     * @post inorder points to the inorder successor, inorder_parent points to its parent (Case 1 only) */
    void inorder_successor(Node<KeyType, ItemType> *root,
                           Node<KeyType, ItemType> *curr,
                           Node<KeyType, ItemType> *&inorder,
                           Node<KeyType, ItemType> *&inorder_parent);

    /** Find the node with the specified key if it exists in the tree
     * @param key: key to search
     * @param curr: will be assigned the pointer to the node with the specified key if found;
                    set to nullptr if not found
                    (pass by reference to allow the caller to modify it)
     * @param curr_parent: will be assigned the pointer to the parent of the found node if found;
                          set to the last node visited during the traversal if not found
                          (i.e., the leaf node where a new child would be attached)
                          (pass by reference to allow the caller to modify it)
     * @return true if key is found, false otherwise */
    bool search(KeyType key, Node<KeyType, ItemType> *&curr, Node<KeyType, ItemType> *&curr_parent);

    /** Create a deep copy of the subtree rooted at source
     * @param source: root of the subtree to copy
     * @return pointer to the root of the copied subtree */
    Node<KeyType, ItemType> *copyTree(Node<KeyType, ItemType> *source);
};

#include "binary_search_tree.tpp"

#endif