//
// Created by G.Q on 2019/4/19.
//

#ifndef CLION_CPP_WEIGHTEDEDGE_H
#define CLION_CPP_WEIGHTEDEDGE_H

#include "edge.h"

template<class T>
class weightedEdge : public edge<T> {
public:
    weightedEdge() {}

    weightedEdge(int theV1, int theV2, T theW) {
        v1 = theV1;
        v2 = theV2;
        w = theW;
    }

    ~weightedEdge() {}

    int vertex1() const { return v1; }

    int vertex2() const { return v2; }

    T weight() const { return w; }

private:
    int v1, v2;
    T w;
};

#endif //CLION_CPP_WEIGHTEDEDGE_H
