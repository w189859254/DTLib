#include <iostream>
#include "LinkList.h"

using namespace std;
using namespace DTLib;

int main()
{
    LinkList<int> list;

    for(int i=0; i<5; i++)
    {
        list.insert(i);
    }

    for(list.move(0); !list.end(); list.next())
    {
        if( list.current() == 3 )
        {
            list.remove(list.find(list.current()));

            cout << list.current() << endl;
        }
    }

    for(int i=0; i<list.length(); i++)
    {
        cout << list.get(i) << endl;
    }

    return 0;
}

