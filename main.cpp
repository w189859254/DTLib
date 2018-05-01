#include <iostream>
#include "DynamicList.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;

int main()
{
    DynamicList<int> l(5);
   // DynamicList<int> n = l;

   // DynamicList<int> n(5);
   // n = l;

    for(int i=0; i<l.capacity(); i++)
    {
        l.insert(i);
    }

    for(int i=0; i<l.capacity(); i++)
    {
        cout << l[i] << endl;
    }

    return 0;
}

