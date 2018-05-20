#include <iostream>
#include "DTString.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;


int main()
{
    String s = "D.T.Software";

    cout << s.startWith("D.T") << endl;
    cout << s.endOf("Software") <<endl;

    return 0;
}

