#pragma once

#include "NaryTree_Node.hpp"

template <typename T>
class NaryTree
{
    private:
        int maxHeight;
        MyList<NaryTree_Node<T>*> children;
    public:
        NaryTree<T>();
        MyList<NaryTree_Node<T>*> GetWithHeight(int height);
        int GetMaxHeight();
        void AddLeaf(T content, NaryTree_Node<T>* parent);
        void AddLeaf(T content, NaryTree_Node<T>* parent, int height);
};

template <typename T>
NaryTree<T>::NaryTree()
{
    maxHeight = -1;
}

template <typename T>
MyList<NaryTree_Node<T>*> NaryTree<T>::GetWithHeight(int height)
{
    MyList<NaryTree_Node<T>*> list = MyList<NaryTree_Node<T>*>();

    for(int i = 0; i < children.Length(); i++)
    {       
        NaryTree_Node<T>* node = children.At(i);

        if(node->GetHeight() == height)
            list.Push(node);
    }

    return list;
}

template <typename T>
void NaryTree<T>::AddLeaf(T content, NaryTree_Node<T>* parent)
{
    int height = parent == nullptr ? 0 : parent->GetHeight() +1;
    NaryTree_Node<T>* node = new NaryTree_Node<T>(content, parent, height);

    if(height > maxHeight)
        maxHeight = height;

    children.Push(node);
}

template <typename T>
void NaryTree<T>::AddLeaf(T content, NaryTree_Node<T>* parent, int height)
{
    NaryTree_Node<T>* node = new NaryTree_Node<T>(content, parent, height);

    if(height > maxHeight)
        maxHeight = height;

    children.Push(node);
}

template <typename T>
int NaryTree<T>::GetMaxHeight()
{
    return maxHeight;
}