#pragma once

#include "MyList.hpp"

#define DEFAULT_VALUE T()

template <typename T>
class NaryTree_Node
{
    private:
        T content;
        NaryTree_Node<T> *parent;
        MyList<NaryTree_Node<T>*> *children;
    public:
        NaryTree_Node<T>();
        NaryTree_Node<T>(NaryTree_Node<T>* parent, T content);

        T GetContent();
        NaryTree_Node<T> *GetParent();
        MyList<NaryTree_Node<T>*> *GetChildren();

        void SetContent(T value);
        void SetParent(NaryTree_Node<T>* parent);
        void AddChildren(NaryTree_Node<T>* child);
};

template <typename T>
NaryTree_Node<T>::NaryTree_Node()
{
    this->parent = nullptr;
    this->children = new MyList<NaryTree_Node<T>*>();
    this->content = DEFAULT_VALUE;
}

template <typename T>
NaryTree_Node<T>::NaryTree_Node(NaryTree_Node<T>* parent, T content)
{
    this->parent = parent;
    this->children = new MyList<NaryTree_Node<T>*>();
    this->content = content;
}

template <typename T>
T NaryTree_Node<T>::GetContent()
{
    return content;
}

template <typename T>
NaryTree_Node<T>* NaryTree_Node<T>::GetParent()
{
    return parent;
}

template <typename T>
MyList<NaryTree_Node<T>*>* NaryTree_Node<T>::GetChildren()
{
    return children;
}

template <typename T>
void NaryTree_Node<T>::SetContent(T value)
{
    this->content = value;
}

template <typename T>
void NaryTree_Node<T>::SetParent(NaryTree_Node<T> *parent)
{
    this->parent = parent;
}

template <typename T>
void NaryTree_Node<T>::AddChildren(NaryTree_Node<T>* child)
{
    this->children->Push(child);
}