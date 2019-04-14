//
// Created by G.Q on 2019/4/14.
//

#ifndef CLION_CPP_BINARYSEARCHTREE_H
#define CLION_CPP_BINARYSEARCHTREE_H

#include "bsTree.h"
#include "../binaryTree/binaryTreeNode.h"

template<class K, class V>
class binarySearchTree : public bsTree<K, V> {
public:

    binarySearchTree() : root(nullptr), treeSize(0) {}

    void inOrder(void(*theFunc)(binaryTreeNode<std::pair<const K, V>> *)) {
        func = theFunc;
        in_Order(this->root);
    }

    void postOrder(void(*theFunc)(binaryTreeNode<std::pair<const K, V>> *)) {
        func = theFunc;
        post_Order(this->root);
    }

    void inOrderOutput() {
        this->inOrder(output);
    }

    int height() const {
        return tree_Height(this->root);
    }

    // 按关键字查找对组
    std::pair<const K, V> *find(const K &theKey) const;

    // 插入对组
    void insert(const std::pair<const K, V> &thePair);

    // 按关键字升序输出所有对组
    void ascend() { this->inOrderOutput(); }

    // 按关键字删除对组
    void erase(const K &theKey);

    ~binarySearchTree() {
        this->postOrder(dispose);
        this->root = nullptr;
        this->treeSize = 0;
    }


private:
    binaryTreeNode<std::pair<const K, V>> *root;
    int treeSize;

    static void (*func)(binaryTreeNode<std::pair<const K, V>> *treeNode);

    static void in_Order(binaryTreeNode<std::pair<const K, V>> *treeNode);

    static void post_Order(binaryTreeNode<std::pair<const K, V>> *treeNode);

    static void output(binaryTreeNode<std::pair<const K, V>> *treeNode) {
        std::cout << "first: " << treeNode->element.first << " second: " << treeNode->element.second << " ";
    }

    static void dispose(binaryTreeNode<std::pair<const K, V>> *treeNode) { delete treeNode; }

    static int tree_Height(binaryTreeNode<std::pair<const K, V>> *treeNode);

    explicit binarySearchTree(const binarySearchTree<K, V> &) {}

    binarySearchTree &operator=(const binarySearchTree<K, V> &) {}
};

template<class K, class V>
void (*binarySearchTree<K, V>::func)(binaryTreeNode<std::pair<const K, V>> *);

template<class K, class V>
void binarySearchTree<K, V>::in_Order(binaryTreeNode<std::pair<const K, V>> *treeNode) {
    if (treeNode != nullptr) {
        func(treeNode);
        in_Order(treeNode->leftChild);
        in_Order(treeNode->rightChild);
    }
}

template<class K, class V>
void binarySearchTree<K, V>::post_Order(binaryTreeNode<std::pair<const K, V>> *treeNode) {
    if (treeNode != nullptr) {
        post_Order(treeNode->leftChild);
        func(treeNode);
        post_Order(treeNode->rightChild);
    }
}

template<class K, class V>
int binarySearchTree<K, V>::tree_Height(binaryTreeNode<std::pair<const K, V>> *treeNode) {
    if (treeNode == nullptr) return 0;
    int hl = tree_Height(treeNode->leftChild);
    int hr = tree_Height(treeNode->rightChild);
    if (hl > hr)
        return ++hl;
    else
        return ++hr;
}

template<class K, class V>
std::pair<const K, V> *binarySearchTree<K, V>::find(const K &theKey) const {
    binaryTreeNode<std::pair<const K, V>> *p = this->root;
    while (p != nullptr) {
        if (theKey < p->element.first)
            p = p->leftChild;
        else if (theKey > p->element.first)
            p = p->rightChild;
        else
            return &p->element;
    }
    return nullptr;
}

template<class K, class V>
void binarySearchTree<K, V>::insert(const std::pair<const K, V> &thePair) {
    binaryTreeNode<std::pair<const K, V>> *p = this->root, *pp = nullptr;
    while (p != nullptr) {
        pp = p;
        if (thePair.first < p->element.first)
            p = p->leftChild;
        else if (thePair.first > p->element.first)
            p = p->rightChild;
        else {
            // 覆盖
            p->element.second = thePair.second;
            return;
        }
    }

    // 未查找到
    binaryTreeNode<std::pair<const K, V>> *newNode = new binaryTreeNode<std::pair<const K, V>>(thePair);
    if (this->root != nullptr) {
        if (thePair.first < pp->element.first)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;
    } else
        this->root = newNode;
    ++this->treeSize;
}

template<class K, class V>
void binarySearchTree<K, V>::erase(const K &theKey) {
    // 查找关键字为theKey的结点
    binaryTreeNode<std::pair<const K, V>> *p = this->root, *pp = nullptr;
    while (p != nullptr && p->element.first != theKey) {
        pp = p;
        if (theKey < p->element.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    if (p == nullptr)
        return;

    // 重新组织树结构
    // 当p有两个子树时
    if (p->leftChild != nullptr && p->rightChild != nullptr) {
        // 在左子树中寻找最大元素
        binaryTreeNode<std::pair<const K, V>> *s = p->leftChild, *ps = p;
        while (s->rightChild != nullptr) {
            ps = s;
            s = s->rightChild;
        }
        // 将最大元素s移到p
        binaryTreeNode<std::pair<const K, V>> *q = new binaryTreeNode<std::pair<const K, V>>(s->element, p->leftChild,
                                                                                             p->rightChild);
        if (pp == nullptr)
            this->root = q;
        else {
            if (p == pp->leftChild)
                pp->leftChild = q;
            else
                pp->rightChild = q;
        }
        if (ps == p) pp = q;
        else pp = ps;
        delete p;
        p = s;
    }

    // p最多有一个孩子
    binaryTreeNode<std::pair<const K, V>> *c;
    if (p->leftChild != nullptr)
        c = p->leftChild;
    else
        c = p->rightChild;

    // 删除p
    if (p == this->root) this->root = c;
    else {
        if (p == pp->leftChild)
            pp->leftChild = c;
        else
            pp->rightChild = c;
    }
    --this->treeSize;
    delete p;
    p = nullptr;
}


#endif //CLION_CPP_BINARYSEARCHTREE_H
