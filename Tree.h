//a tree called Node represents a node in the lubrary search tree
//the class has a pointer to the root node of the binary search tree and an integer representing its class
//the function height will take a pointer to a node and its argument will to return its height and the pointer null will return -1 
//the function max will take two integers as its arguments and return the maximum of them
//the function insert takes an element of type T as its argument and iserts it into a binary seach tree. if the element already exists it will return reference to it otherwise it will create a new node with this element and insert it into the appropreiate pistion in the tree
//the function balanace take sapointer to a node as its argument and balaces of the subtree rooted at this ode using only one of 4 rotation operations
 //the functions rotateWithLeftChild rotateWithRightChild doubleWithLeftChild and doubleWithRightChild are private helper function tha tperform one of four rotataion operations on a subtree rooted at a given node

 
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include<vector>
using namespace std;
template<typename T>
class Tree {
private:
    class Node{
    public:
        T element;
        Node *left;
        Node *right;
        int height;
        Node(const T& theElement,Node *lt=nullptr,Node *rt=nullptr,int h = 0 ):
                element( theElement ), left( lt ), right( rt ), height( h ) { }
    };
    Node *root;
    int size;
    // get height of -1 if nullptr
    int height(Node* v){
        if(v==nullptr)
            return -1;
        return v->height;
    }
    // get max two num
    int max(int a, int b){
        return a > b ? a : b;
    }

    T& insert(const T& x, Node*& curr){
        if(curr==nullptr){
            size++;
            curr = new Node(x); // add node
        }
        else if(x < curr->element)
            return insert(x, curr->left); // descend left child
        else if(curr->element < x)
            return insert(x, curr->right); // descend right child
        else if(x == curr->element)
            return curr->element;
        balance(curr);
        return curr->element;
    }
    void balance(Node*& t){
        if(t==nullptr)
            return;
        // case 1 or 2 rotation
        if(height(t->left)-height(t->right)>1){
            if(height(t->left->left)>=height(t->left->right))
                rotateWithLeftChild(t); //c1
            else
                doubleWithLeftChild(t); //c2
        }
        else if(height(t->right)-height(t->left)>1){
            if(height(t->right->right)>=height(t->right->left))
                rotateWithRightChild(t); // c4
            else
                doubleWithRightChild(t); //c3
        }
        t->height = max(height(t->left),height(t->right))+1;
    }
    // rotations
    void rotateWithLeftChild(Node*& k2){
        Node* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left),height(k2->right))+1;
        k1->height = max(height(k1->left),k2->height)+1;
        k2=k1;
    }
    void rotateWithRightChild(Node*& k1){
        Node* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left),height(k1->right))+1;
        k2->height = max(height(k2->right),k1->height)+1;
        k1 = k2;
    }
    void doubleWithLeftChild(Node*& k3){
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }
    void doubleWithRightChild(Node*& k1){
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    T* getElement(const T& x, Node*& curr){
        if(curr==nullptr)
            return nullptr; // doesn't exist
        if(x < curr->element)
            return getElement(x, curr->left); // descend left child
        else if(curr->element < x)
            return getElement(x, curr->right); // descend right child
        else if(curr->element == x)
            return &curr->element; // exists
        else    return nullptr;
    }
    // check if copy is called
    Tree(const Tree &rhs): root(nullptr) { *this = rhs; }
    // to clear tree
    void emptyTree(Node* n){
        if(n!=nullptr){
            emptyTree(n->left);
            emptyTree(n->right);
            delete n;
        }
    }
    void output(Node* n){
        if(n!=nullptr){
            output(n->left);
            allElements.push_back(n->element);
            output(n->right);
        }
    }
    void print(ostream& out, Node* n)const{
        if(n!=nullptr){
            out<<n->element;
            print(out,n->left);
            print(out,n->right);
        }
    }

public:
    // default constructor
    Tree(): root(nullptr), size(0) {}
    // destructor
    ~Tree() {
        emptyTree(root);
    }

    // public interface functions
    T& insert(const T &x) {
        return insert(x, root);
    }
    T* getElement(const T &x) {
        return getElement(x, root);
    }
    void output(){
        output(root);
    }
    int getSize(){ return size;}

    // specific to this project
    vector<T> allElements;
    vector<T>& getSet(){return allElements;}
    void clearElements(){ allElements.clear();}

    void print(ostream& out){
        print(out, root);
    }
    void emptyTree(){
        emptyTree(root);
        allElements.clear();
        size = 0;
        root = nullptr;
    }
};

#endif //TREE_H