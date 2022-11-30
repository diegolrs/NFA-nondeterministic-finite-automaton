#pragma once

#include "NaryTree_Node.hpp"

template <typename T>
class NaryTree
{
    private:
        NaryTree_Node<T> *root;
        MyList<NaryTree_Node<T>*> *children;
    public:
        NaryTree<T>();
        NaryTree_Node<T>* GetRoot();
        void SetRoot(NaryTree_Node<T>* root);
};

template <typename T>
NaryTree<T>::NaryTree()
{
    root = new NaryTree_Node<T>();
}

template <typename T>
NaryTree_Node<T>* NaryTree<T>::GetRoot()
{
    return root;
}

template <typename T>
void NaryTree<T>::SetRoot(NaryTree_Node<T>* value)
{
    root = value;
}