//
// Created by G.Q on 2019/4/2.
//

#include "arrayQueue.h"

void test01(){
    arrayQueue<int> q;
    for(int i = 0; i != 9; ++i)
        q.push(i);
    cout << q << endl;
    while(!q.empty()){
        q.pop();
        cout << q << endl;
    }
}

int main(){
    test01();
}
