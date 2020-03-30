#include <iostream>
#include "BTreeNode.h"
#include "BTree.h"

using namespace std;
using namespace DTLib;

int main()
{
    BTree<int> bt;
    BTreeNode<int> *n = nullptr;

    bt.insert(1, nullptr);

    n = bt.find(1);
    bt.insert(2, n);
    bt.insert(3, n);

    n = bt.find(2);
    bt.insert(4, n);
    bt.insert(5, n);

    n = bt.find(4);
    bt.insert(8, n);
    bt.insert(9, n);

    n = bt.find(5);
    bt.insert(10, n);

    n = bt.find(3);
    bt.insert(6, n);
    bt.insert(7, n);

    SharedPointer< DynamicArray<int> > tr = bt.traversal(LevelOrder);

    for(int i=0; i<tr->length(); i++)
    {
        cout << (*tr)[i] << " ";
    }

    cout << endl;

    cout << endl;

    BTreeNode<int>* head = bt.thread(LevelOrder);

    while( head != nullptr )
    {
        cout << head->value << " ";
        head = head->right;
    }

    return 0;
}

