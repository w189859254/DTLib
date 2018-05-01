#include <iostream>
#include "DynamicArray.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;

int main()
{
    DynamicArray<int> s1(5);

    for(int i=0; i<s1.length(); i++)
    {
        s1[i] = i*i;
    }

    for(int i=0; i<s1.length(); i++)
    {
        cout << s1[i] << endl;
    }


    DynamicArray<int> s2(10);
    s2 = s1;

    s2.resize(3);
    for(int i=0; i<s2.length(); i++)
    {
        cout << s2[i] << endl;
    }


    s2[4] = 100;

    return 0;
}

