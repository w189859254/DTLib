#include <iostream>
#include "CircleList.h"

using namespace std;
using namespace DTLib;

// n: 多少人玩游戏
// s: 从多少号开始
// m: 几号去死
void josephus(int n, int s, int m)
{
    CircleList<int > cl;

    for(int i=1; i<=n; i++)
    {
        cl.insert(i);
    }

    // 下标从 0 开始，步进为 2
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

