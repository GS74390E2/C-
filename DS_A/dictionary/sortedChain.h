//
// Created by G.Q on 2019/4/4.
//

#ifndef CLION_CPP_SORTEDCHAIN_H
#define CLION_CPP_SORTEDCHAIN_H

#include "Dictionary.h"

template<class K, class V>
struct pairNode {
    typedef std::pair<const K, V> pairType;
    pairType element;
    pairType *nextNode;

    pairNode(const pairType &thePair) : element(thePair), nextNode(nullptr) {}

    pairNode(const pairType &thePair, const pairNode<K, V> &theNext) : element(thePair), nextNode(theNext) {}
};

template<class K, class V>
class sortedChain : public Dictionary<K, V> {
public:
    sortedChain() : firstNode(nullptr), dSize(0) {}

    ~sortedChain();

    bool empty() const { return this->dSize == 0; }

    int size() const { return this->dSize; }

    std::pair<const K, V> *find(const K &theKey) const;

    void erase(const K &theKey);

    void insert(const std::pair<const K, V> &thePair);

private:
    pairNode<K, V> *firstNode;
    int dSize;
};

template<class K, class V>
std::pair<const K, V> *sortedChain<K, V>::find(const K &theKey) const {
    pairNode<K, V> *currentNode = this->firstNode;

    while (currentNode != nullptr && currentNode->element.first != theKey) {
        currentNode = currentNode->nextNode;
    }

    if (currentNode != nullptr && currentNode->element.first == theKey) {
        return &currentNode->element;
    }
    return nullptr;
}

template<class K, class V>
void sortedChain<K, V>::insert(const std::pair<const K, V> &thePair) {
    pairNode<K, V> *p = this->firstNode, *tp = nullptr;

    while (p != nullptr && p->element.first < thePair.first) {
        tp = p;
        p = p->nextNode;
    }
    // 如果找到则替换
    if (p != nullptr && p->element.first == thePair.first) {
        p->element.second = thePair.second;
        return;
    }
    // 如果未找到则添加
    pairNode<K, V> *newNode = new pairNode<K, V>(thePair, p);
    if (tp == nullptr) this->firstNode = newNode;
    else tp->nextNode = newNode;

    ++this->dSize;
}

template<class K, class V>
void sortedChain<K, V>::erase(const K &theKey) {
    pairNode<K, V> *p = this->firstNode, *tp = nullptr;

    while (p != nullptr && p->element.first < theKey) {
        tp = p;
        p = p->nextNode;
    }

    if (p != nullptr && p->element.first == theKey) {
        if (tp == nullptr) this->firstNode = nullptr;
        else tp->nextNode = p->nextNode;
    }

    delete p;
    p = nullptr;
    --this->dSize;
}

template<class K, class V>
sortedChain<K, V>::~sortedChain() {
    while (this->firstNode != nullptr) {
        pairNode<K, V> *next = this->firstNode->nextNode;
        delete this->firstNode;
        this->firstNode = next;
    }
}


#endif //CLION_CPP_SORTEDCHAIN_H
