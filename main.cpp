#include <iostream>
#include "SharedPointer.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
public:
    int value;

    Test() : value(0)
    {
        cout << "Test()" << endl;
    }

    ~Test()
    {
        cout << "~Test()" << endl;
    }

};

int main()
{
    SharedPointer<Test> sp0 = new Test();
    SharedPointer<Test> sp1 = sp0;
    SharedPointer<Test> sp2 = NULL;

    sp2 = sp1;

    sp2->value = 100;

    cout << sp0->value << endl;
    cout << sp1->value << endl;
    cout << sp2->value << endl;

    sp2.clear();

    cout << (sp1 == sp2) << endl;

    return 0;
}

