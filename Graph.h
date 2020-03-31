#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "SharedPointer.h"
#include "DynamicArray.h"
#include "LinkQueue.h"

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
};

template <typename V, typename E>
class Graph : public Object
{
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V &value) = 0;
    virtual bool setVertex(int i, const V &value) = 0;
    virtual SharedPointer<Array<int>> getAdjacent(int i) = 0;
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
};

}

#endif // GRAPH_H

