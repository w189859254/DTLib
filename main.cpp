#include <iostream>
#include "Exception.h"

using namespace std;
using namespace DTLib;

int main()
{
    try
    {
        NullPointerException npe;

        cout << "throw" << endl;

        throw npe;
    }
    catch(const Exception& e)
    {
        cout << "catch" << endl;
    }

    return 0;
}

