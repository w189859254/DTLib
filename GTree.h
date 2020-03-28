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
        return find(root(), value);
    }

    GTreeNode<T>* find(TreeNode<T> *node) const override
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
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

protected:
    GTreeNode<T> *find(GTreeNode<T>* node, const T &value) const
    {
        GTreeNode<T> *ret = nullptr;

        if( node != nullptr )
        {
            if( node->value == value )
            {
                return node;
            }
            else
            {
                for(node->child.move(0); !node->child.end() && (ret == nullptr); node->child.next())
                {
                    ret = find(node->child.current(), value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T> *find(GTreeNode<T>* node, GTreeNode<T> *obj) const
    {
        GTreeNode<T> *ret = nullptr;

        if( node == obj )
        {
            return node;
        }
        else
        {
            if( node != nullptr )
            {
                for(node->child.move(0); !node->child.end() && (ret == nullptr); node->child.next())
                {
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }
};

}

#endif // GTREE_H

