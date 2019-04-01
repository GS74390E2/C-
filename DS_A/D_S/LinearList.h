/*
 * Created by G.Q on 2019/3/12.
 * 抽象基类，线性表
 */

#ifndef CLION_CPP_LINEARLIST_H
#define CLION_CPP_LINEARLIST_H

#include <iostream>


template<class T>
class LinearList {
public:
    // 1.判断表是否为空
    virtual bool isEmpty() const = 0;

    // 2.返回数组大小
    virtual int size() const = 0;

    // 3.根据index获取元素
    virtual T &get(int theIndex) const = 0;

    // 4.根据元素获取第一次出现的索引
    virtual int indexOf(T &theElement) const = 0;

    // 5.删除索引为index的元素
    virtual bool erase(int theIndex) = 0;

    // 6.把元素插入表的index位
    virtual bool insert(int theIndex, T &theElement) = 0;

    // 7.追加元素
    virtual void push_back(T &theElement) = 0;

    // 8.显示所有元素
    virtual void output(std::ostream &out) const = 0;

    // 虚析构
    virtual ~LinearList(){}
};


#endif //CLION_CPP_LINEARLIST_H
