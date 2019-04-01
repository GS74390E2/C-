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

    template<class T>
    void permutations(T *list, int begin, int end) {
        if (begin == end) {
            copy(list, list + end + 1, ostream_iterator<T>(cout, ""));
            cout << endl;
        } else {
            for (int i = begin; i <= end; ++i) {
                swap(list[begin], list[i]);
                permutations(list, begin + 1, end);
                swap(list[begin], list[i]);
            }
        }
    }
}

namespace MATCHEDPAIRS {
    // 输出给定字符串中左右匹配的括号
    void printMatchedPairs(string expr) {
        // 利用栈，把从左到右的左括号压入栈，每有一个右括号则弹出一个，剩余为不匹配
        arrayStack<int> as;
        int length = static_cast<int>(expr.size());

        for (int i = 0; i != length; ++i) {
            if (expr[i] == '(')
                as.push(i);
            else if (expr[i] == ')')
                try {
                    cout << as.top() << " " << i << endl;
                    as.pop();
                } catch (stackEmpty &e) {
                    cout << "No match for right parenthesis" << " at " << i << endl;
                }
        }
        while (!as.empty()) {
            cout << "No match for left parenthesis at " << as.top() << endl;
            as.pop();
        }
    }
}

namespace HANOI {
    void towersOfHanoi(int n, char x, char y, char z) {
        // y作为中转
        if (n > 0) {
            towersOfHanoi(n - 1, x, z, y);
            cout << "Move top disk from tower " << x << " to top of tower " << z << endl;
            towersOfHanoi(n - 1, y, x, z);
        }
    }
}

namespace RAILROAD {
    arrayStack<int> *track;             // 缓冲轨道
    int numberOfCars, numberOfTracks;   // 车厢数、缓冲轨道数
    int smallestCar, itsTrack;          // 最小编号的车厢、对应的缓冲轨道

    // 将车厢移出缓冲轨道
    void outputFromHoldingTrack();

    // 将车厢移入缓冲轨道
    bool putinHoldingTrack(int c);

    // 重排车厢
    bool railroad(int inputorder[], int theNumberOfCars, int theNumberOfTracks) {
        numberOfCars = theNumberOfCars;
        numberOfTracks = theNumberOfTracks;

        // 缓冲轨道数编号从1开始
        track = new arrayStack<int>[numberOfTracks + 1];
        int nextCarToOutput = 1;
        smallestCar = nextCarToOutput + 1;

        for (int i = 0; i != theNumberOfCars; ++i) {
            if (inputorder[i] == nextCarToOutput) {
                cout << "Move car " << inputorder[i] << " from input track to output track" << endl;
                ++nextCarToOutput;
                // 从缓冲轨道移到出轨道
                while (smallestCar == nextCarToOutput) {
                    outputFromHoldingTrack();
                    ++nextCarToOutput;
                }
            } else if (!putinHoldingTrack(inputorder[i]))
                return false;
        }
        return true;
    }

    void outputFromHoldingTrack() {
        // cout << "[INFO]: itstrack " << itsTrack << endl;
        // cout << "[INFO]: smallestCar " << smallestCar << endl;
        // cout << "[INFO]: 1" << track[2].size() << endl;
        track[itsTrack].pop();
        cout << "Move car " << smallestCar << " from holding track " << itsTrack << " to output track" << endl;

        // 检查所有栈顶，寻找编号最小的车厢和所属栈
        smallestCar = numberOfCars + 2;
        for (int i = 1; i <= numberOfTracks; ++i)
            if (!track[i].empty() && (track[i].top() < smallestCar)) {
                smallestCar = track[i].top();
                itsTrack = i;
            }
    }

    bool putinHoldingTrack(int c) {
        int bestTrack = 0, bestTop = numberOfCars + 1;

        // 扫描缓冲轨道
        for (int i = 1; i <= numberOfTracks; ++i) {
            if (!track[i].empty()) {
                int topCar = track[i].top();
                if (c < topCar && topCar < bestTop) {
                    bestTop = topCar;
                    bestTrack = i;
                }
            } else {
                if (bestTrack == 0) bestTrack = i;
            }
        }
        if (bestTrack == 0)
            return false;
        // 把车厢c移入轨道bestTrack
        track[bestTrack].push(c);
        cout << "Move car " << c << " from input track to the holding track " << bestTrack << endl;
        if (c <= smallestCar) {
            smallestCar = c;
            itsTrack = bestTrack;
        }
        return true;
    }
}

namespace ROUTABLEBOX {
    bool checkbox(int net[], int n) {
        // n是管脚数，net是管脚组数

        arrayStack<int> *s = new arrayStack<int>(n);

        for (int i = 0; i < n; ++i) {
            if (!s->empty())
                if (net[i] == net[s->top()])
                    s->pop();
                else
                    s->push(i);
            else s->push(i);
        }
        if(s->empty()){
            cout << "Switch box is routable" << endl;
            return true;
        }
        cout << "Switch box is not routable" << endl;
        return false;
    }
}

namespace EQCLASS{
    void eqClass(){
        int n, r;
        cout << "Enter number of elements" << endl;
        cin >> n;   // 输入元素个数
        if(n < 2){
            cout << "Too few elements" << endl;
            return;
        }
        cout << "Enter number of relations" << endl;
        cin >> r;   // 输入关系个数
        if(r < 1){
            cout << "Too few relations" << endl;
            return;
        }

        // 建立空栈组成的数组，1~n
        arrayStack<int> *list = new arrayStack<int>[n + 1];
        int a, b;
        for(int i = 1; i <= r; ++i){
            cout << "Enter the relation/pair" << endl;
            cin >> a >> b;
            list[a].push(b);
            list[b].push(a);
        }

        // 初始化以输出等价类
        arrayStack<int> unprocessedList;
        bool *out = new bool[n + 1];
        for(int i = 1; i <= n; ++i)
            out[i] = false;

        // 输出等价类
        for(int i = 1; i <= n; ++i) {
            if (!out[i]) {
                cout << "Next class is: " << i << " ";
                out[i] = true;
                unprocessedList.push(i);
                while (!unprocessedList.empty()) {
                    int j = unprocessedList.top();
                    unprocessedList.pop();

                    while (!list[j].empty()) {
                        int q = list[j].top();
                        list[j].pop();
                        if (!out[q]) {
                            cout << q << " ";
                            out[q] = true;
                            unprocessedList.push(q);
                        }
                    }
                }
                cout << endl;
            }
        }
        cout << "End of list of equivalence classses" << endl;
    }
}

void test01() {
    arrayStack<int> s;
    for (int i = 0; i != 10; ++i)
        s.push(i);
    cout << s.size() << endl;
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
}

void ex_test() {
    arrayStack<int> s;
    s.inputStack();
    cout << "size: " << s.size() << endl;
    cout << "top: " << s.top() << endl;
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

void test02() {
    chainNode<int> cn;
    linkedStack<int> ls;
    for (int i = 0; i != 10; ++i)
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

    // test02();

    // string expr("(a+b))(");
    // MATCHEDPAIRS::printMatchedPairs(expr);

    // HANOI::towersOfHanoi(3, 'x', 'y', 'z');

    // int inputOrder[9] = {3, 6, 9, 2, 4, 7, 1, 8, 5};
    // try {
    //     RAILROAD::railroad(inputOrder, 9, 3);
    // } catch (stackEmpty &e) {
    //     e.what();
    // }

    EQCLASS::eqClass();
}
