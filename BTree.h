﻿#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace DTLib
{

enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder
};

template <typename T>
class BTree : public Tree<T>
{
public:
    BTree() = default;

    bool insert(TreeNode<T> *node) override
    {
        return insert(node, ANY);
    }

    virtual bool insert(TreeNode<T> *node, BTNodePos pos)
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
                BTreeNode<T> *np = find(node->parent);

                if( np != nullptr )
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter can not be null ...");
        }

        return ret;
    }

    bool insert(const T &value, TreeNode<T> *parent) override
    {
        return insert(value, parent, ANY);
    }

    virtual bool insert(const T &value, TreeNode<T> *parent, BTNodePos pos)
    {
        bool ret = true;
        BTreeNode<T> *node = BTreeNode<T>::NewNode();

        if( node != nullptr )
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node, pos);

            if( !ret )
            {
                delete node;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create node ...");
        }

        return ret;
    }

    SharedPointer<Tree<T>> remove(const T &value) override
    {
        BTree<T> *ret = nullptr;

        BTreeNode<T> *node = find(value);

        if( node != nullptr )
        {
            remove(node, ret);

            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the tree node via value ...");
        }

        return ret;
    }

    SharedPointer<Tree<T>> remove(TreeNode<T> *node) override
    {
        BTree<T> *ret = nullptr;

        node = find(node);

        if( node != nullptr )
        {
            remove(dynamic_cast<BTreeNode<T>*>(node), ret);

            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }

        return ret;
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
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }

    int degree() const override
    {
        return degree(root());
    }

    int count() const override
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear() override
    {
        free(root());

        m_queue.clear();

        this->m_root = nullptr;
    }

    bool begin() override
    {
        bool ret = (root() != nullptr);

        if( ret )
        {
            m_queue.clear();
            m_queue.add(root());
        }

        return ret;
    }

    bool end() override
    {
        return (m_queue.length() == 0);
    }

    bool next() override
    {
        bool ret = (m_queue.length() > 0);

        if( ret )
        {
            BTreeNode<T> *node = m_queue.front();

            m_queue.remove();

            if( node->left != nullptr )
            {
                m_queue.add(node->left);
            }

            if( node->right != nullptr )
            {
                m_queue.add(node->right);
            }
        }

        return ret;
    }

    T current() override
    {
        if( !end() )
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    SharedPointer<DynamicArray<T>> traversal(BTTraversal order) const
    {
        DynamicArray<T> *ret = nullptr;
        LinkQueue<BTreeNode<T>*> queue;

        switch(order)
        {
        case PreOrder:
            PreOrderTraversal(root(), queue);
            break;
        case InOrder:
            InOrderTraversal(root(), queue);
            break;
        case PostOrder:
            PostOrderTraversal(root(), queue);
            break;
        default:
            THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
            break;
        }

        ret = new DynamicArray<T>(queue.length());

        if( ret != nullptr )
        {
            for(int i=0; i<ret->length(); ++i, queue.remove())
            {
                ret->set(i, queue.front()->value);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough to create return array ...");
        }

        return ret;
    }

    ~BTree()
    {
        clear();
    }

protected:
    LinkQueue<BTreeNode<T>*> m_queue;

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

    virtual bool insert(BTreeNode<T> *node, BTreeNode<T> *np, BTNodePos pos)
    {
        bool ret = true;

        if( pos == ANY )
        {
            if( np->left == nullptr )
            {
                np->left = node;
            }
            else if( np->right == nullptr )
            {
                np->right = node;
            }
            else
            {
                ret = false;
            }
        }
        else if( pos == LEFT )
        {
            if( np->left == nullptr )
            {
                np->left = node;
            }
            else
            {
                ret = false;
            }
        }
        else if( pos == RIGHT )
        {
            if( np->right == nullptr )
            {
                np->right = node;
            }
            else
            {
                ret = false;
            }
        }

        return ret;
    }

    virtual void remove(BTreeNode<T> *node, BTree<T> *&ret)
    {
        ret = new BTree<T>();

        if( ret != nullptr )
        {
            if( root() == node )
            {
                this->m_root = nullptr;
            }
            else
            {
                BTreeNode<T> *parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if( node == parent->left )
                {
                    parent->left = nullptr;
                }
                else if( node == parent->right )
                {
                    parent->right = nullptr;
                }

                node->parent = nullptr;
            }

            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create btree ...");
        }
    }

    virtual void free(BTreeNode<T> *node)
    {
        if( node != nullptr )
        {
            free(node->left);
            free(node->right);

            if (node->flag())
            {
                delete node;
            }
        }
    }

    int count(BTreeNode<T> *node) const
    {
        return (node != nullptr) ? (count(node->left) + count(node->right) + 1) : 0;
    }

    int height(BTreeNode<T> *node) const
    {
        int ret = 0;

        if( node != nullptr )
        {
            int lh = height(node->left);
            int rh = height(node->right);

            ret = ( (lh > rh) ? lh : rh ) + 1;
        }

        return ret;
    }

    int degree(BTreeNode<T> *node) const
    {
        int ret = 0;

        if( node != nullptr )
        {
            BTreeNode<T> *child[] = {node->left, node->right};
            ret = !!node->left + !!node->left;

            for(int i=0; (i<2) && (ret<2); ++i)
            {
                int d = degree(child[i]);

                if( ret < d )
                {
                    ret = d;
                }
            }
#if 0
            // 二叉树度数最大为 2，若已经为 2 了，则没必要继续执行
            if( ret < 2 )
            {
                int dl = degree(node->left);

                if( ret < dl )
                {
                    ret = dl;
                }
            }

            if( ret < 2 )
            {
                int dr = degree(node->right);

                if( ret < dr )
                {
                    ret = dr;
                }
            }
#endif
        }

        return ret;
    }

    void PreOrderTraversal(BTreeNode<T> *node, LinkQueue<BTreeNode<T>*> &queue) const
    {
        if( node != nullptr )
        {
            queue.add(node);
            PreOrderTraversal(node->left, queue);
            PreOrderTraversal(node->right, queue);
        }
    }

    void InOrderTraversal(BTreeNode<T> *node, LinkQueue<BTreeNode<T>*> &queue) const
    {
        if( node != nullptr )
        {
            InOrderTraversal(node->left, queue);
            queue.add(node);
            InOrderTraversal(node->right, queue);
        }
    }

    void PostOrderTraversal(BTreeNode<T> *node, LinkQueue<BTreeNode<T>*> &queue) const
    {
        if( node != nullptr )
        {
            PostOrderTraversal(node->left, queue);
            PostOrderTraversal(node->right, queue);
            queue.add(node);
        }
    }
};


}

#endif // BTREE_H

