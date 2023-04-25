
#ifndef TREE_H
#define TREE_H
#define DEBUG
#include "IndexEntry.h"


#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


// AvlTree class
// This implementation is based on the unbalanced binary search tree and adds hight information 
// to the nodes and a balance function to perform the needed rotations.

template <typename Comparable>
class AvlTree
{
private:
    struct AvlNode
    {
        Comparable key;
        AvlNode *left;
        AvlNode *right;
        int height;      // AVL tree: keeping track of the height is the differnce to a unbalanced binary search tree

        AvlNode(const Comparable &theKey, AvlNode *lt, AvlNode *rt, int h)

            : key{theKey}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;

public:
    /**
     * @brief Default constructor
     */
    AvlTree() : root{nullptr}
    {
    }
    /*
     * @brief Rule-of-3 Part 1: Copy constructor uses internal function clone()
     *
     */
    AvlTree(const AvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }
    /**
     * @brief Rule-of-3 Part 2: Destroy the Binary Search Tree object using the internal
     *   function makeEmpty()
     */
    ~AvlTree()
    {
        makeEmpty();
    }
    /**
     * @brief Rule-of-3 Part 1: Copy constructor uses internal function clone().
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
        return *this;
    }
    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }
    /**
     * Print the tree structure.
     */
    void prettyPrintTree() const
    {
        prettyPrintTree("", root, false);
    }
    /**
     * Make the tree empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x)
    {
        insert(x, root);
    }
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x)
    {
        remove(x, root);
    }
    void clearElements()
    {
        makeEmpty(root);
    }

    //Comparable getEntryHelper(Comparable entry, AvlNode* node) {
      //  if (entry == node->key) {
        //    return node->key;
        //}

    //}

 //put comparable in indexEntry
 //if value that you are looking thenn go left, if higher then go right
 //try catch block
 //boolean if its there or not

    Comparable getEntryHelper(Comparable entry, AvlNode* node) const{
        try {
            if (entry == node->key) {
                return node->key;
            }
            if (entry > node->key){
                if (node->right == nullptr) {
                    throw std::runtime_error("DSAVLTree find(): Search Element not in tree");
                }
                else{
                    return getEntryHelper(entry, node->right);
                }
        }
            if (entry < node->key){
                if (node->left == nullptr) {
                    throw std::runtime_error("DSAVLTree find(): Search Element not in tree");
                }
                else{
                    return getEntryHelper(entry, node->left);
                }
            }
           // else if (entry < node->key) {
             //   return getEntryHelper(entry, node->left);
            //}
            //else {
              //  return getEntryHelper(entry, node->right);
            //}
        }
        catch (exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

    Comparable getEntry(string word) const
    {
        Comparable C;
        if (isEmpty())
        {
            return C;
        }
        else
        {
            IndexEntry t (word, "string");
            return getEntryHelper(t, root);
        }
    };

    vector<Comparable> getEntries() const
     {
         vector<Comparable> entries;
         if (isEmpty()) {
             return entries;
         }
         else
         {
             getEntriesHelper(root, entries);
             return entries;
         }
     };

    //look at print for inspiration
    void getEntriesHelper(AvlNode* node, vector<Comparable>& entries) const {
        if (node == nullptr) {
            return;
        }
        //for (const auto& key : node->items) {
            entries.push_back(node->key);
        //}
        if (node->left != nullptr) {
            getEntriesHelper(node->left, entries);
        }
        if (node->right != nullptr) {
            getEntriesHelper(node->right, entries);
        }
    }


private:
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, AvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{x, nullptr, nullptr, 0};
            return; // a single node is always balanced
        }
        if (x < t->key)
            insert(x, t->left);
        else if (t->key < x)
            insert(x, t->right);
        else
        {
        } // Duplicate; do nothing

        // This will call balance on the way back up the tree. It will only balance
        // once at node the where the tree got imbalanced (called node alpha in the textbook)
        // and update the height all the way back up the tree.
        balance(t);
    }
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    // void remove(const Comparable& item)
    // {
    //     throw std::runtime_error("Not implemented yet!");
    //     // same as in a binary search tree
    //     // don't forget to balance the AVL tree after the deletion!
    // }
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

 //make it comparable because its empty and we cannot return NULL


    //const IndexHandler::Comparable& getEntry(const Comparable& item) const
    //{
      //  return getEntry(item, root)->element;
    //}




    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const
    {
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
    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const
    {
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
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }
    static const int ALLOWED_IMBALANCE = 1; // 1 is the default; more will make balancing cheaper
                                            // but the search less efficient.

    /** 
     * 1. Performs rotations if the the the difference of the height stored in t's two child nodes 
     *    more than ALLOWED_IMBALANCE.
     * 2. Updates the height information of the note t.
     * 
     * Assumes that the high information in the child nodes is correct. This is guaranteed by calling
     * balance() recursivly from the inserted node up to the tree node (see insert()). Rotations will 
     * only be performed for node alpha (parent of the parent of the inserted node). For all other nodes, 
     * only the height will be updated. 
     */
    void balance(AvlNode *&t)
    {
        // special case: empty tree
        if (t == nullptr)
            return;
        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t); // case 1 (outside)
            else
                doubleWithLeftChild(t); // case 2 (inside)
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t); // case 4 (outside)
            else
                doubleWithRightChild(t); // case 3 (inside)
        }
        // else ... no imbalance was created

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2)
    {
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
    void rotateWithRightChild(AvlNode *&k1)
    {

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

    void doubleWithLeftChild(AvlNode *&k3)
    {
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
    void doubleWithRightChild(AvlNode *&k1)
    {
#ifdef DEBUG
        cout << "doubleWithRightChild" << endl;
#endif
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};

#endif
