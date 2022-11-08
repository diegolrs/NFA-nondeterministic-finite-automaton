#pragma once

#include <iostream>

class Node
{
    private:
        int content;
        Node *NextNode;
        Node *PriorNode;
    public:
        int getContent();
        void setContent(int value);
        Node *getNextNode();
        void setNextNode(Node *nextNode);
        Node *getPriorNode();
        void setPriorNode(Node *priorNode);
};