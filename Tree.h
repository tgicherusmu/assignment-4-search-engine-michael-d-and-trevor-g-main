#ifndef AVL_TREE_H
#define AVL_TREE_H

#define DEBUG

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "IndexEntry.h"  //TA Adam E: I added this for you

using namespace std;

// AvlTree class
// This implementation is based on the unbalanced binary search tree and adds hight information
// to the nodes and a balance function to perform the needed rotations.

template <typename Comparable>
class AvlTree {
   private:
    struct AvlNode {
        Comparable key;
        AvlNode *left;
        AvlNode *right;
        int height;  // AVL tree: keeping track of the height is the differnce to a unbalanced binary search tree
        // TA Adam E: What if each AVLNode had a destructor that deleted the left and right AVLNodes it pointed to? WOuld it delete the whole tree?
        AvlNode(const Comparable &theKey, AvlNode *lt, AvlNode *rt, int h)
            : key{theKey}, left{lt}, right{rt}, height{h} {}
    };

    ~AvlNode() {
        delete left;
        delete right;
    }

    AvlNode *root;
    void print(ostream &out, AvlNode *n) const {
        if (n != nullptr) {
            // out << n->element;
            out << n->key;
            print(out, n->left);
            print(out, n->right);
        }
    }

   public:
    /**
     * @brief Default constructor
     */
    AvlTree() : root{nullptr} {
    }

    /**
     * @brief Rule-of-3 Part 1: Copy constructor uses internal function clone().
     *
     */
    AvlTree(const AvlTree &rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    /**
     * @brief Rule-of-3 Part 2: Destroy the Binary Search Tree object using the internal
     *   function makeEmpty().
     */
    ~AvlTree() {
        makeEmpty();
    }

    /**
     * @brief Rule-of-3 Part 1: Copy constructor uses internal function clone().
     */
    AvlTree &operator=(const AvlTree &rhs) {
        makeEmpty();
        root = clone(rhs.root);
        return *this;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree structure.
     */
    void prettyPrintTree() const {
        prettyPrintTree("", root, false);
    }

    /**
     * Make the tree empty.
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x) {
        insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }

    // TA Adam E: this function will only ever work when Comparable is of type string, otherwise GCC will throw a compiler error, the fucntion prototype should be `std::vector<Comparable> getSet() const`
    std::vector<Comparable> getSet() const {
        std::vector<Comparable> set;

        // traverse the tree and add each element to the vector
        traverse(root, set);

        return set;
    }

    //TA Adam E: I added this function for you to finish
    std::vector<IndexEntry> getEntries() const {
        std::vector<IndexEntry> entries;

        // traverse all nodes recursively
        traverseEntries(root, entries);

        return entries;
    }

    void traverseEntries(AvlNode *node, std::vector<IndexEntry> &entries) const {
        if (node == nullptr) {
            return;
        }

        // create and fill a new IndexEntry object
        IndexEntry entry(node->key, node->value);

        // add the new IndexEntry object to entries
        entries.push_back(entry);

        // traverse left and right nodes recursively
        traverseEntries(node->left, entries);
        traverseEntries(node->right, entries);
    }

    inline void clearElements() {
        clear(root);
        root = nullptr;
    }

    // TA Adam E: this function will only ever work when Comparable is of type string, otherwise GCC will throw a compiler error, the fucntion prototype should be `&IndexEntry getEntry(Comparable &word) const`
    // TA Adam E: I changed this function to return a reference to node->key, instead of a pointer, this is much better practice, and it solved your issue in IndexHandler.cpp
    IndexEntry &getEntry(const std::string &word) const {
        AvlNode *node = find(root, word);

        if (node == nullptr) {
            throw invalid_argument("could not find");
        }

    template <typename KeyType, typename ValueType>
    const ValueType& AVLTree<KeyType, ValueType>::find(const KeyType& key) const
    {
        AVLNode* node = findNode(key);
        if (node == nullptr)
        {
            throw std::invalid_argument("Key not found.");
        }
        else
        {
            return node->key;
        }
    }

    void makeEmpty(AvlNode *&t) {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    void emptyTree(AvlNode *n) {
        if (n != nullptr) {
            emptyTree(n->left);
            emptyTree(n->right);
            delete n;
        }
    }

    // TA Adam E: I commented this function out
    //  vector<T>& getSet(){return allElements;}

    // void clearElements(){ allElements.clear();}

    // TA Adam E: I changed T to be Comparable
    Comparable *getElement(const Comparable &x, AvlNode *&curr) {
        if (curr == nullptr)
            return nullptr;  // doesn't exist
        if (x < curr->element)
            return getElement(x, curr->left);  // descend left child
        else if (curr->element < x)
            return getElement(x, curr->right);  // descend right child
        else if (curr->element == x)
            return &curr->element;  // exists
        else
            return nullptr;
    }

    /*
         void output(AvlNode* n){
            if(n!=nullptr){
                output(n->left);
                allElements.push_back(n->element);
                output(n->right);
            }
        }
        */

    void output() {
        output(root);
    }

    void print(ostream &out) {
        print(out, root);
    }

    // TA Adam E: I commented this function out
    //  int getSize(){ return size;}

   private:
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, AvlNode *&t) {
        if (t == nullptr) {
            t = new AvlNode{x, nullptr, nullptr, 0};
            return;  // a single node is always balanced
        }

        if (x < t->key)
            insert(x, t->left);
        else if (t->key < x)
            insert(x, t->right);
        else {
        }  // Duplicate; do nothing

        // This will call balance on the way back up the tree. It will only balance
        // once at node the where the tree got imbalanced (called node alpha in the textbook)
        // and update the height all the way back up the tree.
        balance(t);
    }
    void output(AvlNode *n) {
        if (n == nullptr) {
            return;
        }

        output(n->left);
        std::cout << n->key << std::endl;
        output(n->right);
    }
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable &x, AvlNode *&t) {
        throw std::runtime_error("Not implemented yet!");
        // same as in a binary search tree

        // don't forget to balance the AVL tree!
        balance(t);
    }

    /**
     * Internal method to make subtree empty.
     */

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const {
        if (t == nullptr)
            return nullptr;

        return new AvlNode{t->key, clone(t->left), clone(t->right), t->height};
    }

    /**
     * Pretty print the tree structure
     * Uses preorder traversal with R and L swapped (NRL)
     *
     * Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
     */
    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const {
        if (node == nullptr)
            return;

        std::cout << prefix;
        // Note: this uses unicode characters for the tree structure. They might not print correctly on
        // all systems (Windows!?!) and all types of output devices.
        std::cout << (isRight ? "├──" : "└──");
        // print the value of the node
        std::cout << node->key << std::endl;

        // enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
    }

    // Balancing: AVL Rotations

    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const {
        return t == nullptr ? -1 : t->height;
    }

    static const int ALLOWED_IMBALANCE = 1;  // 1 is the default; more will make balancing cheaper
                                             // but the search less efficient.

    // Assume t is balanced or within one of being balanced since we check this after each manipulation
    // t represents alpha in the textbook
    void balance(AvlNode *&t) {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)  // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);  // case 1 (outside)
            else
                doubleWithLeftChild(t);                                     // case 2 (inside)
        } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)  // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);  // case 4 (outside)
            else
                doubleWithRightChild(t);  // case 3 (inside)
        }

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const {
        return lhs > rhs ? lhs : rhs;
    }

    AvlNode *find(AvlNode *node, const std::string &word) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (word < node->entry.word) {
            return find(node->left, word);
        } else if (word > node->entry.word) {
            return find(node->right, word);
        } else {
            return node;
        }
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2) {
#ifdef DEBUG
        cout << "need to rotateWithLeftChild for node " << k2->key << endl;
        cout << "Before:" << endl;
        prettyPrintTree();
#endif

        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
#ifdef DEBUG
        cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1) {
#ifdef DEBUG
        cout << "need to rotateWithRightChild for node " << k1->key << endl;
        cout << "Before:" << endl;
        prettyPrintTree();

#endif

        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
#ifdef DEBUG
        cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3) {
#ifdef DEBUG
        cout << "doubleWithLeftChild" << endl;
#endif
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1) {
#ifdef DEBUG
        cout << "doubleWithRightChild" << endl;
#endif
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};

#endif
