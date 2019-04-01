//
// Created by G.Q on 2019/3/21.
//

#include "linkList.h"

void test(){
    typedef linkList::linkNode Node;
    Node node1(1, "gjy");
    Node node2(2, "dc");
    Node node3(3, "crm");
    Node node4(4, "jjc");
    Node node5;

    linkList link;
    if(link.isEmpty()){
        cout << "Info : 表长 " << link.size() << endl;
    }

    cout << "*********************" << endl;
    link.add(node1);
    link.add(node2);
    link.add(node3);
    link.add(node4);
    link.add(node5);
    cout << "Info : 表长 " << link.size() << endl;

    cout << "*********************" << endl;
    Node node6(5, "tzj");
    cout << link << endl;

    cout << "*********************" << endl;
    link.insert(2, node6);
    cout << link << endl;
    cout << "Info : 表长 " << link.size() << endl;

    cout << "*********************" << endl;
    try {
        link.erase(5);
    }catch (illegalParameterValue &e){
        e.outputMessage();
    }
    cout << link << endl;
    cout << "Info : 表长 " << link.size() << endl;
}



int main(){
    test();
    return 0;
}
