//
// Created by G.Q on 2019/4/14.
//

#include "binarySearchTree.h"

using std::pair;
using std::cout;
using std::endl;

int main() {
    binarySearchTree<int, char> y;
    y.insert(pair<int, char>(1, 'a'));
    y.insert(pair<int, char>(6, 'c'));
    y.insert(pair<int, char>(4, 'b'));
    y.insert(pair<int, char>(8, 'd'));
    cout << "Elements in ascending order are" << endl;
    y.ascend();

    pair<const int, char> *s = y.find(4);
    cout << "Search for 4 succeeds " << endl;
    cout << s->first << ' ' << s->second << endl;
    y.erase(4);
    cout << "4 deleted " << endl;
    cout << "Elements in ascending order are" << endl;
    y.ascend();
    return 0;
}
