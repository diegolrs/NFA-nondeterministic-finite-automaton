#pragma once

template <typename T>
class Node
{
    private:
        T content;
        Node<T> *NextNode;
        Node<T> *PriorNode;
    public:
        T getContent();
        void setContent(T value);
        Node *getNextNode();
        void setNextNode(Node *nextNode);
        Node *getPriorNode();
        void setPriorNode(Node *priorNode);
};

template <typename T>
T Node<T>::getContent(){
    return content;
}

template <typename T>
void Node<T>::setContent(T value){
    this->content = value;
}

template <typename T>
Node<T>* Node<T>::getNextNode(){
    return NextNode;
}

template <typename T>
void Node<T>::setNextNode(Node<T> *nextNode){
    this->NextNode = nextNode;
}

template <typename T>
Node<T>* Node<T>::getPriorNode(){
    return PriorNode;
}

template <typename T>
void Node<T>::setPriorNode(Node<T> *priorNode){
    this->PriorNode = priorNode;
}