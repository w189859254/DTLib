#include <iostream>
#include "DualCircleList.h"

using namespace std;
using namespace DTLib;

int main()
{
    DualCircleList<int> dl;

    for(int i=0; i<5; i++)
    {
        dl.insert(0, i);
        dl.insert(0, 5);
    }

    dl.move(dl.length()-1);

    while( dl.find(5) != -1)
    {
        if(dl.current() == 5)
        {
            cout << dl.current() << endl;
            dl.remove(dl.find(dl.current()));
        }
        else
        {
            dl.pre();
        }
    }

    for(int i=0; i<dl.length(); i++)// O(n)
    {
        cout << dl.get(i) << endl;
    }

    return 0;
}

