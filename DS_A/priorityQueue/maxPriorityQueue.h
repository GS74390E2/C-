//
// Created by G.Q on 2019/4/10.
//

#ifndef CLION_CPP_PRIORITYQUEUE_H
#define CLION_CPP_PRIORITYQUEUE_H

template<class T>
class maxPriorityQueue {
public:
    virtual ~maxPriorityQueue() {}

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual T &top() const = 0;

    virtual void pop() = 0;

    virtual void push(const T &theElement) = 0;
};

#endif //CLION_CPP_PRIORITYQUEUE_H
