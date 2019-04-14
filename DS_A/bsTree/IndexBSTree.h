//
// Created by G.Q on 2019/4/11.
//

#ifndef CLION_CPP_INDEXBSTREE_H
#define CLION_CPP_INDEXBSTREE_H

#include <iostream>
#include "bsTree.h"

template<class K, class V>
class IndexBSTree : public bsTree<K, V> {
public:
    typedef std::pair<const K, V> Pair;

    virtual ~IndexBSTree() {}

    // 按关键字查找对组
    virtual Pair *find(const K &theKey) const = 0;

    // 插入对组
    virtual void insert(const Pair &thePair) = 0;

    // 按关键字升序输出所有对组
    virtual void ascend() = 0;

    // 按关键字删除对组
    virtual void erase(const K &theKey) = 0;

    // 返回第index个数对
    virtual Pair *get(int theIndex) const = 0;
};

#endif //CLION_CPP_INDEXBSTREE_H
