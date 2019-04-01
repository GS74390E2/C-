//
// Created by G.Q on 2019/3/21.
//

#include "arrayList.h"


void test01() {
    cout << "testing one start..." << endl;
    try {
        LinearList<int> *err_list = new arrayList<int>(-1);
    } catch (illegalParameterValue &e) {
        e.outputMessage();
    }

    LinearList<int> *list = new arrayList<int>;

    if (list->isEmpty()) {
        cout << "Info: 表为空" << endl;
        cout << "Info: 表大小" << list->size() << endl;
    }

    cout << "****************************" << endl;
    for (int i = 0; i != 11; ++i) {
        try {
            list->push_back(i);
            cout << "Info: 表大小" << list->size() << endl;
        }
        catch (illegalParameterValue &e) {
            e.outputMessage();
        }
    }
    list->output(cout);

    cout << "****************************" << endl;
    try {
        int theElement = 21;
        list->insert(-1, theElement);
    }catch (illegalParameterValue &e){
        e.outputMessage();
    }
    int theElement = 21;
    if(list->insert(3, theElement)){
        cout << "Info: 插入 " << theElement << endl;
        cout << "Info: " << theElement << " is " << list->indexOf(theElement) << endl;
    }

    cout << "****************************" << endl;
    int del_theIndex = 11;
    if(list->erase(del_theIndex)){
        cout << "Info: 删除成功" << endl;
        list->output(cout);
    }

    delete list;
    list = nullptr;
}

void test02(){
    cout << "testing two start... (special data)" << endl;
    typedef ARR::DATA arrNode;
    arrNode node1(1, "gjy");
    arrNode node2(2, "dc");
    arrNode node3(3, "crm");
    arrNode node4;
    arrNode node5(4, "jjc");

    arrayList<arrNode> arr;

    arr.push_back(node1);
    arr.push_back(node2);
    arr.push_back(node3);
    arr.push_back(node4);
    arr.push_back(node5);
    cout << "Info : 表的大小 " << arr.size() << endl;
    cout << arr << endl;

    cout << "****************************" << endl;
    arrNode node6(5, "tzj");
    arr.insert(5, node6);
    cout << "Info: new node index is " << arr.indexOf(node6) << endl;
    arr.erase(3);
    cout << "Info: new node index is " << arr.indexOf(node6) << endl;
    cout << arr << endl;

}

void ex_test01(){
    int **arr = new int*[2];
    for(int i = 0; i != 2; ++i)
        arr[i] = new int[2];
    for(int i = 0; i != 2; ++i)
        for(int j = 0; j != 2; ++j)
            arr[i][j] = 1;
    for(int i = 0; i != 2; ++i)
        for(int j = 0; j != 2; ++j)
            cout << arr[i][j] << " ";

    cout << "***************" << endl;

    changeArr2D(arr, 2, 2, 3, 4);

    for(int i = 0; i != 3; ++i)
        for(int j = 0; j != 4; ++j)
            arr[i][j] = 2;

    for(int i = 0; i != 3; ++i)
        for(int j = 0; j != 4; ++j)
            cout << arr[i][j] << " ";
}

void ex_test02(){
    arrayList<int> arr;
    arr.trimToSize();
    cout << "Info : 表的大小 " << arr.size() << endl;
    cout << arr << endl;

    cout << "****************************" << endl;
    arr.setSize(3);
    cout << "Info : 表的大小 " << arr.size() << endl;
    cout << arr << endl;

    cout << "****************************" << endl;
    int theElement = 1;
    arr.push_back(theElement);
    cout << arr[3] << endl;

    cout << "****************************" << endl;
    arrayList<int> arrtmp;
    int eleTmp = 2;
    arrtmp.push_back(eleTmp);
    if(arr == arrtmp)
        cout << "arr == arrtmp" << endl;
    else
        cout << "arr != arrtmp" << endl;

    cout << "****************************" << endl;
    cout << "Info : 表的大小 " << arr.size() << endl;
    cout << arr << endl;
    arr.pop_back();
    cout << "Info : 表的大小 " << arr.size() << endl;
    cout << arr << endl;

    cout << "****************************" << endl;
    cout << "arr: " << arr << endl;
    cout << "arrtmp: " << arrtmp << endl;
    arr.swap(arrtmp);
    cout << "Info : 表的大小 " << arr.size() << endl;
    cout << "arr: " << arr << endl;
    cout << "arrtmp: " << arrtmp << endl;

    cout << "****************************" << endl;
    arr.reserve(11);
    arr.set(0, 11);
    cout << arr << endl;

    cout << "****************************" << endl;
    int eleTmp1 = 3;
    int eleTmp2 = 4;
    int eleTmp3 = 5;
    int eleTmp4 = 6;
    int eleTmp5 = 3;
    arr.push_back(eleTmp1);
    arr.push_back(eleTmp2);
    arr.push_back(eleTmp3);
    arr.push_back(eleTmp4);
    cout << arr << endl;
    arr.removeRange(2, 4);
    cout << arr << endl;

    cout << "****************************" << endl;
    arr.push_back(eleTmp5);
    cout << arr << endl;
    cout << "index: " << arr.lastIndexOf(eleTmp5) << endl;
}

void ex_test03(){
    arrayList<int> arr;
    for(int i = 0; i != 10; ++i)
        arr.push_back(i);

    cout << arr << endl;
    arr.reverse();
    cout << arr << endl;

    cout << "****************************" << endl;
    arr.leftShift(3);
    cout << "Info : 表的大小 " << arr.size() << endl;
    cout << arr << endl;

    cout << "****************************" << endl;
    arr.circularShift(2);
    cout << arr << endl;

    cout << "****************************" << endl;
    arr.half();
    cout << arr << endl;
}

int main() {
    // test01();
    // test02();

    // ex_test01();

    // ex_test02();

    ex_test03();
    return 0;
}
