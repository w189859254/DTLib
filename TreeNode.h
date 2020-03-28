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

    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T>::~TreeNode()
{

}

}

#endif // TREENODE_H
