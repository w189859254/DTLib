#include <iostream>
#include "StaticQueue.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;


int main()
{
    StaticQueue<int, 5> queue;

    for(int i=0; i<5; i++)
    {
        queue.add(i);
    }

    while(queue.length() > 0)
    {
        cout << queue.front() << endl;

        queue.remove();
    }


    return 0;
}

