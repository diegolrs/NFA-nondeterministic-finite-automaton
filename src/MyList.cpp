#include "MyList.h"

MyList::MyList(){
    this->head = NULL;
    this->tail = NULL;
    this->nElements = 0;
}

bool MyList::IsEmpty(){
    return nElements == 0;
}

int MyList::Length(){
    return nElements;
}

int MyList::GetIndexOf(int value)
{
    if (IsEmpty())
    {
        return -1;
    }

    Node *aux = head;
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

int MyList::At(int pos)
{
    if (IsEmpty() || pos < 0 || pos >= Length())
    {
        return -1;
    }

    Node *aux = head;

    for (int i = 1; i <= pos; i++){
        aux = aux->getNextNode();
    }
    return aux->getContent(); 
}

bool MyList::Contains(int value){
    Node *aux = head;
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

void MyList::PushOnBeginning(int value){
    Node *newNode = new Node();

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

void MyList::Push(int value){

    if(IsEmpty())
    {
        PushOnBeginning(value);
        return;
    }

    Node *newNode = new Node();
    newNode->setContent(value);
    newNode->setNextNode(NULL);

    tail->setNextNode(newNode);

    newNode->setPriorNode(tail);
    tail->setNextNode(newNode);
    tail = newNode;

    nElements++;
}

int MyList::RemoveFirst(){
    if(IsEmpty())
        return -1;

    Node *aux = head;
    int value_removido = aux->getContent();

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

int MyList::RemoveLast(){
    if(IsEmpty())
        return -1;

    Node *aux = tail;
    int value_removido = aux->getContent();

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

int MyList::RemoveAt(int pos)
{
    if (IsEmpty() || pos < 0 || pos >= Length())
    {
        return -1;
    }

    if(Length() == 1 || pos == 0)
        return RemoveFirst();
    else if(pos == Length() -1)
        return RemoveLast();

    Node *aux = head;
    int value_removed;

    for (int i = 1; i <= pos; i++)
    {
        aux = aux->getNextNode();
    }

    if (aux == NULL){
        return -1;
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