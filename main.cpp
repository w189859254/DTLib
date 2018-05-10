#include <iostream>
#include "DualLinkList.h"

using namespace std;
using namespace DTLib;

int main()
{
    DualLinkList<int> dl;

    for(int i=0; i<5; i++)
    {
        dl.insert(0, i);
        dl.insert(0, 5);
    }

    for(int i=0; i<dl.length(); i++)  // O(n^2)
    {
        cout << dl.get(i) << endl;
    }

    for(dl.move(0); !dl.end(); dl.next())// O(n)
    {
        cout << dl.current() << endl;
    }

    cout << "begin 1" << endl;

    for(dl.move(dl.length()-1); !dl.end(); dl.pre())// O(n)
    {
        cout << dl.current() << endl;
    }

    cout << "begin 2" << endl;

    dl.move(dl.length()-1);

    while(!dl.end())
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

    for(dl.move(0); !dl.end(); dl.next())// O(n)
    {
        cout << dl.current() << endl;
    }

    return 0;
}

