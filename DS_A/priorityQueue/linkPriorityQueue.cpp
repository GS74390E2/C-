//
// Created by G.Q on 2019/4/10.
//

#include "linkPriorityQueue.h"

using std::cout;
using std::endl;

void test_structure() {
    LINK::DATA<int> d1(0, 1, nullptr);
    LINK::DATA<int> d2(1, 3, nullptr);
    LINK::DATA<int> d3(2, 2, nullptr);
    cout << d1 << endl;

    // 构造函数测试
    linkPriorityQueue<LINK::DATA<int>> l1;
    linkPriorityQueue<LINK::DATA<int>> l2(d1);
    l2.output();
    linkPriorityQueue<LINK::DATA<int>> l3(l2);
    l3.output();
    l3.push(d2);
    l3.push(d3);
    l3.output();

    cout << l3.top() << endl;
    l3.pop();
    cout << l3.top() << endl;
    l3.pop();
    cout << l3.top() << endl;

}

int main() {
    test_structure();
    return 0;

}
