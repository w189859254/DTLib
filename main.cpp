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

    cout << "Original: " << endl;
    for (bt.begin(); !bt.end(); bt.next())
    {
        cout << bt.current() << " ";
    }

    cout << endl;

    SharedPointer<BTree<int>> sp = bt.clone();

    cout << "Clone: " << endl;
    for (sp->begin(); !sp->end(); sp->next())
    {
        cout << sp->current() << " ";
    }

    cout << endl;
    cout << endl;

    cout << "bt == *sp : " << (bt == *sp) << endl;
    cout << "bt != *sp : " << (bt != *sp) << endl;

    cout << endl;

    BTree<int> nbt;

    nbt.insert(0, nullptr);
    n = nbt.find(0);
    nbt.insert(6, n);
    nbt.insert(2, n);

    n = nbt.find(2);
    nbt.insert(7, n);
    nbt.insert(8, n);

    SharedPointer<BTree<int>> r = bt.add(nbt);

    cout << "Add: " << endl;
    for (r->begin(); !r->end(); r->next())
    {
        cout << r->current() << " ";
    }

    return 0;
}

