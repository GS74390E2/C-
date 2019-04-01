//
// Created by G.Q on 2019/3/28.
//

#ifndef CLION_CPP_DERIVEDARRAYSTACK_H
#define CLION_CPP_DERIVEDARRAYSTACK_H

#include "Stack.h"
#include "../arrayList/arrayList.h"
#include "../MyException.h"

/*
 * 利用线性表派生的一个子类数组描述的栈
 * 复用简单，但代价是性能的损失，数组的插入和删除会检查下标，还可能会加长数组、复制元素，对栈来说不必要
 */
//template<class T>
//class derivedArrayStack : private arrayList<T>, public Stack<T> {
//public:
//    derivedArrayStack(int initialCapacity = 10) : arrayList<T>(initialCapacity) {}
//
//    bool empty() const { return arrayList<T>::isEmpty(); }
//
//    int size() const { return arrayList<T>::size(); }
//
//    T &top() {
//        try {
//            return get(arrayList<T>::size() - 1);
//        } catch (illegalParameterValue &) {
//            throw stackEmpty();
//        }
//    }
//
//    void pop() {
//        try {
//            return erase(arrayList<T>::size() - 1);
//        } catch (illegalParameterValue &) {
//            throw stackEmpty();
//        }
//    }
//
//    void push(const T &theElement) {
//        arrayList<T>::push_back(theElement);
//    }
//
//    ~derivedArrayStack() {
//        delete[] this->data;
//    }
//};

/*
 * 性能更好的栈
 */
template<class T>
class arrayStack : public Stack<T> {
public:
    arrayStack(int initialCapacity = 10);

    ~arrayStack() { delete[] this->stack; }

    bool empty() const { return this->stackTop == -1; }

    int size() const { return this->stackTop + 1; }

    T &top() {
        if (this->stackTop == -1)
            throw stackEmpty();
        return this->stack[this->stackTop];
    }

    void pop() {
        if (this->stackTop == -1)
            throw stackEmpty();
        --this->stackTop;
    }

    void push(const T &theElement);

    // test 7.1 输入栈
    void inputStack();

    // test 7.2 输出栈
    void outputStack() const;

    // test 7.3 分割栈
    arrayStack<T> splitStack();

    // test 7.4 合并栈，第二个栈顺序不变位于栈顶
    void expandStack(arrayStack<T> &s);

private:
    int stackTop;
    int arrayLength;
    T *stack;
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream ss;
        ss << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(ss.str());
    }
    this->arrayLength = initialCapacity;
    this->stack = new T[this->arrayLength];
    this->stackTop = -1;
}

template<class T>
void arrayStack<T>::push(const T &theElement) {
    if (this->stackTop == this->arrayLength - 1) {
        T *tmp = new T[this->arrayLength * 2];
        for (int i = 0; i != this->arrayLength; ++i)
            tmp[i] = this->stack[i];
        delete[] this->stack;
        this->stack = tmp;
        this->arrayLength *= 2;
    }
    this->stack[++this->stackTop] = theElement;
}

template<class T>
void arrayStack<T>::inputStack() {
    cout << "Please input the elements of stack (9999 is quit): ";
    while (true) {
        T value;
        cin >> value;
        if (value == 9999) break;
        this->push(value);
    }
}

template<class T>
void arrayStack<T>::outputStack() const {
    for (int i = this->stackTop; i != -1; --i)
        cout << this->stack[i] << " ";
}

template<class T>
arrayStack<T> arrayStack<T>::splitStack() {
    int targetIndex = this->stackTop / 2;
    arrayStack<T> upStack;
    for (int i = 0; i != targetIndex + 1; ++i) {
        upStack.push(this->top());
        this->pop();
    }
    upStack.stackTop = targetIndex;
    return upStack;
}

template<class T>
void arrayStack<T>::expandStack(arrayStack<T> &s) {
    arrayStack<T> stmp;
    int topTemp = s.stackTop;
    for (int i = 0; i != topTemp + 1; ++i) {
        stmp.push(s.top());
        s.pop();
    }
    topTemp = stmp.stackTop;
    for (int j = 0; j != topTemp + 1; ++j) {
        this->push(stmp.top());
        stmp.pop();
    }
}

#endif //CLION_CPP_DERIVEDARRAYSTACK_H
