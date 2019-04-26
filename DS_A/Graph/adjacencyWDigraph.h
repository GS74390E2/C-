/*
 * 加权有向图（邻接矩阵）
 */

#ifndef CLION_CPP_ADJACENCYWDGRAPH_H
#define CLION_CPP_ADJACENCYWDGRAPH_H

#include <iostream>
#include "graph.h"


template<class T>
T **make2dArray(T **&a, int row, int col) {
    a = new T *[row];
    for (int i = 0; i != row; ++i)
        a[i] = new T[col];

    return a;
}

template<class T>
void delete2dArray(T **&a, int row) {
    for (int i = 0; i != row; ++i)
        delete[] a[i];
    delete[] a;
}

template<class T>
class adjacencyWDigraph : public graph<T> {
protected:
    int n;      // 顶点个数
    int e;      // 边的个数
    T **a;      // 邻接数组
    T noEdge;   // 表示不存在的边
public:
    adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0) {
        // 构造函数
        if (numberOfVertices < 0) {
            std::cerr << "number of vertices must be >= 0";
            exit(1);
        }
        this->n = numberOfVertices;
        this->e = 0;
        this->noEdge = theNoEdge;
        make2dArray(this->a, this->n + 1, this->n + 1);
    }

    virtual ~adjacencyWDigraph() { delete2dArray(this->a, this->n + 1); }

    int numberOfVertices() const { return n; }

    int numberOfEdges() const { return e; }

    bool directed() const { return true; }

    bool weighted() const { return true; }

    bool existsEdge(int i, int j) const {
        return !(i < 1 || j < 1 || i > n || j > n || a[i][j] == noEdge);
    }

    void insertEdge(edge<T> *theEdge) {
        int v1 = theEdge->vertex1();
        int v2 = theEdge->vertex2();
        if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2) {
            std::cerr << "is not a permissible edge";
            exit(1);
        }

        if (a[v1][v2] == noEdge)
            ++e;
        a[v1][v2] = theEdge->weight();
    }

    void eraseEdge(int i, int j) {
        if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge) {
            a[i][j] = noEdge;
            --e;
        }
    }

    void checkVertex(int theVertex) const {
        if (theVertex < 1 || theVertex > n) {
            std::cerr << "no vertex";
            exit(1);
        }
    }

    int degree(int theVertex) const {
        std::cerr << "degree undefined";
        exit(1);
    }

    int outDegree(int theVertex) const {
        checkVertex(theVertex);

        int sum = 0;
        for (int j = 1; j <= n; ++j)
            if (a[theVertex][j] != noEdge)
                ++sum;
        return sum;
    }

    int inDegree(int theVertex) const {
        checkVertex(theVertex);

        int sum = 0;
        for (int j = 1; j <= n; ++j)
            if (a[j][theVertex] != noEdge)
                ++sum;
        return sum;
    }

    class myIterator : public vertexIterator<T> {
    public:
        myIterator(T *theRow, T theNoEdge, int numberOfVertices) {
            row = theRow;
            noEdge = theNoEdge;
            n = numberOfVertices;
            currentVertex = 1;
        }

        ~myIterator() {}

        int next(T &theWeight) {
            for (int j = currentVertex; j <= n; ++j)
                if (row[j] != noEdge) {
                    currentVertex = j + 1;
                    theWeight = row[j];
                    return j;
                }
            currentVertex = n + 1;
            return 0;
        }

        int next() {
            for (int j = currentVertex; j <= n; ++j)
                if (row[j] != noEdge) {
                    currentVertex = j + 1;
                    return j;
                }
            currentVertex = n + 1;
            return 0;
        }

    protected:
        T *row;
        T noEdge;
        int n;
        int currentVertex;
    };

    myIterator *iterator(int theVertex) {
        checkVertex(theVertex);
        return new myIterator(a[theVertex], noEdge, n);
    }


};


#endif //CLION_CPP_ADJACENCYWDGRAPH_H
