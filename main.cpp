#include <iostream>
#include "DTString.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;


int main()
{
    String s = "D.T.Software";

    for(int i=0; i<s.length(); i++)
    {
        cout << s[i] << endl;
    }

    return 0;
}

