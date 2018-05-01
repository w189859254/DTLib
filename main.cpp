#include <iostream>
#include "LinkList.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
    int  i;
public:
    Test(int v = 0)
    {
        i = v;
    }

    bool operator ==(const Test& obj)
    {
        return (i == obj.i);
    }
};

int main()
{
#if 0
    LinkList<int> list;

    for(int i=0; i<5; i++)
    {
        list.insert(0, i);
    }

    cout << list.find(3) << endl;
    cout << list.find(-3) << endl;
#endif

    Test t1(1), t2(2), t3(3);
    LinkList<Test> l1;

    l1.insert(t1);
    l1.insert(t2);
    l1.insert(t3);

    cout << l1.find(t2) << endl;

    return 0;
}

