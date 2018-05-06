#include <iostream>
#include "LinkList.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
    int m_id;
public:
    Test(int id = 0)
    {
        m_id = id;
    }

    ~Test()
    {
        if( m_id == 1 )
        {
            throw m_id;
        }
    }
};

int main()
{
    LinkList<Test> list;
    Test t0(0), t1(1), t2(2);

    try
    {
        list.insert(t0);
        list.insert(t1);
        list.insert(t2);

        list.remove(1);
    }
    catch(int e)
    {
        cout << e << endl;
        cout << list.length() << endl;
    }

    return 0;
}

