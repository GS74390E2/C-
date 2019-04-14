//
// Created by G.Q on 2019/4/11.
//

#include "maxHeap.h"

using std::cout;
using std::endl;

void test() {
    maxHeap<int> m1;
    for (int i = 0; i != 10; ++i) {
        m1.push(i);
    }
    m1.output();
    m1.pop();
    m1.output();
}

int main() {
    test();
}

