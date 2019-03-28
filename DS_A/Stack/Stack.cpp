//
// Created by G.Q on 2019/3/28.
//

#include "derivedArrayStack.h"
#include "linkStack.h"

namespace RSUM {
    template<class T>
    T rSum(T *a, int n) {
        // 终止条件 n = 0
        if (n == 0)
            return 0;
        return a[n - 1] + rSum(a, n - 1);
    }

    template<class T>
    T factorial(T n) {
        // 终止条件 n = 1
        if (n == 1)
            return 1;
        return n * factorial(n - 1);
    }

    template <class T>
    void permutations(T *list, int begin, int end){
        if(begin == end){
            copy(list, list + end + 1, ostream_iterator<T>(cout, ""));
            cout << endl;
        }
        else{
            for(int i = begin; i <= end; ++i){
                swap(list[begin], list[i]);
                permutations(list, begin+1, end);
                swap(list[begin], list[i]);
            }
        }
    }
}

void test01(){
    arrayStack<int> s;
    for(int i = 0; i != 10; ++i)
        s.push(i);
    cout << s.size() << endl;
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
}

void ex_test(){
    arrayStack<int> s;
    s.inputStack();
    cout << "size: " << s.size() << endl;
    cout << "top: " << s. top() << endl;
    s.outputStack();
    cout << endl;

    cout << "*********************************" << endl;
    arrayStack<int> stmp = s.splitStack();
    stmp.outputStack();
    cout << "size1: " << stmp.size() << endl;
    s.outputStack();
    cout << "size2: " << s.size() << endl;

    cout << "***********************************" << endl;
    s.expandStack(stmp);
    s.outputStack();
    cout << endl;
}

void test02(){
    chainNode<int> cn;
    linkedStack<int> ls;
    for(int i = 0; i != 10; ++i)
        ls.push(i);
    cout << ls.top() << endl;
    ls.pushNode(&cn);
    cout << ls.top() << endl;

    cout << ls.popNode().element << endl;
    cout << ls.popNode().element << endl;
}


int main() {
    // test01();

    // ex_test();

    test02();
}
