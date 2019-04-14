//
// Created by G.Q on 2019/4/11.
//

#ifndef CLION_CPP_MAXHEAP_H
#define CLION_CPP_MAXHEAP_H

#include <iostream>
#include "maxPriorityQueue.h"

template<class T>
class maxHeap : public maxPriorityQueue<T> {
public:
    // 构造方法
    explicit maxHeap(int initialSize = 10);

    bool empty() const { return this->heapSize == 0; }

    int size() const { return this->heapSize; }

    T &top() const {
        if (this->empty()) {
            std::cerr << "heap is empty";
            exit(1);
        }
        return this->heap[0];
    }

    void push(const T &theElement);

    void pop();

    void output() const {
        for (int i = 1; i <= this->heapSize; ++i)
            std::cout << this->heap[i] << " ";
        std::cout << std::endl;
    }

    // 析构方法
    ~maxHeap() {
        delete this->heap;
        this->heap = nullptr;
    }

private:
    T *heap;
    int arrayLength;
    int heapSize;

    maxHeap &operator=(const maxHeap<T> &) {}

    maxHeap(const maxHeap<T> &) {}
};

template<class T>
maxHeap<T>::maxHeap(int initialSize) {
    if (initialSize < 1) {
        std::cerr << "init size must be > 0";
        exit(1);
    }
    // 下标从1开始, 保证 子节点序号 / 2 = 父结点序号
    this->arrayLength = initialSize + 1;
    this->heap = new T[this->arrayLength];
    this->heapSize = 0;
}

template<class T>
void maxHeap<T>::push(const T &theElement) {
    if (this->heapSize >= this->arrayLength) {
        std::cerr << "size must be lower than arrayLength";
        exit(1);
    }

    // 为新元素寻找位置，从新叶子向上移动
    int currentNode = ++this->heapSize;
    while (currentNode != 1 && this->heap[currentNode / 2] < theElement) {
        this->heap[currentNode] = this->heap[currentNode / 2];
        currentNode /= 2;
    }
    this->heap[currentNode] = theElement;
}

template<class T>
void maxHeap<T>::pop() {
    if (this->heapSize == 0) {
        std::cerr << "heap is empty";
        exit(1);
    }

    // 删除最大元素
    for (int i = 1; i != this->heapSize; ++i)
        this->heap[i] = this->heap[i + 1];
    --this->heapSize;

    // 重新建堆
    int currentNode = 1;
    int child = 0;
    while (child < this->heapSize) {
        child = currentNode * 2;
        if (this->heap[currentNode] < this->heap[child]) {
            std::swap(this->heap[currentNode], this->heap[child]);
            continue;
        }
        if (this->heap[currentNode] < this->heap[++child]) {
            std::swap(this->heap[currentNode], this->heap[child]);
            continue;
        }
        ++currentNode;
    }
}

#endif //CLION_CPP_MAXHEAP_H
