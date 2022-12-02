#pragma once

#include "MyList.hpp"

#define DEFAULT_VALUE T()
#define INVALID_INDEX_POSITION -2

template <typename T>
class NaryTree_Node
{
    private:
        T content;
        NaryTree_Node<T> *parent;
        int height;
    public:
        NaryTree_Node<T>();
        NaryTree_Node<T>(T content, NaryTree_Node<T>* parent, int height);

        T GetContent();
        NaryTree_Node<T> *GetParent();
        int GetHeight();

        void SetContent(T value);
        void SetParent(NaryTree_Node<T>* parent);
        void SetHeight(int value);    
};

template <typename T>
NaryTree_Node<T>::NaryTree_Node()
{
    this->parent = nullptr;
    this->content = DEFAULT_VALUE;
    this->height = INVALID_INDEX_POSITION;
}

template <typename T>
NaryTree_Node<T>::NaryTree_Node(T content, NaryTree_Node<T>* parent, int height)
{
    this->parent = parent;
    this->content = content;
    this->height = height;
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
int NaryTree_Node<T>::GetHeight()
{
    return height;
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
void NaryTree_Node<T>::SetHeight(int value)
{
    this->height = height;
}