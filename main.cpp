#include <iostream>
#include "DTString.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;

void test_1()
{
    cout << "test_1() begin ..." << endl;

    String s;
    s = 'D';

    cout << s.str() << endl;
    cout << s.length() << endl;
    cout << (s == "D") << endl;
    cout << (s > "CCC") << endl;

    cout << endl;

    s += " Delphi Tang ";
    cout << s.str() << endl;
    cout << s.length() << endl;
    cout << (s == "D Delphi Tang ") << endl;

    cout << "test_1() end ..." << endl;
}

void test_2()
{
    cout << "test_2() begin ..." << endl;

    String a[] = {"E", "D", "C", "B", "A"};
    String min = a[0];

    for(int i = 0; i < 5; i++)
    {
        if(min > a[i])
        {
            min = a[i];
        }
    }
    cout << "min = " << min.str() << endl;

    cout << "test_2() end ..." << endl;
}

int main()
{
    test_1();
    cout << endl;
    test_2();

    return 0;
}

