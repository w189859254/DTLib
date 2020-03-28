#include <iostream>
#include <ctime>
#include "Sort.h"

using namespace std;
using namespace DTLib;

struct Test : public Object
{
    int id;
    int data1[1000];
    double data2[500];

    bool operator < (const Test &obj)
    {
        return id < obj.id;
    }

    bool operator <= (const Test &obj)
    {
        return id <= obj.id;
    }

    bool operator > (const Test &obj)
    {
        return id > obj.id;
    }

    bool operator >= (const Test &obj)
    {
        return id >= obj.id;
    }
};

class TestProxy : public Object
{
public:
    int id()
    {
        return m_pTest->id;
    }

    int *data1()
    {
        return m_pTest->data1;
    }

    double *data2()
    {
        return m_pTest->data2;
    }

    Test &test() const  // 获取委托者!!
    {
        return *m_pTest;
    }

    bool operator < (const TestProxy &obj)
    {
        return test() < obj.test();
    }

    bool operator <= (const TestProxy &obj)
    {
        return test() <= obj.test();
    }

    bool operator > (const TestProxy &obj)
    {
        return test() > obj.test();
    }

    bool operator >= (const TestProxy &obj)
    {
        return test() >= obj.test();
    }

    Test &operator = (Test &test)
    {
        m_pTest = &test;

        return test;
    }

protected:
    Test *m_pTest = nullptr;
};

static Test t[1000];
static TestProxy pt[1000];

int main()
{
    clock_t begin = 0;
    clock_t end = 0;

    for (int i=0; i<1000; ++i)
    {
        t[i].id = i;
        pt[i] = t[i];
    }

    begin = clock();
    Sort::Bubble(t, 1000, false);
    end = clock();
    cout << "Entrustor Time : " << end - begin << endl;

    begin = clock();
    Sort::Bubble(pt, 1000);
    end = clock();
    cout << "Proxy Time : " << end - begin << endl;

    for (int i=0; i<1000; ++i)
    {
        cout << t[i].id << " " << pt[i].id() << endl;
    }

    return 0;
}


