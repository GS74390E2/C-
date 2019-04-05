//
// Created by G.Q on 2019/4/2.
//

#ifndef CLION_CPP_QUEUE_H
#define CLION_CPP_QUEUE_H

template<class T>
class queue {
public:
    virtual ~queue() {}

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual T &front() = 0;

    virtual T &back() = 0;

    virtual void pop() = 0;

    virtual void push(const T &theElement) = 0;

};


#endif //CLION_CPP_QUEUE_H
