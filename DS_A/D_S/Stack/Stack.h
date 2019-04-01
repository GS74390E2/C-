//
// Created by G.Q on 2019/3/28.
//

#ifndef CLION_CPP_STACK_H
#define CLION_CPP_STACK_H

#include <algorithm>
#include <iterator>
#include <sstream>

using std::copy;
using std::swap;
using std::ostream_iterator;

template<class T>
class Stack {
public:
    // 虚析构
    ~Stack() {}

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    // 返回栈顶元素
    virtual T &top() = 0;

    // 弹栈
    virtual void pop() = 0;

    // 压栈
    virtual void push(const T &theElement) = 0;


};


#endif //CLION_CPP_STACK_H
