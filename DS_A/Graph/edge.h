/*
 * 模板类，提供方法返回一个边的第一个顶点、第二个顶点和权
 */

#ifndef CLION_CPP_EDGE_H
#define CLION_CPP_EDGE_H

template<class T>
class edge {
public:
    virtual ~edge() {}

    virtual int vertex1() const = 0;

    virtual int vertex2() const = 0;

    virtual T weight() const = 0;
};

#endif //CLION_CPP_EDGE_H
