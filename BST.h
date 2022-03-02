#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    BSTNode<T>* copyConstructorHelper(BSTNode<T> *t);
    void insertHelper(const T &data, BSTNode<T> *node, BSTNode<T> *parent);
    void destructorHelper(BSTNode<T> *node);
    bool containsHelper(BSTNode<T> *myNode, BSTNode<T> *givenNode) const;
    BSTNode<T>* findMin(BSTNode<T> *t) const;
    void removeHelper(const T &data, BSTNode<T>* &t) const;
    void removeAllNodesHelper(BSTNode<T> *node);
    BSTNode<T>* searchHelper(BSTNode<T> *node, const T &data) const;
    BSTNode<T>* operatorHelper(BSTNode<T> *t);

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H




















// DEFAULT CONSTRUCTOR
template<class T>
BST<T>::BST() {
    // TODO
    // root will be null
    root = NULL;
}




















// COPY CONSTRUCTOR
template<class T>
BSTNode<T>* BST<T>::copyConstructorHelper(BSTNode<T> *t) {
    // base case
    if (t == NULL) {
        return NULL;
    }
    // recursive case
    // create a new node
    BSTNode<T> *newNode = new BSTNode<T>();
    // put the data inside the new node
    newNode->data = t->data;
    // copy the left subtree
    newNode->left = copyConstructorHelper(t->left);
    // copy the right subtree
    newNode->right = copyConstructorHelper(t->right);
    // return the new node which is the root node of out new tree
    return newNode;
}
template<class T>
BST<T>::BST(const BST<T> &obj) {
    // TODO
    // a fresh beginning
    root = NULL;
    // call the helper copy constructor
    root = copyConstructorHelper(obj.getRoot());
}
















// DESTRUCTOR
template<class T>
void BST<T>::destructorHelper(BSTNode<T> *node) {
    // base case
    if (node == NULL) {
        return;
    }
    // recursive case
    destructorHelper(node->left);
    destructorHelper(node->right);
    delete node;
}
template<class T>
BST<T>::~BST() {
    // TODO
    // call helper destructor
    destructorHelper(root);
    // since it is an empty tree, root will be null
    root = NULL;
}




















template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    // TODO
    return root;
}




















template<class T>
bool BST<T>::isEmpty() const {
    // TODO
    if (root == NULL) {
        return true;
    }
    else {
        return false;
    }
}



















// CONTAINS
template<class T>
bool BST<T>::containsHelper(BSTNode<T> *myNode, BSTNode<T> *givenNode) const {
    // base case
    if (myNode == NULL) {
        return false;
    }
    // recursive case
    // if we have found the given node in the tree
    if (myNode == givenNode) {
        return true;
    }
    // if this is not the given node
    else {
        return containsHelper(myNode->left, givenNode) || containsHelper(myNode->right, givenNode);
    }
}
template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    // TODO
    // call helper contains function
    return containsHelper(root, node);
}




















// INSERT FUNCTION
template <class T>
void BST<T>::insertHelper(const T &data, BSTNode<T> *node, BSTNode<T> *parent) {
    // base case
    if (node == NULL) {
        // create a new node with the given data
        BSTNode<T> *insertedNode = new BSTNode<T>(data, NULL, NULL);

        // connect it to its parent node properly
        // if the data is less than the parent data
        if (data < parent->data) {
            // Do the connection to the left direction
            parent->left = insertedNode;
            return;
        }
        // if the data is equal to the parent data
        else if (data == parent->data) {
            // give error
            std::cout << "Given data has a duplicate in the tree!" << std::endl;
            return;
        }
        // if the data is greater than the parent data
        else {
            // Do the connection to the right direction
            parent->right = insertedNode;
            return;
        }
    }

    // recursive case
    // if the data is less than the node data
    if (data < node->data) {
        // Do the insertion to the left subtree
        insertHelper(data, node->left, node);
    }
    // if the data is equal to the node data
    else if (data == node->data) {
        // give error
        std::cout << "Given data has a duplicate in the tree!" << std::endl;
        return;
    }
    // if the data is greater than the node data
    else {
        // Do the insertion to the right subtree
        insertHelper(data, node->right, node);
    }
}
template<class T>
void BST<T>::insert(const T &data) {
    // TODO
    // if the tree is empty
    if (root == NULL) {
        BSTNode<T> *insertedNode = new BSTNode<T>(data, NULL, NULL);
        root = insertedNode;
        return;
    }
    // call helper function
    insertHelper(data, root, NULL);
}




















// REMOVE FUNCTION
template<class T>
BSTNode<T>* BST<T>::findMin(BSTNode<T> *t) const {
    if (t == NULL) {
        return NULL;
    }
    if (t->left == NULL) {
        return t;
    }
    return findMin(t->left);
}
template<class T>
void BST<T>::removeHelper(const T &x, BSTNode<T>* &t) const {
    if (t == NULL) {
        return;
    }
    if (x < t->data) {
        removeHelper(x, t->left);
    }
    else if (x > t->data) {
        removeHelper(x, t->right);
    }
    else if (t->left != NULL && t->right != NULL) {
        t->data = findMin(t->right)->data;
        removeHelper(t->data, t->right);
    }
    else {
        BSTNode<T> *oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
}
template<class T>
void BST<T>::remove(const T &data) {
    // TODO
    // if a node with the given data does not exist in the tree
    if (search(data) == NULL) {
        return;
    }
    // call helper remove function
    removeHelper(data, root);
}



















// REMOVE ALL NODES FUNCTION
template<class T>
void BST<T>::removeAllNodesHelper(BSTNode<T> *node) {
    // base case
    if (node == NULL) {
        return;
    }
    // recursive case
    removeAllNodesHelper(node->left);
    removeAllNodesHelper(node->right);
    delete node;
}
template<class T>
void BST<T>::removeAllNodes() {
    // TODO
    // call helper remove all nodes function
    removeAllNodesHelper(root);
    // since it is an empty tree, root will be null
    root = NULL;
}



















// SEARCH FUNCTION
template<class T>
BSTNode<T>* BST<T>::searchHelper(BSTNode<T> *node, const T &data) const {
    // base case
    if (node == NULL) {
        return NULL;
    }
    // recursive case
    // if we have found the data in the tree
    if (data == node->data) {
        return node;
    }
    // if this is not the node that we are looking for
    else {
        // if data is less than the data of node
        if (data < node->data) {
            // we should search the data in the left subtree
            return searchHelper(node->left, data);
        }
        // if data is greater than the data of node
        else if (data > node->data) {
            // we should search the data in the right subtree
            return searchHelper(node->right, data);
        }
    }
}
template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    // TODO
    // call helper search function
    return searchHelper(root, data);
}




















template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {

    if (tp == inorder) {
        // TODO
    } else if (tp == preorder) {
        // TODO
    } else if (tp == postorder) {
        // TODO
    }
}



















// PRINT FUNCTION
template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        // TODO
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        // TODO
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}




















// OPERATOR FUNCTION
template<class T>
BSTNode<T>* BST<T>::operatorHelper(BSTNode<T> *t) {
    if (t == NULL) {
        return NULL;
    }
    BSTNode<T>* copyRoot = new BSTNode<T>();
    copyRoot->data = t->data;
    copyRoot->left = copyConstructorHelper(t->left);
    copyRoot->right = copyConstructorHelper(t->right);
    return copyRoot;
}
template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    // TODO
    // remove all nodes of my tree
    removeAllNodes();
    // copy the rhs to my tree
    // call the helper copy constructor
    root = operatorHelper(rhs.getRoot());
}



















// PRINT FUNCTION HELPER
template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // base case
    if (node == NULL) {
        return;
    }

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == preorder) {
        // TODO
        // recursive case
        // print the node
        std::cout << "\t" << node->data;

        // if the left is not null
        if (node->left != NULL) {
            // put a comma and pass to the new line
            std::cout << "," << std::endl;
        }
        // print the left subtree
        print(node->left, preorder);
        
        // if the right is not null
        if (node->right != NULL) {
            // put a comma and pass to the new line
            std::cout << "," << std::endl;
        }
        // print the right subtree
        print(node->right, preorder);
    } else if (tp == postorder) {
        // TODO
        // recursive case
        // print the left subtree
        print(node->left, postorder);
        // if the left is not null
        if (node->left != NULL) {
            // put a comma and pass to the new line
            std::cout << "," << std::endl;
        }

        // print the right subtree
        print(node->right, postorder);
        // if the right is not null
        if (node->right != NULL) {
            // put a comma and pass to the new line
            std::cout << "," << std::endl;
        }

        // print the node
        std::cout << "\t" << node->data;
    }
}
