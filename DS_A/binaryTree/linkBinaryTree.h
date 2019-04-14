#ifndef CLION_CPP_LINKBINARYTREE_H
#define CLION_CPP_LINKBINARYTREE_H

#include "binaryTreeNode.h"

template<class T>
class linkBinaryTree {
public:
    linkBinaryTree() : root(nullptr), treeSize(0) {}

    bool empty() { return this->treeSize == 0; }

    int size() { return this->treeSize; }

    void makeTree(const T &theElement, linkBinaryTree<T> &left, linkBinaryTree<T> &right);

    void preOrder(void(*theFunc)(binaryTreeNode<T> *)) {
        func = theFunc;
        pre_Order(this->root);
    }

    void inOrder(void(*theFunc)(binaryTreeNode<T> *)) {
        func = theFunc;
        in_Order(this->root);
    }

    void postOrder(void(*theFunc)(binaryTreeNode<T> *)) {
        func = theFunc;
        post_Order(this->root);
    }

    void erase() {
        this->postOrder(this->dispose);
        this->root = nullptr;
        this->treeSize = 0;
    }

    void preOrderOutput() {
        this->preOrder(output);
    }

    void inOrderOutput() {
        this->inOrder(output);
    }

    void postOrderOutput() {
        this->postOrder(output);
    }

    int treeHeight() const {
        return this->tree_Height(this->root);
    }

    ~linkBinaryTree() { this->erase(); }

protected:
    binaryTreeNode<T> *root;
    int treeSize;

    static void (*func)(binaryTreeNode<T> *treeNode);

    static void pre_Order(binaryTreeNode<T> *treeNode);

    static void in_Order(binaryTreeNode<T> *treeNode);

    static void post_Order(binaryTreeNode<T> *treeNode);

    static void dispose(binaryTreeNode<T> *treeNode) { delete treeNode; }

    static void output(binaryTreeNode<T> *treeNode) { std::cout << treeNode->element << " "; }

    static int tree_Height(binaryTreeNode<T> *treeNode);

    linkBinaryTree(const linkBinaryTree<T> &) {}

    linkBinaryTree &operator=(const linkBinaryTree<T> &) {}
};

template<class T>
void (*linkBinaryTree<T>::func)(binaryTreeNode<T> *);

template<class T>
void linkBinaryTree<T>::makeTree(const T &theElement, linkBinaryTree<T> &left, linkBinaryTree<T> &right) {
    this->root = new binaryTreeNode<T>(theElement, left.root, right.root);
    this->treeSize = left.treeSize + right.treeSize + 1;

    left.root = right.root = nullptr;
    left.treeSize = right.treeSize = 0;
}

template<class T>
void linkBinaryTree<T>::pre_Order(binaryTreeNode<T> *treeNode) {
    if (treeNode != nullptr) {
        func(treeNode);
        pre_Order(treeNode->leftChild);
        pre_Order(treeNode->rightChild);
    }
}

template<class T>
void linkBinaryTree<T>::in_Order(binaryTreeNode<T> *treeNode) {
    if (treeNode != nullptr) {
        in_Order(treeNode->leftChild);
        func(treeNode);
        in_Order(treeNode->rightChild);
    }
}

template<class T>
void linkBinaryTree<T>::post_Order(binaryTreeNode<T> *treeNode) {
    if (treeNode != nullptr) {
        post_Order(treeNode->leftChild);
        post_Order(treeNode->rightChild);
        func(treeNode);
    }
}

template<class T>
int linkBinaryTree<T>::tree_Height(binaryTreeNode<T> *treeNode) {
    if (treeNode != nullptr)
        return 0;
    int hl = tree_Height(treeNode->leftChild);
    int hr = tree_Height(treeNode->rightChild);
    if (hl > hr)
        return ++hl;
    else
        return ++hr;
}


#endif