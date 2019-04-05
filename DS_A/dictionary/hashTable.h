//
// Created by G.Q on 2019/4/5.
//

#ifndef CLION_CPP_HASHTABLE_H
#define CLION_CPP_HASHTABLE_H

#include "hash.h"
#include "../MyException.h"

template<class K, class V>
class hashTable {
    hashTable(int theDivisor = 11);

    ~hashTable();

    bool empty() const { return this->dSize == 0; }

    int size() const { return this->dSize; }

    std::pair<K, V> *find(const K &theKey) const;

    void insert(const std::pair<const K, V> &thePair);


protected:
    int search(const K &theKey) const;

    std::pair<const K, V> **table;  // 散列表，一维数组，元素为对组指针
    hash<K> hash;
    int dSize;
    int divisor;
};

template<class K, class V>
hashTable<K, V>::hashTable(int theDivisor) {
    this->divisor = theDivisor;
    this->dSize = 0;

    this->table = new std::pair<const K, V> *[this->divisor];
    for (int i = 0; i != this->divisor; ++i)
        table[i] = nullptr;
}

template<class K, class V>
int hashTable<K, V>::search(const K &theKey) const {
    int i = static_cast<int>(this->hash(theKey) % this->divisor);
    int j = i;
    do {
        if (this->table[i] == nullptr || this->table[j]->first == theKey)
            return j;
        j = (j + 1) % this->divisor;
    } while (j != i);

    return j;
}

template<class K, class V>
std::pair<K, V> *hashTable<K, V>::find(const K &theKey) const {
    int b = this->search(theKey);

    if (this->table == nullptr || this->table[b]->first != theKey)
        return nullptr;

    return this->table[b];
}

template<class K, class V>
void hashTable<K, V>::insert(const std::pair<const K, V> &thePair) {
    int b = this->search(thePair.first);

    if (this->table[b] == nullptr) {
        this->table[b] = new std::pair<const K, V>(thePair);
        ++this->dSize;
    } else {
        if (this->table[b]->first == thePair.first) {
            this->table[b]->second = thePair.second;
        } else
            throw hashTableFull();
    }
}

template<class K, class V>
hashTable<K, V>::~hashTable() {
    for (int i = 0; i != this->divisor; ++i) {
        if (this->table[i] != nullptr)
            delete &(this->table[i]);
    }
    delete[] this->table;
}

#endif //CLION_CPP_HASHTABLE_H
