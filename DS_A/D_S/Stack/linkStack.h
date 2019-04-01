//
// Created by G.Q on 2019/3/28.
//

#ifndef CLION_CPP_LINKSTACK_H
#define CLION_CPP_LINKSTACK_H

#include "Stack.h"
#include "../MyException.h"

template<class T>
struct chainNode {
    T element;
    chainNode *next;

    chainNode(const T &theElement = 11) : element(theElement), next(nullptr) {}

    chainNode(const T &theElement, chainNode<T> *node) {
        this->element = theElement;
        this->next = node;
    }
};

template<class T>
class linkedStack : public Stack<T> {
public:
    linkedStack(int initialCapacity = 10) : stackTop(nullptr), stackSize(0) {}

    ~linkedStack();

    bool empty() const { return this->stackSize == 0; }

    int size() const { return this->stackSize; }

    // 返回栈顶元素
    T &top() {
        if (this->stackSize == 0)
            throw stackEmpty();
        return this->stackTop->element;
    }

    // 弹栈
    void pop();

    // 压栈
    void push(const T &theElement) {
        this->stackTop = new chainNode<T>(theElement, this->stackTop);
        ++this->stackSize;
    }

    // test 12.1
    void pushNode(const chainNode<T> *node);

    // test 12.2
    chainNode<T> popNode();

private:
    chainNode<T> *stackTop;
    int stackSize;
};

template<class T>
linkedStack<T>::~linkedStack() {
    while (this->stackTop != nullptr) {
        chainNode<T> *nextNode = this->stackTop->next;
        delete this->stackTop;
        this->stackTop = nextNode;
    }
}

template<class T>
void linkedStack<T>::pop() {
    if (this->stackSize == 0)
        throw stackEmpty();
    chainNode<T> *nextNode = this->stackTop->next;
    delete this->stackTop;
    this->stackTop = nextNode;
    --this->stackSize;
}

template<class T>
void linkedStack<T>::pushNode(const chainNode<T> *node) {
    this->stackTop = new chainNode<T>(node->element, this->stackTop);
    ++this->stackSize;
}

template <class T>
chainNode<T> linkedStack<T>::popNode() {
    if (this->stackSize == 0)
        throw stackEmpty();
    chainNode<T> *nextNode = this->stackTop->next;
    chainNode<T> *tmp = new chainNode<T>(this->stackTop->element, this->stackTop);
    delete this->stackTop;
    this->stackTop = nextNode;
    --this->stackSize;
    return *tmp;
}

#endif //CLION_CPP_LINKSTACK_H
