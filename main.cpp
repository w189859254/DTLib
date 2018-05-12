#include <iostream>
#include "LinkStack.h"
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
    LinkStack<Test> stack;

    cout << stack.size() << endl;

    return 0;
}

