//
// Created by G.Q on 2019/4/2.
//

#ifndef CLION_CPP_ARRAYQUEUE_H
#define CLION_CPP_ARRAYQUEUE_H

#include <sstream>
#include "queue.h"
#include "../MyException.h"

template<class T>
class arrayQueue : public queue<T> {
    template<class Tb>
    friend std::ostream &operator<<(std::ostream &out, const arrayQueue<Tb> &q);

public:
    arrayQueue(int initialCapacity = 10);

    arrayQueue(const arrayQueue<T> &q);

    ~arrayQueue() { delete[] this->queue; }

    bool empty() const { return this->queueFront == this->queueBack && this->queueFront == -1; }

    int size() const { return this->qSize; }

    T &front() { return this->queue[queueFront]; }

    T &back() { return this->queue[queueBack]; }

    void pop();

    void push(const T &theElement);

private:
    T *queue;
    int queueFront;
    int queueBack;
    int qSize;
};

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream ss;
        ss << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(ss.str());
    }
    this->qSize = initialCapacity;
    this->queue = new T[this->qSize];
    this->queueFront = this->queueBack = -1;
}

template<class T>
arrayQueue<T>::arrayQueue(const arrayQueue<T> &q) {
    this->qSize = q.qSize;
    this->queue = new T[this->qSize];
    for (int i = q.queueBack; i <= q.queueFront; ++i)
        this->queue[i] = q.queue[i];
    this->queueFront = q.queueFront;
    this->queueBack = q.queueBack;
}

template<class T>
void arrayQueue<T>::pop() {
    if (this->queueFront == -1 || this->queueBack == -1)
        throw queueEmpty();
    ++this->queueFront;
    if (this->queueFront > this->queueBack) {
        this->queueFront = -1;
        this->queueBack = -1;
    }
}

template<class T>
void arrayQueue<T>::push(const T &theElement) {
//    if ((this->queueBack + 1) % this->qSize == this->queueFront) {
//        // 扩充数组容量
//        ;
//    }
    this->queueFront = 0;
    this->queue[++this->queueBack] = theElement;
}

template<class T>
std::ostream &operator<<(std::ostream &out, const arrayQueue<T> &q) {
    if(q.queueFront == -1)
        out << "queue is empty" << endl;
    else
        for (int i = q.queueFront; i != q.queueBack + 1; ++i)
            out << q.queue[i] << " ";
    return out;
}

#endif //CLION_CPP_ARRAYQUEUE_H
