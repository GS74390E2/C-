//
// Created by G.Q on 2019/3/21.
//

#ifndef CLION_CPP_ARRAYLIST_H
#define CLION_CPP_ARRAYLIST_H

#include "../LinearList.h"
#include "../MyException.h"
#include <string>
#include <sstream>

const int MAXLEN = 10;      // ����Ĭ�ϳ���
namespace ARR {
    struct DATA {
        unsigned int id;
        std::string name;

        DATA(unsigned int theId = 0, std::string theName = " ") : id(theId), name(theName) {}

        // ���ز�����
        bool operator!=(ARR::DATA &node) const {
            return this->id != node.id && this->name != node.name;
        }

        bool operator==(ARR::DATA &node) const {
            return this->id == node.id && this->name == node.name;
        }

        ARR::DATA &operator=(ARR::DATA &node) {
            this->id = node.id;
            this->name = node.name;
            return *this;
        }
    };

    std::ostream &operator<<(std::ostream &out, ARR::DATA &node) {
        out << "id: " << node.id << ", name: " << node.name << endl;
        return out;
    }

}

template<class T>
class arrayList : public LinearList<T> {
public:
    // ���캯��
    arrayList(int initialCapacity = MAXLEN);

    arrayList(const arrayList<T> &arr);

    // 1.�жϱ��Ƿ�Ϊ��
    bool isEmpty() const { return this->arrSize == 0; }

    // 2.���������С
    int size() const { return this->arrSize; };

    // 3.����index��ȡԪ��
    T &get(int theIndex) const;

    // 4.����Ԫ�ػ�ȡ��һ�γ��ֵ�����
    int indexOf(T &theElement) const;

    // 5.ɾ������Ϊindex��Ԫ��
    bool erase(int theIndex);

    // 6.��Ԫ�ز�����indexλ
    bool insert(int theIndex, T &theElement);

    // 7.׷��Ԫ��
    void push_back(T &theElement);

    // 8.��ʾ����Ԫ��
    void output(std::ostream &out) const;

    // ͳһ����
    void checkIndex(int theIndex) const;

    void changeArr1D(T *&arr, int oldCapacity, int newCapacity);

    // ��ϰ5����֤���鳤������Ϊ1
    void trimToSize();

    // ��ϰ6���ı������С
    void setSize(int theSize);

    // ��ϰ7��������[]
    T &operator[](int theIndex) const;

    // ��ϰ8��������=
    bool operator==(const arrayList<T> &arr) const;

    // ��ϰ9��������!=
    bool operator!=(const arrayList<T> &arr) const;

    // ��ϰ10��������<
    bool operator<(const arrayList<T> &arr) const;

    // ��ϰ12��pop_back
    void pop_back();

    // ��ϰ13��swap
    void swap(arrayList<T> &arr);

    // ��ϰ14��reserve
    void reserve(int theCapacity);

    // ��ϰ15��set
    void set(int theIndex, const T &theData);

    // ��ϰ16��clear
    void clear() { this->arrSize = 0; }

    // ��ϰ17��remove
    void removeRange(int theStart, int theEnd);

    // ��ϰ18��lastInOf
    int lastIndexOf(T &theData) const;

    // ��ϰ22��reverse
    void reverse();

    // ��ϰ23��leftshift
    void leftShift(int offset);

    // ��ϰ24��circularShift
    void circularShift(int offset);

    // ��ϰ25��half
    void half();

    // ��������
    ~arrayList() {
        delete[] this->data;
        cout << "Info: ��������" << endl;
    }

private:
    T *data;
    int arrCapacity;
    int arrSize;
};

// ���캯��
template<class T>
inline arrayList<T>::arrayList(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream ss;
        ss << "InitialCapacity: " << initialCapacity << " Must be > 0!!!";
        throw illegalParameterValue(ss.str());
    }
    this->arrCapacity = initialCapacity;
    this->data = new T[this->arrCapacity];
    this->arrSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T> &arr) {
    this->arrCapacity = arr.arrCapacity;
    this->data = new T[this->arrCapacity];
    for (int i = 0; i != arr.arrSize; ++i)
        this->data[i] = arr.data[i];
    this->arrSize = arr.arrSize;
}

// ͳһ����
template<class T>
inline void arrayList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex > this->arrSize - 1) {
        std::ostringstream ss;
        ss << "theIndex: " << theIndex << " is Out of Size!!!";
        throw illegalParameterValue(ss.str());
    }
}

template<class T>
void arrayList<T>::changeArr1D(T *&arr, int oldCapacity, int newCapacity) {
    if (newCapacity < 0) {
        std::ostringstream ss;
        ss << "newCapacity: " << newCapacity << " Must be >= 0!!!";
        throw illegalParameterValue(ss.str());
    }

    cout << "Info: ��չ��������Ϊ: " << newCapacity << endl;

    this->arrCapacity = newCapacity;
    T *tmp = new T[this->arrCapacity];
    for (int i = 0; i != oldCapacity; ++i) {
        tmp[i] = arr[i];
    }
    delete[] arr;
    arr = tmp;
}

// 3.����index��ȡԪ��
template<class T>
T &arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);

    return this->data[theIndex];
}

// 4.����Ԫ�ػ�ȡ��һ�γ��ֵ�����
template<class T>
int arrayList<T>::indexOf(T &theElement) const {
    for (int i = 0; i != this->arrSize; ++i) {
        if (this->data[i] == theElement)
            return i;
    }
    return -1;
}

// 5.ɾ������Ϊindex��Ԫ��(�������䣬size-1)
template<class T>
bool arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);

    for (int i = theIndex; i != this->arrSize - 1; ++i)
        this->data[i] = this->data[i + 1];
    --this->arrSize;
    return true;
}

// 6.��Ԫ�ز�����indexλ
template<class T>
bool arrayList<T>::insert(int theIndex, T &theElement) {
    if (theIndex < 0 || theIndex > this->arrSize) {
        std::ostringstream ss;
        ss << "theIndex: " << theIndex << " is Out of Size!!!";
        throw illegalParameterValue(ss.str());
    }

    if (this->arrSize == this->arrCapacity) {
        int capacity_cre = 2;
        changeArr1D(this->data, this->arrCapacity, this->arrCapacity * capacity_cre);
    }

    for (int i = this->arrSize; i != theIndex; --i)
        this->data[i] = this->data[i - 1];
    this->data[theIndex] = theElement;
    ++this->arrSize;
    return true;
}

// 7.׷��Ԫ��
template<class T>
inline void arrayList<T>::push_back(T &theElement) {
    if (this->arrSize == this->arrCapacity) {
        int capacity_cre = 2;
        changeArr1D(this->data, this->arrCapacity, this->arrCapacity * capacity_cre);
    }

    this->data[this->arrSize++] = theElement;
}

// 8.��ʾ����Ԫ��
template<class T>
void arrayList<T>::output(std::ostream &out) const {
    for (int i = 0; i != this->arrSize; ++i) {
        out << this->data[i] << ", ";
    }
}

template<class T>
std::ostream &operator<<(std::ostream &out, const arrayList<T> &arr) {
    arr.output(out);
    return out;
}

// ��ϰ1���ı��ά���鳤��
template<class T>
void changeArr2D(T **&arr, int oldRows, int oldColumns, int newRows, int newColumns) {
    if (newRows <= 0 || newColumns <= 0)
        throw illegalParameterValue("new rows or columns must be >= 0");

    T **tmp = new T *[newRows];
    for (int i = 0; i != newRows; ++i)
        tmp[i] = new T[newColumns];
    for (int i = 0; i != oldRows; ++i) {
        for (int j = 0; j != oldColumns; ++j)
            tmp[i][j] = arr[i][j];
    }

    for (int i = 0; i != oldRows; ++i)
        delete[] arr[i];
    delete[] arr;
    arr = tmp;
}

// ��ϰ5
template<class T>
inline void arrayList<T>::trimToSize() {
    if (this->arrSize >= 1)
        return;

    this->arrSize = 1;
}

// ��ϰ6
template<class T>
void arrayList<T>::setSize(int theSize) {
    if (theSize >= this->arrSize) {
        if (theSize >= this->arrCapacity) {
            int capacity_cre = 2;
            changeArr1D(this->data, this->arrCapacity, this->arrCapacity * capacity_cre);
        }
    }
    this->arrSize = theSize;
}

// ��ϰ7
template<class T>
T &arrayList<T>::operator[](int theIndex) const {
    checkIndex(theIndex);

    return this->data[theIndex];
}

// ��ϰ8
template<class T>
bool arrayList<T>::operator==(const arrayList<T> &arr) const {
    if (this->arrSize != arr.arrSize)
        return false;

    for (int i = 0; i != this->arrSize; ++i)
        if (this->data[i] != arr.data[i])
            return false;

    return true;
}

// ��ϰ9
template<class T>
bool arrayList<T>::operator!=(const arrayList<T> &arr) const {
    if (this->arrSize == arr.arrSize)
        return false;

    for (int i = 0; i != this->arrSize; ++i)
        if (this->data[i] == arr.data[i])
            return false;

    return true;
}

// ��ϰ10
template<class T>
bool arrayList<T>::operator<(const arrayList<T> &arr) const {
    int sizetmp = this->arrSize < arr.arrSize ? this->arrSize : arr.arrSize;
    for (int i = 0; i != sizetmp; ++i)
        if (this->data[i] < arr.data[i])
            return true;

    return sizetmp == this->arrSize;
}

// ��ϰ12
template<class T>
void arrayList<T>::pop_back() {
    --this->arrSize;
}

// ��ϰ13
template<class T>
void arrayList<T>::swap(arrayList<T> &arr) {
    T *tmp = new T[arr.arrCapacity];
    for (int i = 0; i != arr.arrSize; ++i)
        tmp[i] = arr.data[i];
    for (int i = 0; i != this->arrSize; ++i)
        arr.data[i] = this->data[i];
    int tmpSize = arr.arrSize;
    arr.arrSize = this->arrSize;
    this->arrSize = tmpSize;
    delete[] this->data;
    this->data = tmp;
}

// ��ϰ14
template<class T>
void arrayList<T>::reserve(int theCapacity) {
    cout << "capacity: " << this->arrCapacity << endl;
    if (this->arrCapacity < theCapacity) {
        T *tmp = new T[theCapacity];
        for (int i = 0; i != this->arrSize; ++i)
            tmp[i] = this->data[i];
        delete[] this->data;
        this->data = tmp;
        this->arrCapacity = theCapacity;
    }
    cout << "capacity: " << this->arrCapacity << endl;
}

// ��ϰ15
template<class T>
void arrayList<T>::set(int theIndex, const T &theData) {
    checkIndex(theIndex);

    this->data[theIndex] = theData;
}

// ��ϰ17
template<class T>
void arrayList<T>::removeRange(int theStart, int theEnd) {
    checkIndex(theStart);
    checkIndex(theEnd);
    if (theStart >= theEnd)
        throw illegalParameterValue("range is wrong");

    int step = theEnd - theStart;
    for (int i = theStart; i + step != this->arrSize; ++i) {
        this->data[i] = this->data[i + step];
    }
    this->arrSize -= step;
}

// ��ϰ18
template<class T>
int arrayList<T>::lastIndexOf(T &theData) const {
    for (int i = this->arrSize - 1; i >= 0; --i)
        if (this->data[i] == theData) {
            checkIndex(i);
            return i;
        }
    return -1;
}

// ��ϰ22
template<class T>
void arrayList<T>::reverse() {
    for (int i = 0; i != (this->arrSize - 1) / 2; ++i) {
        T tmp = this->data[i];
        this->data[i] = this->data[this->arrSize - i - 1];
        this->data[this->arrSize - i - 1] = tmp;
    }
}

// ��ϰ23
template<class T>
void arrayList<T>::leftShift(int offset) {
    T *tmp = new T[this->arrSize - offset];
    int j = 0;
    for (int i = offset; i != this->arrSize; ++i) {
        tmp[j++] = this->data[i];
    }
    delete[] this->data;
    this->data = tmp;
    this->arrSize -= offset;
}

// ��ϰ24
template<class T>
void arrayList<T>::circularShift(int offset) {
    if (this->arrSize < offset) {
        illegalParameterValue("offset Must be >= arrSize!");
    }
    while (offset--) {
        T tmp = this->data[0];
        for (int i = 0; i != this->arrSize - 1; ++i) {
            this->data[i] = this->data[i + 1];
        }
        this->data[this->arrSize - 1] = tmp;
    }
}

// ��ϰ25
template <class T>
void arrayList<T>::half() {
    int newSize = (this->arrSize + 1) / 2;
    T *tmp = new T[newSize];
    int j = 0;
    for(int i = 0; i != this->arrSize; ++i){
        if(i % 2 == 0){
            tmp[j++] = this->data[i];
        }
    }
    delete[] this->data;
    this->data = tmp;
    this->arrSize = newSize;
}

#endif //CLION_CPP_ARRAYLIST_H
