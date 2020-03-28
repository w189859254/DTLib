#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"

namespace DTLib
{

template <typename T>
class GTree : public Tree<T>
{
public:
    bool insert(TreeNode<T> *node) override
    {
        bool ret = true;

        return ret;
    }

    bool insert(const T &value, TreeNode<T> *parent) override
    {
        bool ret = true;

        return ret;
    }

    SharedPointer<Tree<T>> remove(const T &value) override
    {
        return nullptr;
    }

    SharedPointer<Tree<T>> remove(TreeNode<T> *node) override
    {
        return nullptr;
    }

    GTreeNode<T>* find(const T &value) const override
    {
        return nullptr;
    }

    GTreeNode<T>* find(TreeNode<T> *node) const override
    {
        return nullptr;
    }

    GTreeNode<T>* root() const override
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    int degree() const override
    {
        return 0;
    }

    int count() const override
    {
        return 0;
    }

    int height() const override
    {
        return 0;
    }

    void clear() override
    {
        this->m_root = nullptr;
    }

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H

