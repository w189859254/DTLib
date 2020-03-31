#include <iostream>
#include "MatrixGraph.h"

using namespace std;
using namespace DTLib;

int main()
{
    MatrixGraph<9, char, int> g;
    const char* VD = "ABEDCGFHI";

    for(int i=0; i<9; i++)
    {
        g.setVertex(0, VD[i]);
    }

    // 权值为 0：只关系连接关系
    // 用有向图表示无向图
    g.setEdge(0, 1, 0);
    g.setEdge(1, 0, 0);

    g.setEdge(0, 3, 0);
    g.setEdge(3, 0, 0);

    g.setEdge(0, 4, 0);
    g.setEdge(4, 0, 0);

    g.setEdge(1, 2, 0);
    g.setEdge(2, 1, 0);

    g.setEdge(1, 4, 0);
    g.setEdge(4, 1, 0);

    g.setEdge(2, 5, 0);
    g.setEdge(5, 2, 0);

    g.setEdge(3, 6, 0);
    g.setEdge(6, 3, 0);

    g.setEdge(4, 6, 0);
    g.setEdge(6, 4, 0);

    g.setEdge(6, 7, 0);
    g.setEdge(7, 6, 0);

    g.setEdge(7, 8, 0);
    g.setEdge(8, 7, 0);

    SharedPointer<Array<int>> sa = g.BFS(0);

    for(int i=0; i<sa->length(); ++i)
    {
        cout << (*sa)[i] << " ";
    }

    cout << endl;

    return 0;
};

