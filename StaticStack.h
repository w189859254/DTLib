#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "stack.h"
#include "Exception.h"

namespace DTLib
{
template <typename T, int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];
    int m_top;
    int m_size;
public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }

    int capacity() const
    {
        return N;
    }

    void push(const T& e)
    {
        if(m_size < N)
        {
            // 异常安全
            m_space[m_top + 1] = e;
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack ...");
        }
    }

    void pop()
    {
        if(m_size > 0)
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top() const
    {
        if(m_size > 0)
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    int size() const
    {
        return m_size;
    }

    void clear()
    {
        m_top = -1;
        m_size = 0;
    }

    ~StaticStack()
    {
        clear();
    }

};
}

#endif // STATICSTACK_H

