/*
 * 图顶点的迭代器
 */

#ifndef CLION_CPP_VERTEXITERATOR_H
#define CLION_CPP_VERTEXITERATOR_H

template<class T>
class vertexIterator {
public:
    virtual ~vertexIterator() {}

    // 返回一个只想顶点的相邻顶点
    virtual int next() = 0;

    // 加权图，设置权值
    virtual int next(T &) = 0;
};

#endif //CLION_CPP_VERTEXITERATOR_H
