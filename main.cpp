#include <iostream>
#include "SmartPointer.h"

using namespace std;
using namespace DTLib;

class Test
{
public:
    Test()
    {
        cout << "Test()" << endl;
    }

    ~Test()
    {
        cout << "Test()" << endl;
    }

};

int main()
{
    SmartPointer<Test> sp = new Test();
    SmartPointer<Test> nsp;


    nsp = sp;

    //nsp++;  //±àÒë´íÎó

    cout << sp.isNull() << endl;
    cout << nsp.isNull() << endl;

    return 0;
}

