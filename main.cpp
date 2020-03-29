#include <iostream>
#include "GTree.h"

using namespace std;
using namespace DTLib;

int main()
{
    GTree<char> t;
    GTreeNode<char> *node = nullptr;

    t.insert('A', nullptr);

    node = t.find('A');
    t.insert('B', node);
    t.insert('C', node);
    t.insert('D', node);

    node = t.find('B');
    t.insert('E', node);
    t.insert('F', node);

    node = t.find('E');
    t.insert('K', node);
    t.insert('L', node);

    node = t.find('C');
    t.insert('G', node);

    node = t.find('D');
    t.insert('H', node);
    t.insert('I', node);
    t.insert('J', node);

    node = t.find('H');
    t.insert('M', node);

    for(t.begin(); !t.end(); t.next())
    {
        cout << t.current() << " ";
    }

    return 0;
}

