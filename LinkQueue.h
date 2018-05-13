#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "LinkList.h"
#include "Exception.h"

namespace DTLib
{
template <typename T>
class LinkQueue : public Queue<T>
{
protected:
    LinkList<T> m_list;
public:
    LinkQueue()
    {

    }

    void add(const T& e)    // O(n)
    {
        // 从队头开始遍历
        m_list.insert(e);
    }

    void remove()   // O(1)
    {
        if(m_list.length() > 0)
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T front() const // O(1)
    {
        if(m_list.length() > 0)
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void clear()    // O(n)
    {
       m_list.clear();
    }

    int length() const  // O(1)
    {
        return m_list.length();
    }
};


}

#endif // LINKQUEUE_H
