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

    for (bt.begin(); !bt.end(); bt.next())
    {
        cout << bt.current() << " ";
    }

    cout << endl;

    SharedPointer<DynamicArray<int>> sp1 = bt.traversal(PreOrder);
    for (int i=0; i<(*sp1).length(); ++i)
    {
        cout << (*sp1)[i] << " ";
    }

    cout << endl;

    SharedPointer<DynamicArray<int>> sp2 = bt.traversal(InOrder);
    for (int i=0; i<(*sp2).length(); ++i)
    {
        cout << (*sp2)[i] << " ";
    }

    cout << endl;

    SharedPointer<DynamicArray<int>> sp3 = bt.traversal(PostOrder);
    for (int i=0; i<(*sp3).length(); ++i)
    {
        cout << (*sp3)[i] << " ";
    }

    cout << endl;

    return 0;
}

