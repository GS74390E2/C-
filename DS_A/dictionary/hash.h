//
// Created by G.Q on 2019/4/5.
//

#ifndef CLION_CPP_HASH_H
#define CLION_CPP_HASH_H

#include <iostream>
#include <string>

template<class K>
class hash;

template<>
class hash<std::string> {
public:
    size_t operator()(const std::string theKey) const {
        // 把关键字转换为一个hash值
        unsigned long hashValue = 0;
        int length = static_cast<int>(theKey.length());
        for (int i = 0; i != length; ++i)
            hashValue += 5 * hashValue + theKey.at(i);

        return size_t(hashValue);
    }
};

template<>
class hash<int> {
public:
    size_t operator()(const int theKey) const {
        return size_t(theKey);
    }
};

template<>
class hash<long> {
public:
    size_t operator()(const long theKey) const {
        return size_t(theKey);
    }
};

#endif //CLION_CPP_HASH_H
