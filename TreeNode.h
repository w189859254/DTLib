#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DTLib
{

template <typename T>
class TreeNode : public Object
{
public:
    T value;
    TreeNode<T> *parent = nullptr;

    TreeNode()
    {
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;

    TreeNode(const TreeNode<T>&) = delete;
    TreeNode<T>& operator = (const TreeNode<T>&) = delete;

protected:
    bool m_flag = false;

    void *operator new (unsigned long long size) noexcept(true)
    {
        return Object::operator new(size);
    }
};

template <typename T>
TreeNode<T>::~TreeNode()
{

}

}

#endif // TREENODE_H
