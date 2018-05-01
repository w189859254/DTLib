#include <iostream>
#include "LinkList.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;

int main()
{
    LinkList<int> list;

    for(int i=0; i<5; i++)
    {
        list.insert(0, i);
        list.set(0, i*i);
    }

    for(int i=0; i<list.length(); i++)
    {
        int v = 0;

        list.get(i, v);

        cout << v << endl;
    }

    list.remove(2);
    for(int i=0; i<list.length(); i++)
    {
        cout << list.get(i) << endl;
    }

    list.clear();
    for(int i=0; i<list.length(); i++)
    {
        cout << list.get(i) << endl;
    }

    return 0;
}

