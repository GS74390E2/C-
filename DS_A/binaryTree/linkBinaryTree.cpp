//
// Created by G.Q on 2019/4/11.
//

#include "linkBinaryTree.h"
#include "binaryTreeNode.h"

using std::cout;
using std::endl;

int main() {
    linkBinaryTree<char> tree1, tree2, tree3, tree4;
    tree1.makeTree('A', tree4, tree4);
    tree2.makeTree('B', tree4, tree4);
    tree3.makeTree('C', tree1, tree2);
    tree1.makeTree('D', tree3, tree4);
    tree1.preOrderOutput();
    cout << endl;
    tree1.inOrderOutput();
    cout << endl;
    tree1.postOrderOutput();
    cout << endl;
    cout << tree1.size() << endl;

    cout << tree1.treeHeight() << endl;
    return 0;

}
