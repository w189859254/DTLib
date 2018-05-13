#include <iostream>
#include "LinkQueue.h"
#include "StaticQueue.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
public:
    Test()
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
    LinkQueue<Test> lq;
    StaticQueue<Test, 5> sq;

    return 0;
}

