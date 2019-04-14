//
// Created by G.Q on 2019/4/10.
//

#include "arrayPriorityQueue.h"
#include "maxPriorityQueue.h"

using std::cout;
using std::endl;

void test_structure() {
    // 结点构造函数测试
    ARRAY::DATA<int> d1(0, 1);
    ARRAY::DATA<int> d2 = d1;
    ARRAY::DATA<int> d3(1);
    cout << d1 << endl;
    cout << d2 << endl;
    cout << d3 << endl;

    // 优先级队列构造函数测试
    arrayPriorityQueue<ARRAY::DATA<int>> a1(d1, 1);
    arrayPriorityQueue<ARRAY::DATA<int>> a2;
    a2.output();
    a2 = a1;
    a2.output();
    arrayPriorityQueue<ARRAY::DATA<int>> a3(a2);
    a3.output();
    a1.output();
    maxPriorityQueue<ARRAY::DATA<int>> *m = new arrayPriorityQueue<ARRAY::DATA<int>>(d3);
    cout << m->size() << endl;
    delete m;
    m = nullptr;
}

void test_func() {
    ARRAY::DATA<int> d1(0, 1);
    arrayPriorityQueue<ARRAY::DATA<int>> a1(d1, 1);
    a1.output();
    ARRAY::DATA<int> d2(0, 2);
    ARRAY::DATA<int> d3(1, 1);
    ARRAY::DATA<int> d4(2, 4);
    ARRAY::DATA<int> d5(4, 7);
    a1.push(d2);
    a1.push(d3);
    a1.push(d4);
    a1.push(d5);
    a1.output();
    cout << a1.top() << endl;
    a1.pop();
    cout << a1.top() << endl;
}

int main() {
    // test_structure();
    test_func();
    return 0;
}
