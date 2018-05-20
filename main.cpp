#include <iostream>
#include "DTString.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;


int main()
{
    String s = "  abc  ";

    if(s.trim().insert(0, "D.T.").endOf("abc") && s.startWith("D.T."))
    {
        cout << "[" << s.str() << "]" << endl;
    }


    return 0;
}

