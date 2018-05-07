#include <iostream>
#include "CircleList.h"

using namespace std;
using namespace DTLib;

// n: ����������Ϸ
// s: �Ӷ��ٺſ�ʼ
// m: ����ȥ��
void josephus(int n, int s, int m)
{
    CircleList<int > cl;

    for(int i=1; i<=n; i++)
    {
        cl.insert(i);
    }

    // �±�� 0 ��ʼ������Ϊ 2
    cl.move(s-1, m-1);

    while(cl.length() > 0)
    {
        cl.next();

        cout << cl.current() << endl;

        cl.remove(cl.find(cl.current()));
    }
}


int main()
{
    josephus(41, 1, 3);

    return 0;
}

