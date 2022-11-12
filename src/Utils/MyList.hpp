#pragma once

#include <iostream>
#include "Node.hpp"

#define DEFAULT_RETURN T()

template <typename T>
class MyList
{
    private:
        Node<T> *head;
        Node<T> *tail;
        int nElements;
    public:
        MyList();
        ~MyList();

        bool IsEmpty();
        bool Contains(T value);
        int Length();
        int GetIndexOf(T value);   
        T At(int pos);    

        void PushOnBeginning(T value);
        void Push(T value);
        T RemoveFirst();
        T RemoveLast();
        T RemoveAt(int pos);
        void Clear();
};

template <typename T>
MyList<T>::MyList()
{
    head = NULL;
    tail = NULL;
    nElements = 0;
}

template <typename T>
MyList<T>::~MyList()
{
    this->Clear();
}

template <typename T>
bool MyList<T>::IsEmpty(){
    return nElements == 0;
}

template <typename T>
int MyList<T>::Length(){
    return nElements;
}

template <typename T>
int MyList<T>::GetIndexOf(T value)
{
    if (IsEmpty())
    {
        return DEFAULT_RETURN;
    }

    Node<T> *aux = head;
    int cont = -1;

    while (aux != NULL)
    {
        cont++;

        if (aux->getContent() == value)
        {
            break;
        }

        aux = aux->getNextNode();   
    }
    
    return cont;
}

template <typename T>
T MyList<T>::At(int pos)
{
    if (IsEmpty() || pos < 0 || pos >= Length())
    {
        return DEFAULT_RETURN;
    }

    Node<T> *aux = head;

    for (int i = 1; i <= pos; i++){
        aux = aux->getNextNode();
    }
    
    return aux->getContent(); 
}

template <typename T>
bool MyList<T>::Contains(T value){
    Node<T> *aux = head;
    if (IsEmpty()){
        return false;
    }

    while (aux->getNextNode() != NULL){
        if (aux->getContent() == value){
            return true;
        }
        aux = aux->getNextNode();
    }
    return false;
}

template <typename T>
void MyList<T>::PushOnBeginning(T value){
    Node<T> *newNode = new Node<T>();

    newNode->setContent(value);
    newNode->setNextNode(head);
    newNode->setPriorNode(NULL);

    if(IsEmpty()){
        tail = newNode;
    }else{
        head->setPriorNode(newNode);
    }
    head = newNode;
    nElements++;
}

template <typename T>
void MyList<T>::Push(T value){

    if(IsEmpty())
    {
        PushOnBeginning(value);
        return;
    }

    Node<T> *newNode = new Node<T>();
    newNode->setContent(value);
    newNode->setNextNode(NULL);

    tail->setNextNode(newNode);

    newNode->setPriorNode(tail);
    tail->setNextNode(newNode);
    tail = newNode;

    nElements++;
}

template <typename T>
T MyList<T>::RemoveFirst(){
    if(IsEmpty())
        return DEFAULT_RETURN;

    Node<T> *aux = head;
    T value_removido = aux->getContent();

    if (nElements == 1){
        head = NULL;
        tail = NULL;
    }else{
        head = aux->getNextNode();
        aux->getNextNode()->setPriorNode(NULL);
    }

    nElements--;
    delete aux;
    return value_removido;
}

template <typename T>
T MyList<T>::RemoveLast(){
    if(IsEmpty())
        return DEFAULT_RETURN;

    Node<T> *aux = tail;
    T value_removido = aux->getContent();

    if(Length() == 1)
    {
        head = NULL;
        tail = NULL;
    }
    else
    {
        aux->getPriorNode()->setNextNode(NULL);
        tail = aux->getPriorNode();
    }

    nElements--;
    delete aux;

    return value_removido;
}

template <typename T>
T MyList<T>::RemoveAt(int pos)
{
    if (IsEmpty() || pos < 0 || pos >= Length())
    {
        return DEFAULT_RETURN;
    }

    if(Length() == 1 || pos == 0)
        return RemoveFirst();
    else if(pos == Length() -1)
        return RemoveLast();

    Node<T> *aux = head;
    T value_removed;

    for (int i = 1; i <= pos; i++)
    {
        aux = aux->getNextNode();
    }

    if (aux == NULL){
        return DEFAULT_RETURN;
    }

    value_removed = aux->getContent();

    if(aux->getPriorNode() != NULL)
        aux->getPriorNode()->setNextNode(aux->getNextNode());

    if(aux->getNextNode() != NULL)
        aux->getNextNode()->setPriorNode(aux->getPriorNode());

    nElements--;
    delete aux;
    return value_removed;
}

template <typename T>
void MyList<T>::Clear()
{
    Node<T>* currentNode = this->head;

    while (currentNode)
    {
        Node<T>* nextNode = currentNode->getNextNode();
        delete currentNode;
        currentNode = nextNode;
        nElements--;
    }
}