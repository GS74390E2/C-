//
// Created by G.Q on 2019/4/5.
//

#ifndef CLION_CPP_HASHCHAIN_H
#define CLION_CPP_HASHCHAIN_H

#include <iostream>
#include "Dictionary.h"
#include "sortedChain.h"
#include "hash.h"

// 链式描述
template<class K, class V>
class hashChain : public Dictionary<K, V> {
public:
    hashChain(int theDivisor = 11) {
        this->divisor = theDivisor;
        this->dSize = 0;

        this->table = new sortedChain<K, V>[this->divisor];
    }

    ~hashChain() { delete[] this->table; }

    bool empty() const { return this->dSize == 0; }

    int size() const { return this->dSize; }

    std::pair<const K, V> *find(const K &theKey) const {
        return this->table[this->hash(theKey) % this->divisor].find(theKey);
    }

    void erase(const K &theKey) {
        this->table[this->hash(theKey) % this->divisor].erase(theKey);
    }

    void insert(const std::pair<const K, V> &thePair) {
        int homeBucket = static_cast<int>(this->hash(thePair.first) % this->divisor);
        int homeSize = this->table[homeBucket].size();

        this->table[homeBucket].insert(thePair);
        if (this->table[homeBucket].size() > homeSize)
            ++this->dSize;
    }


private:
    sortedChain<K, V> *table;
    hash<K> hash;
    int dSize;
    int divisor;
};

#endif //CLION_CPP_HASHCHAIN_H
