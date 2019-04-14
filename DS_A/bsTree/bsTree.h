//
// Created by G.Q on 2019/4/11.
//

#ifndef CLION_CPP_BSTREE_H
#define CLION_CPP_BSTREE_H

#include <iostream>

template<class K, class V>
class bsTree {
public:
    typedef std::pair<const K, V> Pair;

    virtual ~bsTree() {}

    // 按关键字查找对组
    virtual Pair *find(const K &theKey) const = 0;

    // 插入对组
    virtual void insert(const Pair &thePair) = 0;

    // 按关键字升序输出所有对组
    virtual void ascend() = 0;

    // 按关键字删除对组
    virtual void erase(const K &theKey) = 0;
};

#endif //CLION_CPP_BSTREE_H
