//
// Created by G.Q on 2019/4/10.
//

#ifndef CLION_CPP_ARRAYPRIORITYQUEUE_H
#define CLION_CPP_ARRAYPRIORITYQUEUE_H

#include "maxPriorityQueue.h"
#include <algorithm>
#include <iostream>

namespace ARRAY {
    template<class T>
    struct DATA {
        T element;
        int priority;

        explicit DATA(const T theElement = 0, int thePriority = 1) : element(theElement), priority(thePriority) {}

        DATA(const DATA<T> &theData) {
            if (this != &theData) {
                this->element = theData.element;
                this->priority = theData.priority;
            } else {
                std::cerr << "cannot structure by self";
                exit(1);
            }
        }

        DATA &operator=(const DATA<T> &theData) {
            if (this != &theData) {
                this->element = theData.element;
                this->priority = theData.priority;
            }
            return *this;
        }

        void output() const {
            std::cout << "element: " << this->element << ", priority: " << this->priority;
        }
    };

    template<class T>
    std::ostream &operator<<(std::ostream &out, DATA<T> &theData) {
        theData.output();
        return out;
    }
}

template<class T>
class arrayPriorityQueue : public maxPriorityQueue<T> {
public:
    // 构造方法
    explicit arrayPriorityQueue(int initialLength = 10);

    explicit arrayPriorityQueue(T &theData, int initialLength = 10);

    explicit arrayPriorityQueue(const arrayPriorityQueue<T> &theArr);

    arrayPriorityQueue<T> &operator=(const arrayPriorityQueue<T> &theArr);

    // 析构
    ~arrayPriorityQueue() {
        delete[] this->data;
        this->data = nullptr;
        std::cout << "[INFO]: 优先级队列被析构了" << std::endl;
    }

    // 常用操作
    bool empty() const { return this->length == 0; }

    int size() const { return this->length; }

    T &top() const;

    void pop();

    void push(const T &theElement);

    void output() const {
        for (int i = 0; i != this->length; ++i)
            std::cout << this->data[i] << " ";
        std::cout << std::endl;
    }

private:
    T *data;
    int capacity;
    int length;
};

template<class T>
arrayPriorityQueue<T>::arrayPriorityQueue(int initialLength) {
    if (initialLength < 1) {
        std::cerr << "initial length must be > 0";
        exit(1);
    }
    this->capacity = initialLength;
    this->data = new T[this->capacity];
    this->length = 0;
}

template<class T>
arrayPriorityQueue<T>::arrayPriorityQueue(T &theData, int initialLength) {
    if (initialLength < 1) {
        std::cerr << "initial length must be > 0";
        exit(1);
    }
    this->length = initialLength;
    this->data = new T[this->capacity];
    this->length = 1;
    this->data[this->length] = theData;
}

template<class T>
arrayPriorityQueue<T>::arrayPriorityQueue(const arrayPriorityQueue<T> &theArr) {
    this->length = theArr.length;
    this->capacity = theArr.capacity;
    this->data = new T[this->capacity];
    std::copy(theArr.data, theArr.data + theArr.length, this->data);
}

template<class T>
arrayPriorityQueue<T> &arrayPriorityQueue<T>::operator=(const arrayPriorityQueue<T> &theArr) {
    if (this != &theArr) {
        this->length = theArr.length;
        this->capacity = theArr.capacity;
        auto *tmp = new T[this->capacity];
        for (int i = 0; i != this->length; ++i)
            tmp[i] = theArr.data[i];
        delete[] this->data;
        this->data = tmp;
    }
    return *this;
}

template<class T>
void arrayPriorityQueue<T>::push(const T &theElement) {
    if (this->length >= this->capacity) {
        std::cerr << "length must be lower than capacity";
        exit(1);
    }
    this->data[this->length++] = theElement;
}

template<class T>
T &arrayPriorityQueue<T>::top() const {
    if (this->length == 0) {
        std::cerr << "arr is empty";
        exit(1);
    }
    // 返回优先级最大的元素
    for (int i = 0; i != this->length - 1; ++i)
        for (int j = 0; j != this->length - i - 1; ++j) {
            if (this->data[j].priority < this->data[j + 1].priority) {
                T tmp = this->data[j];
                this->data[j] = this->data[j + 1];
                this->data[j + 1] = tmp;
            }
        }
    return this->data[0];
}

template<class T>
void arrayPriorityQueue<T>::pop() {
    if (this->length == 0) {
        std::cerr << "arr is empty";
        exit(1);
    }
    // 返回优先级最大的元素
    for (int i = 0; i != this->length - 1; ++i)
        for (int j = 0; j != this->length - i - 1; ++j) {
            if (this->data[j].priority < this->data[j + 1].priority) {
                T tmp = this->data[j];
                this->data[j] = this->data[j + 1];
                this->data[j + 1] = tmp;
            }
        }
    for (int i = 0; i != this->length - 1; ++i)
        this->data[i] = this->data[i + 1];
    --this->length;
}

#endif //CLION_CPP_ARRAYPRIORITYQUEUE_H
