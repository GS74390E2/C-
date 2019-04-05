//
// Created by G.Q on 2019/4/4.
//

#ifndef CLION_CPP_DICTIONARY_H
#define CLION_CPP_DICTIONARY_H

#include <iostream>

template<class K, class V>
class Dictionary {
public:
    virtual ~Dictionary() {}

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual std::pair<const K, V> *find(const K &) const = 0;

    virtual void erase(const K &theKey) = 0;

    virtual void insert(const std::pair<const K, V> &) = 0;

};


#endif //CLION_CPP_DICTIONARY_H
