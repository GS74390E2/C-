/*
 * 抽象类
 */

#ifndef CLION_CPP_GRAPH_H
#define CLION_CPP_GRAPH_H

#include "edge.h"
#include "vertexIterator.h"

template<class T>
class graph {
public:
    virtual ~graph() {}

    // 返回图的顶点数
    virtual int numberOfVertices() const = 0;

    // 返回图的边数
    virtual int numberOfEdges() const = 0;

    // 如果边存在返回true
    virtual bool existsEdge(int, int) const = 0;

    // 插入边
    virtual void insertEdge(edge<T> *) = 0;

    // 删除边
    virtual void eraseEdge(int, int) = 0;

    // 返回顶点的度
    virtual int degree(int) const = 0;

    // 有向图：入度
    virtual int inDegree(int) const = 0;

    // 有向图：出度
    virtual int outDegree(int) const = 0;

    // 有向图：返回值为true
    virtual bool directed() const = 0;

    // 加权图：返回值为true
    virtual bool weighted() const = 0;

    // 访问指定顶点的相邻顶点
    virtual vertexIterator<T> *iterator(int) = 0;

};

#endif //CLION_CPP_GRAPH_H
