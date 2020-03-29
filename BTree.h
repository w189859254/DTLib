#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace DTLib
{

template <typename T>
class BTree : public Tree<T>
{
public:
    BTree() = default;

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

    BTreeNode<T>* find(const T &value) const override
    {
        return nullptr;
    }

    BTreeNode<T>* find(TreeNode<T> *node) const override
    {
        return nullptr;
    }

    BTreeNode<T>* root() const override
    {
        return nullptr;
    }

    int degree() const override
    {
        return 0;
    }

    int count() const override
    {
        return 0;
    }

    int height() const
    {
        return 0;
    }

    void clear() override
    {
        this->m_root = nullptr;
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif // BTREE_H

