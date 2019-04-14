//
// Created by G.Q on 2019/4/10.
//

#ifndef CLION_CPP_BINARYTREENODE_H
#define CLION_CPP_BINARYTREENODE_H

#include <iostream>

template<class T>
struct binaryTreeNode {
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;

    // 构造方法
    binaryTreeNode() : leftChild(nullptr), rightChild(nullptr) {}

    binaryTreeNode(const T &theElement) : element(theElement), leftChild(nullptr), rightChild(nullptr) {}

    binaryTreeNode(const T &theElement, binaryTreeNode<T> *theLeftChild, binaryTreeNode<T> *theRightChild) :
            element(theElement), leftChild(theLeftChild), rightChild(theRightChild) {}

    binaryTreeNode<T> &operator=(const binaryTreeNode<T> &theTree) {
        if (this != &theTree) {
            this->element = theTree.element;
            this->leftChild = theTree.leftChild;
            this->rightChild = theTree.rightChild;
        }
        return *this;
    }

private:

    binaryTreeNode(const binaryTreeNode<T> &) {}
};

#endif //CLION_CPP_BINARYTREENODE_H
