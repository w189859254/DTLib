#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace DTLib
{

template<typename T, int N>
class StaticLinkList : public LinkList<T>
{
protected:

    typedef typename LinkList<T>::Node Node;

    // 目的：在指定地址调用构造函数
    struct SNode : public Node
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void)size;
            return loc;
        }
    };

    unsigned char m_space[sizeof(SNode) * N];
    int m_used[N];

    Node* create()
    {
        SNode* ret = NULL;

        for(int i=0; i<N; i++)
        {
            if(!m_used[i])
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;
                // 调用构造函数
                ret = new(ret)SNode();
                m_used[i] = 1;
                break;
            }
        }
        return ret;
    }

    void destroy(Node* pn)
    {
        SNode* space = reinterpret_cast<SNode*>(m_space);
        // 将父类指针转换到子类指针用 dynamic_cast
        SNode* psn = dynamic_cast<SNode*>(pn);

        for(int i=0; i<N; i++)
        {
            if(psn == (space + i))
            {
                m_used[i] = 0;
                psn->~SNode();
                break;
            }
        }
    }

public:
    StaticLinkList()
    {
        for(int i=0; i<N; i++)
        {
            m_used[i] = 0;
        }
    }

    int capacity()
    {
        return N;
    }
};



}



#endif // STATICLINKLIST_H

