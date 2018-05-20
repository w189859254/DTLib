#include <iostream>
#include "DTString.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;


int main()
{
    String s = "";

    s.insert(0, "D.T.");
    s.insert(4, "Software");

    cout << s.str() << endl;

    return 0;
}

