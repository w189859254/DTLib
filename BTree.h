#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace DTLib
{

enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
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
        free(root());

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

};


}

#endif // BTREE_H

