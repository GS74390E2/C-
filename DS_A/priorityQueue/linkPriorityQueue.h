//
// Created by G.Q on 2019/4/10.
//

#ifndef CLION_CPP_LINKPRIORITYQUEUE_H
#define CLION_CPP_LINKPRIORITYQUEUE_H

#include <iostream>
#include "maxPriorityQueue.h"

namespace LINK {
    template<class T>
    struct DATA {
        T element;
        int priority;
        DATA *next;

        explicit DATA(T theElement, int thePriority) : element(theElement), priority(thePriority), next(nullptr) {}

        DATA(T theElement, int thePriority, DATA *theNext) : element(theElement), priority(thePriority),
                                                             next(theNext) {}

        DATA(const DATA<T> &theData) {
            this->element = theData.element;
            this->priority = theData.priority;
            this->next = nullptr;
        }

        void output() {
            std::cout << "element: " << this->element << ", priority: " << this->priority << " ";
        }

    };

    template<class T>
    std::ostream &operator<<(std::ostream &out, DATA<T> &theData) {
        theData.output();
        return out;
    }
}


template<class T>
class linkPriorityQueue : public maxPriorityQueue<T> {
public:
    // 构造函数
    linkPriorityQueue() : head(nullptr), length(0) {}

    explicit linkPriorityQueue(const T &theElement);

    explicit linkPriorityQueue(const linkPriorityQueue<T> &theLink);

    linkPriorityQueue<T> &operator=(const linkPriorityQueue<T> &theLink);

    // 析构
    ~linkPriorityQueue();

    // 常用操作
    bool empty() const { return this->length == 0; }

    int size() const { return this->length; }

    T &top() const;

    void pop();

    void push(const T &theElement);

    void output() const;

private:
    T *head;
    int length;
};

template<class T>
linkPriorityQueue<T>::linkPriorityQueue(const T &theElement) {
    this->head = new T(theElement);
    this->length = 1;
}

template<class T>
linkPriorityQueue<T>::linkPriorityQueue(const linkPriorityQueue<T> &theLink) {
    this->length = theLink.length;
    T *tmp1 = theLink.head;
    this->head = new T(tmp1->element, tmp1->priority, tmp1->next);
    T *tmp2 = this->head;
    tmp1 = tmp1->next;
    while (tmp1 != nullptr) {
        tmp2 = new T(tmp1->element, tmp1->priority, tmp1->next);
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    tmp2->next = nullptr;
}

template<class T>
linkPriorityQueue<T> &linkPriorityQueue<T>::operator=(const linkPriorityQueue<T> &theLink) {
    if (this != &theLink) {
        this->length = theLink.length;
        T *tmp1 = theLink.head;
        this->head = new T(tmp1->element, tmp1->priority, tmp1->next);
        T *tmp2 = this->head;
        tmp1 = tmp1->next;
        while (tmp1 != nullptr) {
            tmp2 = new T(tmp1);
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        tmp2->next = nullptr;
    }
    return *this;
}

template<class T>
linkPriorityQueue<T>::~linkPriorityQueue() {
    while (this->head != nullptr) {
        T *temp = this->head->next;
        delete this->head;
        this->head = temp;
    }
    this->length = 0;
    std::cout << "[INFO]: 析构了" << std::endl;
}

template<class T>
void linkPriorityQueue<T>::push(const T &theElement) {
    T *temp = this->head;
    while (temp->next != nullptr)
        temp = temp->next;
    temp->next = new T(theElement);
    ++this->length;
}

template<class T>
T &linkPriorityQueue<T>::top() const {
    if (this->head == nullptr) {
        std::cerr << "link priority is empty";
        exit(1);
    }
    int maxPriority = 0;
    T *temp = this->head;
    while (temp != nullptr) {
        if (temp->priority > maxPriority)
            maxPriority = temp->priority;
        temp = temp->next;
    }
    temp = this->head;
    while (temp != nullptr) {
        if (temp->priority == maxPriority)
            return *temp;
        temp = temp->next;
    }
    std::cerr << "something wrong";
    exit(1);
}

template<class T>
void linkPriorityQueue<T>::pop() {
    if (this->head == nullptr) {
        std::cerr << "link priority is empty";
        exit(1);
    }
    int maxPriority = 0;
    T *temp = this->head;
    while (temp != nullptr) {
        if (temp->priority > maxPriority)
            maxPriority = temp->priority;
        temp = temp->next;
    }
    temp = this->head;
    while (temp->next != nullptr) {
        if (temp->next->priority == maxPriority)
            break;
        temp = temp->next;
    }
    T *del = temp->next;
    temp->next = temp->next->next;
    delete del;
}

template<class T>
void linkPriorityQueue<T>::output() const {
    T *temp = this->head;
    while (temp != nullptr) {
        temp->output();
        temp = temp->next;
    }
    std::cout << std::endl;
}


#endif //CLION_CPP_LINKPRIORITYQUEUE_H
