#include "Node.h"

int Node::getContent(){
    return content;
}
void Node::setContent(int value){
    this->content = value;
}
Node* Node::getNextNode(){
    return NextNode;
}
void Node::setNextNode(Node *nextNode){
    this->NextNode = nextNode;
}
Node* Node::getPriorNode(){
    return PriorNode;
}
void Node::setPriorNode(Node *priorNode){
    this->PriorNode = priorNode;
}