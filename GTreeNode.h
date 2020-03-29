#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"

namespace DTLib
{

template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>*> child;

    GTreeNode() = default;
    GTreeNode(const GTreeNode<T>&) = delete;
    GTreeNode<T>& operator = (const GTreeNode<T>&) = delete;

    bool flag()
    {
        return m_flag;
    }

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T> *ret = new GTreeNode<T>();

        if( ret != nullptr )
        {
            ret->m_flag = true;
        }

        return ret;
    }

protected:
    bool m_flag = false;

    void *operator new (unsigned long long size) noexcept(true)
    {
        return Object::operator new(size);
    }
};

}

#endif // GTREENODE_H

