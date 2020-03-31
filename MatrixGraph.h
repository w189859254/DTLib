#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace DTLib
{

template <int N, typename V, typename E>
class MatrixGraph : public Graph<V, E>
{
public:
    MatrixGraph() = default;

    V getVertex(int i) override
    {
        V ret;

        if( !getVertex(i, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return ret;
    }

    bool getVertex(int i, V &value) override
    {
        bool ret = ( (0 <= i) && (i < vCount()) );

        if( ret )
        {
            if( m_vertexes[i] != nullptr )
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
            }
        }

        return ret;
    }

    bool setVertex(int i, const V &value) override
    {
        bool ret = ( (0 <= i) && (i < vCount()) );

        if( ret )
        {
            V *data = m_vertexes[i];

            if( data == nullptr )
            {
                data = new V();
            }

            if( data != nullptr )
            {
                *data = value;

                m_vertexes[i] = data;  // 异常安全！！！
#if 0
                // 若没有 data 临时变量，直接操作 m_vertexes
                m_vertexes[i] = new V();
                *(m_vertexes[i]) = value;   // 若发生异常，则破坏 m_vertexes.
#endif
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new vertex value ...");
            }

        }

        return ret;
    }

    SharedPointer<Array<int>> getAdjacent(int i) override
    {
        DynamicArray<int> *ret = nullptr;

        if( (0 <= i) && (i < vCount()) )
        {
            int n = 0;

            for(int j=0; j<vCount(); ++j)
            {
                if( m_edges[i][j] != nullptr )
                {
                    ++n;
                }
            }

            ret = new DynamicArray<int>(n);

            if( ret != nullptr )
            {
                for(int j=0, k=0; j<vCount(); ++j)
                {
                    if( m_edges[i][j] != nullptr )
                    {
                        ret->set(k++, j);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret obj ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return ret;
    }

    E getEdge(int i, int j) override
    {
        E ret;

        if( !getEdge(i, j, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter <i, j> is invalid ...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E &value) override
    {
        bool ret = ( (0 <= i) && (i < vCount()) &&
                     (0 <= j) && (j < vCount()) );

        if( ret )
        {
            if( m_edges[i][j] != nullptr )
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E &value) override
    {
        bool ret = ( (0 <= i) && (i < vCount()) &&
                     (0 <= j) && (j < vCount()) );

        if( ret )
        {
            E *ne = m_edges[i][j];

            if( ne != nullptr )
            {
                *ne = value;
            }
            else
            {
                ne = new E();

                if( ne != nullptr )
                {
                    *ne = value;

                    m_edges[i][j] = ne;  // 异常安全！！！

                    ++m_eCount;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new edge value ...");
                }
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j) override
    {
        bool ret =( (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()) );

        if( ret )
        {
            E *todel = m_edges[i][j];

            m_edges[i][j] = nullptr;

             if( todel != nullptr )
             {
                 --m_eCount;

                 delete todel;
             }
        }

        return ret;
    }

    int vCount() override
    {
        return N;
    }

    int eCount() override
    {
        return m_eCount;
    }

    int OD(int i) override // 顶点 i 的出度
    {
        int ret = 0;

        if( (0 <= i) && (i < vCount()) )
        {
            for(int j=0; j<vCount(); ++j)
            {
                if( m_edges[i][j] != nullptr )
                {
                    ++ret;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invald ...");
        }

        return ret;
    }

    int ID(int i) override
    {
        int ret = 0;

        if ((0 <= i) && (i < vCount()))
        {
            for (int j=0; j<vCount(); ++j)
            {
                if (m_edges[j][i] != nullptr)
                {
                    ++ret;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invald ...");
        }

        return ret;
    }

    ~MatrixGraph()
    {
        for (int i=0; i<vCount(); ++i)
        {
            for (int j=0; j<vCount(); ++j)
            {
                delete m_edges[i][j];
            }

            delete m_vertexes[i];
        }
    }

protected:
    V *m_vertexes[N] = {nullptr};
    E *m_edges[N][N] = {nullptr};
    int m_eCount = 0;

    MatrixGraph(const MatrixGraph &) = default;
    MatrixGraph &operator = (const MatrixGraph &) = default;
};

}

#endif // MATRIXGRAPH_H
