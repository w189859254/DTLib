﻿#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "SharedPointer.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "Sort.h"

namespace DTLib
{

template <typename E>
struct Edge : public Object
{
    int b;
    int e;
    E data;

    Edge(int i=-1, int j=-1)  : b(i), e(j)
    {
    }

    Edge(int i, int j, const E &value) : b(i), e(j), data(value)
    {
    }

    bool operator == (const Edge &obj)
    {
        return (b == obj.b) && (e == obj.e);
    }

    bool operator != (const Edge &obj)
    {
        return !(*this == obj);
    }

    bool operator < (const Edge &obj)
    {
        return (data < obj.data);
    }

    bool operator > (const Edge &obj)
    {
        return (data > obj.data);
    }
};

template <typename V, typename E>
class Graph : public Object
{
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V &value) = 0;
    virtual bool setVertex(int i, const V &value) = 0;
    virtual SharedPointer<Array<int>> getAdjacent(int i) = 0;
    virtual bool isAdjacent(int i, int j) = 0;
    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E &value) = 0;
    virtual bool setEdge(int i, int j, const E &value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;

    virtual int TD(int i)
    {
        return OD(i) + ID(i);
    }

    bool asUndirected()
    {
        bool ret = true;

        for(int i=0; i<vCount() && ret; ++i)
        {
            for(int j=0; j<vCount() && ret; ++j)
            {
                if( isAdjacent(i, j) )
                {
                    ret = isAdjacent(j, i) && (getEdge(i, j) == getEdge(j, i));
                }
            }
        }

        return ret;
    }

    SharedPointer<Array<int>> BFS(int i)
    {
        DynamicArray<int> *ret = nullptr;

        if( (0 <= i) && (i < vCount()) )
        {
            LinkQueue<int> q; // queue
            LinkQueue<int> r; // ret
            DynamicArray<bool> visited(vCount());

            for(int i=0; i<visited.length(); ++i)
            {
                visited[i] = false;
            }

            q.add(i);

            while( q.length() > 0 )
            {
                int v = q.front();

                q.remove();

                if( !visited[v] )
                {
                    SharedPointer<Array<int>> aj = getAdjacent(v);

                    for(int i=0; i<aj->length(); ++i)
                    {
                        q.add((*aj)[i]);
                    }

                    r.add(v);

                    visited[v] = true;
                }
            }

            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return ret;
    }

    SharedPointer<Array<int>> DFS(int i)
    {
        DynamicArray<int> *ret = nullptr;

        if( (0 <= i) && (i < vCount()) )
        {
            LinkStack<int> s;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());

            for(int j=0; j<visited.length(); ++j)
            {
                visited[j] = false;
            }

            s.push(i);

            while( s.size() > 0 )
            {
                int v = s.top();

                s.pop();

                if( !visited[v] )
                {
                    SharedPointer<Array<int>> aj = getAdjacent(v);
#if 0
                    for(int j=aj->length()-1; j>=0; --j)
                    {
                        s.push((*aj)[j]);
                    }
#endif
                    for(int j=0; j < aj->length(); ++j)
                    {
                        s.push((*aj)[j]);
                    }
                    r.add(v);

                    visited[v] = true;
                }
            }

            ret = toArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return ret;
    }

    // LIMIT：理论上的最大权值
    SharedPointer<Array<Edge<E>>> prim(const E &LIMIT, bool MINIMUM = true)
    {
        LinkQueue<Edge<E>> ret;

        if( asUndirected() )
        {
            DynamicArray<int> adjVex(vCount());
            DynamicArray<bool> mark(vCount());
            DynamicArray<E> cost(vCount());
            SharedPointer<Array<int>> aj = nullptr; // 邻接矩阵数组
            bool end = false;
            int v = 0;

            for(int i=0; i<vCount(); ++i)
            {
                adjVex[i] = -1;
                mark[i] = false;
                cost[i] = LIMIT;
            }

            mark[v] = true;

            aj = getAdjacent(v);

            for(int i=0; i<aj->length(); ++i)
            {
                cost[(*aj)[i]] = getEdge(v, (*aj)[i]);
                adjVex[(*aj)[i]] = v;
            }

            for(int i=0; i<vCount() && !end; ++i)
            {
                E m = LIMIT;
                int k = -1;

                for(int j=0; j<vCount(); ++j)
                {
                    if( !mark[j] && (MINIMUM ? (m > cost[j]) : (m < cost[j])) )
                    {
                        m = cost[j];
                        k = j;
                    }
                }

                end = (k == -1);

                if( !end )
                {
                    ret.add(Edge<E>(adjVex[k],k, getEdge(adjVex[k],k)));

                    mark[k] = true;

                    aj = getAdjacent(k);

                    for(int j=0; j<aj->length(); ++j)
                    {
                        if( !mark[(*aj)[j]] && (MINIMUM ?
                                                (getEdge(k, (*aj)[j]) < cost[(*aj)[j]]) :
                                                (getEdge(k, (*aj)[j]) > cost[(*aj)[j]])) )
                        {
                            cost[(*aj)[j]] = getEdge(k, (*aj)[j]);

                            adjVex[(*aj)[j]] = k;
                        }
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Prim operator is for undirected grap only ...");
        }

        if( ret.length() != (vCount() - 1) )
        {
            THROW_EXCEPTION(InvalidOperationException, "No enough edge for prim operation ...");
        }

        return toArray(ret);
    }

    SharedPointer<Array<Edge<E>>> kruskal( const bool MINIMUM = true)
    {
        LinkQueue<Edge<E>> ret;
        DynamicArray<int> p(vCount());
        SharedPointer<Array<Edge<E>>> edges = getUndirectedEdges();

        for(int i=0; i<p.length(); ++i)
        {
            p[i] = -1;
        }

        Sort::Shell(*edges, MINIMUM);

        for(int i=0; (i<edges->length()) && (ret.length() < (vCount()-1)); ++i)
        {
            int b = find(p, (*edges)[i].b);
            int e = find(p, (*edges)[i].e);

            if( b != e )
            {
                p[e] = b;

                ret.add((*edges)[i]);
            }
        }

        if( ret.length() != vCount() - 1 )
        {
            THROW_EXCEPTION(InvalidOperationException, "No enough edges for Kruskal operation ...");
        }

        return toArray(ret);
    }

protected:
    template <typename T>
    DynamicArray<T>* toArray(LinkQueue<T> &queue)
    {
        DynamicArray<T> *ret = new DynamicArray<T>(queue.length());

        if( ret != nullptr )
        {
            for(int i=0; i<ret->length(); ++i, queue.remove())
            {
                ret->set(i, queue.front());
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret obj ...");
        }

        return ret;
    }

    int find(Array<int> &p, int v)
    {
        while( p[v] != -1 )
        {
            v = p[v];
        }

        return v;
    }

    SharedPointer<Array<Edge<E>>> getUndirectedEdges()
    {
        DynamicArray<Edge<E>> *ret = nullptr;

        if( asUndirected() )
        {
            LinkQueue<Edge<E>> queue;

            for(int i=0; i<vCount(); ++i)
            {
                for(int j=0; j<vCount(); ++j)
                {
                    if( isAdjacent(i, j) )
                    {
                        queue.add(Edge<E>(i, j, getEdge(i, j)));
                    }
                }
            }

            ret = toArray(queue);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "This function is for undirected graph only ...");
        }

        return ret;
    }
};

}

#endif // GRAPH_H

