#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

#include <stack>
#include <cstdlib>

template <typename KeyType, typename ItemType>
class BinarySearchTree
{
public:
    BinarySearchTree();

    // rule of 3 with copy swap idiom
    BinarySearchTree(const BinarySearchTree &tree_to_copy);
    BinarySearchTree &operator=(BinarySearchTree tree_to_copy);
    void swap(BinarySearchTree &tree_to_swap);
    ~BinarySearchTree();

    /** Clears the tree, deallocates all nodes */
    void destroy();

    /** Insert a new node with the specified key,item pair
     * @param key: sorting key
     * @param item: other data associated with the key
     * @return true if insert was successful, false otherwise;
     *      duplicate keys are not allowed
     * @post tree contains the new node if the insert was successful
     */
    bool insert(const KeyType &key, const ItemType &item);

    /** Check if the tree is empty
     * @return true if the tree is empty, false otherwise
     */
    bool isEmpty();

    /** Retrieve the item associated with the specified key
     * @param key: the key to search for the associated item
     * @param item: will be assigned the item (data) associated with the key
     *      if the key is found
     * @return true if the key is found, false otherwise
     */
    bool retrieve(const KeyType &key, ItemType &item);

    /** Remove the node with the specified key
     * @param key: the key of the node to remove
     * @return true if the key is found and removed, false otherwise
     * @post the node with the specified key is removed from the tree
     */
    bool remove(KeyType key);

    /** Sort the input data in arr using a tree sort algorithm
     * @param arr: array of data to sort, will be replaced with sorted data
     * @param arr_size: size of the array arr
     * @post arr contains sorted data
     */
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
     * @param curr: node to find the inorder successor
     * @param inorder: will be assigned the pointer to the inorder successor if one exists, else nullptr
     * @param inorder_parent: will be assigned the pointer to the parent of the inorder successor
     */
    void inorder_successor(Node<KeyType, ItemType> *curr,
                           Node<KeyType, ItemType> *&inorder,
                           Node<KeyType, ItemType> *&inorder_parent);

    /** Find the node with the specified key if it exists in the tree
     * @param key: key to search
     * @param curr: will be assigned the pointer to the node with the specified key if found
            (if not, the pointer to the last node that was checked during the traversal)
     * @param curr_parent: will be assigned the pointer to the parent of the found node
     *      (to facilitate insert/remove)
     * @return true if key is found, false otherwise
     */
    bool search(KeyType key, Node<KeyType, ItemType> *&curr,
                Node<KeyType, ItemType> *&curr_parent);

    // stackvar is only used for the copy constructor
    // it is a struct to hold the node to copy and the address of the node
    template <typename K, typename I>
    struct stackvar
    {
        Node<K, I> *node_to_copy;
        Node<K, I> **this_node_address;
    };
};

#include "binary_search_tree.tpp"

#endif