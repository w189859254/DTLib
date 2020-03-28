#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class GTree : public Tree<T>
{
public:
    bool insert(TreeNode<T> *node) override
    {
        bool ret = true;

        if( node != nullptr )
        {
            if( this->m_root == nullptr )
            {
                node->parent = nullptr;
                this->m_root = node;
            }
            else
            {
                GTreeNode<T> *np = find(node->parent);

                if( np != nullptr )
                {
                    GTreeNode<T> *n = dynamic_cast<GTreeNode<T>*>(node);

                    // 避免重复插入
                    if( np->child.find(n) < 0 )
                    {
                        np->child.insert(n);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "Invalid parent tree node ...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot be NULL ...");
        }

        return ret;
    }

    bool insert(const T &value, TreeNode<T> *parent) override
    {
        bool ret = true;

        GTreeNode<T> *node = new GTreeNode<T>();

        if( node != nullptr )
        {
            node->value = value;
            node->parent = parent;

            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create node ...");
        }

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

