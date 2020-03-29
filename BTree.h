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
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T> *node) const override
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
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

protected:
    virtual BTreeNode<T>* find(BTreeNode<T> *node, const T &value) const
    {
        BTreeNode<T> *ret = nullptr;

        if( node != nullptr )
        {
            if( node->value == value )
            {
                ret = node;
            }
            else
            {
                if( ret == nullptr )
                {
                    ret = find(node->left, value);
                }

                if( ret == nullptr )
                {
                    ret = find(node->right, value);
                }
            }
        }

        return ret;
    }

    virtual BTreeNode<T>* find(BTreeNode<T> *node, BTreeNode<T> *obj) const
    {
        BTreeNode<T> *ret = nullptr;

        if( node == obj )
        {
            ret = node;
        }
        else
        {
            if( node != nullptr )
            {
                if( ret == nullptr )
                {
                    ret = find(node->left, obj);
                }

                if( ret == nullptr )
                {
                    ret = find(node->right, obj);
                }
            }
        }

        return ret;
    }

};


}

#endif // BTREE_H

